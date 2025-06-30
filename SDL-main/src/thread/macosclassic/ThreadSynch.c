// ThreadSynch.c
// 
// Copyright (C) 6th March 1994  Stuart Cheshire <cheshire@cs.stanford.edu>
//
// See ThreadSynch.h for usage instructions.

#include "ThreadSynch.h"
struct SemaphoreWaiter { SemaphoreWaiter *next; ThreadID ID; };
struct ConditionWaiter { ConditionWaiter *next; Semaphore sem; };

// *****************************************************************
// Semaphore. Operations: Init, Proben (test), Verhogen (increment)

void SemaphoreInit(Semaphore *s, long initialvalue)
	{
	s->value = initialvalue;
	s->head = NULL;
	s->tail = &s->head;
	}

void SemaphoreP(Semaphore *s)
	{
	ThreadBeginCritical();
	if (s->value > 0)		// If resource available, consume and continue
		{
		s->value--;
		ThreadEndCritical();
		}
	else					// else queue up and sleep
		{
		SemaphoreWaiter me;
		me.next = NULL;
		GetCurrentThread(&me.ID);
		*(s->tail) = &me;
		s->tail = &me.next;
		SetThreadStateEndCritical(kCurrentThreadID, kStoppedThreadState, kNoThreadID);
		}
	}

void SemaphoreV(Semaphore *s)
	{
	ThreadBeginCritical();
	if (!s->head)			// If no waiters, increment resource count
		{
		s->value++;
		ThreadEndCritical();
		}
	else					// else wake up one of the waiters
		{
		SemaphoreWaiter *w = s->head;
		s->head = s->head->next;
		if (!s->head) s->tail = &s->head;
		SetThreadStateEndCritical(w->ID, kReadyThreadState, kNoThreadID);
		}
	}


// *****************************************************************
// MutexLock. Operations: Init, Acquire, Release

void MutexLockInit(MutexLock *m)
	{
	SemaphoreInit(&m->sem, 1);
	m->lockholder = kNoThreadID;
	}

void MutexLockAcquire(MutexLock *m)
	{
	ThreadID currentThread;
	GetCurrentThread(&currentThread);
	if (m->lockholder == currentThread)
		DebugStr("\pError: Deadlock: Attempt to reaquire lock already held");
	SemaphoreP(&m->sem);
	m->lockholder = currentThread;
	}

void MutexLockRelease(MutexLock *m)
	{
	ThreadID currentThread;
	GetCurrentThread(&currentThread);
	if (m->lockholder != currentThread)
		DebugStr("\pError: Thread releasing lock does not hold it");
	m->lockholder = kNoThreadID;
	SemaphoreV(&m->sem);
	}


// *****************************************************************
// ConditionVar. Operations: Init, Wait, Signal, Broadcast

void ConditionVarInit(ConditionVar *c, MutexLock *lock)
	{
	c->lock = lock;
	c->head = NULL;
	c->tail = &c->head;
	}

void ConditionVarWait(ConditionVar *c)
	{
	ConditionWaiter me;
	ThreadID currentThread;
	GetCurrentThread(&currentThread);
	if (c->lock->lockholder != currentThread)
		DebugStr("\pError: Thread waiting on condition variable does not hold correct lock");

	me.next = NULL;
	SemaphoreInit(&me.sem, 0);
	*(c->tail) = &me;
	c->tail = &me.next;
	MutexLockRelease(c->lock);
	SemaphoreP(&me.sem);
	MutexLockAcquire(c->lock);
	}

void ConditionVarSignal(ConditionVar *c)
	{
	ThreadID currentThread;
	GetCurrentThread(&currentThread);
	if (c->lock->lockholder != currentThread)
		DebugStr("\pError: Thread signalling condition variable does not hold correct lock");
	if (c->head)					// If there is someone waiting
		{
		SemaphoreV(&c->head->sem);	// Wake them up
		c->head = c->head->next;	// And remove them from the list
		if (!c->head) c->tail = &c->head;
		}
	}

void ConditionVarBroadcast(ConditionVar *c)
	{
	ThreadID currentThread;
	GetCurrentThread(&currentThread);
	if (c->lock->lockholder != currentThread)
		DebugStr("\pError: Thread signalling condition variable does not hold correct lock");
	while (c->head)					// For every waiter in list
		{
		SemaphoreV(&c->head->sem);	// Wake them up
		c->head = c->head->next;	// And remove them from the list
		}
	c->tail = &c->head;
	}

// Note: We do not have to worry here about new waiters joining the end
// of the queue while we are processing it because they can't join unless
// they hold the correct lock -- and they can't because we have it.
