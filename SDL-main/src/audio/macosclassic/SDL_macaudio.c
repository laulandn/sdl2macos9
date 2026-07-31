/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "../../SDL_internal.h"

#ifdef SDL_AUDIO_DRIVER_MACOSCLASSIC

/* Output audio to Mac */

#include <Gestalt.h>
#include <Sound.h>
#include <DriverServices.h>

#include "SDL_audio.h"
#include "../SDL_audio_c.h"
#include "SDL_macaudio.h"

#if !defined(NewSndDoubleBackUPP)
#define NewSndDoubleBackUPP NewSndDoubleBackProc
#endif
#if !defined(DisposeSndDoubleBackUPP)
#define DisposeSndDoubleBackUPP(x) ((void)0)
#endif

static UInt32 MACOSAUDIO_AtomicRead32(volatile UInt32 *value)
{
    return BitAndAtomic(0xFFFFFFFFU, (UInt32 *)value);
}

static void MACOSAUDIO_FillBuffer(SDL_AudioDevice *device, int index);

static void MACOSAUDIO_LockDevice(_THIS)
{
    struct SDL_PrivateAudioData *hidden = this->hidden;

    if (!hidden) {
        return;
    }

    /* The doubleback runs at interrupt time and cannot take an SDL mutex.
       Inhibit it before waiting so it can always return immediately. */
    IncrementAtomic((SInt32 *)&hidden->callback_lock_count);
    while (MACOSAUDIO_AtomicRead32(
               (volatile UInt32 *)&hidden->callback_active)) {
        /* The interrupt callback is bounded and clears this before returning. */
    }
    SDL_LockMutex(hidden->mixer_lock);
}

static void MACOSAUDIO_UnlockDevice(_THIS)
{
    struct SDL_PrivateAudioData *hidden = this->hidden;

    if (!hidden) {
        return;
    }

    SDL_UnlockMutex(hidden->mixer_lock);
    DecrementAtomic((SInt32 *)&hidden->callback_lock_count);
}

static void MACOSAUDIO_PublishBuffer(SDL_AudioDevice *device,
                                     SndDoubleBufferPtr buffer)
{
    buffer->dbNumFrames = device->spec.samples;
    /* Publish readiness last. Sound Manager clears this bit when the buffer
       is exhausted and may start consuming it as soon as it is restored. */
    BitOrAtomic(dbBufferReady, (UInt32 *)&buffer->dbFlags);
}

static pascal void MACOSAUDIO_DoubleBack(SndChannelPtr channel,
                                         SndDoubleBufferPtr buffer)
{
    SDL_AudioDevice *device = (SDL_AudioDevice *)buffer->dbUserInfo[0];
    struct SDL_PrivateAudioData *hidden;
    int index;
    (void)channel;

    if (!device || !(hidden = device->hidden) || hidden->shutting_down ||
        MACOSAUDIO_AtomicRead32((volatile UInt32 *)&device->shutdown.value)) {
        return;
    }

    if (buffer == hidden->buffers[0]) {
        index = 0;
    } else if (buffer == hidden->buffers[1]) {
        index = 1;
    } else {
        return;
    }

    /* Sound Manager requires the exhausted buffer to be made ready from this
       callback. Claim the mixer state before inspecting SDL's stream or queue;
       API-side LockDevice calls inhibit new claims and wait for this bounded
       refill to finish. This keeps audio independent of the video event pump. */
    if (!MACOSAUDIO_AtomicRead32((volatile UInt32 *)&device->enabled.value) ||
        MACOSAUDIO_AtomicRead32((volatile UInt32 *)&device->paused.value) ||
        MACOSAUDIO_AtomicRead32((volatile UInt32 *)&hidden->callback_lock_count) ||
        !CompareAndSwap(0, 1, (UInt32 *)&hidden->callback_active)) {
        SDL_memset(buffer->dbSoundData, device->spec.silence,
                   device->spec.size);
        MACOSAUDIO_PublishBuffer(device, buffer);
        return;
    }

    if (MACOSAUDIO_AtomicRead32(
            (volatile UInt32 *)&hidden->callback_lock_count)) {
        SDL_memset(buffer->dbSoundData, device->spec.silence,
                   device->spec.size);
        MACOSAUDIO_PublishBuffer(device, buffer);
    } else {
        MACOSAUDIO_FillBuffer(device, index);
    }
    DecrementAtomic((SInt32 *)&hidden->callback_active);
}

static SDL_bool MACOSAUDIO_Available(void)
{
    NumVersion version = SndSoundManagerVersion();
    long attributes = 0;

    /* On m68k this seems to always return zero! */
#ifdef powerc
    if (version.majorRev < 3) {
#ifdef MAC_DEBUG
        fprintf(stderr,"sound manager version 3 not avail, only %d!\n",version.majorRev); fflush(stderr);
#endif
        return SDL_FALSE;
    }
#endif

    if (Gestalt(gestaltSoundAttr, &attributes) != noErr) {
        return SDL_FALSE;
    }
    return (attributes & (1L << gestaltSndPlayDoubleBuffer)) != 0;
}

static void MACOSAUDIO_FreeDeviceData(_THIS)
{
    struct SDL_PrivateAudioData *hidden = this->hidden;
    int i;

    if (!hidden) {
        return;
    }
    hidden->shutting_down = SDL_TRUE;
    if (hidden->channel) {
        SndDisposeChannel(hidden->channel, true);
        hidden->channel = NULL;
    }
    if (hidden->callback) {
        DisposeSndDoubleBackUPP(hidden->callback);
        hidden->callback = NULL;
    }
    for (i = 0; i < 2; ++i) {
        SDL_free(hidden->buffers[i]);
        hidden->buffers[i] = NULL;
    }
    if (hidden->mixer_lock) {
        SDL_DestroyMutex(hidden->mixer_lock);
        hidden->mixer_lock = NULL;
    }
    hidden->callback_lock_count = 0;
    hidden->callback_active = 0;
}

static int MACOSAUDIO_OpenDevice(_THIS, const char *devname)
{
    struct SDL_PrivateAudioData *hidden;
    SDL_AudioFormat format;
    long init_options;
    int sample_bits;
    int i;
    OSErr err;
    (void)devname;

    if (this->iscapture) {
        return SDL_SetError("Classic Sound Manager capture is not supported");
    }
    if (!MACOSAUDIO_Available()) {
        return SDL_SetError("Sound Manager 3 double-buffered playback is unavailable");
    }

    for (format = SDL_FirstAudioFormat(this->spec.format); format;
         format = SDL_NextAudioFormat()) {
        if (format == AUDIO_U8 || format == AUDIO_S16MSB) {
            break;
        }
    }
    if (!format) {
        /* Didn't find a compatible format :( */
        return SDL_SetError("Sound Manager supports only U8 and native-endian S16 audio");
    }
    this->spec.format = format;
    if (this->spec.channels < 1) {
        this->spec.channels = 1;
    } else if (this->spec.channels > 2) {
        this->spec.channels = 2;
    }
    SDL_CalculateAudioSpec(&this->spec);

    hidden = (struct SDL_PrivateAudioData *)SDL_calloc(1, sizeof(*hidden));
    if (!hidden) {
        return SDL_OutOfMemory();
    }
    this->hidden = hidden;
    hidden->mixer_lock = SDL_CreateMutex();
    if (!hidden->mixer_lock) {
        MACOSAUDIO_FreeDeviceData(this);
        SDL_free(hidden);
        this->hidden = NULL;
        return SDL_SetError("Unable to create Sound Manager mixer lock");
    }
    hidden->callback = NewSndDoubleBackUPP(MACOSAUDIO_DoubleBack);
    if (!hidden->callback) {
        MACOSAUDIO_FreeDeviceData(this);
        SDL_free(hidden);
        this->hidden = NULL;
        return SDL_SetError("Unable to create Sound Manager callback");
    }

    sample_bits = SDL_AUDIO_BITSIZE(this->spec.format);
    SDL_zero(hidden->header);
    hidden->header.dbhNumChannels = this->spec.channels;
    hidden->header.dbhSampleSize = sample_bits;
    hidden->header.dbhCompressionID = 0;
    hidden->header.dbhPacketSize = 0;
    hidden->header.dbhSampleRate = ((UnsignedFixed)this->spec.freq) << 16;
    hidden->header.dbhDoubleBack = hidden->callback;
    hidden->header.dbhFormat = 0;

    for (i = 0; i < 2; ++i) {
        hidden->buffers[i] = (SndDoubleBufferPtr)SDL_calloc(
            1, sizeof(SndDoubleBuffer) + this->spec.size);
        if (!hidden->buffers[i]) {
            MACOSAUDIO_FreeDeviceData(this);
            SDL_free(hidden);
            this->hidden = NULL;
            return SDL_OutOfMemory();
        }
        hidden->buffers[i]->dbNumFrames = this->spec.samples;
        SDL_memset(hidden->buffers[i]->dbSoundData, this->spec.silence,
                   this->spec.size);
        hidden->buffers[i]->dbFlags = dbBufferReady;
        hidden->buffers[i]->dbUserInfo[0] = (long)this;
        hidden->header.dbhBufferPtr[i] = hidden->buffers[i];
    }

    init_options = (this->spec.channels == 2) ? initStereo : initMono;
    err = SndNewChannel(&hidden->channel, sampledSynth, init_options, NULL);
    if (err != noErr) {
        MACOSAUDIO_FreeDeviceData(this);
        SDL_free(hidden);
        this->hidden = NULL;
        return SDL_SetError("SndNewChannel failed (%d)", (int)err);
    }

    err = SndPlayDoubleBuffer(hidden->channel,
                              (SndDoubleBufferHeaderPtr)&hidden->header);
    if (err != noErr) {
        MACOSAUDIO_FreeDeviceData(this);
        SDL_free(hidden);
        this->hidden = NULL;
        return SDL_SetError("SndPlayDoubleBuffer failed (%d)", (int)err);
    }
    return 0;
}

static void MACOSAUDIO_FillBuffer(SDL_AudioDevice *device, int index)
{
    struct SDL_PrivateAudioData *hidden = device->hidden;
    SndDoubleBufferPtr buffer = hidden->buffers[index];
    Uint8 *stream = (Uint8 *)buffer->dbSoundData;
    SDL_AudioCallback callback = device->callbackspec.callback;
    const int stream_len = device->callbackspec.size;

    if (!buffer || hidden->shutting_down) {
        return;
    }

    if (!SDL_AtomicGet(&device->enabled) || SDL_AtomicGet(&device->paused)) {
        if (device->stream) {
            SDL_AudioStreamClear(device->stream);
        }
        SDL_memset(stream, device->spec.silence, device->spec.size);
    } else if (!device->stream) {
        callback(device->callbackspec.userdata, stream, device->spec.size);
    } else {
        int got;
        while (SDL_AudioStreamAvailable(device->stream) < (int)device->spec.size) {
            callback(device->callbackspec.userdata, device->work_buffer, stream_len);
            if (SDL_AudioStreamPut(device->stream, device->work_buffer, stream_len) == -1) {
                SDL_AudioStreamClear(device->stream);
                SDL_AtomicSet(&device->enabled, 0);
                break;
            }
        }
        got = SDL_AudioStreamGet(device->stream, stream, device->spec.size);
        if (got != (int)device->spec.size) {
            SDL_memset(stream, device->spec.silence, device->spec.size);
        }
    }
    MACOSAUDIO_PublishBuffer(device, buffer);
}

static void MACOSAUDIO_CloseDevice(_THIS)
{
    struct SDL_PrivateAudioData *hidden = this->hidden;
    MACOSAUDIO_FreeDeviceData(this);
    SDL_free(hidden);
    this->hidden = NULL;
}

static SDL_bool MACOSAUDIO_Init(SDL_AudioDriverImpl *impl)
{
    if (!MACOSAUDIO_Available()) {
#ifdef MAC_DEBUG
        fprintf(stderr,"MACOSAUDIO_Available is false!\n"); fflush(stderr);
#endif
        return SDL_FALSE;
    }

    /* Set the function pointers */
    impl->OpenDevice = MACOSAUDIO_OpenDevice;
    impl->CloseDevice = MACOSAUDIO_CloseDevice;
    impl->LockDevice = MACOSAUDIO_LockDevice;
    impl->UnlockDevice = MACOSAUDIO_UnlockDevice;

    /* and the capabilities */
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
    impl->HasCaptureSupport = SDL_FALSE;
    impl->ProvidesOwnCallbackThread = SDL_TRUE;
    return SDL_TRUE; /* this audio target is available. */
}

AudioBootStrap MACOSAUDIO_bootstrap = {
    "sndmgr", "Classic Mac OS Sound Manager", MACOSAUDIO_Init, SDL_FALSE
};

/* Pause (block) all non already paused audio devices by taking their mixer lock */
void MACOSAUDIO_PauseDevices(void) {}

/* Resume (unblock) all non already paused audio devices by releasing their mixer lock */
void MACOSAUDIO_ResumeDevices(void) {}

#else
void MACOSAUDIO_ResumeDevices(void) {}
void MACOSAUDIO_PauseDevices(void) {}

#endif /* SDL_AUDIO_DRIVER_MACOSCLASSIC */

/* vi: set ts=4 sw=4 expandtab: */
