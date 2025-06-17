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

#ifndef _SDL_mosvideo_h
#define _SDL_mosvideo_h

#include "SDL_keycode.h"

#include "../SDL_sysvideo.h"
#include "../../events/SDL_mouse_c.h"

#include "SDL_mosclipboard.h"
#include "SDL_moswindow.h"

#ifndef EXEC_PORTS_H
#include <exec/ports.h>
#endif

#ifndef LIBRARIES_COMMODITIES_H
#include <libraries/commodities.h>
#endif

/* Private display data */

struct DiskObject;

typedef struct SDL_VideoData
{
	struct MsgPort ScreenNotifyPort;
	struct MsgPort BrokerPort;
	struct MsgPort WBPort;
	struct MsgPort WinPort;

	size_t ScrNotifySig, BrokerSig, WBSig, WinSig;

	struct Screen *WScreen;
	struct Screen *CustomScreen;

	struct MinList windowlist;

	SDL_Cursor *CurrentPointer;
	ULONG sdlpixfmt;

	ULONG coltab[256];
	UBYTE gammatable[3][256];

	LONG ScreenSaverSuspendCount;

	APTR ScreenNotifyHandle;

	CONST_STRPTR FullAppName;
	struct DiskObject *AppIcon;

	APTR AppIconRef;
	APTR BrokerRef;

	struct NewBroker AppBroker;

	// Screen information
	size_t ScrWidth, ScrHeight, ScrDepth;
	CONST_STRPTR ScrMonName;

	SDL_VideoDevice *VideoDevice;

	BYTE FullScreen;
	BYTE vsyncEnabled;
	
} SDL_VideoData;

/* SDL functions */
extern void MOS_CloseDisplay(_THIS);
extern void MOS_HideApp(_THIS, size_t with_app_icon);
extern void MOS_ShowApp(_THIS);

/* Non-SDL functions */
extern size_t getv(APTR obj, size_t attr);

#endif /* _SDL_mosvideo_h */
