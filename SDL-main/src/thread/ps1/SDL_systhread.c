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

#ifdef SDL_THREAD_PS1


/* Thread management routines for SDL */

#include "SDL_thread.h"
#include "../SDL_systhread.h"

static void *RunThread(void *data)
{
    SDL_Thread *t=(SDL_Thread *)data;
#ifdef MYDEBUG
    fprintf(stderr,"ps1 RunThread data=%08lx\n",(long)data); fflush(stderr);
#endif
    if(data) {
#ifdef MYDEBUG
      fprintf(stderr,"handle=%08lx userfunc=%08lx userdata=%08lx\n",(long)t->handle,(long)t->userfunc,(long)t->userdata); fflush(stderr);
#endif
      //YieldToThread(t->handle);
      SDL_RunThread((SDL_Thread *)data);
    }
    else {
      fprintf(stderr,"ps1 RunThread data is null!"); fflush(stderr);
    }
#ifdef MYDEBUG
    fprintf(stderr,"ps1 RunThread done\n"); fflush(stderr);
#endif
    return NULL;
}

#if defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON
static ThreadEntryUPP run_thread_upp;
#endif

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
int SDL_SYS_CreateThread(SDL_Thread *thread,
                         pfnSDL_CurrentBeginThread pfnBeginThread,
                         pfnSDL_CurrentEndThread pfnEndThread)
#else
int SDL_SYS_CreateThread(SDL_Thread *thread)
#endif /* SDL_PASSED_BEGINTHREAD_ENDTHREAD */
{
    //fprintf(stderr,"ps1 create thread %08lx\n",(long)thread); fflush(stderr);
    //fprintf(stderr,"ps1 create thread name=%s\n",thread->name); fflush(stderr);
    // style entry param stack opts &result &id
    // NOTE: We don't handle return code
    /*
#if defined(TARGET_API_MAC_CARBON) && TARGET_API_MAC_CARBON
    if (!run_thread_upp)
      run_thread_upp = NewThreadEntryUPP(RunThread);
    if (NewThread(kCooperativeThread, run_thread_upp, thread, 65535, 0, NULL, &thread->handle) != noErr) {
#else
    if (NewThread(kCooperativeThread, RunThread, thread, 65535, 0, NULL, &thread->handle) != noErr) {
#endif
      fprintf(stderr,"ps1 create thread failed!\n"); fflush(stderr);
      return -1;
    }
*/
#ifdef MYDEBUG
    fprintf(stderr,"ps1 create thread %08lx name=%s handle=%08lx\n",(long)thread,thread->name,(long)thread->handle); fflush(stderr);
#endif
    return 0;
}

void SDL_SYS_SetupThread(const char *name)
{
#ifdef MYDEBUG
    fprintf(stderr,"ps1 setup thread name=%s\n",name); fflush(stderr);
#endif
    // Safe to ignore?
    return;
}

SDL_threadID SDL_ThreadID(void)
{
    SDL_threadID ret=0;
    int id;
    //fprintf(stderr,"ps1 id thread\n"); fflush(stderr);
    /*Mac*///GetCurrentThread(&id);
    ret=id;
#ifdef MYDEBUG
    fprintf(stderr,"ps1 id thread id=%08lx\n",(long)id); fflush(stderr);
#endif
    return ret;
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
#ifdef MYDEBUG
    fprintf(stderr,"ps1 setpriority thread priority=%d\n",priority); fflush(stderr);
#endif
    return 0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
    //ThreadState tstate = kStoppedThreadState;
    //fprintf(stderr,"ps1 wait thread=%08lx\n",(long)thread); fflush(stderr);
#ifdef MYDEBUG
    fprintf(stderr,"ps1 wait thread %08lx handle=%08lx\n",(long)thread,(long)thread->handle); fflush(stderr);
#endif
/*
    while (GetThreadState(thread->handle, &tstate) == noErr &&
           tstate != kStoppedThreadState) {
        //YieldToAnyThread();
    }
    */
#ifdef MYDEBUG
    fprintf(stderr,"tstate=%d state=%08lx status=%08lx\n",tstate,(long)thread->state.value,(long)thread->status);
#endif
    /* Returning from the entry point makes Thread Manager dispose the
       native thread automatically. GetThreadState reports that transition;
       an explicit DisposeThread here would only target an expired ID. */
    //thread->handle = kNoThreadID;
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
#ifdef MYDEBUG
    fprintf(stderr,"ps1 detach thread=%08lx\n",(long)thread); fflush(stderr);
    fprintf(stderr,"ps1 detach thread handle=%08lx\n",(long)thread->handle); fflush(stderr);
#endif
    /* Thread Manager also disposes a detached native thread when its entry
       point returns; SDL_RunThread owns the detached SDL wrapper lifetime. */
    (void)thread;
    return;
}

#endif
/* vi: set ts=4 sw=4 expandtab: */
