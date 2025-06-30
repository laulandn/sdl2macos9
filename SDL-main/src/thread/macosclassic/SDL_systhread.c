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

#ifdef SDL_THREAD_MACOSCLASSIC

//#define MYDEBUG 1

/* Thread management routines for SDL */

#include "SDL_thread.h"
#include "../SDL_systhread.h"

static void *RunThread(void *data)
{
    SDL_Thread *t=(SDL_Thread *)data;
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic RunThread data=%08lx\n",(long)data); fflush(stderr);
#endif
    if(data) {
#ifdef MYDEBUG
      fprintf(stderr,"handle=%08lx userfunc=%08lx userdata=%08lx\n",(long)t->handle,(long)t->userfunc,(long)t->userdata); fflush(stderr);
#endif
      YieldToThread(t->handle);
      SDL_RunThread((SDL_Thread *)data);
    }
    else {
      fprintf(stderr,"macosclassic RunThread data is null!"); fflush(stderr);
    }
    return NULL;
}

#ifdef SDL_PASSED_BEGINTHREAD_ENDTHREAD
int SDL_SYS_CreateThread(SDL_Thread *thread,
                         pfnSDL_CurrentBeginThread pfnBeginThread,
                         pfnSDL_CurrentEndThread pfnEndThread)
#else
int SDL_SYS_CreateThread(SDL_Thread *thread)
#endif /* SDL_PASSED_BEGINTHREAD_ENDTHREAD */
{
    //fprintf(stderr,"macosclassic create thread %08lx\n",(long)thread); fflush(stderr);
    //fprintf(stderr,"macosclassic create thread name=%s\n",thread->name); fflush(stderr);
    // style entry param stack opt res id
    if (NewThread(kCooperativeThread, /*thread->userfunc*/RunThread, thread, 0, 0, NULL, &thread->handle) != noErr) {
      fprintf(stderr,"macosclassic create thread failed!\n"); fflush(stderr);
      return -1;
    }
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic create thread %08lx name=%s handle=%08lx\n",(long)thread,thread->name,(long)thread->handle); fflush(stderr);
#endif
    return 0;
}

void SDL_SYS_SetupThread(const char *name)
{
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic setup thread name=%s\n",name); fflush(stderr);
#endif
    // Safe to ignore?
    return;
}

SDL_threadID SDL_ThreadID(void)
{
    SDL_threadID ret=0;
    ThreadID id;
    //fprintf(stderr,"macosclassic id thread\n"); fflush(stderr);
    /*Mac*/GetCurrentThread(&id);
    ret=id;
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic id thread id=%08lx\n",(long)id); fflush(stderr);
#endif
    return ret;
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic setpriority thread priority=%d\n",priority); fflush(stderr);
#endif
    return 0;
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
    int wait=true; 
    ThreadState tstate;
    //fprintf(stderr,"macosclassic wait thread=%08lx\n",(long)thread); fflush(stderr);
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic wait thread %08lx handle=%08lx\n",(long)thread,(long)thread->handle); fflush(stderr);
#endif
    GetThreadState(thread->handle,&tstate);
#ifdef MYDEBUG
    fprintf(stderr,"tstate=%d state=%08lx status=%08lx\n",tstate,(long)thread->state.value,(long)thread->status);
#endif
    if(thread->state.value) { 
#ifdef MYDEBUG
      fprintf(stderr,"NOT WAITING!\n"); 
#endif
      wait=false; 
    }
    else { 
#ifdef MYDEBUG
      fprintf(stderr,"WILL WAIT!\n"); 
#endif
    }
    /*if(tstate) { fprintf(stderr,"NOT WAITING2!\n"); wait=false; }
    else { fprintf(stderr,"WOULD WAIT2!\n"); }*/
    // TODO: Actually wait for the thread to complete, while yielding, here...
    if(wait) for(int i=0;i<1000;i++) { YieldToAnyThread();}
    return;
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
#ifdef MYDEBUG
    fprintf(stderr,"macosclassic detach thread=%08lx\n",(long)thread); fflush(stderr);
    fprintf(stderr,"macosclassic detach thread handle=%08lx\n",(long)thread->handle); fflush(stderr);
#endif
    return;
}

#endif
/* vi: set ts=4 sw=4 expandtab: */
