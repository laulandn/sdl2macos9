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

#include "SDL_messagebox.h"
#include "../SDL_sysvideo.h"
#include "../../core/morphos/SDL_misc.h"

#include <proto/charsets.h>
#include <proto/exec.h>
#include <proto/muimaster.h>

int
MOS_ShowMessageBox(const SDL_MessageBoxData *mbd, int *buttonid)
{
	struct Library *MUIMasterBase = OpenLibrary("muimaster.library", 0);
	int rc = -1;

	D("[%s]\n", __FUNCTION__);

	if (MUIMasterBase) {

		char *title = MOS_ConvertText(mbd->title, MIBENUM_UTF_8, MIBENUM_SYSTEM);
        if (title) {

            char *message = MOS_ConvertText(mbd->message, MIBENUM_UTF_8, MIBENUM_SYSTEM);

            if (message) {
                size_t i, tlen = 1024;
                char *btxt;

                btxt = SDL_malloc(tlen);

                if (btxt) {
                    char *buf = btxt;

                    for (i = 0; i < mbd->numbuttons; i++) {
                        if (i > 0)
                            *buf++ = '|';

                        if (mbd->buttons[i].flags & SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT)
                            *buf++ = '*';

                        buf += ConvertTagList((APTR)mbd->buttons[i].text, -1, buf, -1, MIBENUM_UTF_8, MIBENUM_SYSTEM, NULL);
                    }

                    *buf = '\0';

                    rc = MUI_RequestA(NULL, NULL, 0, title == NULL ? "SDL2" : title, btxt, message, NULL);

                    if (rc == 0)
                        rc = mbd->numbuttons - 1;
                    else
                        rc -= 1;

                    *buttonid = mbd->buttons[rc].buttonid;

                    SDL_free(btxt);
                    rc = 0;
                }

                SDL_free(message);
            }

            SDL_free(title);
        }

		CloseLibrary(MUIMasterBase);
	}

	return rc;
}
