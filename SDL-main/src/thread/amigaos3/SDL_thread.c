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

#ifdef SDL_THREAD_AMIGAOS3

/* System independent thread management routines for SDL */

#include "SDL_mutex.h"
#include "SDL_thread.h"
#include "../SDL_thread_c.h"
#include "../SDL_systhread.h"
#include <exec/semaphores.h>
#include <dos/dos.h>
#include <proto/exec.h>

#define ARRAY_CHUNKSIZE	32
/* The array of threads currently active in the application
   (except the main thread)
   The manipulation of an array here is safer than using a linked list.
*/

static int SDL_maxthreads = 0;
static int SDL_numthreads = 0;
static SDL_Thread **SDL_Threads = NULL;
static struct SignalSemaphore thread_lock;
int thread_lock_created = 0;

extern void SDL_SYS_KillThread(SDL_Thread *thread);


int SDL_ThreadsInit(void)
{
    fprintf(stderr,"amigaos3 threads init\n");
	InitSemaphore(&thread_lock);
	thread_lock_created=1;
	return 0;
}

/* This should never be called...
   If this is called by SDL_Quit(), we don't know whether or not we should
   clean up threads here.  If any threads are still running after this call,
   they will no longer have access to any per-thread data.
 */
void SDL_ThreadsQuit()
{
    fprintf(stderr,"amigaos3 threads quit\n");
	thread_lock_created=0;
}

/* Routines for manipulating the thread list */
static void SDL_AddThread(SDL_Thread *thread)
{
	SDL_Thread **threads;

    fprintf(stderr,"amigaos3 add thread %8lx\n",(long)thread);
	/* WARNING:
	   If the very first threads are created simultaneously, then
	   there could be a race condition causing memory corruption.
	   In practice, this isn't a problem because by definition there
	   is only one thread running the first time this is called.
	*/
	if ( !thread_lock_created ) {
		if ( SDL_ThreadsInit() < 0 ) {
			return;
		}
	}
	ObtainSemaphore(&thread_lock);

	/* Expand the list of threads, if necessary */
#ifdef DEBUG_THREADS
	printf("Adding thread (%d already - %d max)\n",
			SDL_numthreads, SDL_maxthreads);
#endif
	if ( SDL_numthreads == SDL_maxthreads ) {
		threads=(SDL_Thread **)SDL_malloc((SDL_maxthreads+ARRAY_CHUNKSIZE)*
		                              (sizeof *threads));
		if ( threads == NULL ) {
			SDL_OutOfMemory();
			goto done;
		}
		SDL_memcpy(threads, SDL_Threads, SDL_numthreads*(sizeof *threads));
		SDL_maxthreads += ARRAY_CHUNKSIZE;
		if ( SDL_Threads ) {
			SDL_free(SDL_Threads);
		}
		SDL_Threads = threads;
	}
	SDL_Threads[SDL_numthreads++] = thread;
done:
	ReleaseSemaphore(&thread_lock);
}

static void SDL_DelThread(SDL_Thread *thread)
{
	int i;

    fprintf(stderr,"amigaos3 del thread %8lx\n",(long)thread);
	if ( thread_lock_created ) {
		ObtainSemaphore(&thread_lock);
		for ( i=0; i<SDL_numthreads; ++i ) {
			if ( thread == SDL_Threads[i] ) {
				break;
			}
		}
		if ( i < SDL_numthreads ) {
			--SDL_numthreads;
			while ( i < SDL_numthreads ) {
				SDL_Threads[i] = SDL_Threads[i+1];
				++i;
			}
#ifdef DEBUG_THREADS
			printf("Deleting thread (%d left - %d max)\n",
					SDL_numthreads, SDL_maxthreads);
#endif
		}
		ReleaseSemaphore(&thread_lock);
	}
}

/* The default (non-thread-safe) global error variable */
static SDL_error SDL_global_error;

/* Routine to get the thread-specific error variable */
SDL_error *SDL_GetErrBuf(void)
{
	SDL_error *errbuf;

    fprintf(stderr,"amigaos3 thread geterrbuf\n");
	errbuf = &SDL_global_error;
	if ( SDL_Threads ) {
		int i;
		Uint32 this_thread;

		this_thread = SDL_ThreadID();
		ObtainSemaphore(&thread_lock);
		for ( i=0; i<SDL_numthreads; ++i ) {
			if ( this_thread == SDL_Threads[i]->threadid ) {
				errbuf = &SDL_Threads[i]->errbuf;
				break;
			}
		}
		ReleaseSemaphore(&thread_lock);
	}
	return(errbuf);
}


/* Arguments and callback to setup and run the user thread function */
typedef struct {
	int (*func)(void *);
	void *data;
	SDL_Thread *info;
	struct Task *wait;
} thread_args;

void SDL_RunThread(SDL_Thread *thread)
{
	void *data=NULL;
	thread_args *args;
	int (*userfunc)(void *);
	void *userdata;
	int *statusloc;

    fprintf(stderr,"amigaos3 run thread %8lx\n",(long)thread);
	/* Perform any system-dependent setup
	   - this function cannot fail, and cannot use SDL_SetError()
	 */
	SDL_SYS_SetupThread("My thread");

	/* Get the thread id */
	args = (thread_args *)data;
	args->info->threadid = SDL_ThreadID();

	/* Figure out what function to run */
	userfunc = args->func;
	userdata = args->data;
	statusloc = &args->info->status;

	/* Wake up the parent thread */
	Signal(args->wait,SIGBREAKF_CTRL_E);

	/* Run the function */
	*statusloc = userfunc(userdata);
}

SDL_Thread *SDL_CreateThread(SDL_ThreadFunction fn, const char *name, void *data/*int (*fn)(void *), void *data*/)
{
	SDL_Thread *thread;
	thread_args *args;
	int ret;

    fprintf(stderr,"amigaos3 create thread %8lx %s %8lx\n",(long)fn,name,(long)data);
	/* Allocate memory for the thread info structure */
	thread = (SDL_Thread *)SDL_malloc(sizeof(*thread));
	if ( thread == NULL ) {
		SDL_OutOfMemory();
		return(NULL);
	}
	SDL_memset(thread, 0, (sizeof *thread));
	thread->status = -1;

	/* Set up the arguments for the thread */
	args = (thread_args *)SDL_malloc(sizeof(*args));
	if ( args == NULL ) {
		SDL_OutOfMemory();
		SDL_free(thread);
		return(NULL);
	}
	args->func = fn;
	args->data = data;
	args->info = thread;
	args->wait = FindTask(NULL);
	if ( args->wait == NULL ) {
		SDL_free(thread);
		SDL_free(args);
		SDL_OutOfMemory();
		return(NULL);
	}

	/* Add the thread to the list of available threads */
	SDL_AddThread(thread);

	fprintf(stderr,"Starting thread...\n");

	/* Create the thread and go! */
	ret = SDL_SYS_CreateThread(thread/*, args*/);
	if ( ret >= 0 ) {
		fprintf(stderr,"Waiting for thread CTRL_E...\n");
		/* Wait for the thread function to use arguments */
		Wait(SIGBREAKF_CTRL_E);
		fprintf(stderr,"  Arrived.");
	} else {
		/* Oops, failed.  Gotta free everything */
		SDL_DelThread(thread);
		SDL_free(thread);
		thread = NULL;
	}
	SDL_free(args);

	/* Everything is running now */
	return(thread);
}

void SDL_WaitThread(SDL_Thread *thread, int *status)
{
    fprintf(stderr,"amigaos3 wait thread %8lx\n",(long)thread);
	if ( thread ) {
		SDL_SYS_WaitThread(thread);
		if ( status ) {
			*status = thread->status;
		}
		SDL_DelThread(thread);
		SDL_free(thread);
	}
}

SDL_threadID SDL_GetThreadID(SDL_Thread *thread)
{
	SDL_threadID id;

    fprintf(stderr,"amigaos3 get thread id %8lx\n",(long)thread);
	if ( thread ) {
		id = thread->threadid;
	} else {
		id = SDL_ThreadID();
	}
	return(id);
}

void SDL_KillThread(SDL_Thread *thread)
{
    fprintf(stderr,"amigaos3 kill thread %8lx\n",(long)thread);
	if ( thread ) {
		SDL_SYS_KillThread(thread);
		SDL_WaitThread(thread, NULL);
	}
}

#endif
