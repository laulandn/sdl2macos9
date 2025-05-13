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
#include "../SDL_syslocale.h"
//#include "../../main/amigaos4/SDL_os4debug.h"

//#include <proto/exec.h>
//#include <proto/locale.h>

void
SDL_SYS_GetPreferredLocales(char *buf, size_t buflen)
{
    snprintf(buf, buflen, "en_GB, en");

#if 0 // TODO: improve this later.
    struct Library* LocaleBase = IExec->OpenLibrary("locale.library", 53);

    if (LocaleBase) {
        struct LocaleIFace* ILocale = (struct LocaleIFace*)IExec->GetInterface(LocaleBase, "main", 1, NULL);

        if (ILocale) {
            struct Locale* locale = ILocale->OpenLocale(NULL);
            if (locale) {
                for (int i = 0; i < 10; i++) {
                    if (locale->loc_PrefLanguages[i]) {
                        printf("%s\n", locale->loc_PrefLanguages[i]);
                    }
                }
            } else {
                dprintf("Failed to open locale\n");
            }

            IExec->DropInterface((struct Interface*)ILocale);
        } else {
            dprintf("Failed to get locale interface\n");
        }

        IExec->CloseLibrary(LocaleBase);
    } else {
        dprintf("Failed to open locale.library\n");
    }
#endif
}

/* vi: set ts=4 sw=4 expandtab: */

