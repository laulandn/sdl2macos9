/* SDL2 semaphores over OPENSTEP Mach cthreads primitives. */
#include "../../SDL_internal.h"

#include <errno.h>
#include <libc.h>
#include <mach/cthreads.h>
#include <sys/time.h>

#include "SDL_mutex.h"
#include "SDL_thread.h"

struct SDL_semaphore
{
    Uint32 count;
    mutex_t mutex;
    condition_t condition;
};

/*
 * Mach cthreads has no timed condition wait.  Keep that limitation local to
 * this backend: finite waits poll at a one-millisecond maximum interval,
 * while an infinite wait uses the native condition queue.
 */
static Uint32 OpenStep_GetMilliseconds(void)
{
    struct timeval now;

    gettimeofday(&now, (struct timezone *)0);
    return ((Uint32)now.tv_sec * 1000U) + ((Uint32)now.tv_usec / 1000U);
}

static void OpenStep_DelayMilliseconds(Uint32 milliseconds)
{
    struct timeval delay;
    int result;

    delay.tv_sec = (long)(milliseconds / 1000U);
    delay.tv_usec = (long)((milliseconds % 1000U) * 1000U);
    do {
        result = select(0, 0, 0, 0, &delay);
    } while ((result < 0) && (errno == EINTR));
}

SDL_sem *SDL_CreateSemaphore(Uint32 initial_value)
{
    SDL_sem *sem;

    sem = (SDL_sem *)SDL_calloc(1, sizeof(*sem));
    if (!sem) {
        SDL_OutOfMemory();
        return NULL;
    }
    sem->mutex = mutex_alloc();
    sem->condition = condition_alloc();
    if (!sem->mutex || !sem->condition) {
        if (sem->mutex) {
            mutex_free(sem->mutex);
        }
        if (sem->condition) {
            condition_free(sem->condition);
        }
        SDL_free(sem);
        SDL_OutOfMemory();
        return NULL;
    }
    mutex_init(sem->mutex);
    condition_init(sem->condition);
    sem->count = initial_value;
    return sem;
}

/* The caller must ensure no other thread is using sem during destruction. */
void SDL_DestroySemaphore(SDL_sem *sem)
{
    if (sem) {
        condition_free(sem->condition);
        mutex_free(sem->mutex);
        SDL_free(sem);
    }
}

int SDL_SemTryWait(SDL_sem *sem)
{
    int result;

    if (!sem) {
        return SDL_SetError("Passed a NULL semaphore");
    }
    mutex_lock(sem->mutex);
    result = SDL_MUTEX_TIMEDOUT;
    if (sem->count) {
        --sem->count;
        result = 0;
    }
    mutex_unlock(sem->mutex);
    return result;
}

int SDL_SemWaitTimeout(SDL_sem *sem, Uint32 timeout)
{
    Uint32 start;

    if (!sem) {
        return SDL_SetError("Passed a NULL semaphore");
    }
    if (timeout == 0) {
        return SDL_SemTryWait(sem);
    }

    start = OpenStep_GetMilliseconds();
    mutex_lock(sem->mutex);
    while (!sem->count) {
        if (timeout == SDL_MUTEX_MAXWAIT) {
            condition_wait(sem->condition, sem->mutex);
        } else {
            Uint32 elapsed = OpenStep_GetMilliseconds() - start;
            Uint32 remaining;

            if (elapsed >= timeout) {
                mutex_unlock(sem->mutex);
                return SDL_MUTEX_TIMEDOUT;
            }
            remaining = timeout - elapsed;
            mutex_unlock(sem->mutex);
            OpenStep_DelayMilliseconds((remaining < 1U) ? remaining : 1U);
            mutex_lock(sem->mutex);
        }
    }
    --sem->count;
    mutex_unlock(sem->mutex);
    return 0;
}

int SDL_SemWait(SDL_sem *sem)
{
    return SDL_SemWaitTimeout(sem, SDL_MUTEX_MAXWAIT);
}

Uint32 SDL_SemValue(SDL_sem *sem)
{
    Uint32 value;

    if (!sem) {
        return 0;
    }
    mutex_lock(sem->mutex);
    value = sem->count;
    mutex_unlock(sem->mutex);
    return value;
}

int SDL_SemPost(SDL_sem *sem)
{
    if (!sem) {
        return SDL_SetError("Passed a NULL semaphore");
    }
    mutex_lock(sem->mutex);
    ++sem->count;
    condition_signal(sem->condition);
    mutex_unlock(sem->mutex);
    return 0;
}
