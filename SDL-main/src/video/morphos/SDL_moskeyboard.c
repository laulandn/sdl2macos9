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

#include "../SDL_sysvideo.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/scancodes_morphos.h"

#include <proto/keymap.h>

static SDL_Keycode MOS_MapRawKey(UWORD code)
{
    struct InputEvent ie;
    char buffer[2] = {0, 0};

    ie.ie_Class = IECLASS_RAWKEY;
    ie.ie_SubClass = 0;
    ie.ie_Code = code;
    ie.ie_Qualifier = 0;
    ie.ie_EventAddress = NULL;

    const WORD res = MapRawKey(&ie, buffer, sizeof(buffer), NULL);
    if (res == 1)
    {
        return buffer[0];
    }

    D("[%s](code %u) returned %d\n", __FUNCTION__, code, res);
    return 0;
}

static void MOS_UpdateKeymap(_THIS)
{
    SDL_Keycode keymap[SDL_NUM_SCANCODES];

    SDL_GetDefaultKeymap(keymap);

    for (int i = 0; i < SDL_arraysize(morphos_scancode_table); i++) {
        /* Make sure this scancode is a valid character scancode */
        const SDL_Scancode scancode  = morphos_scancode_table[i];
        if (scancode == SDL_SCANCODE_UNKNOWN)
            continue;

        /* If this key is one of the non-mappable keys, ignore it */
        /* Don't allow the number keys right above the qwerty row to translate or the top left key (grave/backquote) */
        /* Not mapping numbers fixes the French layout, giving numeric keycodes for the number keys, which is the expected behavior */
        if ((keymap[scancode] & SDLK_SCANCODE_MASK) || scancode == SDL_SCANCODE_GRAVE) 
            continue;

        keymap[scancode] = MOS_MapRawKey(i);
    }

    SDL_SetKeymap(0, keymap, SDL_NUM_SCANCODES, SDL_FALSE);
}

void MOS_InitKeyboard(_THIS)
{
    MOS_UpdateKeymap(_this);
  
    SDL_SetScancodeName(SDL_SCANCODE_APPLICATION, "Menu");
    SDL_SetScancodeName(SDL_SCANCODE_LGUI, "Left Command");
    SDL_SetScancodeName(SDL_SCANCODE_RGUI, "Right Command");
	//SDL_SetScancodeName(SDL_SCANCODE_LCTRL, "Control");

}
