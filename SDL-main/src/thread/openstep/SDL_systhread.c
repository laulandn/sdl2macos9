#include "../../SDL_internal.h"

#include <mach/cthreads.h>

#include "SDL_thread.h"
#include "../SDL_thread_c.h"
#include "../SDL_systhread.h"

static SDL_SpinLock openstep_cthreads_init_lock;
static int openstep_cthreads_initialized;

static any_t OpenStep_RunThread(any_t data)
{
    SDL_RunThread((SDL_Thread *)data);
    return (any_t)0;
}

int SDL_SYS_CreateThread(SDL_Thread *thread)
{
    cthread_t handle;

    if (thread->stacksize != 0) {
        return SDL_SetError("OPENSTEP cthreads has no requested stack-size API");
    }

    SDL_AtomicLock(&openstep_cthreads_init_lock);
    if (!openstep_cthreads_initialized) {
        cthread_init();
        openstep_cthreads_initialized = 1;
    }
    SDL_AtomicUnlock(&openstep_cthreads_init_lock);

    handle = cthread_fork((cthread_fn_t)OpenStep_RunThread, (any_t)thread);
    if (handle == NO_CTHREAD) {
        return SDL_SetError("cthread_fork failed");
    }
    thread->handle = handle;
    return 0;
}

void SDL_SYS_SetupThread(const char *name)
{
    cthread_t current;

    /* cthreads exposes a documented per-thread diagnostic name.  SDL calls
       this only from the newly created thread, so name the current cthread
       rather than relying on a parent-side race after cthread_fork(). */
    if (name == NULL || *name == '\0') return;
    current = cthread_self();
    if (current != NO_CTHREAD) {
        cthread_set_name(current, name);
    }
}

SDL_threadID SDL_ThreadID(void)
{
    return (SDL_threadID)(unsigned long)cthread_self();
}

int SDL_SYS_SetThreadPriority(SDL_ThreadPriority priority)
{
    (void)priority;
    return SDL_Unsupported();
}

void SDL_SYS_WaitThread(SDL_Thread *thread)
{
    if (thread->handle != NO_CTHREAD) {
        cthread_join(thread->handle);
        thread->handle = NO_CTHREAD;
    }
}

void SDL_SYS_DetachThread(SDL_Thread *thread)
{
    if (thread->handle != NO_CTHREAD) {
        cthread_detach(thread->handle);
        thread->handle = NO_CTHREAD;
    }
}
