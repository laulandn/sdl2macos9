/* SDL2 condition variables over the OPENSTEP semaphore and mutex backends. */
#include "../../SDL_internal.h"

#include "SDL_mutex.h"
#include "SDL_thread.h"

/*
 * Mach cthreads has an untimed condition API only.  This established SDL
 * semaphore-handshake algorithm keeps timed wait behaviour in SDL_syssem.c
 * and prevents a signal/timeout race from losing a wake-up.
 */
struct SDL_cond
{
    SDL_mutex *lock;
    int waiting;
    int signals;
    SDL_sem *wait_sem;
    SDL_sem *wait_done;
};

SDL_cond *SDL_CreateCond(void)
{
    SDL_cond *cond;

    cond = (SDL_cond *)SDL_calloc(1, sizeof(*cond));
    if (!cond) {
        SDL_OutOfMemory();
        return NULL;
    }
    cond->lock = SDL_CreateMutex();
    cond->wait_sem = SDL_CreateSemaphore(0);
    cond->wait_done = SDL_CreateSemaphore(0);
    if (!cond->lock || !cond->wait_sem || !cond->wait_done) {
        SDL_DestroyCond(cond);
        return NULL;
    }
    return cond;
}

/* The caller must ensure no other thread is using cond during destruction. */
void SDL_DestroyCond(SDL_cond *cond)
{
    if (cond) {
        SDL_DestroySemaphore(cond->wait_sem);
        SDL_DestroySemaphore(cond->wait_done);
        SDL_DestroyMutex(cond->lock);
        SDL_free(cond);
    }
}

int SDL_CondSignal(SDL_cond *cond)
{
    if (!cond) {
        return SDL_SetError("Passed a NULL condition variable");
    }
    SDL_LockMutex(cond->lock);
    if (cond->waiting > cond->signals) {
        ++cond->signals;
        SDL_SemPost(cond->wait_sem);
        SDL_UnlockMutex(cond->lock);
        SDL_SemWait(cond->wait_done);
    } else {
        SDL_UnlockMutex(cond->lock);
    }
    return 0;
}

int SDL_CondBroadcast(SDL_cond *cond)
{
    int index;
    int number_waiting;

    if (!cond) {
        return SDL_SetError("Passed a NULL condition variable");
    }
    SDL_LockMutex(cond->lock);
    if (cond->waiting > cond->signals) {
        number_waiting = cond->waiting - cond->signals;
        cond->signals = cond->waiting;
        for (index = 0; index < number_waiting; ++index) {
            SDL_SemPost(cond->wait_sem);
        }
        SDL_UnlockMutex(cond->lock);
        for (index = 0; index < number_waiting; ++index) {
            SDL_SemWait(cond->wait_done);
        }
    } else {
        SDL_UnlockMutex(cond->lock);
    }
    return 0;
}

int SDL_CondWaitTimeout(SDL_cond *cond, SDL_mutex *mutex, Uint32 timeout)
{
    int result;

    if (!cond || !mutex) {
        return SDL_SetError("Passed a NULL condition or mutex");
    }
    SDL_LockMutex(cond->lock);
    ++cond->waiting;
    SDL_UnlockMutex(cond->lock);

    SDL_UnlockMutex(mutex);
    if (timeout == SDL_MUTEX_MAXWAIT) {
        result = SDL_SemWait(cond->wait_sem);
    } else {
        result = SDL_SemWaitTimeout(cond->wait_sem, timeout);
    }

    SDL_LockMutex(cond->lock);
    if (cond->signals > 0) {
        if (result > 0) {
            SDL_SemWait(cond->wait_sem);
        }
        SDL_SemPost(cond->wait_done);
        --cond->signals;
    }
    --cond->waiting;
    SDL_UnlockMutex(cond->lock);

    SDL_LockMutex(mutex);
    return result;
}

int SDL_CondWait(SDL_cond *cond, SDL_mutex *mutex)
{
    return SDL_CondWaitTimeout(cond, mutex, SDL_MUTEX_MAXWAIT);
}
