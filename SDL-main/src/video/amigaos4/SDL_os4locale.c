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

#if SDL_VIDEO_DRIVER_AMIGAOS4

#include <proto/dos.h>
#include <proto/locale.h>

#include "SDL_os4locale.h"
#include "../../main/amigaos4/SDL_os4debug.h"

#define CATCOMP_CODE
#define CATCOMP_BLOCK
#include "../../../amiga-extra/locale_generated.h"

static struct Locale* locale;
static struct Catalog* catalog;
static struct LocaleInfo localeInfo;

BOOL OS4_InitLocale(void)
{
    if (ILocale) {
        localeInfo.li_ILocale = ILocale;

        locale = ILocale->OpenLocale(NULL);
        if (locale) {
            //dprintf("%s\n", locale->loc_LanguageName);
            catalog = ILocale->OpenCatalog(NULL, "sdl2.catalog",
                                           TAG_DONE);
            if (!catalog) {
                const LONG err = IDOS->IoErr();
                if (err != 0) {
                    dprintf("Failed to open catalog (%ld)\n", err);
                }
            }
            localeInfo.li_Catalog = catalog;
            return TRUE;
        } else {
            dprintf("Failed to open locale\n");
        }
    }

    return FALSE;
}

void OS4_QuitLocale(void)
{
    if (ILocale) {
        if (catalog) {
            ILocale->CloseCatalog(catalog);
            catalog = NULL;
            localeInfo.li_Catalog = NULL;
        }

        if (locale) {
            ILocale->CloseLocale(locale);
            locale = NULL;
        }
    }
}

CONST_STRPTR OS4_GetString(LONG stringNum)
{
    CONST_STRPTR str = GetStringGenerated(&localeInfo, stringNum);
    if (str == NULL) {
        dprintf("Locale string num %ld missing\n", stringNum);
        return "missing";
    }

    return str;
}

#endif /* SDL_VIDEO_DRIVER_AMIGAOS4 */

/* vi: set ts=4 sw=4 expandtab: */

