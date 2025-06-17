/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

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

#if defined(SDL_TIMER_MORPHOS) || defined(SDL_TIMERS_DISABLED)

#include "SDL_timer.h"

#include <exec/execbase.h>
#include <proto/exec.h>
#include <proto/timer.h>

extern struct timerequest GlobalTimeReq;

static SDL_bool ticks_started = SDL_FALSE;
static struct timeval basetime;

void
SDL_TicksInit(void)
{
	if (ticks_started)
		return;

	ticks_started = SDL_TRUE;
	GetSysTime(&basetime);
}

void
SDL_TicksQuit(void)
{
	ticks_started = SDL_FALSE;
}

Uint64
SDL_GetTicks64(void)
{
	struct timeval tv;

	if (!ticks_started)
		SDL_TicksInit();

	GetSysTime(&tv);

	if (basetime.tv_micro > tv.tv_micro) {
		tv.tv_secs--;
		tv.tv_micro += 1000000;
	}

	return (Uint64)((tv.tv_secs - basetime.tv_secs) * 1000) + ((tv.tv_micro - basetime.tv_micro)/1000);
}

Uint64
SDL_GetPerformanceCounter(void)
{
	Uint64 val;
	ReadCPUClock(&val);
	return val;
}

Uint64
SDL_GetPerformanceFrequency(void)
{
	Uint64 val;
	return ReadCPUClock(&val);
}

void
InitQPort(struct MsgPort *port)
{
	port->mp_SigBit = SIGB_SINGLE;
	port->mp_Flags = PA_SIGNAL;
	port->mp_SigTask = SysBase->ThisTask;
	NEWLIST(&port->mp_MsgList);
}

void
SDL_Delay(Uint32 ms)
{
	struct timerequest req;
	struct MsgPort port;

	InitQPort(&port);

	req.tr_node.io_Message.mn_Node.ln_Type = 0;
	req.tr_node.io_Message.mn_ReplyPort = &port;
	req.tr_node.io_Device = GlobalTimeReq.tr_node.io_Device;
	req.tr_node.io_Unit = GlobalTimeReq.tr_node.io_Unit;
	req.tr_node.io_Command = TR_ADDREQUEST;
	req.tr_time.tv_secs = ms / 1000;
	req.tr_time.tv_micro = (ms % 1000) * 1000;

	DoIO((struct IORequest *)&req);
}

#endif /* SDL_TIMER_MORPHOS || SDL_TIMERS_DISABLED */
