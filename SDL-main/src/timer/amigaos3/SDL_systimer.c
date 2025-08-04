/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org


	20040210	atexit(close_timer) removed
			static struct definitions removed

	20040208	extern struct GfxBase removed

*/
#include <SDL_config.h>

#ifdef SDL_TIMER_AMIGAOS3

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_systimer.c,v 1.4 2008/09/29 20:54:05 r� Exp $";
#endif

#include <SDL.h>
#include <devices/timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <exec/execbase.h>

//#include <clib/alib_protos.h>
#ifdef MORPHOS
#include <ppcinline/dos.h>
#include <ppcinline/exec.h>
#include <ppcinline/graphics.h>
#else

#include <proto/dos.h>
#include <inline/dos.h>
#include <inline/exec.h>
#include <inline/graphics.h>

#endif

//#include "../../mydebug.h"

#include "SDL_error.h"
#include "SDL_timer.h"
#include "../SDL_timer_c.h"

#if defined(DISABLE_THREADS) || defined(FORK_HACK)
#define USE_ITIMER
#endif

/* The first ticks value of the application */

#ifdef MORPHOS
#include <ppcinline/timer.h>
#else

#include <inline/timer.h>

#endif

extern struct ExecBase *SysBase;

static struct timeval basetime;
struct Library *TimerBase;

struct Task *OwnerTask;
struct timerequest *TimerReq[2];         /* Local copy! */
unsigned long ticks;

ULONG SDL_timer_running=0;

static SDL_bool ticks_started = SDL_FALSE;

void SDL_TicksInit(void)
{
#ifdef USE_MICROSECONDS
        UnsignedWide now;

        Microseconds(&now);
        start = WideTo64bit(now);
#else
        /* FIXME: Should we implement a wrapping algorithm, like Win32? */
#endif
    if (ticks_started) {
        return;
    }
    ticks_started = SDL_TRUE;
}

void SDL_TicksQuit(void)
{
    ticks_started = SDL_FALSE;
}

void delete_timer(struct timerequest *tr) {
	struct MsgPort *tp;

	SDL_timer_running--; // TODO: Maybe not right
	if ( tr != 0 ) {
		tp = tr->tr_node.io_Message.mn_ReplyPort;

		if ( tp != 0 ) DeleteMsgPort(tp);

		CloseDevice((struct IORequest *)tr);
		DeleteIORequest((struct IORequest *)tr);
	}
}

struct timerequest *create_timer(ULONG unit) {
	/* return a pointer to a timer request.  If any problem, return NULL */
	LONG error;
	struct MsgPort *timerport;
	struct timerequest *TimerIO;

	SDL_timer_running++; // TODO: Maybe not right
	timerport = CreateMsgPort();
	if ( timerport == NULL )
		return (NULL);

	TimerIO = (struct timerequest *)
			CreateIORequest(timerport, sizeof(struct timerequest));

	if ( TimerIO == NULL ) {
		DeleteMsgPort(timerport);   /* Delete message port */
		return (NULL);
	}

	error = 0;
	error = OpenDevice((CONST_STRPTR)TIMERNAME, unit, (struct IORequest *)TimerIO, 0L);
	//see powersdl source

	//TimerIO->tr_node.io_Device                  = TimerReq[0]->tr_node.io_Device;
	//TimerIO->tr_node.io_Unit                    = TimerReq[0]->tr_node.io_Unit;

	if ( error != 0 ) {
		fprintf(stderr,"Can't open timer device\n"); fflush(stderr);

		delete_timer(TimerIO);
		return (NULL);
	}

	return (TimerIO);
}

/* more precise timer than AmigaDOS Delay() */
void wait_for_timer(struct timerequest *tr, struct timeval *tv) {
	tr->tr_node.io_Command = TR_ADDREQUEST; /* add a new timer request */

	/* structure assignment */
	tr->tr_time = *tv;

	/* post request to the timer -- will go to sleep till done */
	DoIO((struct IORequest *)tr);
}

LONG time_delay(struct timeval *tv, LONG unit) {
	struct timerequest *tr;
	/* get a pointer to an initialized timer request block */
	tr = create_timer(unit);

	/* any nonzero return says timedelay routine didn't work. */
	if ( tr == NULL )
		return (-1L);

	wait_for_timer(tr, tv);

	/* deallocate temporary structures */
	delete_timer(tr);
	return (0L);
}

struct timerequest *TimerIO_2;
struct MsgPort *TimerMP_2;

int gettimerbase() {
	long error;
	atexit(SDL_Quit);
	if ( TimerMP_2 = CreateMsgPort()) {
		if ( TimerIO_2 = (struct timerequest *)CreateIORequest(TimerMP_2, sizeof(struct timerequest))) {
			/* Open with UNIT_VBLANK, but any unit can be used */
			if ( !(error = OpenDevice((CONST_STRPTR)TIMERNAME, UNIT_MICROHZ, (struct IORequest *)TimerIO_2, 0L))) {
				/* Issue the command and wait for it to finish, then get the reply */
				TimerBase = (struct Library *)TimerIO_2->tr_node.io_Device;

				TimerReq[0] = TimerIO_2;
				TimerReq[1] = TimerIO_2;
				/* Close the timer device */
				//CloseDevice((struct IORequest *) TimerIO_2);
			} 
			else {
				fprintf(stderr,"Error: Could not open timer device\n"); fflush(stderr);
		       	}

			/* Delete the IORequest structure */
			//DeleteIORequest(TimerIO_2);
		} 
		else {
			fprintf(stderr,"Error: Could not create I/O structure\n"); fflush(stderr);
		}

		/* Delete the port */
		//DeleteMsgPort(TimerMP_2);
	}
	return 0;
}

void SDL_StartTicks(void) {
	if ( !TimerBase )gettimerbase();
	GetSysTime(&basetime);
}

//#define ECLOCK

Uint64 SDL_GetTicks64(void) {
#ifdef ECLOCK
	struct EClockVal time1;
	long efreq;
	long long eval;
#endif
	struct timeval tv;
	Uint64 ticks1;

	if ( !TimerBase )gettimerbase();

#ifndef ECLOCK
	GetSysTime(&tv);
	if ( basetime.tv_micro > tv.tv_micro ) {
		tv.tv_secs--;

		tv.tv_micro += 1000000;
	}

	ticks1 = ((tv.tv_secs - basetime.tv_secs) * 1000) + ((tv.tv_micro - basetime.tv_micro) / 1000);
#else
	efreq = ReadEClock(&time1);
	eval = time1.ev_lo;
	eval +=(time1.ev_hi << 32);
	ticks1 = eval /(efreq/1000);
#endif

	return ticks1;
}

void SDL_Delay(Uint32 ms) {
	struct timeval tv;

	if ( ms == 0 ) return;

	if ( ms & 0xff000000 ) return; //time to large
	tv.tv_secs = ms / 1000;
	tv.tv_micro = (ms % 1000) * 1000;

	time_delay(&tv, UNIT_MICROHZ);
}

#include "SDL_thread.h"

/* Data to handle a single periodic alarm */
static int timer_alive = 0;
static SDL_Thread *timer_thread = NULL;
struct Library *TimerBase;

int RunTimer(void *unused) {
	struct timeval tv;
	struct timerequest *tr;
	unsigned long threadid;
	fprintf(stderr,"SYSTimer: Entering RunTimer loop..."); fflush(stderr);
	threadid = SDL_ThreadID();
	SetTaskPri((struct Task *)threadid, 4);

	/* get a pointer to an initialized timer request block */
	tr = create_timer(UNIT_MICROHZ);

	/* any nonzero return says timedelay routine didn't work. */
	if ( tr == NULL )
		return (-1L);

	/* deallocate temporary structures */

	while ( timer_alive ) {
		//ULONG running = SDL_timer_running;

		tv.tv_secs = 0;
		tv.tv_micro = 4000;

		wait_for_timer(tr, &tv);
		//time_delay(&tv, UNIT_MICROHZ );

		//if ( running ) SDL_ThreadedTimerCheck();

	}

	fprintf(stderr,"SYSTimer: EXITING RunTimer loop..."); fflush(stderr);

	delete_timer(tr);
	return 0;
}

/* This is only called if the event thread is not running */
int SDL_SYS_TimerInit(void) {
	fprintf(stderr,"Creating thread for the timer (NOITIMER)...\n"); fflush(stderr);

	timer_alive = 1;
	timer_thread = SDL_CreateThread(RunTimer, "Timer Thread",NULL);
	if ( timer_thread == NULL ) {
		fprintf(stderr,"Thread creation failed...\n"); fflush(stderr);

		return (-1);
	}

	//return (SDL_SetTimerThreaded(1));
	return 0;  // TODO: Maybe not right
}

void SDL_SYS_TimerQuit(void) {
	timer_alive = 0;
	if ( timer_thread ) {
		SDL_WaitThread(timer_thread, NULL);
		timer_thread = NULL;
	}

	fprintf(stderr,"SYS_TimerQuit\n"); fflush(stderr);
}

void amiga_quit_timer(void) //called at end of sdl program from sdl.c
{
	if ( TimerIO_2 ) {
		CloseDevice((struct IORequest *)TimerIO_2);
		DeleteIORequest(TimerIO_2);
		DeleteMsgPort(TimerMP_2);
		TimerIO_2 = 0;
	}
}

int SDL_SYS_StartTimer(void) {
	SDL_SetError("Internal logic error: AmigaOS uses threaded timer");
	return -1;
}

void SDL_SYS_StopTimer(void) {
	return;
}

Uint64 SDL_GetPerformanceCounter(void)
{
    return SDL_GetTicks();
}

Uint64 SDL_GetPerformanceFrequency(void)
{
    // NOTE: This is completely arbitrary and made up
    return 1000;
}

#endif
