// ThreadSynch.h
// 
// (C) 6th March 1994  Stuart Cheshire <cheshire@cs.stanford.edu>
// 
// This header file defines three synchronization primitives:
// Semaphores, Mutual exclusion locks, and Condition variables.
// They can all be allocated in static storage, dynamic storage,
// or on the stack, and should be initialized (by calling xxxInit)
// before use. (In C++, a constructor would do this automatically.)
//
// If you aren't familiar with Semaphores, Mutual exclusion locks,
// and Condition variables, pick up a good Operating Systems text book.
//
//
// Brief explanation (for those who were sleeping in CS lectures :-)
//
// Mutual exclusion locks are used to prevent two threads accessing the
// same critical piece of code or the same critical piece of data at
// the same time. Put MutexLockAcquire at the start of the critical
// section and MutexLockRelease at the end. If a thread tries to do
// a MutexLockAcquire while another thread is in the critical section,
// it will wait until the other thread has finished before it proceeds.
// It is an error to call MutexLockRelease if you do not hold the lock,
// and it is an error to try to wait for a lock which you are already
// holding yourself ("you" means a particular thread). These errors
// are detected and reported via MacsBug breakpoints.
//
// Condition variables are used when you are waiting for a particular
// condition to become true. The "country bridge" example in test.c
// illustrates this. The easiest way to think of condition variables
// is to consider the following evolution of a program:
//
//		while (!done)
//			{
//			MutexLockAcquire(&lock);
//			if (A && B || C && D && E ...) { do_stuff(); done = TRUE; }
//			MutexLockRelease(&lock);
//			}
//
// The program keeps re-testing its condition until it is satisfactory,
// and this does its stuff. This known as busy-waiting, because the
// program is actively rereading the values of the variables as fast
// as it can, waiting until the variables change to the correct state
// so that it can proceed.
// This could be re-written as follows to eliminate the variable "done":
//
//		MutexLockAcquire(&lock);
//		while (!(A && B || C && D && E ...))
//			{ MutexLockRelease(&lock); Pause(); MutexLockAcquire(&lock); }
//		do_stuff();
//		MutexLockRelease(&lock);
//
// Now, while the condition is NOT satisfactory, the program releases
// the lock, pauses for a moment, and then reclaims the lock to re-test
// the condition. The question is, how long should the pause be? If it
// is very short, then the while loop may execute millions of times,
// wasting CPU time and slowing down everything else on the computer,
// including the thing that the while loop is waiting for. If the pause
// is too long, when the condition becomes true, the thread may be in
// the middle of a long pause and it may be a long time before it wakes
// up and "notices" that its condition is OK now. This is where condition
// variables come to the rescue:
//
//		MutexLockAcquire(&lock);
//		while (!(A && B || C && D && E ...)) ConditionVarWait(&cond);
//		do_stuff();
//		MutexLockRelease(&lock);
//
// Now, every time the program does anything that could change the truth
// of the condition (ie changing the value of A, B, C, D or E ...) it is
// required to signal this fact to the condition variable. What the
// ConditionVarWait call does is to release the lock and put the thread
// to sleep, waiting for this signal to arrive. When it arrives, the
// thread wakes up and retests the condition. The ConditionVarWait routine
// reaquires the lock before it returns to the caller, so the single call
// to ConditionVarWait replaces the entire { Release; Pause; Acquire; }
// sequence of the previous example.
//
// The ConditionVarSignal routine wakes up a single waiter, and the
// ConditionVarBroadcast routine wakes up all of them. If you know that
// the change you have made to the condition is such that ANY thread will
// be able to make use of it and proceed, then it is okay to just wake up
// one. If the change to the condition is such that some of the waiting
// threads may be able to make use of it and some may not (as in the
// "country bridge" example) then you MUST use ConditionVarBroadcast
// so that they all get a chance to take a look at the new values. If
// in doubt, use ConditionVarBroadcast exclusively.
//
// Before you can call ConditionVarWait, Signal or Broadcast, you must
// be holding the lock that was associated with the Condition variable
// when it was created (with ConditionVarInit). There are sound reasons
// for this even though they may not always be obvious every time
// (if you have variables that are changed in one thread and tested in
// another, then all accesses to those variables should be protected by
// a mutual exclusion lock). You may be tempted to cut corners with your
// locking in some cases, but it's not worth it. Multi-threaded code is
// hard enough to get right anyway, without inviting extra intermittent
// unrepeatable bugs which are almost impossible to find.
//
// Hint:
// There is no need to try to be to fancy with locking. Just have a small
// number of locks with fairly wide scope -- perhaps even just have a single
// lock with which to synchronize all shared state updates for your entire
// program. Threading is going to give your program such a huge performance
// win anyway that it is hardly worth struggling for that 10% extra
// efficiency if it is going to cause you ten times as many bugs. After
// the program is finished and running reliably you'll have time to
// worry about finding ways to improve performance even more.
//
//
// Semaphores are simple basic counting primitives. It is easiest to think of
// them counting some kind of abstract 'resource' which is in limited supply.
//
// Semaphores are not usually used directly -- they are the basis for
// Mutual exclusion locks and Condition variables described above.
//
// If a buffer has n spaces in it, you can initialize a semaphore to n
// to count the spaces. Each time you want to use a space in the buffer,
// call P(semaphore) and it will decrement the count. If the count is
// already zero, your thread will be stopped until the count increases
// above zero again. When you have finished with your space in the buffer,
// call V(semaphore) to increment the count and indicate that the resource
// is now available for someone else again. If there is another thread
// currently waiting in a P call, it will be woken up so that it can use
// the space which has become available.
//
// If you have a critical section of code, then a semaphore initialized
// to one can act as a mutual exclusion lock (because ONE thread is allowed
// to execute the code at a time).
//
// If you wish to signal from one thread to another, a semaphore initialized
// zero can achieve this (there is initially NO signal, until the signalling
// thread calls V(semaphore) to cause the signal to come into existence).
//
//
// One final note:
// Do NOT forcibly kill a thread with DisposeThread while it it waiting on a
// Semaphore, Mutual exclusion lock, or Condition variable. One deficiency of
// the current Thread Manager is that it has no provision to notify libraries
// (such as this one) when a thread they are managing is destroyed. If you
// destroy a thread that this library thinks it is in control of, then all
// hell will break loose when the deceased thread is woken up again.

#ifndef __THREADSYNCH__
#define __THREADSYNCH__

#include	"./MacThreads.h"

// *****************************************************************
// Semaphore. Operations: Init, Proben (test), Verhogen (increment)

typedef struct SemaphoreWaiter SemaphoreWaiter;
typedef struct
	{
	long value;
	SemaphoreWaiter *head;
	SemaphoreWaiter **tail;
	} Semaphore;

extern void SemaphoreInit(Semaphore *s, long initialvalue);
extern void SemaphoreP(Semaphore *s);
extern void SemaphoreV(Semaphore *s);

#define SemaphoreAcquire SemaphoreP
#define SemaphoreRelease SemaphoreV

// *****************************************************************
// MutexLock. Operations: Init, Acquire, Release

typedef struct
	{
	Semaphore sem;
	ThreadID lockholder;
	} MutexLock;

extern void MutexLockInit(MutexLock *m);
extern void MutexLockAcquire(MutexLock *m);
extern void MutexLockRelease(MutexLock *m);

// *****************************************************************
// ConditionVar. Operations: Init, Wait, Signal, Broadcast

typedef struct ConditionWaiter ConditionWaiter;
typedef struct
	{
	MutexLock       *lock;
	ConditionWaiter *head;
	ConditionWaiter **tail;
	} ConditionVar;

extern void ConditionVarInit(ConditionVar *c, MutexLock *lock);
extern void ConditionVarWait(ConditionVar *c);
extern void ConditionVarSignal(ConditionVar *c);
extern void ConditionVarBroadcast(ConditionVar *c);

#endif

