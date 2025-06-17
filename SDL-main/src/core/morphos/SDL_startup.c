/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

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

#define USE_INLINE_STDARG

#include <libraries/threadpool.h>
#include <proto/threadpool.h>

#include "SDL_library.h"

/*********************************************************************/
struct SDL_Library *SDL2Base;
struct Library *TinyGLBase;
	
int ThisRequiresConstructorHandling = 0;

/* This function must preserve all registers except r13 */
asm
("\n"
"	.section \".text\"\n"
"	.align 2\n"
"	.type __restore_r13, @function\n"
"__restore_r13:\n"
"	lwz 13, 36(3)\n"
"	blr\n"
"__end__restore_r13:\n"
"	.size __restore_r13, __end__restore_r13 - __restore_r13\n"
);

APTR threadpool;
APTR libnix_mempool;

/**********************************************************************
	Startup/Cleanup
**********************************************************************/

int SAVEDS MOS_Startup(struct SDL_Library *LibBase)
{
	struct CTDT *ctdt = LibBase->ctdtlist, *last_ctdt = LibBase->last_ctdt;

	SDL2Base = (struct SDL_Library*)&LibBase->Library;
	
	threadpool = CreateThreadPoolTags(32768, THREADPOOL_Name, (size_t)"SDL2", THREADPOOL_DataSegment, (size_t)LibBase->DataSeg, TAG_DONE);

	if (threadpool == NULL)
		return 0;

	// Run constructors
	while (ctdt < last_ctdt)
	{
		if (ctdt->priority >= 0)
		{
			if (ctdt->fp() != 0)
				return 0;
		}

		ctdt++;
	}

	return 1;
}

VOID SAVEDS MOS_Cleanup(struct SDL_Library *LibBase)
{
	extern void SDL_Quit_REAL();
	struct CTDT *ctdt = LibBase->ctdtlist, *last_ctdt = LibBase->last_ctdt;

	SDL_Quit_REAL();

	if (threadpool)
		DeleteThreadPool(threadpool);

	// Run destructors
	while (ctdt < last_ctdt)
	{
		if (ctdt->priority < 0)
		{
			if (ctdt->fp != (int (*)(void)) -1)
			{
				ctdt->fp();
			}
		}

		ctdt++;
	}
}

/**********************************************************************
	Library setup
**********************************************************************/

void (*morphos_exit)(int exitcode);

void __saveds LIB_SetExitPointer(struct SDL_Library *base, void (*exitfunc)(int))
{
	morphos_exit = exitfunc;
}

/**********************************************************************
	LIB_InitTGL

	Called from auto-open library only
**********************************************************************/

VOID LIB_InitTGL(struct SDL_Library *base, void **glc, struct Library **tgl)
{
	if (base->MyTinyGLBase == NULL)
	{
		base->MyTinyGLBase = tgl;
		base->MyGLContext  = glc;
	}
}

VOID LIB_InitTGL2(struct SDL_Library *base, void **glc, struct Library **tgl, unsigned int (*getmaximumcontextversion)(struct Library *TinyGLBase))
{
	if (base->MyTinyGLBase == NULL)
	{
		base->MyTinyGLBase = tgl;
		base->MyGLContext = glc;
		base->MyGetMaximumContextVersion = getmaximumcontextversion;
	}
}


void __chkabort(void) { }
