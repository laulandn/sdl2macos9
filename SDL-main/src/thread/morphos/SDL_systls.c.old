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

#if SDL_THREAD_MORPHOS

#include <exec/execbase.h>
#include <proto/exec.h>
#define AROS_ALMOST_COMPATIBLE 1
#include <exec/lists.h>

#include "../SDL_thread_c.h"
#undef D
#define D(fmt, ...) ({((STRPTR (*)(void *, CONST_STRPTR , APTR (*)(APTR, UBYTE), STRPTR , ...))*(void**)((long)(*((APTR *)4)) - 922))((void*)(*((APTR *)4)), fmt, (APTR)1, NULL, ##__VA_ARGS__);})

#define TLS_MAGICID "SDL2TLS"

struct tlsmagic
{
	UBYTE	magicid[sizeof(TLS_MAGICID)];
	APTR	tlsptr;
};

SDL_TLSData *
SDL_SYS_GetTLSData()
{
	struct MemList *ml;

	ForeachNode(&SysBase->ThisTask->tc_MemEntry, ml) {
		if (ml->ml_NumEntries == 1 &&
		    ml->ml_Node.ln_Name == (char *) ml->ml_ME[0].me_Addr &&
		    !strcmp(ml->ml_Node.ln_Name, TLS_MAGICID)) {
			struct tlsmagic *tm = ml->ml_ME[0].me_Addr;
			return tm->tlsptr;
		}
	}

	return NULL;
}

static const struct MemList stml = {{0,0,0,0,0}, 1, {{{MEMF_ANY}, sizeof(struct tlsmagic)}}};

int
SDL_SYS_SetTLSData(SDL_TLSData *data)
{
	struct Task *t = SysBase->ThisTask;
	struct MemList *ml;
	struct tlsmagic *tm;

	ForeachNode(&t->tc_MemEntry, ml) {
		if (ml->ml_NumEntries == 1 &&
		    ml->ml_Node.ln_Name == (char *) ml->ml_ME[0].me_Addr &&
		    !strcmp(ml->ml_Node.ln_Name, TLS_MAGICID)) {
			tm = ml->ml_ME[0].me_Addr;
			tm->tlsptr = data;
			return 0;
		}
	}

	ml = AllocEntry((struct MemList *) &stml);
	if ((ULONG) ml & 0x80000000)
		return 1;

	tm = ml->ml_ME[0].me_Addr;
	ml->ml_Node.ln_Name = tm->magicid;
	memcpy(tm->magicid, TLS_MAGICID, sizeof(TLS_MAGICID));
	tm->tlsptr = data;
	ADDHEAD(&t->tc_MemEntry, &ml->ml_Node);
	return 0;
}

#endif /* SDL_THREAD_MORPHOS */

/* vi: set ts=4 sw=4 expandtab: */
