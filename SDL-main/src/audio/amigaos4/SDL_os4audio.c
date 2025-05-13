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

#if SDL_AUDIO_DRIVER_AMIGAOS4

#include "SDL_audio.h"
#include "SDL_timer.h"
#include "../SDL_audio_c.h"
#include "../SDL_sysaudio.h"
#include "SDL_os4audio.h"

#include "../../main/amigaos4/SDL_os4debug.h"

#include <proto/exec.h>

/* The tag name used by the AmigaOS4 audio driver */
#define DRIVER_NAME "amigaos4"

static SDL_bool
OS4_OpenAhiDevice(OS4AudioData * os4data)
{
    if (os4data->deviceOpen) {
        dprintf("Device already open\n");
    }

    os4data->deviceOpen = SDL_FALSE;

    os4data->ahiReplyPort = (struct MsgPort *)IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE);

    if (os4data->ahiReplyPort) {

        /* create a iorequest for the device */
        os4data->ahiRequest[0] = (struct AHIRequest *)
            IExec->AllocSysObjectTags(
                ASOT_IOREQUEST,
                ASOIOR_ReplyPort, os4data->ahiReplyPort,
                ASOIOR_Size,      sizeof(struct AHIRequest),
                TAG_DONE);

        if (os4data->ahiRequest[0]) {

            if (!IExec->OpenDevice(AHINAME, 0, (struct IORequest *)os4data->ahiRequest[0], 0)) {

                dprintf("%s opened\n", AHINAME);

                /* Create a copy */
                os4data->ahiRequest[1] = (struct AHIRequest *)
                    IExec->AllocSysObjectTags(
                        ASOT_IOREQUEST,
                        ASOIOR_Duplicate, os4data->ahiRequest[0],
                        TAG_DONE);

                if (os4data->ahiRequest[1]) {

                    dprintf("IO requests created\n");

                    os4data->deviceOpen = SDL_TRUE;
                    os4data->currentBuffer = 0;
                    os4data->link = NULL;
                } else {
                    dprintf("Failed to duplicate IO request\n");
                }
            } else {
                dprintf("Failed to open %s\n", AHINAME);
            }
        } else {
            dprintf("Failed to create IO request\n");
        }
    } else {
        dprintf("Failed to create reply port\n");
    }

    dprintf("deviceOpen = %d\n", os4data->deviceOpen);
    return os4data->deviceOpen;
}

static void
OS4_CloseAhiDevice(OS4AudioData * os4data)
{
    if (os4data->ahiRequest[0]) {
        if (os4data->link) {
            dprintf("Aborting I/O...\n");

            IExec->AbortIO((struct IORequest *)os4data->link);
            IExec->WaitIO((struct IORequest *)os4data->link);
        }

        dprintf("Closing device\n");
        IExec->CloseDevice((struct IORequest *)os4data->ahiRequest[0]);

        dprintf("Freeing I/O requests\n");
        IExec->FreeSysObject(ASOT_IOREQUEST, os4data->ahiRequest[0]);
        os4data->ahiRequest[0] = NULL;

        if (os4data->ahiRequest[1]) {
            IExec->FreeSysObject(ASOT_IOREQUEST, os4data->ahiRequest[1]);
            os4data->ahiRequest[1] = NULL;
        }
    }

    if (os4data->ahiReplyPort) {
        dprintf("Deleting message port\n");
        IExec->FreeSysObject(ASOT_PORT, os4data->ahiReplyPort);
        os4data->ahiReplyPort = NULL;
    }

    os4data->deviceOpen = SDL_FALSE;

    dprintf("Device closed\n");
}

static SDL_bool
OS4_AudioAvailable(void)
{
    SDL_bool isAvailable = SDL_FALSE;

    OS4AudioData *tempData = SDL_calloc(1, sizeof(OS4AudioData));

    if (!tempData) {
        dprintf("Failed to allocate temp data\n");
    } else {
        isAvailable = OS4_OpenAhiDevice(tempData);

        OS4_CloseAhiDevice(tempData);

        SDL_free(tempData);
    }

    dprintf("AHI is %savailable\n", isAvailable ? "" : "not ");
    return isAvailable;
}

static int
OS4_SwapBuffer(int current)
{
    return (1 - current);
}

static void
OS4_FillCaptureRequest(struct AHIRequest * request, void * buffer, int length, int frequency, int type)
{
    request->ahir_Std.io_Message.mn_Node.ln_Pri = 60;
    request->ahir_Std.io_Data    = buffer,
    request->ahir_Std.io_Length  = length;
    request->ahir_Std.io_Command = CMD_READ;
    request->ahir_Volume         = 0x10000;
    request->ahir_Position       = 0x8000;
    request->ahir_Link           = NULL;
    request->ahir_Frequency      = frequency;
    request->ahir_Type           = type;
}

/* ---------------------------------------------- */
/* Audio driver exported functions implementation */
/* ---------------------------------------------- */
static void
OS4_CloseDevice(_THIS)
{
    OS4AudioData *os4data = _this->hidden;

    dprintf("Called\n");

    OS4_CloseAhiDevice(os4data);

    int i;
    for (i = 0; i < 2; i++) {
        if (os4data->audioBuffer[i]) {
            SDL_free(os4data->audioBuffer[i]);
            os4data->audioBuffer[i] = NULL;
        }
    }

    SDL_free(os4data);
}

static int
OS4_OpenDevice(_THIS, const char * devname)
{
    int result = 0;
    OS4AudioData *os4data = NULL;

    dprintf("devname %s\n", devname);

    _this->hidden = (OS4AudioData *) SDL_malloc(sizeof(OS4AudioData));

    if (!_this->hidden) {
        dprintf("Failed to allocate private data\n");
        return SDL_OutOfMemory();
    }

    SDL_memset(_this->hidden, 0, sizeof(OS4AudioData));
    os4data = _this->hidden;

    switch (_this->spec.format & 0xFF) {
        case 8:
            dprintf("8-bits requested, use AUDIO_S8\n");
            _this->spec.format = AUDIO_S8;
            break;
        case 16:
            dprintf("16 bits requested, use AUDIO_S16MSB\n");
            _this->spec.format = AUDIO_S16MSB;
            break;
        case 32:
            dprintf("32 bits requested, use AUDIO_S32MSB\n");
            _this->spec.format = AUDIO_S32MSB;
            break;
        default:
            dprintf("%u bits requested, fallback to AUDIO_S16MSB\n", _this->spec.format & 0xFF);
            _this->spec.format = AUDIO_S16MSB;
            break;
    }

    /* AHI supports 1, 2 or 8 channels sound: 3-7 channels may be converted to 7.1 format */
    if (_this->spec.channels < 1 || _this->spec.channels > 8) {
        dprintf("%u channels requested, fallback to stereo", _this->spec.channels);
        _this->spec.channels = 2;
    } else if (_this->spec.channels > 2) {
        dprintf("%u channels requested, use 8 channel AUDIO_S32MSB\n", _this->spec.channels);
        _this->spec.channels = 8;
        _this->spec.format = AUDIO_S32MSB;
    }

    dprintf("SDL audio format = 0x%x\n", _this->spec.format);
    dprintf("Buffer size = %u\n", _this->spec.size);
    dprintf("Channels = %u\n", _this->spec.channels);

    /* Calculate the final parameters for this audio specification */
    SDL_CalculateAudioSpec(&_this->spec);

    os4data->audioBufferSize = _this->spec.size;
    os4data->audioBuffer[0] = (Uint8 *) SDL_malloc(_this->spec.size);
    os4data->audioBuffer[1] = (Uint8 *) SDL_malloc(_this->spec.size);

    if (os4data->audioBuffer[0] == NULL || os4data->audioBuffer[1] == NULL) {
        OS4_CloseDevice(_this);
        dprintf("No memory for audio buffer\n");
        SDL_SetError("No memory for audio buffer");
        return -1;
    }

    SDL_memset(os4data->audioBuffer[0], _this->spec.silence, _this->spec.size);
    SDL_memset(os4data->audioBuffer[1], _this->spec.silence, _this->spec.size);

    /* Decide AHI format */
    switch(_this->spec.format) {
        case AUDIO_S8:
            os4data->ahiType = (_this->spec.channels < 2) ? AHIST_M8S : AHIST_S8S;
            break;

        case AUDIO_S16MSB:
            os4data->ahiType = (_this->spec.channels < 2) ? AHIST_M16S : AHIST_S16S;
            break;

        case AUDIO_S32MSB:
            switch (_this->spec.channels) {
                case 1:
                    os4data->ahiType = AHIST_M32S;
                    break;
                case 2:
                    os4data->ahiType = AHIST_S32S;
                    break;
                case 8:
                    os4data->ahiType = AHIST_L7_1;
                    break;
                default:
                    dprintf("Unsupported channel count %u for 32-bit mode\n", _this->spec.channels);
                    os4data->ahiType = AHIST_M32S;
                    break;
            }
            break;

        default:
            dprintf("Unsupported audio format 0x%X requested\n", _this->spec.format);
            os4data->ahiType = (_this->spec.channels < 2) ? AHIST_M16S : AHIST_S16S;
            break;
    }

    dprintf("AHI format 0x%lX\n", os4data->ahiType);

    return result;
}

static void
OS4_ThreadInit(_THIS)
{
    OS4AudioData *os4data = _this->hidden;

    dprintf("Called\n");

    /* Signal must be opened in the task which is using it (player) */
    if (!OS4_OpenAhiDevice(os4data)) {
        // FIXME: this is bad. We have failed and SDL core doesn't know about that.
        dprintf("Failed to open AHI\n");
    }

    /* This will cause a lot of problems.. and should be removed.

    One possibility: create a configuration GUI or ENV variable that allows
    user to select priority, if there is no silver bullet value */
    IExec->SetTaskPri(IExec->FindTask(NULL), 5);
}

static void
OS4_WaitDevice(_THIS)
{
    /* Dummy - OS4_PlayDevice handles the waiting */
    //dprintf("Called\n");
}

#define SDL_FC  2
#define SDL_LFE 3
#define SDL_BL  4
#define SDL_BR  5
#define SDL_SL  6
#define SDL_SR  7

#define AHI_BL  2
#define AHI_BR  3
#define AHI_SL  4
#define AHI_SR  5
#define AHI_FC  6
#define AHI_LFE 7

static void
OS4_RemapSurround(Sint32* buffer, int samples)
{
    int i;
    for (i = 0; i < samples; i++) {
        Sint32 bl, br, sl, sr, fc, lfe;

        bl = buffer[SDL_BL];
        br = buffer[SDL_BR];
        sl = buffer[SDL_SL];
        sr = buffer[SDL_SR];
        fc = buffer[SDL_FC];
        lfe = buffer[SDL_LFE];

        buffer[AHI_BL] = bl;
        buffer[AHI_BR] = br;
        buffer[AHI_SL] = sl;
        buffer[AHI_SR] = sr;
        buffer[AHI_FC] = fc;
        buffer[AHI_LFE] = lfe;

        buffer += 8;
    }
}

static void
OS4_PlayDevice(_THIS)
{
    struct AHIRequest  *ahiRequest;
    SDL_AudioSpec      *spec    = &_this->spec;
    OS4AudioData       *os4data = _this->hidden;
    int                 current = os4data->currentBuffer;

    //dprintf("Called\n");

    if (!os4data->deviceOpen) {
        dprintf("Device is not open\n");
        return;
    }

    ahiRequest = os4data->ahiRequest[current];

    ahiRequest->ahir_Std.io_Message.mn_Node.ln_Pri = 60;
    ahiRequest->ahir_Std.io_Data    = os4data->audioBuffer[current];
    ahiRequest->ahir_Std.io_Length  = os4data->audioBufferSize;
    ahiRequest->ahir_Std.io_Offset  = 0;
    ahiRequest->ahir_Std.io_Command = CMD_WRITE;
    ahiRequest->ahir_Volume         = 0x10000;
    ahiRequest->ahir_Position       = 0x8000;
    ahiRequest->ahir_Link           = os4data->link;
    ahiRequest->ahir_Frequency      = spec->freq;
    ahiRequest->ahir_Type           = os4data->ahiType;

    /* Let SDL handle possible conversions between formats, channels etc., but
       because order of 7.1 channels is different (AHI <-> SDL), remap it here */

    if (spec->channels == 8) {
        OS4_RemapSurround((Sint32 *)os4data->audioBuffer[current], spec->samples);
    }

    IExec->SendIO((struct IORequest *)ahiRequest);

    if (os4data->link) {
        IExec->WaitIO((struct IORequest *)os4data->link);
    }

    os4data->link = ahiRequest;
    os4data->currentBuffer = OS4_SwapBuffer(current);
}

static Uint8 *
OS4_GetDeviceBuf(_THIS)
{
    //dprintf("Called\n");

    return _this->hidden->audioBuffer[_this->hidden->currentBuffer];
}

#ifndef MIN
#define MIN(a, b) (a) < (b) ? (a) : (b)
#endif

#define RESTART_CAPTURE_THRESHOLD 500

static int
OS4_CaptureFromDevice(_THIS, void * buffer, int buflen)
{
    struct AHIRequest  *request;
    SDL_AudioSpec      *spec    = &_this->spec;
    OS4AudioData       *os4data = _this->hidden;
    Uint32 now;
    size_t copyLen;
    void *completedBuffer;
    int current;

    //dprintf("Called %p, %d\n", buffer, buflen);

    if (!os4data->deviceOpen) {
        dprintf("Device is not open\n");
        return 0;
    }

    now = SDL_GetTicks();
    current = os4data->currentBuffer;
    request = os4data->ahiRequest[0];

    if (os4data->lastCaptureTicks == 0 || (now - os4data->lastCaptureTicks) > RESTART_CAPTURE_THRESHOLD) {
        if (os4data->link) {
            IExec->WaitIO((struct IORequest *)os4data->link);
        }

        /* Assume that we have to (re)start recording */
        OS4_FillCaptureRequest(
            request,
            os4data->audioBuffer[current],
            os4data->audioBufferSize,
            spec->freq,
            os4data->ahiType);

        request->ahir_Std.io_Offset = 0;

        dprintf("Start recording\n");

        IExec->DoIO((struct IORequest *)request);
        os4data->link = NULL;

        current = OS4_SwapBuffer(current);
    } else {
        /* Wait for the previous request completion */
        if (os4data->link) {
            IExec->WaitIO((struct IORequest *)os4data->link);
        }
    }

    OS4_FillCaptureRequest(
        request,
        os4data->audioBuffer[current],
        os4data->audioBufferSize,
        spec->freq,
        os4data->ahiType);

    IExec->SendIO((struct IORequest *)request);
    os4data->link = request;

    current = OS4_SwapBuffer(current);

    completedBuffer = os4data->audioBuffer[current];

    copyLen = MIN(buflen, os4data->audioBufferSize);

    SDL_memcpy(buffer, completedBuffer, copyLen);

    os4data->lastCaptureTicks = now;
    os4data->currentBuffer = current;

    //dprintf("%d bytes copied\n", copyLen);

    return copyLen;
}

/* ------------------------------------------ */
/* Audio driver init functions implementation */
/* ------------------------------------------ */
static SDL_bool
OS4_Init(SDL_AudioDriverImpl * impl)
{
    if (!OS4_AudioAvailable()) {
        SDL_SetError("Failed to open AHI device");
        return SDL_FALSE;
    }

    // impl->DetectDevices?
    impl->OpenDevice = OS4_OpenDevice;
    impl->ThreadInit = OS4_ThreadInit;
    impl->WaitDevice = OS4_WaitDevice;
    impl->PlayDevice = OS4_PlayDevice;
    // impl->GetPendingBytes?
    impl->GetDeviceBuf = OS4_GetDeviceBuf;
    impl->CaptureFromDevice = OS4_CaptureFromDevice;
    // impl->FlushCapture
    // impl->PrepareToClose()
    impl->CloseDevice = OS4_CloseDevice;
    // impl->Lock+UnlockDevice
    // impl->FreeDeviceHandle
    // impl->Deinitialize

    impl->HasCaptureSupport = SDL_TRUE;
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
    impl->OnlyHasDefaultCaptureDevice = SDL_TRUE;

    return SDL_TRUE;
}

AudioBootStrap AMIGAOS4AUDIO_bootstrap = {
   DRIVER_NAME, "AmigaOS4 AHI audio", OS4_Init, SDL_FALSE
};
#endif
