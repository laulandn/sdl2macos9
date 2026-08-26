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
#include "sdl_mac.h"
#include "SDL_events.h"

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC

#if !TARGET_API_MAC_CARBON
#include <CursorDevices.h>
#if defined(SDL_MACOSCLASSIC_INPUTSPROCKET)
#include <InputSprocket.h>
#endif
#include <LowMem.h>
#endif

static int mac_cursor_visible = 1;
static int mac_relative_mouse;
static Cursor mac_invisible_cursor;

#if !TARGET_API_MAC_CARBON && defined(SDL_MACOSCLASSIC_INPUTSPROCKET)

#define MAC_ISP_MAX_DEVICES 4
#define MAC_ISP_MAX_ELEMENTS 32
#define MAC_ISP_MAX_BUTTONS 5
/* InputSprocket mouse deltas use finer units than SDL pixel motion. Keep the
   fractional remainder so slow movement is not lost between polls. */
#define MAC_ISP_MOUSE_UNITS_PER_PIXEL 163

typedef struct MacISpButton
{
    ISpElementReference element;
    Uint8 sdl_button;
    Uint8 down;
} MacISpButton;

typedef struct MacISpMouse
{
    ISpDeviceReference device;
    ISpElementReference delta_x;
    ISpElementReference delta_y;
    MacISpButton buttons[MAC_ISP_MAX_BUTTONS];
    Uint8 button_count;
} MacISpMouse;

static MacISpMouse mac_isp_mice[MAC_ISP_MAX_DEVICES];
static ISpDeviceReference mac_isp_device_refs[MAC_ISP_MAX_DEVICES];
static int mac_isp_mouse_count;
static int mac_isp_started;
static int mac_isp_active;
static int mac_isp_suspended;
static int mac_isp_foreground;
static int mac_isp_wants_capture;
static Sint32 mac_isp_accum_x;
static Sint32 mac_isp_accum_y;
static Uint32 mac_isp_sent_buttons;
static Uint32 mac_isp_error_tick;

static Uint8 Mac_InputSprocketButtonForLabel(ISpElementLabel label,
                                              int fallback_index)
{
    switch (label) {
    case kISpElementLabel_Btn_MouseOne:
        return SDL_BUTTON_LEFT;
    case kISpElementLabel_Btn_MouseTwo:
        return SDL_BUTTON_RIGHT;
    case kISpElementLabel_Btn_MouseThree:
        return SDL_BUTTON_MIDDLE;
    default:
        break;
    }

    switch (fallback_index) {
    case 0:
        return SDL_BUTTON_LEFT;
    case 1:
        return SDL_BUTTON_RIGHT;
    case 2:
        return SDL_BUTTON_MIDDLE;
    case 3:
        return SDL_BUTTON_X1;
    case 4:
        return SDL_BUTTON_X2;
    default:
        return 0;
    }
}

static void Mac_InputSprocketReportError(const char *operation, OSStatus err)
{
    Uint32 now = TickCount();

    if (mac_isp_error_tick == 0 ||
        (Sint32)(now - mac_isp_error_tick) >= 0) {
        SDL_LogWarn(SDL_LOG_CATEGORY_INPUT,
                    "macosclassic: InputSprocket %s failed (%ld)",
                    operation, (long)err);
        mac_isp_error_tick = now + 300;
    }
}

static void Mac_InputSprocketReleaseButtons(void)
{
    Uint8 button;

    if (sdlw) {
        for (button = SDL_BUTTON_LEFT; button <= SDL_BUTTON_X2; ++button) {
            if (mac_isp_sent_buttons & SDL_BUTTON(button))
                SDL_SendMouseButton(sdlw, 0, SDL_RELEASED, button);
        }
    }
    mac_isp_sent_buttons = 0;
}

static void Mac_InputSprocketResetState(void)
{
    int i;
    int j;

    mac_isp_accum_x = 0;
    mac_isp_accum_y = 0;
    for (i = 0; i < mac_isp_mouse_count; ++i) {
        UInt32 ignored;

        ISpElement_Flush(mac_isp_mice[i].delta_x);
        ISpElement_Flush(mac_isp_mice[i].delta_y);
        ignored = 0;
        ISpElement_GetSimpleState(mac_isp_mice[i].delta_x, &ignored);
        ignored = 0;
        ISpElement_GetSimpleState(mac_isp_mice[i].delta_y, &ignored);
        for (j = 0; j < mac_isp_mice[i].button_count; ++j) {
            ISpElement_Flush(mac_isp_mice[i].buttons[j].element);
            mac_isp_mice[i].buttons[j].down = 0;
        }
    }
    Mac_InputSprocketReleaseButtons();
}

static void Mac_InputSprocketApplyCapture(void)
{
    const int should_be_active =
        mac_isp_started && mac_isp_mouse_count > 0 &&
        mac_isp_wants_capture && mac_isp_foreground && !mac_isp_suspended;
    OSStatus err;

    if (should_be_active == mac_isp_active)
        return;

    if (should_be_active) {
        Mac_InputSprocketResetState();
        err = ISpDevices_Activate((UInt32)mac_isp_mouse_count,
                                  mac_isp_device_refs);
        if (err != noErr && err != kISpDeviceActiveErr) {
            Mac_InputSprocketReportError("activate", err);
            return;
        }
        mac_isp_active = 1;
        Mac_InputSprocketResetState();
    } else {
        Mac_InputSprocketResetState();
        err = ISpDevices_Deactivate((UInt32)mac_isp_mouse_count,
                                    mac_isp_device_refs);
        if (err != noErr && err != kISpDeviceInactiveErr)
            Mac_InputSprocketReportError("deactivate", err);
        mac_isp_active = 0;
    }
}

static void Mac_InitInputSprocket(void)
{
    ISpDeviceReference candidates[MAC_ISP_MAX_DEVICES];
    UInt32 candidate_count = 0;
    UInt32 available_count;
    OSStatus err;
    int i;

    SDL_zeroa(mac_isp_mice);
    SDL_zeroa(mac_isp_device_refs);
    mac_isp_mouse_count = 0;
    mac_isp_started = 0;
    mac_isp_active = 0;
    mac_isp_suspended = 0;
    mac_isp_foreground = 0;
    mac_isp_wants_capture = 0;
    mac_isp_error_tick = 0;

    err = ISpStartup();
    if (err != noErr) {
        Mac_InputSprocketReportError("startup", err);
        return;
    }
    mac_isp_started = 1;

    err = ISpDevices_ExtractByClass(kISpDeviceClass_Mouse,
                                    MAC_ISP_MAX_DEVICES,
                                    &candidate_count, candidates);
    if (err != noErr) {
        OSStatus shutdown_err;

        Mac_InputSprocketReportError("enumerate-mice", err);
        shutdown_err = ISpShutdown();
        if (shutdown_err != noErr)
            Mac_InputSprocketReportError("shutdown", shutdown_err);
        mac_isp_started = 0;
        return;
    }

    available_count = candidate_count;
    if (candidate_count > MAC_ISP_MAX_DEVICES)
        candidate_count = MAC_ISP_MAX_DEVICES;

    for (i = 0; i < (int)candidate_count; ++i) {
        ISpElementListReference list = NULL;
        ISpElementReference elements[MAC_ISP_MAX_ELEMENTS];
        UInt32 element_count = 0;
        MacISpMouse mouse;
        ISpElementReference fallback_deltas[2] = { NULL, NULL };
        int fallback_delta_count = 0;
        UInt32 j;

        SDL_zero(mouse);
        mouse.device = candidates[i];
        if (ISpDevice_GetElementList(candidates[i], &list) != noErr || !list)
            continue;
        if (ISpElementList_Extract(list, MAC_ISP_MAX_ELEMENTS,
                                   &element_count, elements) != noErr)
            continue;
        if (element_count > MAC_ISP_MAX_ELEMENTS)
            element_count = MAC_ISP_MAX_ELEMENTS;

        for (j = 0; j < element_count; ++j) {
            ISpElementInfo info;

            if (ISpElement_GetInfo(elements[j], &info) != noErr)
                continue;
            if (info.theKind == kISpElementKind_Delta) {
                if (info.theLabel == kISpElementLabel_Delta_X ||
                    info.theLabel == kISpElementLabel_Delta_Cursor_X) {
                    if (!mouse.delta_x)
                        mouse.delta_x = elements[j];
                } else if (info.theLabel == kISpElementLabel_Delta_Y ||
                           info.theLabel == kISpElementLabel_Delta_Cursor_Y) {
                    if (!mouse.delta_y)
                        mouse.delta_y = elements[j];
                } else if (fallback_delta_count < 2) {
                    fallback_deltas[fallback_delta_count++] = elements[j];
                }
            } else if (info.theKind == kISpElementKind_Button &&
                       mouse.button_count < MAC_ISP_MAX_BUTTONS) {
                MacISpButton *button = &mouse.buttons[mouse.button_count];

                button->element = elements[j];
                button->sdl_button = Mac_InputSprocketButtonForLabel(
                    info.theLabel, mouse.button_count);
                if (button->sdl_button)
                    mouse.button_count++;
            }
        }

        /* Prefer labelled axes. Only use anonymous deltas to fill an axis
           that the device did not identify, so wheel/Z elements cannot
           overwrite a valid X or Y mapping. */
        for (j = 0; j < (UInt32)fallback_delta_count; ++j) {
            if (!mouse.delta_x)
                mouse.delta_x = fallback_deltas[j];
            else if (!mouse.delta_y)
                mouse.delta_y = fallback_deltas[j];
        }

        if (mouse.delta_x && mouse.delta_y) {
            mac_isp_mice[mac_isp_mouse_count] = mouse;
            mac_isp_device_refs[mac_isp_mouse_count] = mouse.device;
            mac_isp_mouse_count++;
        }
    }

    if (mac_isp_mouse_count == 0) {
        OSStatus shutdown_err;

        SDL_LogDebug(SDL_LOG_CATEGORY_INPUT,
                     "macosclassic: no usable InputSprocket mouse among %lu devices",
                     (unsigned long)available_count);
        shutdown_err = ISpShutdown();
        if (shutdown_err != noErr)
            Mac_InputSprocketReportError("shutdown", shutdown_err);
        mac_isp_started = 0;
        return;
    }

    SDL_LogDebug(SDL_LOG_CATEGORY_INPUT,
                 "macosclassic: using %d of %lu InputSprocket mouse devices",
                 mac_isp_mouse_count, (unsigned long)available_count);
}

static void Mac_QuitInputSprocket(void)
{
    OSStatus err;

    if (!mac_isp_started)
        return;

    mac_isp_wants_capture = 0;
    mac_isp_foreground = 0;
    Mac_InputSprocketApplyCapture();
    err = ISpShutdown();
    if (err != noErr)
        Mac_InputSprocketReportError("shutdown", err);
    mac_isp_started = 0;
    mac_isp_mouse_count = 0;
    mac_isp_active = 0;
    mac_isp_suspended = 0;
    mac_isp_foreground = 0;
}

void Mac_InputSprocketSetCapture(int enabled)
{
    mac_isp_wants_capture = enabled ? 1 : 0;
    Mac_InputSprocketApplyCapture();
}

void Mac_InputSprocketSetForeground(int active)
{
    OSStatus err;

    active = active ? 1 : 0;
    if (!mac_isp_started) {
        mac_isp_foreground = active;
        return;
    }

    if (!active) {
        mac_isp_foreground = 0;
        Mac_InputSprocketApplyCapture();
        if (!mac_isp_suspended) {
            err = ISpSuspend();
            if (err == noErr || err == kISpSystemInactiveErr)
                mac_isp_suspended = 1;
            else
                Mac_InputSprocketReportError("suspend", err);
        }
        return;
    }

    if (mac_isp_suspended) {
        err = ISpResume();
        if (err != noErr && err != kISpSystemActiveErr) {
            Mac_InputSprocketReportError("resume", err);
            return;
        }
        mac_isp_suspended = 0;
    }
    mac_isp_foreground = 1;
    Mac_InputSprocketApplyCapture();
}

int Mac_InputSprocketIsActive(void)
{
    return mac_isp_active;
}

int Mac_InputSprocketPoll(int *dx, int *dy)
{
    Sint32 total_x = 0;
    Sint32 total_y = 0;
    Uint32 button_mask = 0;
    int i;
    int j;

    *dx = 0;
    *dy = 0;
    if (!mac_isp_active)
        return 0;

    /* Some drivers deliver fresh samples from ISpTickle. Service them on
       every SDL pump so Classic's 60 Hz TickCount does not pace the mouse. */
    {
        OSStatus err = ISpTickle();
        if (err != noErr)
            Mac_InputSprocketReportError("tickle", err);
    }

    for (i = 0; i < mac_isp_mouse_count; ++i) {
        UInt32 state_x = 0;
        UInt32 state_y = 0;
        OSStatus err_x;
        OSStatus err_y;

        err_x = ISpElement_GetSimpleState(mac_isp_mice[i].delta_x,
                                           &state_x);
        err_y = ISpElement_GetSimpleState(mac_isp_mice[i].delta_y,
                                           &state_y);
        if (err_x == noErr && err_y == noErr) {
            total_x += (Sint32)state_x;
            total_y += (Sint32)state_y;
        } else {
            Mac_InputSprocketReportError("poll-delta",
                                         err_x != noErr ? err_x : err_y);
        }

        for (j = 0; j < mac_isp_mice[i].button_count; ++j) {
            MacISpButton *button = &mac_isp_mice[i].buttons[j];
            ISpElementEvent event;
            Boolean was_event = false;
            int event_limit = 64;

            do {
                OSStatus event_err = ISpElement_GetNextEvent(
                    button->element, sizeof(event), &event, &was_event);
                if (event_err != noErr) {
                    Mac_InputSprocketReportError("poll-button", event_err);
                    break;
                }
                if (was_event)
                    button->down = event.data != 0;
            } while (was_event && --event_limit > 0);

            if (button->down)
                button_mask |= SDL_BUTTON(button->sdl_button);
        }
    }

    if (sdlw && button_mask != mac_isp_sent_buttons) {
        Uint8 button;

        for (button = SDL_BUTTON_LEFT; button <= SDL_BUTTON_X2; ++button) {
            const Uint32 bit = SDL_BUTTON(button);
            if ((button_mask ^ mac_isp_sent_buttons) & bit) {
                SDL_SendMouseButton(sdlw, 0,
                    (button_mask & bit) ? SDL_PRESSED : SDL_RELEASED,
                    button);
            }
        }
        mac_isp_sent_buttons = button_mask;
    }

    mac_isp_accum_x += total_x;
    mac_isp_accum_y -= total_y;
    *dx = mac_isp_accum_x / MAC_ISP_MOUSE_UNITS_PER_PIXEL;
    *dy = mac_isp_accum_y / MAC_ISP_MOUSE_UNITS_PER_PIXEL;
    mac_isp_accum_x -= *dx * MAC_ISP_MOUSE_UNITS_PER_PIXEL;
    mac_isp_accum_y -= *dy * MAC_ISP_MOUSE_UNITS_PER_PIXEL;
    return 1;
}

#else

static void Mac_InitInputSprocket(void) {}
static void Mac_QuitInputSprocket(void) {}
void Mac_InputSprocketSetCapture(int enabled) { (void)enabled; }
void Mac_InputSprocketSetForeground(int active) { (void)active; }
int Mac_InputSprocketIsActive(void) { return 0; }
int Mac_InputSprocketPoll(int *dx, int *dy)
{
    *dx = *dy = 0;
    return 0;
}

#endif

static void Mac_SetArrowCursor(void)
{
#if TARGET_API_MAC_CARBON
    Cursor arrow;
    GetQDGlobalsArrow(&arrow);
    SetCursor(&arrow);
#else
    if (theQD)
        SetCursor(&theQD->arrow);
    else
        InitCursor();
#endif
}

static void Mac_SetInvisibleCursor(void)
{
    /* A zero image and zero mask is a fully transparent 16x16 cursor. */
    SetCursor(&mac_invisible_cursor);
}

static SDL_Cursor *Mac_CreateDefaultCursor(void)
{
    SDL_Cursor *cursor = (SDL_Cursor *)SDL_calloc(1, sizeof(*cursor));

    if (!cursor)
        SDL_OutOfMemory();
    return cursor;
}

static void Mac_FreeCursor(SDL_Cursor *cursor)
{
    SDL_free(cursor);
}

static int Mac_ShowCursor(SDL_Cursor *cursor)
{
    /* The Classic Cursor Manager uses a visibility counter. Only make
       balanced transitions, and never leave the host cursor hidden after
       this process loses the foreground. */
    const int visible = (cursor != NULL || !mac_window_active);

    if (visible) {
        Mac_SetArrowCursor();
        if (!mac_cursor_visible) {
            ShowCursor();
            mac_cursor_visible = 1;
        }
    } else {
        Mac_SetInvisibleCursor();
        if (mac_cursor_visible) {
            HideCursor();
            mac_cursor_visible = 0;
        }
    }
    return 0;
}

static void Mac_MoveCursorGlobal(Point where)
{
#if !TARGET_API_MAC_CARBON
    CursorDevicePtr device = NULL;

    /* Universal Interfaces' PPC CursorDevicesGlue fixes the Mixed Mode
       transition used by these Cursor Device Manager calls. */
    if (CursorDeviceNextDevice(&device) == noErr && device != NULL &&
        CursorDeviceMoveTo(device, where.h, where.v) == noErr) {
        return;
    }

    /* Cursor Device Manager should always exist on Mac OS 9. Keep a
       low-memory fallback for unusual Classic installations and emulators. */
#ifdef BUILDING_FOR_PRE9
    /* Those were added to InterfaceLib for MacOS 9, but not earlier MacOS */ 
    /* For those we bang the actual low memory globals */
    *(Point *)0x0830 = where;  /* LMSetMouseTemp */
    *(Point *)0x0828 = where;  /* LMSetRawMouseLocation */
    *(Point *)0x082C = where; /* LMSetMouseLocation */
    *(char *)0x08CE = 0xff;  /* Force mouse pointer to draw */ 
#else
    LMSetMouseTemp(where);
    LMSetRawMouseLocation(where);
    LMSetMouseLocation(where);
#endif
#else
    typedef struct MacCGPoint {
        float x;
        float y;
    } MacCGPoint;
    typedef SInt32 (*CGWarpMouseCursorPositionProc)(MacCGPoint);
    static CGWarpMouseCursorPositionProc warp_cursor;
    static int looked_up;

    if (!looked_up) {
        CFBundleRef bundle;

        looked_up = 1;
        bundle = CFBundleGetBundleWithIdentifier(CFSTR("com.apple.CoreGraphics"));
        if (!bundle) {
            CFURLRef url = CFURLCreateWithFileSystemPath(
                kCFAllocatorDefault,
                CFSTR("/System/Library/Frameworks/ApplicationServices.framework/Frameworks/CoreGraphics.framework"),
                kCFURLPOSIXPathStyle, true);
            if (url) {
                bundle = CFBundleCreate(kCFAllocatorDefault, url);
                CFRelease(url);
            }
        }
        if (bundle) {
            warp_cursor = (CGWarpMouseCursorPositionProc)
                CFBundleGetFunctionPointerForName(
                    bundle, CFSTR("CGWarpMouseCursorPosition"));
        }
    }

    if (warp_cursor) {
        MacCGPoint point;

        point.x = (float)where.h;
        point.y = (float)where.v;
        warp_cursor(point);
    }
#endif
}

static void Mac_WarpMouse(SDL_Window *window, int x, int y)
{
    GrafPtr saved_port;
    Point where;
    Rect bounds;
    int port_w;
    int port_h;

    (void)window;
    if (!macport)
        return;

#if TARGET_API_MAC_CARBON
    GetPortBounds(macport, &bounds);
#else
    bounds = macport->portRect;
#endif
    port_w = bounds.right - bounds.left;
    port_h = bounds.bottom - bounds.top;
    if (sdlw && sdlw->w > 0 && port_w > 0)
        x = bounds.left + (int)(((long)x * port_w) / sdlw->w);
    if (sdlw && sdlw->h > 0 && port_h > 0)
        y = bounds.top + (int)(((long)y * port_h) / sdlw->h);
    where.h = (short)x;
    where.v = (short)y;
    GetPort(&saved_port);
    SetPort((GrafPtr)macport);
    LocalToGlobal(&where);
    SetPort(saved_port);
    Mac_MoveCursorGlobal(where);
}

static int Mac_WarpMouseGlobal(int x, int y)
{
    Point where;

    where.h = (short)x;
    where.v = (short)y;
    Mac_MoveCursorGlobal(where);
    return 0;
}

void Mac_CenterMouse(void)
{
    if (sdlw && macwindow) {
        Mac_WarpMouse(sdlw, sdlw->w / 2, sdlw->h / 2);
        if (mac_relative_mouse && mac_window_active)
            Mac_SetInvisibleCursor();
    }
}

static int Mac_SetRelativeMouseMode(SDL_bool enabled)
{
    const int relative = enabled ? 1 : 0;

    if (mac_relative_mouse != relative) {
        mac_relative_mouse = relative;
        Mac_ResetMouseTracking();
    }
    Mac_InputSprocketSetCapture(mac_relative_mouse);
    if (mac_relative_mouse && mac_window_active &&
        !Mac_InputSprocketIsActive())
        Mac_CenterMouse();
    return 0;
}

int Mac_IsRelativeMouseMode(void)
{
    return mac_relative_mouse;
}

void Mac_ForceShowCursor(void)
{
    Mac_SetArrowCursor();
    if (!mac_cursor_visible) {
        ShowCursor();
        mac_cursor_visible = 1;
    }
}

int Mac_InitMouse(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    SDL_Cursor *cursor;

    mac_cursor_visible = 1;
    mac_relative_mouse = 0;
    SDL_zero(mac_invisible_cursor);
    mouse->ShowCursor = Mac_ShowCursor;
    mouse->FreeCursor = Mac_FreeCursor;
    mouse->WarpMouse = Mac_WarpMouse;
    mouse->WarpMouseGlobal = Mac_WarpMouseGlobal;
    mouse->SetRelativeMouseMode = Mac_SetRelativeMouseMode;

    /* The generic SDL fallback uses overlapping 0xff channel masks, which
       this branch rejects as an unknown pixel format. Without a non-NULL
       sentinel, SDL_ShowCursor(false) returns before Mac_ShowCursor(NULL)
       can reach QuickDraw's HideCursor. Classic only needs identity here;
       QuickDraw continues to own and draw the native arrow. */
    cursor = Mac_CreateDefaultCursor();
    if (!cursor)
        return -1;
    SDL_SetDefaultCursor(cursor);
    Mac_InitInputSprocket();
    return 0;
}

void Mac_QuitMouse(void)
{
    mac_relative_mouse = 0;
    Mac_InputSprocketSetCapture(0);
    Mac_QuitInputSprocket();
    Mac_ForceShowCursor();
}

#endif
