// test.c
//
// Copyright (C) 6th March 1994  Stuart Cheshire <cheshire@cs.stanford.edu>
//
// The program contains three tests of the Stu’s thread utils.
 
#include <stdio.h>
#include "ThreadSynch.h"
#include "PipeLine.h"

// *************************************************************************
// Test of pipeline routines
//
// This test has a number of producers concurrently writing into a single
// pipeline, and multiple consumers concurrently reading out of that
// pipeline and printing onto the console window.

#define BUFFER_SIZE 4
#define NUM_PRODUCERS 7
#define NUM_CONSUMERS 6
static const char message[] = "Hello world";

static unsigned char buffer[BUFFER_SIZE];
static PipeLine pipe;
static Semaphore threadwait;	// to wait for all threads to finish

static pascal void *producer(void *unused)
	{
	const char *ptr = message;
	while (*ptr) PipeLinePutData(&pipe, *ptr++);
	PipeLineClose(&pipe);
	return(NULL);
	}

static pascal void *consumer(void *unused)
	{
	int c;
	while ((c = PipeLineGetData(&pipe)) != NO_WRITERS) { putchar(c); fflush(stdout); }
	SemaphoreV(&threadwait);	// Signal that thread has finished
	return(NULL);
	}

static void pipetest(void)
	{
	int i;
	PipeLineInit(&pipe, buffer, sizeof(buffer));
	SemaphoreInit(&threadwait, 0);
	
	// Create a bunch of preemptive threads writing into the pipe
	for (i=0; i<NUM_PRODUCERS; i++)
		{
		PipeLineOpen(&pipe);
		if (NewThread(kPreemptiveThread, &producer, NULL, 0, 0, NULL, NULL) != noErr)
			ExitToShell();
		}

	// Create a bunch of cooperative threads reading from the pipe
	for (i=0; i<NUM_CONSUMERS; i++)
		if (NewThread(kCooperativeThread, &consumer, NULL, 0, 0, NULL, NULL) != noErr)
			ExitToShell();

	// Wait for all the readers to terminate
	for (i=0; i<NUM_CONSUMERS; i++) SemaphoreP(&threadwait);
	}

// *************************************************************************
// Test of Locks and Condition Variables
//
// This test models a country bridge, which is only wide enough to carry
// cars in one direction at a time, and only strong enough to carry three
// cars at a time. 25 cars arrive from each direction and have to wait until
// the conditions are safe for them to cross the bridge. It is a lightly
// travelled rural bridge, so enforcing strict queueing and fairness is not
// necessary. Simplicity and elegance of the code is more important.

#define NUM_CARS 25

static MutexLock lock;
static ConditionVar cond;
static int cars[2];

static void ArriveBridge(short direc)
	{
	short other_direction = 1 - direc;
	MutexLockAcquire(&lock);
	while (cars[direc] >= 3 || cars[other_direction] > 0) ConditionVarWait(&cond);
	cars[direc]++;
	if (direc) printf("            <-XXX\n"); else printf("XXX->\n");
	MutexLockRelease(&lock);
	YieldToAnyThread();		// Yield time while we drive onto bridge
	}

static void CrossBridge(short direc)
	{
	if (direc) printf("      <-XXX\n"); else printf("      XXX->\n");
	YieldToAnyThread();		// Yield time while we trundle over bridge
	}

static void ExitBridge(short direc)
	{
	YieldToAnyThread();		// Yield time while we drive off bridge
	MutexLockAcquire(&lock);
	if (direc) printf("<-XXX\n"); else printf("            XXX->\n");
	cars[direc]--;
	ConditionVarBroadcast(&cond);
	MutexLockRelease(&lock);
	}

static pascal void *OneVehicle(void *direc)
	{
	ArriveBridge((short)direc);
	CrossBridge((short)direc);
	ExitBridge((short)direc);
	SemaphoreV(&threadwait);	// Signal that thread has finished
	}

static pascal void *make_cars(void *direc)
	{
	int i,j;
	for (i=0; i<NUM_CARS; i++)
	    {
	    if (NewThread(kCooperativeThread, &OneVehicle, direc, 0, 0, NULL, NULL) != noErr)
			ExitToShell();
	    for (j=0; j<5; j++) YieldToAnyThread();
	    }
	}

static void condtest(void)
	{
	int i;
	MutexLockInit(&lock);
	ConditionVarInit(&cond, &lock);
	if (NewThread(kCooperativeThread, &make_cars, (void*)0, 0, 0, NULL, NULL) != noErr)
			ExitToShell();
	if (NewThread(kCooperativeThread, &make_cars, (void*)1, 0, 0, NULL, NULL) != noErr)
			ExitToShell();
	for (i=0; i<NUM_CARS*2; i++) SemaphoreP(&threadwait);
	}

// *************************************************************************
// Thread Manager speed test
//
// How long does it take your Mac to context switch from one thread to another?
// My Quadra 700 averages about 100us (microseconds) which is pretty good
// even compared to threads packages on high-end workstations.

#define SPEED_TESTS 5000
Semaphore speed1, speed2;

static pascal void *speedthread(void *unused)
	{
	int i;
	for (i=0; i<SPEED_TESTS; i++) { SemaphoreV(&speed1); SemaphoreP(&speed2); }
	}

static void speedtest(void)
	{
	int i;
	long time1, time;
	SemaphoreInit(&speed1, 0);
	SemaphoreInit(&speed2, 0);
    if (NewThread(kCooperativeThread, &speedthread, NULL, 0, kFPUNotNeeded, NULL, NULL) != noErr)
		ExitToShell();
	time1 = TickCount();
	for (i=0; i<SPEED_TESTS; i++) { SemaphoreP(&speed1); SemaphoreV(&speed2); }
	time = TickCount() - time1;
	printf("%d context switches took %ld.%03ld seconds\n",
		SPEED_TESTS*2, time/60, (time%60) * 16);
	}

// *************************************************************************
// main. It all starts here.

main()
	{
	// Call printf first to make sure ANSI segment gets loaded
	printf("Thread synchronization tests\n");

	printf("Pipeline test\n\n");
	pipetest();

	printf("\n\nCountry Bridge test\n\n");
	condtest();

	printf("\n\nContext switch speed test\n\n");
	speedtest();
	}
