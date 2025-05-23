/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

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

#ifndef SDL_os4library_h_
#define SDL_os4library_h_

#include <exec/types.h>

extern void OS4_INIT(void) __attribute__((constructor(101)));
extern void OS4_QUIT(void) __attribute__((destructor(101)));

// A couple of helper functions for dealing with AmigaOS libraries

extern struct Library * OS4_OpenLibrary(STRPTR name, ULONG version);

extern struct Interface * OS4_GetInterface(struct Library * lib);

extern void OS4_DropInterface(struct Interface ** interface);

extern void OS4_CloseLibrary(struct Library ** library);

#endif
