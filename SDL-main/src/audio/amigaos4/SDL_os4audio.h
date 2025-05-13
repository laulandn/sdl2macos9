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
#ifndef SDL_os4audio_h_
#define SDL_os4audio_h_

#include <exec/types.h>
#include <exec/ports.h>
#include <devices/ahi.h>

#include "SDL_types.h"

#include "../SDL_sysaudio.h"

/* Hidden "this" pointer for the video functions */
#define _THIS   SDL_AudioDevice *_this

struct SDL_PrivateAudioData
{
    struct MsgPort       *ahiReplyPort;
    struct AHIRequest    *ahiRequest[2];
    Uint32                ahiType;
    int                   currentBuffer; // buffer number to fill
    struct AHIRequest    *link;          // point to previous I/O request sent (both recording and playing)

    SDL_bool              deviceOpen;
    Uint32                audioBufferSize;
    Uint8                *audioBuffer[2];

    Uint32                lastCaptureTicks;
};

typedef struct SDL_PrivateAudioData OS4AudioData;

#endif
