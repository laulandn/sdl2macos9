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
#include "SDL_timer.h"
#include "SDL_systhread_c.h"

#ifdef SDL_THREAD_PS1

#include "./ThreadSynch.h"




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

    return SemaphoreTryP(&sem->Sem) ? 0 : SDL_MUTEX_TIMEDOUT;
}

int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 timeout)
{
	Uint64 deadline;

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
    if (timeout == SDL_MUTEX_MAXWAIT) {
        return SDL_SemWait(sem);
    }

    deadline = SDL_GetTicks64() + timeout;
    do {
        if (SemaphoreTryP(&sem->Sem)) {
            return 0;
        }
        //YieldToAnyThread();
    } while (SDL_GetTicks64() < deadline);

    /* Check once more at the boundary so a simultaneous post wins. */
    return SemaphoreTryP(&sem->Sem) ? 0 : SDL_MUTEX_TIMEDOUT;
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
