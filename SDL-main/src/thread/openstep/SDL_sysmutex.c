#include "../../SDL_internal.h"

#include <mach/cthreads.h>

#include "SDL_mutex.h"
#include "SDL_thread.h"

struct SDL_mutex
{
    mutex_t mutex;
    SDL_threadID owner;
    int recursive;
};

SDL_mutex *SDL_CreateMutex(void)
{
    SDL_mutex *mutex;

    mutex = (SDL_mutex *)SDL_calloc(1, sizeof(*mutex));
    if (!mutex) {
        SDL_OutOfMemory();
        return NULL;
    }
    mutex->mutex = mutex_alloc();
    if (!mutex->mutex) {
        SDL_free(mutex);
        SDL_OutOfMemory();
        return NULL;
    }
    mutex_init(mutex->mutex);
    return mutex;
}

void SDL_DestroyMutex(SDL_mutex *mutex)
{
    if (mutex) {
        if (mutex->mutex) {
            mutex_free(mutex->mutex);
        }
        SDL_free(mutex);
    }
}

int SDL_LockMutex(SDL_mutex *mutex)
{
    SDL_threadID self;

    if (!mutex) {
        return SDL_SetError("Passed a NULL mutex");
    }
    self = SDL_ThreadID();
    if (mutex->owner == self) {
        ++mutex->recursive;
        return 0;
    }
    mutex_lock(mutex->mutex);
    mutex->owner = self;
    mutex->recursive = 0;
    return 0;
}

int SDL_TryLockMutex(SDL_mutex *mutex)
{
    SDL_threadID self;

    if (!mutex) {
        return SDL_SetError("Passed a NULL mutex");
    }
    self = SDL_ThreadID();
    if (mutex->owner == self) {
        ++mutex->recursive;
        return 0;
    }
    if (!mutex_try_lock(mutex->mutex)) {
        return SDL_MUTEX_TIMEDOUT;
    }
    mutex->owner = self;
    mutex->recursive = 0;
    return 0;
}

int SDL_UnlockMutex(SDL_mutex *mutex)
{
    if (!mutex) {
        return SDL_SetError("Passed a NULL mutex");
    }
    if (mutex->owner != SDL_ThreadID()) {
        return SDL_SetError("mutex not owned by this thread");
    }
    if (mutex->recursive) {
        --mutex->recursive;
    } else {
        mutex->owner = 0;
        mutex_unlock(mutex->mutex);
    }
    return 0;
}

