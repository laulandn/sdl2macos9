/*
  System 6 event pump.

  sdl2macos9 used WaitNextEvent(everyEvent), AppleEvents, InputSprocket,
  and DrawSprocket suspend. On a Plus, everyEvent lets the Menu Manager
  resurrect an empty white bar (68k-mac-dev). Pump mouse + update only.
  Keyboard is KeyMap at $174, not keyDown autoKey flood.
*/
#include "../../SDL_internal.h"
#include "../SDL_sysvideo.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_mouse_c.h"
#include "../../events/SDL_windowevents_c.h"
#include "SDL_events.h"
#include "sdl_mac.h"

#if defined(SDL_VIDEO_DRIVER_MACOSCLASSIC) && defined(SDL_MACOSCLASSIC_SYS6)

#include <Events.h>
#include <Windows.h>
#include <OSUtils.h>

static int mouse_button_down;
static int last_mouse_x = -1;
static int last_mouse_y = -1;

static void sys6_mouse_motion(Point global)
{
    Point local = global;
    int x, y;

    if (!sdlw) {
        return;
    }
    if (macport) {
        SetPort(macport);
        GlobalToLocal(&local);
    }
    x = local.h;
    y = local.v;
    if (x < 0) {
        x = 0;
    } else if (x >= sdlw->w) {
        x = sdlw->w - 1;
    }
    if (y < 0) {
        y = 0;
    } else if (y >= sdlw->h) {
        y = sdlw->h - 1;
    }
    if (x == last_mouse_x && y == last_mouse_y) {
        return;
    }
    last_mouse_x = x;
    last_mouse_y = y;
    SDL_SendMouseMotion(sdlw, 0, 0, x, y);
}

void SDL_Mac_pumpEvents(_THIS)
{
    EventRecord event;
    Point mouse;
    const short mask = (short)(mDownMask | mUpMask | updateMask);

    (void)_this;

    while (GetNextEvent(mask, &event)) {
        switch (event.what) {
        case updateEvt:
            if ((WindowPtr)event.message == macwindow && macwindow) {
                BeginUpdate(macwindow);
                if (sdlw) {
                    SDL_SendWindowEvent(sdlw, SDL_WINDOWEVENT_EXPOSED, 0, 0);
                }
                EndUpdate(macwindow);
            }
            break;
        case mouseDown:
            if (macwindow) {
                SelectWindow(macwindow);
            }
            mac_window_active = 1;
            sys6_mouse_motion(event.where);
            if (!mouse_button_down) {
                mouse_button_down = 1;
                SDL_SendMouseButton(sdlw, 0, SDL_PRESSED, SDL_BUTTON_LEFT);
            }
            break;
        case mouseUp:
            sys6_mouse_motion(event.where);
            if (mouse_button_down) {
                mouse_button_down = 0;
                SDL_SendMouseButton(sdlw, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
            }
            break;
        default:
            break;
        }
    }

    GetMouse(&mouse);
    {
        Point global = mouse;
        if (macport) {
            SetPort(macport);
            LocalToGlobal(&global);
        }
        sys6_mouse_motion(global);
    }

    Mac_PollKeyboard();
}

#endif /* SDL_VIDEO_DRIVER_MACOSCLASSIC && SDL_MACOSCLASSIC_SYS6 */
