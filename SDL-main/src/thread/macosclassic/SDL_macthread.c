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

/* Thread management routines for SDL */

#include "SDL_thread.h"
#include "../SDL_systhread.h"

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
int SDL_SYS_CreateThread(SDL_Thread *thread,
                         pfnSDL_CurrentBeginThread pfnBeginThread,
                         pfnSDL_CurrentEndThread pfnEndThread)
#else
int SDL_SYS_CreateThread(SDL_Thread *thread)
#endif /* SDL_PASSED_BEGINTHREAD_ENDTHREAD */
{
    fprintf(stderr,"generic create thread\n"); fflush(stderr);
    return SDL_SetError("Threads are not supported on this platform");
}

void SDL_SYS_SetupThread(const char *name)
{
    fprintf(stderr,"generic setup thread\n"); fflush(stderr);
    return;
}

SDL_threadID SDL_ThreadID(void)
{
    fprintf(stderr,"generic id thread\n"); fflush(stderr);
    return 0;
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    fprintf(stderr,"generic setpriority thread\n"); fflush(stderr);
    return 0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
    fprintf(stderr,"generic wait thread\n"); fflush(stderr);
    return;
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
    fprintf(stderr,"generic detach thread\n"); fflush(stderr);
    return;
}

/* vi: set ts=4 sw=4 expandtab: */
