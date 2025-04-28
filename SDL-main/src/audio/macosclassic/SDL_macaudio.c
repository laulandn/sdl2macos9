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

#include "SDL_audio.h"
#include "../SDL_audio_c.h"
#include "SDL_macaudio.h"

//#include "../../core/android/SDL_android.h"

//#include <android/log.h>

static SDL_AudioDevice *audioDevice = NULL;
static SDL_AudioDevice *captureDevice = NULL;


int Mac_OpenAudioDevice(int iscapture, int dev_id, SDL_AudioSpec *spec)
{
  fprintf(stderr,"macosclassic Mac_OpenAudioDevice\n"); fflush(stderr);
  if(spec) {
    fprintf(stderr,"macosclassic Mac_OpenAudioDevice passed spec\n"); fflush(stderr);
  }
  else {
    fprintf(stderr,"macosclassic Mac_OpenAudioDevice NULL spec\n"); fflush(stderr);
  }
  /* TODO */
  return 0;
}


void Mac_CloseAudioDevice(int iscapture)
{
  fprintf(stderr,"macosclassic Mac_CloseAudioDevice\n"); fflush(stderr);
  /* TODO */
}


void MACOSAUDIO_DetectDevices()
{
  fprintf(stderr,"macosclassic MACOSAUDIO_DetectDevices\n"); fflush(stderr);
  /* TODO */
}


static int MACOSAUDIO_OpenDevice(_THIS, const char *devname)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_OpenDevice\n"); fflush(stderr);
    SDL_AudioFormat test_format;
    SDL_bool iscapture = this->iscapture;

    SDL_assert((captureDevice == NULL) || !iscapture);
    SDL_assert((audioDevice == NULL) || iscapture);

    if (iscapture) {
        captureDevice = this;
    } else {
        audioDevice = this;
    }

    this->hidden = (struct SDL_PrivateAudioData *)SDL_calloc(1, sizeof(*this->hidden));
    if (!this->hidden) {
        return SDL_OutOfMemory();
    }

    for (test_format = SDL_FirstAudioFormat(this->spec.format); test_format; test_format = SDL_NextAudioFormat()) {
        if ((test_format == AUDIO_U8) ||
            (test_format == AUDIO_S16) ||
            (test_format == AUDIO_F32)) {
            this->spec.format = test_format;
            break;
        }
    }

    if (!test_format) {
        /* Didn't find a compatible format :( */
        return SDL_SetError("%s: Unsupported audio format", "macos");
    }

    {
        int audio_device_id = 0;
        if (devname) {
            audio_device_id = SDL_atoi(devname);
        }
        if (Mac_OpenAudioDevice(iscapture, audio_device_id, &this->spec) < 0) {
            return -1;
        }
    }

    SDL_CalculateAudioSpec(&this->spec);

    return 0;
}


static void MACOSAUDIO_PlayDevice(_THIS)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_PlayDevice\n"); fflush(stderr);
  /* TODO */
}


static Uint8 *MACOSAUDIO_GetDeviceBuf(_THIS)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_GetDeviceBuf\n"); fflush(stderr);
  /* TODO */
  return NULL;
}


static int MACOSAUDIO_CaptureFromDevice(_THIS, void *buffer, int buflen)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_CaptureFromDevice\n"); fflush(stderr);
  if(buffer) {
    fprintf(stderr,"macosclassic Mac_CaptureAudioBuffer passed buffer\n"); fflush(stderr);
  }
  else {
    fprintf(stderr,"macosclassic Mac_CaptureAudioBuffer NULL buffer\n"); fflush(stderr);
  }
  /* TODO */
  return 0;
}


static void MACOSAUDIO_FlushCapture(_THIS)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_FlushCapture\n"); fflush(stderr);
}


static void MACOSAUDIO_CloseDevice(_THIS)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_CloseDevice\n"); fflush(stderr);
    /* At this point SDL_CloseAudioDevice via close_audio_device took care of terminating the audio thread
       so it's safe to terminate the Java side buffer and AudioTrack
     */
    Mac_CloseAudioDevice(this->iscapture);
    if (this->iscapture) {
        SDL_assert(captureDevice == this);
        captureDevice = NULL;
    } else {
        SDL_assert(audioDevice == this);
        audioDevice = NULL;
    }
    SDL_free(this->hidden);
}


static SDL_bool MACOSAUDIO_Init(SDL_AudioDriverImpl *impl)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_Init\n"); fflush(stderr);
    /* Set the function pointers */
    impl->DetectDevices = MACOSAUDIO_DetectDevices;
    impl->OpenDevice = MACOSAUDIO_OpenDevice;
    impl->PlayDevice = MACOSAUDIO_PlayDevice;
    impl->GetDeviceBuf = MACOSAUDIO_GetDeviceBuf;
    impl->CloseDevice = MACOSAUDIO_CloseDevice;
    impl->CaptureFromDevice = MACOSAUDIO_CaptureFromDevice;
    impl->FlushCapture = MACOSAUDIO_FlushCapture;
    impl->AllowsArbitraryDeviceNames = SDL_TRUE;

    /* and the capabilities */
    impl->HasCaptureSupport = SDL_FALSE;
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
    impl->OnlyHasDefaultCaptureDevice = SDL_TRUE;

    return SDL_TRUE; /* this audio target is available. */
}


AudioBootStrap MACOSAUDIO_bootstrap = {
    "macosclassic", "Mac audio driver", MACOSAUDIO_Init, SDL_FALSE
};


/* Pause (block) all non already paused audio devices by taking their mixer lock */
void MACOSAUDIO_PauseDevices(void)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_PauseDevices\n"); fflush(stderr);
    /* TODO: Handle multiple devices? */
    if (audioDevice && audioDevice->hidden) {
        SDL_LockMutex(audioDevice->mixer_lock);
    }

    if (captureDevice && captureDevice->hidden) {
        SDL_LockMutex(captureDevice->mixer_lock);
    }
}


/* Resume (unblock) all non already paused audio devices by releasing their mixer lock */
void MACOSAUDIO_ResumeDevices(void)
{
  fprintf(stderr,"macosclassic MACOSAUDIO_ResumeDevices\n"); fflush(stderr);
    /* TODO: Handle multiple devices? */
    if (audioDevice && audioDevice->hidden) {
        SDL_UnlockMutex(audioDevice->mixer_lock);
    }

    if (captureDevice && captureDevice->hidden) {
        SDL_UnlockMutex(captureDevice->mixer_lock);
    }
}


#else

void MACOSAUDIO_ResumeDevices(void) {}
void MACOSAUDIO_PauseDevices(void) {}

#endif /* SDL_AUDIO_DRIVER_MACOSCLASSIC */

/* vi: set ts=4 sw=4 expandtab: */
