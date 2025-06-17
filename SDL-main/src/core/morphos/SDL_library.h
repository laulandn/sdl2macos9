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

#ifndef SDL_CORE_MORPHOS_LIBRARY_H
#define SDL_CORE_MORPHOS_LIBRARY_H

#include "../../SDL_internal.h"

#ifndef DOS_DOS_H
#include <dos/dos.h>
#endif

#ifndef EXEC_LIBRARIES_H
#include <exec/libraries.h>
#endif

#ifndef EXEC_SEMAPHORES_H
#include <exec/semaphores.h>
#endif

#define SAVEDS __saveds

#if defined(__PPC__)
#define __TEXTSEGMENT__ __attribute__((section(".text")))
#endif

struct CTDT
{
	int	(*fp)(void);
	long	priority;
};

struct HunkSegment
{
	unsigned int Size;
	struct HunkSegment *Next;
};

struct TaskNode
{
	struct MinNode Node;
	struct Task *Task;
};

struct SDL_Library
{
	struct Library Library;
	UWORD          Alloc;
	APTR           DataSeg;	   /* DON'T CHANGE POSITION */

	ULONG                  DataSize;
	struct SDL_Library    *Parent;
	BPTR                   SegList;
	struct ExecBase       *MySysBase;
	struct DosLibrary     *MyDOSBase;
	struct IntuitionBase  *MyIntuiBase;
	struct GfxBase        *MyGfxBase;
	struct Library        *MyCyberGfxBase;
	struct Library        *MyKeymapBase;
	struct Library        *MyWorkbenchBase;
	struct Library        *MyIconBase;
	struct Library        *MyMUIMasterBase;
	struct Library        *MyCxBase;
	struct Library        *MyScreenNotifyBase;
	APTR                   tglcontext;
	struct Library       **MyTinyGLBase;
	void                 **MyGLContext;
	unsigned int		 (*MyGetMaximumContextVersion)(struct Library *TinGLBase);

	union
	{
		struct MinList TaskList;
		struct TaskNode TaskNode;
	} TaskContext;

	// library management

	struct SignalSemaphore Semaphore;
	APTR ctdtlist;
	APTR last_ctdt;
};

extern BYTE HasAltiVec;

#endif /* SDL_CORE_MORPHOS_LIBRARY_H */
