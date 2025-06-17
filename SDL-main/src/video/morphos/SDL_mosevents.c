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

#include "SDL_scancode.h"
#include "../SDL_sysvideo.h"
#include "../../events/SDL_events_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/scancodes_morphos.h"
#include "../../core/morphos/SDL_library.h"

#include "SDL_mosvideo.h"
#include "SDL_moswindow.h"
#include "SDL_mosopengl.h"
#include "SDL_mosmouse.h"

#include "SDL_timer.h"
#include "SDL_syswm.h"
#include "SDL.h"

#include <devices/rawkeycodes.h>
#include <intuition/extensions.h>
#include <intuition/intuimessageclass.h>
#include <libraries/screennotify.h>
#include <rexx/errors.h>
#include <rexx/storage.h>
#include <workbench/workbench.h>
#include <workbench/startup.h>
#include <exec/system.h>

#include <proto/dos.h>
#include <proto/alib.h>
#include <proto/commodities.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/keymap.h>
#include <proto/locale.h>
#include <proto/screennotify.h>
#include <libraries/gadtools.h>

void AHI_Mute(ULONG mute);
extern MOS_GlobalMouseState globalMouseState;

static int
MOS_GetButton(int code)
{
    switch (code & ~IECODE_UP_PREFIX) {
        case IECODE_LBUTTON:
            return SDL_BUTTON_LEFT;
        case IECODE_RBUTTON:
            return SDL_BUTTON_RIGHT;
        case IECODE_MBUTTON:
            return SDL_BUTTON_MIDDLE;
        default:
            return 0;
    }
}

static void
MOS_DispatchMouseButtons(_THIS, struct IntuiMessage *m, const SDL_WindowData *data)
{
    SDL_WindowData *sdlwin = (SDL_WindowData *)m->IDCMPWindow->UserData;

    if (sdlwin) {
        int state = (m->Code & IECODE_UP_PREFIX) ? SDL_RELEASED : SDL_PRESSED;
        int button = MOS_GetButton(m->Code & ~(IECODE_UP_PREFIX));

        globalMouseState.buttonPressed[button] = state;

        SDL_SendMouseButton(data->window, 0, state, button);
    }

}

static int
MOS_TranslateUnicode(struct IntuiMessage *m, char *buffer)
{
	int length;
    WCHAR keycode = getv(m, IMSGA_UCS4);
	length = UTF8_Encode(keycode, buffer);

	return length;
}

static void
MOS_DispatchRawKey(_THIS, struct IntuiMessage *m, const SDL_WindowData *data)
{
	
	UWORD code = m->Code;
	UWORD rawkey = m->Code & 0x7F;

	switch (code) {
		case RAWKEY_NM_WHEEL_UP:
			SDL_SendMouseWheel(data->window, 0, 0, 1, SDL_MOUSEWHEEL_NORMAL);
			break;

		case RAWKEY_NM_WHEEL_DOWN:
			SDL_SendMouseWheel(data->window, 0, 0, -1, SDL_MOUSEWHEEL_NORMAL);
			break;

		case RAWKEY_NM_WHEEL_LEFT:
			SDL_SendMouseWheel(data->window, 0, -1, 0, SDL_MOUSEWHEEL_NORMAL);
			break;

		case RAWKEY_NM_WHEEL_RIGHT:
			SDL_SendMouseWheel(data->window, 0, 1, 0,  SDL_MOUSEWHEEL_NORMAL);
			break;

		case RAWKEY_NM_BUTTON_FOURTH:
		    globalMouseState.buttonPressed[SDL_BUTTON_X1] = SDL_PRESSED;;
			SDL_SendMouseButton(data->window, 0, SDL_PRESSED, SDL_BUTTON_X1);
			break;

		case RAWKEY_NM_BUTTON_FOURTH | IECODE_UP_PREFIX:
			globalMouseState.buttonPressed[SDL_BUTTON_X1] = SDL_RELEASED;
			SDL_SendMouseButton(data->window, 0, SDL_RELEASED, SDL_BUTTON_X1);
			break;

		default:
			if (rawkey < sizeof(morphos_scancode_table) / sizeof(morphos_scancode_table[0])) {
                SDL_Scancode s = morphos_scancode_table[rawkey];
                if (m->Code < 128) {
                    char text[5] = { 0 };
					int length = MOS_TranslateUnicode(m, text);
					SDL_SendKeyboardKey(SDL_PRESSED, s);
					if (length > 0) {
						text[length] = '\0';
						SDL_SendKeyboardText(text);
					}
				} else {
					SDL_SendKeyboardKey(SDL_RELEASED, s);
				}
			}
			break;
	}
}

static void
MOS_MouseMove(_THIS, struct IntuiMessage *m, SDL_WindowData *data)
{
    struct Screen *s = data->win->WScreen;

    //D("[%s] X:%d Y:%d, ScreenX: %d ScreenY: %d\n", __FUNCTION__, m->MouseX, m->MouseY, s->MouseX, s->MouseY);
    globalMouseState.x = s->MouseX;
    globalMouseState.y = s->MouseY;

    if (SDL_GetRelativeMouseMode()) {
        if (data->first_deltamove) {
            data->first_deltamove = 0;
            return;
        }
        SDL_SendMouseMotion(data->window, 0, 1, m->MouseX, m->MouseY);
    } else {
    	//struct Screen *s = data->win->WScreen;
        int x = (s->MouseX - data->win->LeftEdge - data->win->BorderLeft);
        int y = (s->MouseY - data->win->TopEdge - data->win->BorderTop);
        SDL_SendMouseMotion(data->window, 0, 0, x, y);
    }
}

static void
MOS_HandleActivation(_THIS, struct IntuiMessage *m, SDL_bool activated)
{
	SDL_WindowData *data = (SDL_WindowData *)m->IDCMPWindow->UserData;
    if (data) {
        if (data->window) {
            if (activated) {

                SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_SHOWN, 0, 0);
                if (SDL_GetKeyboardFocus() != data->window)
                    SDL_SetKeyboardFocus(data->window);

                SDL_SetMouseFocus(data->window);
                MOS_MouseMove(_this, m, data);

            } else {
                if (SDL_GetKeyboardFocus() == data->window)
                    SDL_SetKeyboardFocus(NULL);
                if (SDL_GetMouseFocus() == data->window)
                    SDL_SetMouseFocus(NULL);
            }
        }
    }
}

static void
MOS_ChangeWindow(_THIS, const struct IntuiMessage *m, SDL_WindowData *data)
{
	struct Window *w = data->win;

	if (data->curr_x != w->LeftEdge || data->curr_h != w->TopEdge) {
		data->curr_x = w->LeftEdge;
		data->curr_y = w->TopEdge;
		SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_MOVED, data->curr_x, data->curr_y);
	}

	if (data->curr_w != w->Width || data->curr_h != w->Height) {
		data->curr_w = w->Width;
		data->curr_h = w->Height;
		SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_RESIZED, (data->curr_w - w->BorderLeft - w->BorderRight), (data->curr_h - w->BorderTop - w->BorderBottom));
		if (__tglContext) MOS_GL_ResizeContext(_this, data->window);
	}
}

static void MOS_GadgetEvent(_THIS, const struct IntuiMessage *m)
{
	D("[%s]\n", __FUNCTION__);

	switch (((struct Gadget *)m->IAddress)->GadgetID) {
		case ETI_Iconify:
			MOS_HideApp(_this, TRUE);
			break;
		case ETI_Jump:
			D("[%s] ETI_JUMP\n", __FUNCTION__);
			//SDL_WindowData *data = (SDL_WindowData *)m->IDCMPWindow->UserData;
			//SDL_SetWindowFullscreen(data->window, data->winflags);
			break;
	}
}

static const char porters[] = "Bruno Peloille (BeWorld)\nSzilard Biro (BSzili)\n";
static const char bases[] = "SDL 2.0.3 sources by Ilkka Lehtoranta";

static void
MOS_AboutSDL(struct Window *window)
{
	struct EasyStruct es;
	es.es_StructSize   = sizeof(struct EasyStruct);
	es.es_Flags        = 0;
	es.es_Title        = "SDL2";
	es.es_TextFormat   = "SDL %ld.%ld.%ld -MorphOS-\nCompiled on " __AMIGADATE__ "\n\nSimple DirectMedia Layer is cross-platform development library designed to\nprovide low level access audio, keyboard, mouse, joysticks, and graphics hardware.\n\nSDL 2.0 is distributed under zlib license.\nThis license allows you to use SDL freely in any software.\n\nPorters:\n%s\nBased on %s\n\nwww.libsdl.org";
	es.es_GadgetFormat = "Ok";

	EasyRequest(window, &es, NULL, SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL, (ULONG)porters, (ULONG)bases);
}

static void
MOS_AboutSystem(struct Window *window)
{
	struct EasyStruct es;
	es.es_StructSize   = sizeof(struct EasyStruct);
	es.es_Flags        = 0;
	es.es_Title        = "About System";
	es.es_TextFormat   = "System: %s - Vendor: %s\n\nHas Altivec: %s\n";
	es.es_GadgetFormat = "Ok";

	char System[256];
	char Vendor[256];

	NewGetSystemAttrs(&System,sizeof(System),SYSTEMINFOTYPE_SYSTEM,TAG_DONE);
	NewGetSystemAttrs(&Vendor,sizeof(Vendor),SYSTEMINFOTYPE_VENDOR,TAG_DONE);

	EasyRequest(window, &es, NULL, System, Vendor, ((HasAltiVec)?"Yes":"No"));
}

static void
MOS_Joystick(struct Window *window)
{
	char text1[2000] = "";
	char text2[254] = "";
	int i;
    int controller_count = 0;
    char guid[64];
	
	SDL_InitSubSystem(SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
	
	for (i = 0; i < SDL_NumJoysticks(); ++i) {
    	const char *name;
		char text[254] = "";
		SDL_JoystickGetGUIDString(SDL_JoystickGetDeviceGUID(i), guid, sizeof (guid));
		SDL_Joystick *joystick = SDL_JoystickOpen(i);
        if (joystick != NULL) {		
			if (SDL_IsGameController(i)) {
				controller_count++;
				name = SDL_GameControllerNameForIndex(i);
			} else {
				name = SDL_JoystickNameForIndex(i);	
			}			
		
			snprintf(text, sizeof(text), "%d: %s (guid %s, VID 0x%.4x, PID 0x%.4x, player index = %d)\n",
				i, name ? name : "Unknown", guid,
			SDL_JoystickGetDeviceVendor(i), SDL_JoystickGetDeviceProduct(i), SDL_JoystickGetDevicePlayerIndex(i));
			strcat(text1, text);
			snprintf(text, sizeof(text),"    Joystick has %d axes, %d hats, %d balls, and %d buttons\n",
			SDL_JoystickNumAxes(joystick), SDL_JoystickNumHats(joystick),
			SDL_JoystickNumBalls(joystick), SDL_JoystickNumButtons(joystick));
			strcat(text1, text);
			SDL_JoystickClose(joystick);
		}
	}
	
	snprintf(text2, sizeof(text2),"There are %d game controller(s) attached (%d joystick(s))\n", controller_count, SDL_NumJoysticks());
	struct EasyStruct es;
	es.es_StructSize   = sizeof(struct EasyStruct);
	es.es_Flags        = 0;
	es.es_Title        = "SDL2 Joystick/GameController";
	es.es_TextFormat   = "SDL %ld.%ld.%ld -MorphOS-\n\n%s\n%s";
	es.es_GadgetFormat = "Ok";

	EasyRequest(window, &es, NULL, SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_PATCHLEVEL, (ULONG)text2, (ULONG)text1);
}

static int 
MOS_setenv(const char *name, const char *value, int overwrite)
{
	char dummy[2];
	if (!name || SDL_strlen(name) == 0 || SDL_strchr(name, '=') != NULL || !value) {
		return (-1);
	}

	if (!overwrite && GetVar(name, dummy, sizeof(dummy), GVF_GLOBAL_ONLY) != -1) {
		return 0;
	}
	
	if (SDL_strlen(value) > 0)
	{		
		if (!SetVar(name, value, -1, LV_VAR | GVF_GLOBAL_ONLY | GVF_SAVE_VAR)) 
			return -1;
	
	} else {
		DeleteVar(name, LV_VAR | GVF_GLOBAL_ONLY | GVF_SAVE_VAR);
	}

	return 0;
}

static void
MOS_Priority(ULONG prio)
{
	SDL_ThreadPriority Priority = prio ? SDL_THREAD_PRIORITY_LOW : SDL_THREAD_PRIORITY_NORMAL;
	SDL_SetThreadPriority(Priority);
	MOS_setenv("SDL_THREAD_PRIORITY_POLICY", (prio ? "-1" : "0"), SDL_TRUE);
}

void 
MOS_GlobalMenu(struct Menu * mymenu, UWORD menu, UWORD item, UWORD sub, UWORD check)
{
	struct MenuItem *subitem;
	subitem = ItemAddress(mymenu, FULLMENUNUM(menu, item, sub));
	if (subitem) {
		if (check)
			subitem->Flags |= CHECKED;
		else
			subitem->Flags &= ~CHECKED;
	}
}

static void
MOS_HandleMenu(_THIS, struct IntuiMessage *m)
{
    SDL_WindowData *data = (SDL_WindowData *)m->IDCMPWindow->UserData;
    if (data->win) {
        if (data->menu) {
            struct MenuItem *item = ItemAddress(data->menu, m->Code);
            if (item) {
                switch ((ULONG)GTMENUITEM_USERDATA(item)) {
                case MID_ABOUT:
                    MOS_AboutSDL(data->win);
                    break;
                case MID_QUIT:
                    SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_CLOSE, 0, 0);
                    break;
                case MID_HIDE:
                    MOS_HideApp(_this, TRUE);
                    break;
                case MID_MUTE:
                    AHI_Mute(item->Flags & CHECKED);
                    break;
                case MID_PRIORITY:
                    MOS_Priority(item->Flags & CHECKED);
                    break;
                case MID_RRAUTO:
                    MOS_GlobalMenu(data->menu, 1, 3, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 3, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "");
                    MOS_setenv("SDL_RENDER_DRIVER", "", SDL_TRUE);
                    break;
                case MID_RRGL:
                    MOS_GlobalMenu(data->menu, 1, 3, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 3, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
                    MOS_setenv("SDL_RENDER_DRIVER", "opengl", SDL_TRUE);
                    break;
                case MID_RRSOFT:
                    MOS_GlobalMenu(data->menu, 1, 3, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 3, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "software");
                    MOS_setenv("SDL_RENDER_DRIVER", "software", SDL_TRUE);
                    break;
                case MID_RVAUTO:
                    MOS_GlobalMenu(data->menu, 1, 4, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 4, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "");
                    MOS_setenv("SDL_RENDER_VSYNC", "", SDL_TRUE);
                    break;
                case MID_RVENABLE:
                    MOS_GlobalMenu(data->menu, 1, 4, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 4, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");
                    MOS_setenv("SDL_RENDER_VSYNC", "1", SDL_TRUE);
                    break;
                case MID_RVDISABLE:
                    MOS_GlobalMenu(data->menu, 1, 4, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 4, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
                    MOS_setenv("SDL_RENDER_VSYNC", "0", SDL_TRUE);
                    break;
                case MID_AUTO:
                    MOS_GlobalMenu(data->menu, 1, 5, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 5, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "");
                    MOS_setenv("SDL_RENDER_SCALE_QUALITY", "", SDL_TRUE);
                    break;
                case MID_NEAREST:
                    MOS_GlobalMenu(data->menu, 1, 5, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 5, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
                    MOS_setenv("SDL_RENDER_SCALE_QUALITY", "nearest", SDL_TRUE);
                    break;
                case MID_LINEAR:
                    MOS_GlobalMenu(data->menu, 1, 5, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 5, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
                    MOS_setenv("SDL_RENDER_SCALE_QUALITY", "linear", SDL_TRUE);
                    break;
                case MID_LAUTO:
                    MOS_GlobalMenu(data->menu, 1, 6, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 6, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "");
                    MOS_setenv("SDL_RENDER_LOGICAL_SIZE_MODE", "", SDL_TRUE);
                    break;
                case MID_LLETTER:
                    MOS_GlobalMenu(data->menu, 1, 6, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 6, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "0");
                    MOS_setenv("SDL_RENDER_LOGICAL_SIZE_MODE", "0", SDL_TRUE);
                    break;
                case MID_LOVERS:
                    MOS_GlobalMenu(data->menu, 1, 6, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 6, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LOGICAL_SIZE_MODE, "1");
                    MOS_setenv("SDL_RENDER_LOGICAL_SIZE_MODE", "1", SDL_TRUE);
                    break;
                case MID_BAUTO:
                    MOS_GlobalMenu(data->menu, 1, 7, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 7, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "");
                    MOS_setenv("SDL_RENDER_BATCHING", "", SDL_TRUE);
                    break;
                case MID_BENABLE:
                    MOS_GlobalMenu(data->menu, 1, 7, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 7, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "0");
                    MOS_setenv("SDL_RENDER_BATCHING", "0", SDL_TRUE);
                    break;
                case MID_BDISABLE:
                    MOS_GlobalMenu(data->menu, 1, 7, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 7, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "1");
                    MOS_setenv("SDL_RENDER_BATCHING", "1", SDL_TRUE);
                    break;
                case MID_MDEF:
                    MOS_GlobalMenu(data->menu, 1, 8, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 2, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 3, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "");
                    MOS_setenv("SDL_RENDER_LINE_METHOD", "", SDL_TRUE);
                    break;
                case MID_MPOINT:
                    MOS_GlobalMenu(data->menu, 1, 8, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 2, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 3, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "1");
                    MOS_setenv("SDL_RENDER_LINE_METHOD", "1", SDL_TRUE);
                    break;
                case MID_MLINE:
                    MOS_GlobalMenu(data->menu, 1, 8, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 3, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "2");
                    MOS_setenv("SDL_RENDER_LINE_METHOD", "2", SDL_TRUE);
                    break;
                case MID_MGEO:
                    MOS_GlobalMenu(data->menu, 1, 8, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 8, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_LINE_METHOD, "3");
                    MOS_setenv("SDL_RENDER_LINE_METHOD", "3", SDL_TRUE);
                    break;
                case MID_SHADERS_AUTO:
                    MOS_GlobalMenu(data->menu, 1, 9, 1, 0);
                    MOS_GlobalMenu(data->menu, 1, 9, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_BATCHING, "");
                    MOS_setenv("SDL_RENDER_OPENGL_SHADERS", "", SDL_TRUE);
                    break;
                case MID_SHADERS_ENABLE:
                    MOS_GlobalMenu(data->menu, 1, 9, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 9, 2, 0);
                    SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "1");
                    MOS_setenv("SDL_RENDER_OPENGL_SHADERS", "1", SDL_TRUE);
                    break;
                case MID_SHADERS_DISABLE:
                    MOS_GlobalMenu(data->menu, 1, 9, 0, 0);
                    MOS_GlobalMenu(data->menu, 1, 9, 1, 0);
                    SDL_SetHint(SDL_HINT_RENDER_OPENGL_SHADERS, "0");
                    MOS_setenv("SDL_RENDER_OPENGL_SHADERS", "0", SDL_TRUE);
                    break;
                case MID_JOYSTICK:
                    MOS_Joystick(data->win);
                    break;
                case MID_ABOUTSYS:
                    MOS_AboutSystem(data->win);
                default:
                    break;
                }
            }
        }
    }

}

static void
MOS_DispatchEvent(_THIS, struct IntuiMessage *m)
{
    //D("[%s] \n", __FUNCTION__);
    SDL_WindowData *data = (SDL_WindowData *)m->IDCMPWindow->UserData;

    switch (m->Class) {
    case IDCMP_MENUPICK:
        MOS_HandleMenu(_this, m);
        break;

    case IDCMP_REFRESHWINDOW:
        BeginRefresh(m->IDCMPWindow);
        SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_EXPOSED, 0, 0);
        EndRefresh(m->IDCMPWindow, TRUE);
        break;

    case IDCMP_CLOSEWINDOW:
        SDL_SendWindowEvent(data->window, SDL_WINDOWEVENT_CLOSE, 0, 0);
        break;

    case IDCMP_MOUSEMOVE:
        MOS_MouseMove(_this, m, data);
        break;

    case IDCMP_MOUSEBUTTONS:
        MOS_DispatchMouseButtons(_this, m, data);
        break;

    case IDCMP_RAWKEY:
        MOS_DispatchRawKey(_this, m, data);
        break;

    case IDCMP_ACTIVEWINDOW:
        MOS_HandleActivation(_this, m, SDL_TRUE);
        break;

    case IDCMP_INACTIVEWINDOW:
        MOS_HandleActivation(_this, m, SDL_FALSE);
        break;

    case IDCMP_CHANGEWINDOW:
        MOS_ChangeWindow(_this, m, data);
        break;

    case IDCMP_GADGETUP:
        MOS_GadgetEvent(_this, m);
        break;

    default:
        break;
    }
}

static void
MOS_CheckBrokerMsg(_THIS)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	CxMsg *msg;

	while ((msg = (CxMsg *)GetMsg(&data->BrokerPort))) {
		size_t id = CxMsgID(msg);
		size_t tp = CxMsgType(msg);

		D("[%s] check CxMsg\n", __FUNCTION__);

		ReplyMsg((APTR)msg);

		if (tp == CXM_COMMAND) {
			switch (id) {
				case CXCMD_KILL:
					SDL_SendAppEvent(SDL_QUIT);
					break;

				case CXCMD_APPEAR:
					MOS_ShowApp(_this);
					break;

				case CXCMD_DISAPPEAR:
					MOS_HideApp(_this, TRUE);
					break;
			}
		}
	}
}

static void
MOS_CheckScreenEvent(_THIS)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

	for (;;) {
		struct ScreenNotifyMessage *snm;

		while ((snm = (struct ScreenNotifyMessage *)GetMsg(&data->ScreenNotifyPort)) != NULL) {
			D("[%s] check ScreenNotifyMessage\n", __FUNCTION__);

			switch ((size_t)snm->snm_Value) {
				case FALSE:
					MOS_HideApp(_this, FALSE);
					break;

				case TRUE:
					MOS_ShowApp(_this);
					break;
			}
		}

		if (data->WScreen)
			break;

		WaitPort(&data->ScreenNotifyPort);
	}
}

static void
MOS_CheckWBEvents(_THIS)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	struct AppMessage *msg;
	
	while ((msg = (struct AppMessage *)GetMsg(&data->WBPort)) != NULL) {
		D("[%s] check AppMessage\n", __FUNCTION__);

		switch (msg->am_Type) {
			case AMTYPE_APPWINDOW: 
				{
				    SDL_Window *window = (SDL_Window *)msg->am_UserData;
					char filename[1024];
					struct WBArg *argptr = msg->am_ArgList;
				    for (int i = 0; i < msg->am_NumArgs; i++) {
						if (argptr->wa_Lock) {
							NameFromLock(argptr->wa_Lock, filename, 1024);
							AddPart(filename, argptr->wa_Name, 1024);

							D("[%s] SDL_SendDropfile : '%s'\n", __FUNCTION__, filename);
							SDL_SendDropFile(window, filename);
							argptr++;
						}
					}
					SDL_SendDropComplete(window);
                    SDL_RaiseWindow(window);
				}
				break;
			case AMTYPE_APPICON:
				MOS_ShowApp(_this);
				break;
			default:
				//D("[%s] Unknown AppMsg %d %p\n", __FUNCTION__, msg->am_Type, (APTR)msg->am_UserData);
				break;
		}

	}
}

void
MOS_PumpEvents(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *)_this->driverdata;
    struct IntuiMessage *m;

    BOOL check_mousecoord = FALSE;
    size_t sigs = SetSignal(0, data->ScrNotifySig | data->BrokerSig | data->WBSig | data->WinSig | SIGBREAKF_CTRL_C);

    if (sigs & data->WinSig) {
        SDL_WindowData *wdata = NULL;
        while ((m = (struct IntuiMessage *)GetMsg(&data->WinPort))) {
            wdata = (SDL_WindowData *)m->IDCMPWindow->UserData;
            if (m->Class == IDCMP_MOUSEMOVE && !SDL_GetRelativeMouseMode())
                check_mousecoord = TRUE;

            MOS_DispatchEvent(_this, m);
            ReplyMsg((struct Message *)m);
        }

        if (wdata && check_mousecoord && wdata->win) {
            struct Window *w = wdata->win;
            struct Screen *s = w->WScreen;
            if (s) {
                LONG mx = s->MouseX;
                LONG my = s->MouseY;
                LONG ws = w->LeftEdge + w->BorderLeft;
                LONG wy = w->TopEdge + w->BorderTop;
                LONG wx2 = w->LeftEdge + w->Width - w->BorderRight;
                LONG wy2 = w->TopEdge + w->Height - w->BorderBottom;
                if (mx >= ws && my >= wy && mx <= wx2 && my <= wy2) {
                    w->Flags |= WFLG_RMBTRAP;

                    if (data->CurrentPointer) {
                        if (!IS_SYSTEM_CURSOR(data->CurrentPointer)) {
                            SDL_MOSCursor *ac = (SDL_MOSCursor *)data->CurrentPointer;
                            if (ac->Pointer.mouseptr)
                                SetWindowPointer(w, WA_Pointer, (size_t)ac->Pointer.mouseptr, TAG_DONE);
                        }
                    } else {
                        size_t pointertags[] = { WA_PointerType, POINTERTYPE_INVISIBLE, TAG_DONE };
                        SetAttrsA(w, (struct TagItem *)&pointertags);
                    }

                } else {
                    w->Flags &= ~WFLG_RMBTRAP;
                    ClearPointer(w);
                }
            }
        }
    }

    if (sigs & data->ScrNotifySig && data->ScreenNotifyHandle)
        MOS_CheckScreenEvent(_this);

    if (sigs & data->BrokerSig)
        MOS_CheckBrokerMsg(_this);

    if (sigs & data->WBSig)
        MOS_CheckWBEvents(_this);

    if (sigs & SIGBREAKF_CTRL_C)
        SDL_SendAppEvent(SDL_QUIT);
}
