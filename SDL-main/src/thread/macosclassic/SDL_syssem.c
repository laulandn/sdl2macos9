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

#include "SDL_thread.h"
#include "SDL_systhread_c.h"

#ifdef SDL_THREAD_MACOSCLASSIC

#include "./ThreadSynch.h"


#define MYDEBUG 1


extern void SDL_Delay(int timeout);


struct SDL_semaphore
{
	Semaphore Sem;
};


SDL_sem *SDL_CreateSemaphore(Uint32 initial_value)
{
	SDL_sem *sem;

	sem = (SDL_sem *)SDL_malloc(sizeof(*sem));

	if ( ! sem ) {
		SDL_OutOfMemory();
		return(0);
	}

#ifdef MYDEBUG
	fprintf(stderr,"macosclassic Creating semaphore %lx...\n",(long)sem);
#endif

	SDL_memset(sem,0,sizeof(*sem));

	//InitSemaphore(&sem->Sem);
	SemaphoreInit(&sem->Sem,initial_value);

	return(sem);
}

void SDL_DestroySemaphore(SDL_sem *sem)
{
#ifdef MYDEBUG
	fprintf(stderr,"macosclassic Destroying semaphore %lx...\n",(long)sem);
#endif

	if ( sem ) {
// Condizioni per liberare i task in attesa?
		SDL_free(sem);
	}
}

int SDL_SemTryWait(SDL_sem *sem)
{
	if ( ! sem ) {
		SDL_SetError("Passed a NULL semaphore");
		return -1;
	}

#ifdef MYDEBUG
	fprintf(stderr,"macosclassic TryWait semaphore...%lx\n",(long)sem);
#endif

    //if(sem->Sem.value>0) {
      SemaphoreAcquire(&sem->Sem);
    //}
    //else return SDL_MUTEX_TIMEDOUT;
    return 1;
}

int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 timeout)
{
	int retval=0;

	if ( ! sem ) {
		SDL_SetError("Passed a NULL semaphore");
		return -1;
	}

#ifdef MYDEBUG
    fprintf(stderr,"macosclassic WaitTimeout (%ld) semaphore...%lx\n",(long)timeout,(long)sem);
#endif

    /* A timeout of 0 is an easy case */
    if ( timeout == 0 ) {
      return SDL_SemTryWait(sem);
    }
    // Max wait...
    if(timeout== -1) {
    }
    // TODO: This is NOT right at all...it always waits...
    if(!(retval=SDL_SemTryWait(sem)))
    {
      // We didn't immediately get it so wait the timeout
      // So do we just wait, try again and then give up?
      SDL_Delay(timeout);
      retval=SDL_SemTryWait(sem);
     }
     // No release here right?
     return retval;
}

int SDL_SemWait(SDL_sem *sem)
{
#ifdef MYDEBUG
	fprintf(stderr,"macosclassic SemWait semaphore...%lx\n",(long)sem);
#endif
	//ObtainSemaphore(&sem->Sem);
	SemaphoreAcquire(&sem->Sem);
	// TODO: Yield here or does SemaphoreAcquire do that for me?
	return 0;
}

Uint32 SDL_SemValue(SDL_sem *sem)
{
	Uint32 value;

	value = 0;
	if ( sem ) {
		//#ifdef STORMC4_WOS
		//value = sem->Sem.ssppc_SS.ss_NestCount;
		//#else
		//value = sem->Sem.ss_NestCount;
		value = sem->Sem.value;
		//#endif
	}
	return value;
}

int SDL_SemPost(SDL_sem *sem)
{
	if ( ! sem ) {
		SDL_SetError("Passed a NULL semaphore");
		return -1;
	}
#ifdef MYDEBUG
	fprintf(stderr,"macosclassic SemPost semaphore...%lx\n",(long)sem);
#endif

	//ReleaseSemaphore(&sem->Sem);
	SemaphoreRelease(&sem->Sem);
	return 0;
}

#endif
