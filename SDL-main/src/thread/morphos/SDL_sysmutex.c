/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2021 Sam Lantinga <slouken@libsdl.org>

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

/* An implementation of mutexes using semaphores */

#include "SDL_thread.h"
#include "SDL_systhread_c.h"

#include <proto/exec.h>


struct SDL_mutex
{
    struct SignalSemaphore sem;
};

/* Create a mutex */
SDL_mutex *
SDL_CreateMutex(void)
{
    SDL_mutex *mutex;

    /* Allocate mutex memory */
    mutex = (SDL_mutex *) SDL_malloc(sizeof(*mutex));
    if (mutex) {
        /* Create the mutex semaphore, with initial value 1 */
        memset(&mutex->sem, 0, sizeof(mutex->sem));
        InitSemaphore(&mutex->sem);
    } else {
        SDL_OutOfMemory();
    }
    return mutex;
}

/* Free the mutex */
void
SDL_DestroyMutex(SDL_mutex * mutex)
{
    if (mutex)
        SDL_free(mutex);
}

/* Lock the mutex */
int
SDL_LockMutex(SDL_mutex * mutex)
{
#if SDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL)
        return SDL_SetError("Passed a NULL mutex");

    ObtainSemaphore(&mutex->sem);
    return 0;
#endif /* SDL_THREADS_DISABLED */
}

/* try Lock the mutex */
int
SDL_TryLockMutex(SDL_mutex * mutex)
{
#if SDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL)
        return SDL_SetError("Passed a NULL mutex");

    return AttemptSemaphore(&mutex->sem) ? 0 : SDL_MUTEX_TIMEDOUT;
#endif /* SDL_THREADS_DISABLED */
}

/* Unlock the mutex */
int
SDL_mutexV(SDL_mutex * mutex)
{
#if SDL_THREADS_DISABLED
    return 0;
#else
    if (mutex == NULL)
        return SDL_SetError("Passed a NULL mutex");

    ReleaseSemaphore(&mutex->sem);
    return 0;
#endif /* SDL_THREADS_DISABLED */
}

/* vi: set ts=4 sw=4 expandtab: */
