/* Classic Mac OS event handling, originally derived from SDL's QNX driver. */

/*
  Simple DirectMedia Layer
  Copyright (C) 2017 BlackBerry Limited

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
#include "../../events/SDL_windowevents_c.h"
#include "SDL_events.h"
#include "sdl_mac.h"
#ifdef TARGET_OS_OSX
#else
#include <AppleEvents.h>
#include <Gestalt.h>
#endif

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC

/**
 * Runs the main event loop.
 * @param   _THIS
 */
static int mouse_button_down;
int mac_window_active;
static int last_mouse_x = -1;
static int last_mouse_y = -1;
static int mac_mouse_warp_pending;
static AEEventHandlerUPP mac_open_app_handler;
static AEEventHandlerUPP mac_document_handler;
static AEEventHandlerUPP mac_quit_app_handler;
static int mac_apple_events_ready;

void Mac_ResetMouseTracking(void)
{
  last_mouse_x = -1;
  last_mouse_y = -1;
  mac_mouse_warp_pending = 0;
}

static pascal OSErr MacAEOpenApplication(const AppleEvent *event,
                                         AppleEvent *reply, long refcon)
{
  (void)event;
  (void)reply;
  (void)refcon;
  return noErr;
}

static pascal OSErr MacAEQuitApplication(const AppleEvent *event,
                                         AppleEvent *reply, long refcon)
{
  SDL_Event quit_event;
  (void)event;
  (void)reply;
  (void)refcon;

  SDL_zero(quit_event);
  quit_event.type = SDL_QUIT;
  return SDL_PushEvent(&quit_event) == 1 ? noErr : errAEEventNotHandled;
}

static pascal OSErr MacAEDocumentEvent(const AppleEvent *event,
                                       AppleEvent *reply, long refcon)
{
  /* SDL has no document model, but these are mandatory events for an
     application that advertises high-level-event awareness. */
  (void)event;
  (void)reply;
  (void)refcon;
  return noErr;
}

void Mac_InitAppleEvents(void)
{
  long attributes;
  OSErr error;

  if (mac_apple_events_ready ||
      Gestalt(gestaltAppleEventsAttr, &attributes) != noErr)
    return;

  mac_open_app_handler = NewAEEventHandlerUPP(MacAEOpenApplication);
  mac_document_handler = NewAEEventHandlerUPP(MacAEDocumentEvent);
  mac_quit_app_handler = NewAEEventHandlerUPP(MacAEQuitApplication);
  if (!mac_open_app_handler || !mac_document_handler || !mac_quit_app_handler) {
    Mac_QuitAppleEvents();
    return;
  }

  error = AEInstallEventHandler(kCoreEventClass, kAEOpenApplication,
                                mac_open_app_handler, 0, false);
  if (error != noErr)
    goto fail_handlers;
  error = AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments,
                                mac_document_handler, 0, false);
  if (error != noErr)
    goto fail_open;
  error = AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments,
                                mac_document_handler, 0, false);
  if (error != noErr)
    goto fail_open_documents;
  error = AEInstallEventHandler(kCoreEventClass, kAEQuitApplication,
                                mac_quit_app_handler, 0, false);
  if (error != noErr) {
    AERemoveEventHandler(kCoreEventClass, kAEPrintDocuments,
                         mac_document_handler, false);
    goto fail_open_documents;
  }
  mac_apple_events_ready = 1;
  return;

fail_open_documents:
  AERemoveEventHandler(kCoreEventClass, kAEOpenDocuments,
                       mac_document_handler, false);
fail_open:
  AERemoveEventHandler(kCoreEventClass, kAEOpenApplication,
                       mac_open_app_handler, false);
fail_handlers:
  SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
              "macosclassic: could not install AppleEvent handlers (%d)",
              (int)error);
  Mac_QuitAppleEvents();
}

void Mac_QuitAppleEvents(void)
{
  if (mac_apple_events_ready) {
    AERemoveEventHandler(kCoreEventClass, kAEOpenApplication,
                         mac_open_app_handler, false);
    AERemoveEventHandler(kCoreEventClass, kAEOpenDocuments,
                         mac_document_handler, false);
    AERemoveEventHandler(kCoreEventClass, kAEPrintDocuments,
                         mac_document_handler, false);
    AERemoveEventHandler(kCoreEventClass, kAEQuitApplication,
                         mac_quit_app_handler, false);
    mac_apple_events_ready = 0;
  }
  if (mac_open_app_handler) {
    DisposeAEEventHandlerUPP(mac_open_app_handler);
    mac_open_app_handler = NULL;
  }
  if (mac_document_handler) {
    DisposeAEEventHandlerUPP(mac_document_handler);
    mac_document_handler = NULL;
  }
  if (mac_quit_app_handler) {
    DisposeAEEventHandlerUPP(mac_quit_app_handler);
    mac_quit_app_handler = NULL;
  }
}

static void MacGlobalToWindow( Point global, int *x, int *y )
{
  Point local = global;

  if (macport) {
    SetPort((GrafPtr)macport);
    GlobalToLocal(&local);
  }

  *x = local.h;
  *y = local.v;
}

static void MacWindowToSDL( int *x, int *y )
{
  Rect bounds;
  int port_w, port_h;

  if (!macport || !sdlw)
    return;

#if TARGET_API_MAC_CARBON
  GetPortBounds(macport, &bounds);
#else
  bounds = macport->portRect;
#endif
  port_w = bounds.right - bounds.left;
  port_h = bounds.bottom - bounds.top;
  if (port_w <= 0 || port_h <= 0)
    return;

  /* Fullscreen software output is stretched to the native window. Map the
     pointer back into the logical SDL surface used by the game menus. */
  if (port_w != sdlw->w)
    *x = (int)(((long)(*x - bounds.left) * sdlw->w) / port_w);
  else
    *x -= bounds.left;
  if (port_h != sdlw->h)
    *y = (int)(((long)(*y - bounds.top) * sdlw->h) / port_h);
  else
    *y -= bounds.top;

  if (*x < 0)
    *x = 0;
  else if (*x >= sdlw->w)
    *x = sdlw->w - 1;
  if (*y < 0)
    *y = 0;
  else if (*y >= sdlw->h)
    *y = sdlw->h - 1;
}

#if TARGET_API_MAC_CARBON
static void MacPollCarbonMouseDeltas(void)
{
  static const EventTypeSpec mouse_events[] = {
    { kEventClassMouse, kEventMouseMoved },
    { kEventClassMouse, kEventMouseDragged }
  };
  EventRef event;
  int total_x = 0;
  int total_y = 0;
  int event_limit = 256;

  while (event_limit-- > 0 &&
         ReceiveNextEvent(2, mouse_events, kEventDurationNoWait,
                          true, &event) == noErr) {
    Point delta;

    if (GetEventParameter(event, kEventParamMouseDelta, typeQDPoint,
                          NULL, sizeof(delta), NULL, &delta) == noErr) {
      total_x += delta.h;
      total_y += delta.v;
    }
    ReleaseEvent(event);
  }

  if ((total_x || total_y) && sdlw)
    SDL_SendMouseMotion(sdlw, 0, 1, total_x, total_y);
}
#endif

void Mac_SetWindowActive( int active )
{
  active = active ? 1 : 0;

  if (!active) {
#ifdef SDL_VIDEO_OPENGL
    if (Mac_GL_SetDrawableActive(0) < 0) {
      SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                   "macosclassic: could not detach the suspended AGL drawable: %s",
                   SDL_GetError());
    }
#endif
  }

  if (mac_window_active == active)
    return;

  mac_window_active = active;
  if (!active)
    Mac_InputSprocketSetForeground(0);

  /* The Window Manager updates highlighting when it delivers activation. */

  if (!sdlw) {
    if (!active)
      Mac_ForceShowCursor();
    return;
  }

  if (active) {
    if (SDL_GetKeyboardFocus() != sdlw)
      SDL_SetKeyboardFocus(sdlw);
#ifdef SDL_VIDEO_OPENGL
    if (Mac_GL_SetDrawableActive(1) < 0) {
      SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                   "macosclassic: could not attach the active AGL drawable: %s",
                   SDL_GetError());
    }
#endif
    Mac_InputSprocketSetForeground(1);
    if (Mac_IsRelativeMouseMode()) {
      SDL_SetMouseFocus(sdlw);
      Mac_ResetMouseTracking();
      Mac_InputSprocketSetCapture(1);
      if (!Mac_InputSprocketIsActive())
        Mac_CenterMouse();
      SDL_SetCursor(NULL);
    } else {
      Mac_ForceShowCursor();
    }
  } else {
    Mac_ResetKeyboardState();
    if (mouse_button_down) {
      /* A mouseUp is delivered to the new foreground process, so release our
         SDL button state when Classic suspends us. */
      mouse_button_down = 0;
      SDL_SendMouseButton(sdlw, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
    }
    SDL_SetMouseFocus(NULL);
    SDL_SetKeyboardFocus(NULL);
    Mac_ForceShowCursor();
    Mac_ResetMouseTracking();
  }
}

static void MacSendMouseMotion( Point global )
{
  int x, y, center_x, center_y, dx, dy;

  if (!sdlw || !macwindow)
    return;

  MacGlobalToWindow(global, &x, &y);
  if (Mac_IsRelativeMouseMode()) {
    /* InputSprocket owns the relative stream while active. Event Manager
       coordinates are then only useful for window hit-testing; mixing them
       with physical deltas would count the same movement twice. */
    if (Mac_InputSprocketIsActive())
      return;

#if TARGET_API_MAC_CARBON
    /* Relative Carbon motion is drained from the native event queue. */
    return;
#endif

    center_x = sdlw->w / 2;
    center_y = sdlw->h / 2;

    /* Establish a centered baseline before reporting relative motion. */
    if (last_mouse_x < 0 || last_mouse_y < 0) {
      last_mouse_x = center_x;
      last_mouse_y = center_y;
      mac_mouse_warp_pending = 1;
      Mac_CenterMouse();
      return;
    }

    if (mac_mouse_warp_pending) {
      if (SDL_abs(x - center_x) <= 2 && SDL_abs(y - center_y) <= 2) {
        last_mouse_x = center_x;
        last_mouse_y = center_y;
        mac_mouse_warp_pending = 0;
      }
      return;
    }

    dx = x - center_x;
    dy = y - center_y;
    if (dx || dy) {
      SDL_SendMouseMotion(sdlw, 0, 1, dx, dy);
      Mac_CenterMouse();
      mac_mouse_warp_pending = 1;
    }
    return;
  }

  MacWindowToSDL(&x, &y);

  if (x == last_mouse_x && y == last_mouse_y)
    return;

  last_mouse_x = x;
  last_mouse_y = y;
  SDL_SendMouseMotion(sdlw, 0, 0, x, y);
}

void SDL_Mac_pumpEvents(_THIS)
{
  EventRecord event;
  int etype;
  WindowPtr target;
  short part;
  Point mouse;
  Boolean got_event;

#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic pumpEvents...\n"); fflush(stderr);
#endif

  /* WaitNextEvent both retrieves the next Toolbox event and yields time to
     other cooperative processes when the queue is empty. */
  got_event = WaitNextEvent(everyEvent & ~autoKeyMask, &event, 1, NULL);
  if (got_event) {
    etype=event.what;
    switch(etype) {
      case kHighLevelEvent:
        if (mac_apple_events_ready) {
          OSErr error = AEProcessAppleEvent(&event);
          if (error != noErr && error != errAEEventNotHandled) {
            SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION,
                        "macosclassic: AEProcessAppleEvent failed (%d)",
                        (int)error);
          }
        }
        break;
      case activateEvt:
        if ((WindowPtr)event.message == macwindow)
          Mac_SetWindowActive((event.modifiers & activeFlag) != 0);
        break;
      case updateEvt:
        target = (WindowPtr)event.message;
        if (target == macwindow) {
          BeginUpdate(macwindow);
          SDL_SendWindowEvent(sdlw, SDL_WINDOWEVENT_EXPOSED, 0, 0);
          EndUpdate(macwindow);
        }
        break;
      case mouseDown:
        target = NULL;
        part = FindWindow(event.where, &target);
        if (target == macwindow && part == inContent) {
          if (FrontWindow() != macwindow)
            SelectWindow(macwindow);
          Mac_SetWindowActive(1);
          MacSendMouseMotion(event.where);
          if (!Mac_InputSprocketIsActive() && !mouse_button_down) {
            mouse_button_down = 1;
            SDL_SendMouseButton(sdlw, 0, SDL_PRESSED, SDL_BUTTON_LEFT);
          }
        } else if (target && part == inDrag) {
          {
            Rect drag_bounds;
#if TARGET_API_MAC_CARBON
            GetRegionBounds(GetGrayRgn(), &drag_bounds);
#else
            drag_bounds = (**GetGrayRgn()).rgnBBox;
#endif
            DragWindow(target, event.where, &drag_bounds);
          }
          if (target == macwindow)
#ifdef SDL_VIDEO_OPENGL
            Mac_GL_Update();
#else
            ;
#endif
        } else if (target && part == inGoAway && TrackGoAway(target, event.where)) {
          if (target == macwindow && sdlw)
            SDL_SendWindowEvent(sdlw, SDL_WINDOWEVENT_CLOSE, 0, 0);
        }
        break;
      case mouseUp:
        if (!mac_window_active)
          break;
        MacSendMouseMotion(event.where);
        if (mouse_button_down && sdlw) {
          mouse_button_down = 0;
          SDL_SendMouseButton(sdlw, 0, SDL_RELEASED, SDL_BUTTON_LEFT);
        }
        break;
      case autoKey:
        handleKeyboardEvent(&event,etype);
        break;
	  case keyDown:
        handleKeyboardEvent(&event,etype);
        break;
	  case keyUp:
        handleKeyboardEvent(&event,etype);
	    break;
      case osEvt:
        if (((event.message >> 24) & 0xff) == suspendResumeMessage) {
          const int resuming = (event.message & resumeFlag) != 0;

          /* Detach process-owned resources before DrawSprocket restores the
             desktop. On resume, let DrawSprocket restore the game display
             before scheduling AGL and input reattachment. */
          if (!resuming)
            Mac_SetWindowActive(0);
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
          Mac_ProcessDrawSprocketEvent(&event);
#endif
          if (resuming)
            Mac_SetWindowActive(1);
        }
        break;
	  default:
#ifdef MAC_DEBUG
	    fprintf(stderr,"macosclassic mac event.what=%d skipped!\n",etype); fflush(stderr);
#endif
	    break;
	}
  }

  if (macwindow && sdlw) {
    if (mac_window_active)
      Mac_PollKeyboard();
    if (mac_window_active) {
#if !TARGET_API_MAC_CARBON
      int relative_dx;
      int relative_dy;
#endif

      if (Mac_IsRelativeMouseMode()) {
#if TARGET_API_MAC_CARBON
        MacPollCarbonMouseDeltas();
#else
        if (Mac_InputSprocketPoll(&relative_dx, &relative_dy)) {
          if (relative_dx || relative_dy)
            SDL_SendMouseMotion(sdlw, 0, 1, relative_dx, relative_dy);
        } else {
          SetPort((GrafPtr)macport);
          GetMouse(&mouse);
          LocalToGlobal(&mouse);
          MacSendMouseMotion(mouse);
        }
#endif
      } else {
        SetPort((GrafPtr)macport);
        GetMouse(&mouse);
        LocalToGlobal(&mouse);
        MacSendMouseMotion(mouse);
      }
    }
  }
}

#endif
