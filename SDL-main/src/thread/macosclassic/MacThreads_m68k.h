/*
 	File:		Threads.h
 
 	Copyright:	© 1984-1994 by Apple Computer, Inc.
 				All rights reserved.
 
 	Version:	Universal Interfaces 2.0a3  ETO #16, MPW prerelease.  Friday, November 11, 1994. 
 
 	Bugs?:		If you find a problem with this file, send the file and version
 				information (from above) and the problem description to:
 
 					Internet:	apple.bugs@applelink.apple.com
 					AppleLink:	APPLE.BUGS
 
*/

#ifndef __THREADS__
#define __THREADS__


#ifndef __ERRORS__
#include <Errors.h>
#endif
/*	#include <ConditionalMacros.h>								*/

#ifndef __MEMORY__
#include <Memory.h>
#endif
/*	#include <Types.h>											*/
/*	#include <MixedMode.h>										*/

#ifdef __cplusplus
extern "C" {
#endif

#if GENERATINGPOWERPC
#pragma options align=mac68k
#endif

#ifdef __CFM68K__
#pragma lib_export on
#endif

typedef unsigned short ThreadState;


enum {
	kReadyThreadState			= 0,
	kStoppedThreadState			= 1,
	kRunningThreadState			= 2
};

/* Error codes have been meoved to Errors.(pah) */
/* Thread environment characteristics */
typedef void *ThreadTaskRef;

/* Thread characteristics */
typedef unsigned long ThreadStyle;


enum {
	kCooperativeThread			= 1L << 0,
	kPreemptiveThread			= 1L << 1
};

/* Thread identifiers */
typedef unsigned long ThreadID;


enum {
	kNoThreadID					= 0,
	kCurrentThreadID			= 1,
	kApplicationThreadID		= 2
};

/* Options when creating a thread */
typedef unsigned long ThreadOptions;


enum {
	kNewSuspend					= (1 << 0),
	kUsePremadeThread			= (1 << 1),
	kCreateIfNeeded				= (1 << 2),
	kFPUNotNeeded				= (1 << 3),
	kExactMatchThread			= (1 << 4)
};

/* Information supplied to the custom scheduler */
struct SchedulerInfoRec {
	unsigned long					InfoRecSize;
	ThreadID						CurrentThreadID;
	ThreadID						SuggestedThreadID;
	ThreadID						InterruptedCoopThreadID;
};
typedef struct SchedulerInfoRec SchedulerInfoRec;

typedef SchedulerInfoRec *SchedulerInfoRecPtr;

/*
	The following ProcPtrs cannot be interchanged with UniversalProcPtrs because
	of differences between 680x0 and PowerPC runtime architectures with regard to
	the implementation of the Thread Manager.
 */
/* Prototype for thread's entry (main) routine */
typedef void *voidPtr;

typedef pascal voidPtr (*ThreadEntryProcPtr)(void *threadParam);
/* Prototype for custom thread scheduler routine */
typedef pascal ThreadID (*ThreadSchedulerProcPtr)(SchedulerInfoRecPtr schedulerInfo);
/* Prototype for custom thread switcher routine */
typedef pascal void (*ThreadSwitchProcPtr)(ThreadID threadBeingSwitched, void *switchProcParam);
/* Prototype for thread termination notification routine */
typedef pascal void (*ThreadTerminationProcPtr)(ThreadID threadTerminated, void *terminationProcParam);
/* Prototype for debugger NewThread notification */
typedef pascal void (*DebuggerNewThreadProcPtr)(ThreadID threadCreated);
/* Prototype for debugger DisposeThread notification */
typedef pascal void (*DebuggerDisposeThreadProcPtr)(ThreadID threadDeleted);
/* Prototype for debugger schedule notification */
typedef pascal ThreadID (*DebuggerThreadSchedulerProcPtr)(SchedulerInfoRecPtr schedulerInfo);
/* Thread Manager routines */
extern pascal OSErr CreateThreadPool(ThreadStyle threadStyle, short numToCreate, Size stackSize)
 THREEWORDINLINE(0x303C, 0x0501, 0xABF2);
extern pascal OSErr GetFreeThreadCount(ThreadStyle threadStyle, short *freeCount)
 THREEWORDINLINE(0x303C, 0x0402, 0xABF2);
extern pascal OSErr GetSpecificFreeThreadCount(ThreadStyle threadStyle, Size stackSize, short *freeCount)
 THREEWORDINLINE(0x303C, 0x0615, 0xABF2);
extern pascal OSErr GetDefaultThreadStackSize(ThreadStyle threadStyle, Size *stackSize)
 THREEWORDINLINE(0x303C, 0x0413, 0xABF2);
extern pascal OSErr ThreadCurrentStackSpace(ThreadID thread, unsigned long *freeStack)
 THREEWORDINLINE(0x303C, 0x0414, 0xABF2);
extern pascal OSErr NewThread(ThreadStyle threadStyle, ThreadEntryProcPtr threadEntry, void *threadParam, Size stackSize, ThreadOptions options, void **threadResult, ThreadID *threadMade)
 THREEWORDINLINE(0x303C, 0x0E03, 0xABF2);
extern pascal OSErr DisposeThread(ThreadID threadToDump, void *threadResult, Boolean recycleThread)
 THREEWORDINLINE(0x303C, 0x0504, 0xABF2);
extern pascal OSErr YieldToThread(ThreadID suggestedThread)
 THREEWORDINLINE(0x303C, 0x0205, 0xABF2);
extern pascal OSErr YieldToAnyThread(void)
 FOURWORDINLINE(0x42A7, 0x303C, 0x0205, 0xABF2);
extern pascal OSErr GetCurrentThread(ThreadID *currentThreadID)
 THREEWORDINLINE(0x303C, 0x0206, 0xABF2);
extern pascal OSErr GetThreadState(ThreadID threadToGet, ThreadState *threadState)
 THREEWORDINLINE(0x303C, 0x0407, 0xABF2);
extern pascal OSErr SetThreadState(ThreadID threadToSet, ThreadState newState, ThreadID suggestedThread)
 THREEWORDINLINE(0x303C, 0x0508, 0xABF2);
extern pascal OSErr SetThreadStateEndCritical(ThreadID threadToSet, ThreadState newState, ThreadID suggestedThread)
 THREEWORDINLINE(0x303C, 0x0512, 0xABF2);
extern pascal OSErr SetThreadScheduler(ThreadSchedulerProcPtr threadScheduler)
 THREEWORDINLINE(0x303C, 0x0209, 0xABF2);
extern pascal OSErr SetThreadSwitcher(ThreadID thread, ThreadSwitchProcPtr threadSwitcher, void *switchProcParam, Boolean inOrOut)
 THREEWORDINLINE(0x303C, 0x070A, 0xABF2);
extern pascal OSErr SetThreadTerminator(ThreadID thread, ThreadTerminationProcPtr threadTerminator, void *terminationProcParam)
 THREEWORDINLINE(0x303C, 0x0611, 0xABF2);
extern pascal OSErr ThreadBeginCritical(void)
 THREEWORDINLINE(0x303C, 0x000B, 0xABF2);
extern pascal OSErr ThreadEndCritical(void)
 THREEWORDINLINE(0x303C, 0x000C, 0xABF2);
extern pascal OSErr SetDebuggerNotificationProcs(DebuggerNewThreadProcPtr notifyNewThread, DebuggerDisposeThreadProcPtr notifyDisposeThread, DebuggerThreadSchedulerProcPtr notifyThreadScheduler)
 THREEWORDINLINE(0x303C, 0x060D, 0xABF2);
extern pascal OSErr GetThreadCurrentTaskRef(ThreadTaskRef *threadTRef)
 THREEWORDINLINE(0x303C, 0x020E, 0xABF2);
extern pascal OSErr GetThreadStateGivenTaskRef(ThreadTaskRef threadTRef, ThreadID threadToGet, ThreadState *threadState)
 THREEWORDINLINE(0x303C, 0x060F, 0xABF2);
extern pascal OSErr SetThreadReadyGivenTaskRef(ThreadTaskRef threadTRef, ThreadID threadToSet)
 THREEWORDINLINE(0x303C, 0x0410, 0xABF2);

#ifdef __CFM68K__
#pragma lib_export off
#endif

#if GENERATINGPOWERPC
#pragma options align=reset
#endif

#ifdef __cplusplus
}
#endif

#endif /* __THREADS__ */
