/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997-2006 Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    Sam Lantinga
    slouken@libsdl.org
*/
#include "SDL_config.h"

//#define MYDEBUG 1

#ifdef SDL_THREAD_AMIGAOS3

/* Amiga thread management routines for SDL */

#include "SDL_mutex.h"
#include "SDL_thread.h"
#include "../SDL_thread_c.h"
#include "../SDL_systhread.h"
//#include "mydebug.h"
#include <exec/exec.h>
#include <dos/dos.h>
#include <dos/dostags.h>
#include <proto/exec.h>
#include <proto/dos.h>


#define WHERE stderr


// NOTE: Not fully using this
typedef struct {
	int (*func)(void *);
	void *data;
	SDL_Thread *info;
	struct Task *wait;
} thread_args;


SDL_threadID theMainThread=0;


#ifndef MORPHOS

#if defined(__SASC) && !defined(__PPC__) 
__saveds __asm Uint32 RunThread(register __a0 char *args )
#elif defined(__PPC__)
Uint32 RunThread(char *args)
#else
Uint32 /*__saveds*/ RunThread(char *args __asm("a0") )
#endif
{
	#ifdef STORMC4_WOS
	thread_args *data=(thread_args *)args;
	#else
	//thread_args *data=(thread_args *)atol(args);
	SDL_Thread *data=(SDL_Thread *)atol(args);
	#endif

    // Because proc's are created with NIL: stdio
    //freopen("stdout2.txt","w",stdout);
    //freopen("stderr2.txt","w",stderr);

	struct Task *Father;

#ifdef MYDEBUG
	fprintf(stderr,"amigaos3 RunThread Received args=%s data: %08lx\n",args,(long)data); fflush(stderr);
#endif
	
	//Father=data->wait;
	Father=(struct Task *)theMainThread;
	
#ifdef MYDEBUG
fprintf(stderr,"We be %08lx\n",SDL_ThreadID()); fflush(stderr);
#endif
	SDL_RunThread(data);
#ifdef MYDEBUG
fprintf(stderr,"We now be %08lx\n",SDL_ThreadID()); fflush(stderr);
#endif

	Signal(Father,SIGBREAKF_CTRL_F);
#ifdef MYDEBUG
	fprintf(stderr,"amigaos3 RunThread Thread done\n"); fflush(stderr);
#endif
	return(0);
}

#else

#error this code not worked on

#include <emul/emulinterface.h>

Uint32 RunTheThread(void)
{
	thread_args *data=(thread_args *)atol((char *)REG_A0);
	struct Task *Father;

#ifdef MYDEBUG
	fprintf(stderr,"amigaos3 RunTheThread Received data: %lx\n",(long)data); fflush(stderr);
#endif
	Father=data->wait;

	SDL_RunThread(data);

	Signal(Father,SIGBREAKF_CTRL_F);
#ifdef MYDEBUG
	fprintf(stderr,"amigaos3 RunTheThread Thread with data %lx ended\n",(long)data); fflush(stderr);
#endif
	return(0);
}

struct EmulLibEntry RunThreadStruct=
{
	TRAP_LIB,
	0,
	(ULONG)RunTheThread
};

void *RunThread=&RunThreadStruct;
#endif


int SDL_SYS_CreateThread(SDL_Thread *thread/*, void *args*/)
{
	/* Create the thread and go! */
	char buffer[20];

#ifdef MYDEBUG
	fprintf(WHERE,"amigaos3 sys create thread %8lx\n",(long)thread); fflush(WHERE);
	//fprintf(WHERE,"Sending %lx to the new thread...\n",args);
#endif

	SDL_snprintf(buffer, SDL_arraysize(buffer),"%ld",(long)thread);
	
#ifdef MYDEBUG
fprintf(WHERE,"We are %08lx\n",SDL_ThreadID()); fflush(WHERE);
#endif
    if(theMainThread) {
      if(SDL_ThreadID()!=theMainThread) {
        SDL_SetError("Sorry, threads creating threads not implemented!\n");
        return (-1);
      }
    }
    else
    {
      theMainThread=SDL_ThreadID();
    }

	#ifdef STORMC4_WOS
	#error code not worked on
	thread->handle=CreateTaskPPCTags(TASKATTR_CODE,	RunThread,
					TASKATTR_NAME,	"SDL subtask",
					TASKATTR_STACKSIZE, 100000,
					//(args ? TASKATTR_R3 : TAG_IGNORE), args,
					TASKATTR_R3,(ULONG)thread,
					TASKATTR_INHERITR2, TRUE,
					TAG_DONE);
	#else
	thread->handle=(struct Task *)CreateNewProcTags(NP_Output,Output(),
					NP_Name,(ULONG)"SDL subtask",
					NP_CloseOutput, FALSE,
					NP_StackSize,65535,
					NP_Entry,(ULONG)RunThread,
					NP_Arguments,(ULONG)buffer,
					//args ? NP_Arguments : TAG_IGNORE,(ULONG)buffer,
					TAG_DONE);
	#endif

	if(!thread->handle)
	{
		SDL_SetError("Not enough resources to create thread");
		return(-1);
	}

#ifdef MYDEBUG
fprintf(WHERE,"We are now %08lx\n",SDL_ThreadID()); fflush(WHERE);
#endif

#ifdef MYDEBUG
	fprintf(WHERE,"amigaos3 sys create thread created handle=%08lx\n",(long)thread->handle); fflush(WHERE);
#endif
	return(0);
}

void SDL_SYS_SetupThread(const char *name)
{
#ifdef MYDEBUG
	fprintf(WHERE,"amigaos3 sys setup thread %s\n",name); fflush(WHERE);
#endif
	// NOTE: Safe to ignore, many systems do that
}

SDL_threadID SDL_ThreadID(void)
{
	return((SDL_threadID)FindTask(NULL));
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
#ifdef MYDEBUG
	fprintf(WHERE,"amigaos3 sys wait thread %8lx\n",(long)thread); fflush(WHERE);
#endif
	SetSignal(0L,SIGBREAKF_CTRL_F|SIGBREAKF_CTRL_C);
	Wait(SIGBREAKF_CTRL_F|SIGBREAKF_CTRL_C);
}

void SDL_SYS_KillThread(SDL_Thread *thread)
{
#ifdef MYDEBUG
	fprintf(WHERE,"amigaos3 sys kill thread %8lx\n",(long)thread); fflush(WHERE);
#endif
	Signal((struct Task *)thread->handle,SIGBREAKF_CTRL_C);
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
#ifdef MYDEBUG
    fprintf(WHERE,"amigaos3 sys detach thread %8lx\n",(long)thread); fflush(WHERE);
#endif
    return;
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
#ifdef MYDEBUG
    fprintf(WHERE,"amigaos3 sys setpriority thread\n"); fflush(WHERE);
#endif
    return 0;
}

#endif
