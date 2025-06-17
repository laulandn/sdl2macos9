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

/* An implementation of semaphores using mutexes and condition variables */

#include "SDL_timer.h"
#include "SDL_thread.h"
#include "SDL_systhread_c.h"

#include <devices/timer.h>
#include <dos/dos.h>
#include <exec/execbase.h>
#include <proto/exec.h>


#if SDL_THREADS_DISABLED

SDL_sem *
SDL_CreateSemaphore(Uint32 initial_value)
{
    SDL_SetError("SDL not built with thread support");
    return (SDL_sem *) 0;
}

void
SDL_DestroySemaphore(SDL_sem * sem)
{
}

int
SDL_SemTryWait(SDL_sem * sem)
{
    return SDL_SetError("SDL not built with thread support");
}

int
SDL_SemWaitTimeout(SDL_sem * sem, Uint32 timeout)
{
    return SDL_SetError("SDL not built with thread support");
}

int
SDL_SemWait(SDL_sem * sem)
{
    return SDL_SetError("SDL not built with thread support");
}

Uint32
SDL_SemValue(SDL_sem * sem)
{
    return 0;
}

int
SDL_SemPost(SDL_sem * sem)
{
    return SDL_SetError("SDL not built with thread support");
}

#else

struct waitnode
{
	struct Message msg;
	struct MsgPort port;
};

struct SDL_semaphore
{
    Uint32 sem_value;
    struct MinList waitlist;
    struct SignalSemaphore sem;
};

extern void InitQPort(struct MsgPort *port);

static
void mywaitinit(struct timerequest *r, Uint32 timeout, struct waitnode *wn)
{
    extern struct timerequest GlobalTimeReq;
    struct timerequest *req = &GlobalTimeReq;

    r->tr_node.io_Message.mn_Node.ln_Type = NT_REPLYMSG;
    r->tr_node.io_Message.mn_ReplyPort    = &wn->port;
    r->tr_node.io_Device                  = req->tr_node.io_Device;
    r->tr_node.io_Unit                    = req->tr_node.io_Unit;
}

SDL_sem *
SDL_CreateSemaphore(Uint32 initial_value)
{
    SDL_sem *sem;

    sem = (SDL_sem *) SDL_malloc(sizeof(*sem));
    if (!sem) {
        SDL_OutOfMemory();
        return NULL;
    }

    sem->sem_value = initial_value;

    NEWLIST(&sem->waitlist);
    memset(&sem->sem, 0, sizeof(sem->sem));
    InitSemaphore(&sem->sem);

    return sem;
}

/* WARNING:
   You cannot call this function when another thread is using the semaphore.
*/
void
SDL_DestroySemaphore(SDL_sem * sem)
{
    if (sem) {
        ObtainSemaphore(&sem->sem);

        sem->sem_value = (Uint32)-1;

        while (!IsListEmpty((struct List *) &sem->waitlist)) {
            struct waitnode *wn;

            for (wn = (struct waitnode *) sem->waitlist.mlh_Head; wn->msg.mn_Node.ln_Succ; wn = (struct waitnode *) wn->msg.mn_Node.ln_Succ)
                ReplyMsg(&wn->msg);

            if (SDL_SemWaitTimeout(sem, 10) < 0)
                break;
        }

        ReleaseSemaphore(&sem->sem);

        SDL_free(sem);
    }
}

int
SDL_SemTryWait(SDL_sem * sem)
{
    int retval = SDL_MUTEX_TIMEDOUT;

    if (!sem)
        return SDL_SetError("Passed a NULL semaphore");

    if (sem->sem_value > 0) {
        ObtainSemaphore(&sem->sem);

        if (sem->sem_value > 0) {
            --sem->sem_value;
            retval = 0;
        }

        ReleaseSemaphore(&sem->sem);
    }

    return retval;
}

int
SDL_SemWaitTimeout(SDL_sem * sem, Uint32 timeout)
{
    int retval = SDL_MUTEX_TIMEDOUT;
    struct waitnode wn;

    if (!sem)
        return SDL_SetError("Passed a NULL semaphore");

    /* Try semaphore */
    ObtainSemaphore(&sem->sem);

    if (sem->sem_value > 0) {
        --sem->sem_value;
        retval = 0;
    }
    else if (timeout > 0) {
        InitQPort(&wn.port);
        wn.msg.mn_Node.ln_Type = NT_MESSAGE;
        wn.msg.mn_ReplyPort = &wn.port;
        ADDTAIL(&sem->waitlist, &wn);
    }

    ReleaseSemaphore(&sem->sem);

    /* Sem not available and we have timeout */
    if (retval == SDL_MUTEX_TIMEDOUT && timeout > 0) {
        struct timerequest req;
        struct Message *msg;

        mywaitinit(&req, timeout, &wn);

        req.tr_node.io_Command = TR_ADDREQUEST;
        req.tr_time.tv_secs  = timeout / 1000;
        req.tr_time.tv_micro = (timeout % 1000) * 1000;
        SendIO((struct IORequest *) &req);

        msg = WaitPort(&wn.port);
        retval = 0;

        if (msg != &wn.msg) {
            ObtainSemaphore(&sem->sem);
            REMOVE(&wn);
            retval = wn.msg.mn_Node.ln_Type == NT_REPLYMSG ?  0 : SDL_MUTEX_TIMEDOUT;
            ReleaseSemaphore(&sem->sem);
        }

        AbortIO((struct IORequest *) &req);
        WaitIO((struct IORequest *) &req);
    }

    return retval;
}

int
SDL_SemWait(SDL_sem * sem)
{
    return SDL_SemWaitTimeout(sem, SDL_MUTEX_MAXWAIT);
}

Uint32
SDL_SemValue(SDL_sem * sem)
{
    if (!sem) {
        SDL_SetError("Passed a NULL semaphore");
        return -1;
    }

    return sem->sem_value;
}

int
SDL_SemPost(SDL_sem * sem)
{
    struct waitnode *wn;

    if (!sem)
        return SDL_SetError("Passed a NULL semaphore");

    ObtainSemaphore(&sem->sem);

    sem->sem_value++;

   	/* Wake whatever task happens to be first in the waitlist */
    if ((wn = (APTR)REMHEAD(&sem->waitlist))) {
        sem->sem_value--;
        ReplyMsg(&wn->msg);
    }

    ReleaseSemaphore(&sem->sem);

    return 0;
}

#endif /* SDL_THREADS_DISABLED */
/* vi: set ts=4 sw=4 expandtab: */
