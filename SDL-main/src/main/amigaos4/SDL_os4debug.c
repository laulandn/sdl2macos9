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

#include "SDL_os4debug.h"

#include <proto/exec.h>

#include <stdio.h>
#include <stdarg.h>

extern struct Interface* INewlib;

void OS4_DebugPrintF(const char* const fmt, ...)
{
    if (!INewlib) {
        IExec->DebugPrintF("INewlib nullptr\n");
        return;
    }

    va_list ap;
    va_start(ap, fmt);

    char buffer[1024];

    const int ret = vsnprintf(buffer, sizeof(buffer), fmt, ap);

    if (ret < 0) {
        IExec->DebugPrintF("vsnprintf returned %d\n", ret);
    } else {
        IExec->DebugPrintF("%s", buffer);
    }

    va_end(ap);
}


