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

#ifndef _SDL_mosmouse_h
#define _SDL_mosmouse_h

#include "SDL_mosvideo.h"
#include <proto/intuition.h>

#define IS_SYSTEM_CURSOR(cursor) (cursor == NULL || ((size_t)(cursor)->driverdata) < POINTERTYPE_NUMTYPES)

struct SDL_MOSPointerData
{
	Object *mouseptr;
	int offx, offy;
};

typedef struct
{
	struct SDL_Cursor Cursor;
	struct SDL_MOSPointerData Pointer;
} SDL_MOSCursor;

typedef struct MOS_GlobalMouseState
{
    int x;
    int y;
    int buttonPressed[SDL_BUTTON_X1 + 1];
} MOS_GlobalMouseState;

extern void MOS_InitMouse(_THIS);
extern void MOS_QuitMouse(_THIS);

#endif /* _SDL_mosmouse_h */
