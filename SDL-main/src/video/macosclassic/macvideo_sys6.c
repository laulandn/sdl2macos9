/*
  System 6.0.8 / Mac Plus video driver for SDL2.

  sdl2macos9 macosclassic is the API skeleton (QNX-style bootstrap,
  CreateWindowFramebuffer). Toolbox calls follow pew-pew-68k /
  opposite-day-68k: 1-bit BitMap, static GrafPort, NewPtr not NewPtrClear,
  hide menubar via $0BAA, BlockMove present. No Color QD, GWorlds,
  DrawSprocket, or NewCWindow.
*/
#include "../../SDL_internal.h"

#if defined(SDL_VIDEO_DRIVER_MACOSCLASSIC) && defined(SDL_MACOSCLASSIC_SYS6)

#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_keyboard_c.h"
#include "../../events/SDL_windowevents_c.h"
#include "sdl_mac.h"

#include "../../events/SDL_mouse_c.h"

#include <Quickdraw.h>
#include <Windows.h>
#include <Events.h>
#include <Fonts.h>
#include <Menus.h>
#include <MacMemory.h>
#include <OSUtils.h>

static void SYS6_DestroyWindowFramebuffer(_THIS, SDL_Window *window);

#define SYS6_SURFACE "_SDL_Sys6Surface"

WindowPtr macwindow;
GrafPtr macport;
SDL_Window *sdlw;
int mac_window_active;

static short gOldMBar;
static int gChrome;
static int gToolbox;

static void sys6_hide_chrome(void)
{
    volatile short *mbar = (short *)0x0BAAL;
    if (gChrome) {
        return;
    }
    gOldMBar = *mbar;
    if (gOldMBar <= 0) {
        gOldMBar = 20;
    }
    *mbar = 0;
    gChrome = 1;
}

static void sys6_show_chrome(void)
{
    volatile short *mbar = (short *)0x0BAAL;
    if (!gChrome) {
        return;
    }
    ShowCursor();
    InitCursor();
    *mbar = gOldMBar;
    DrawMenuBar();
    gChrome = 0;
}

static void sys6_init_toolbox(void)
{
    if (gToolbox) {
        return;
    }
    InitGraf(&qd.thePort);
    InitFonts();
    InitWindows();
    InitCursor();
    FlushEvents(everyEvent, 0);
    gToolbox = 1;
}

static void sys6_present(SDL_Surface *surface)
{
    unsigned char *src;
    unsigned char *dst;
    short srb, drb, y, n, h;

    if (!surface || !surface->pixels) {
        return;
    }
    src = (unsigned char *)surface->pixels;
    srb = (short)surface->pitch;
    dst = (unsigned char *)qd.screenBits.baseAddr;
    drb = (short)(qd.screenBits.rowBytes & 0x3FFF);
    if (!dst) {
        return;
    }
    h = (short)surface->h;
    if (h > (qd.screenBits.bounds.bottom - qd.screenBits.bounds.top)) {
        h = (short)(qd.screenBits.bounds.bottom - qd.screenBits.bounds.top);
    }
    n = srb;
    if (n > drb) {
        n = drb;
    }
    if (src == dst) {
        return;
    }
    /* BlockMove over the cursor XOR-smears it. The player follows the
     * mouse, so that smear sits on the player sprite. */
    {
        Rect shield;
        Point origin;
        SetRect(&shield, 0, 0, n * 8, h);
        origin.h = 0;
        origin.v = 0;
        ShieldCursor(&shield, origin);
    }
    if (srb == drb && n == srb) {
        BlockMove((Ptr)src, (Ptr)dst, (long)srb * (long)h);
    } else {
        for (y = 0; y < h; y++) {
            BlockMove((Ptr)src, (Ptr)dst, n);
            src += srb;
            dst += drb;
        }
    }
    ShowCursor();
}

static int SYS6_VideoInit(_THIS)
{
    SDL_DisplayMode mode;
    Rect sb;
    int w, h;

    sys6_init_toolbox();
    sb = qd.screenBits.bounds;
    w = sb.right - sb.left;
    h = sb.bottom - sb.top;
    if (w > 512) {
        w = 512;
    }
    if (h > 342) {
        h = 342;
    }
    w &= ~15;
    if (w < 160) {
        w = 160;
    }
    if (h < 160) {
        h = 160;
    }

    SDL_zero(mode);
    mode.format = SDL_PIXELFORMAT_INDEX1MSB;
    mode.w = w;
    mode.h = h;
    mode.refresh_rate = 60;
    if (SDL_AddBasicVideoDisplay(&mode) < 0) {
        return -1;
    }
    SDL_AddDisplayMode(&_this->displays[0], &mode);
    return 0;
}

static void SYS6_VideoQuit(_THIS)
{
    (void)_this;
    if (macwindow) {
        DisposeWindow(macwindow);
        macwindow = NULL;
    }
    macport = NULL;
    sdlw = NULL;
    mac_window_active = 0;
    sys6_show_chrome();
}

static int SYS6_CreateWindow(_THIS, SDL_Window *window)
{
    Rect r;

    (void)_this;
    if (sdlw || macwindow) {
        return SDL_SetError("System 6 SDL2 supports one window");
    }
    sys6_init_toolbox();
    sys6_hide_chrome();
    r = qd.screenBits.bounds;
    macwindow = NewWindow(NULL, &r, "\p", true, plainDBox, (WindowPtr)-1L, false, 0);
    if (!macwindow) {
        sys6_show_chrome();
        return SDL_SetError("Unable to create System 6 window");
    }
    macport = (GrafPtr)macwindow;
    SetPort(macport);
    PenPat(&qd.black);
    BackPat(&qd.white);
    PaintRect(&macwindow->portRect);
    sdlw = window;
    mac_window_active = 1;
    window->driverdata = macwindow;
    SDL_SetKeyboardFocus(window);
    SDL_SetMouseFocus(window);
    return 0;
}

static void SYS6_DestroyWindow(_THIS, SDL_Window *window)
{
    (void)_this;
    (void)window;
    if (macwindow) {
        DisposeWindow(macwindow);
        macwindow = NULL;
    }
    macport = NULL;
    sdlw = NULL;
    mac_window_active = 0;
    sys6_show_chrome();
}

static void SYS6_SetWindowTitle(_THIS, SDL_Window *window)
{
    (void)_this;
    (void)window;
}

static void SYS6_ShowWindow(_THIS, SDL_Window *window)
{
    (void)_this;
    (void)window;
    if (macwindow) {
        ShowWindow(macwindow);
        SelectWindow(macwindow);
        mac_window_active = 1;
    }
}

static int SYS6_CreateWindowFramebuffer(_THIS, SDL_Window *window,
                                        Uint32 *format, void **pixels, int *pitch)
{
    SDL_Surface *surface;
    SDL_Color colors[2];
    int w, h;

    SYS6_DestroyWindowFramebuffer(_this, window);
    SDL_GetWindowSizeInPixels(window, &w, &h);
    w &= ~15;
    if (w < 16) {
        w = 16;
    }
    surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, 1, SDL_PIXELFORMAT_INDEX1MSB);
    if (!surface) {
        return -1;
    }
    /* Mac 1-bit: 0 paper (white), 1 ink (black). */
    colors[0].r = colors[0].g = colors[0].b = 255;
    colors[0].a = 255;
    colors[1].r = colors[1].g = colors[1].b = 0;
    colors[1].a = 255;
    if (surface->format->palette) {
        SDL_SetPaletteColors(surface->format->palette, colors, 0, 2);
    }
    SDL_SetWindowData(window, SYS6_SURFACE, surface);
    *format = SDL_PIXELFORMAT_INDEX1MSB;
    *pixels = surface->pixels;
    *pitch = surface->pitch;
    return 0;
}

static int SYS6_UpdateWindowFramebuffer(_THIS, SDL_Window *window,
                                        const SDL_Rect *rects, int numrects)
{
    SDL_Surface *surface;

    (void)_this;
    (void)rects;
    (void)numrects;
    surface = (SDL_Surface *)SDL_GetWindowData(window, SYS6_SURFACE);
    if (!surface) {
        return SDL_SetError("System 6 framebuffer is missing");
    }
    sys6_present(surface);
    return 0;
}

static void SYS6_DestroyWindowFramebuffer(_THIS, SDL_Window *window)
{
    SDL_Surface *surface;

    (void)_this;
    surface = (SDL_Surface *)SDL_SetWindowData(window, SYS6_SURFACE, NULL);
    SDL_FreeSurface(surface);
}

static void SYS6_DeleteDevice(SDL_VideoDevice *device)
{
    SYS6_VideoQuit(device);
    SDL_free(device);
}

static SDL_VideoDevice *SYS6_CreateDevice(void)
{
    SDL_VideoDevice *device;

    device = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        SDL_OutOfMemory();
        return NULL;
    }
    device->VideoInit = SYS6_VideoInit;
    device->VideoQuit = SYS6_VideoQuit;
    device->CreateSDLWindow = SYS6_CreateWindow;
    device->DestroyWindow = SYS6_DestroyWindow;
    device->SetWindowTitle = SYS6_SetWindowTitle;
    device->ShowWindow = SYS6_ShowWindow;
    device->CreateWindowFramebuffer = SYS6_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = SYS6_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = SYS6_DestroyWindowFramebuffer;
    device->PumpEvents = SDL_Mac_pumpEvents;
    device->free = SYS6_DeleteDevice;
    return device;
}

#if !TARGET_API_MAC_CARBON
struct QDGlobals *theQD = NULL;

void SDL_InitQuickDraw(struct QDGlobals *the_qd)
{
    theQD = the_qd;
}
#endif

VideoBootStrap Mac_bootstrap = {
    "macosclassic", "Mac Plus / System 6 QuickDraw",
    SYS6_CreateDevice,
    NULL
};

#endif /* SDL_VIDEO_DRIVER_MACOSCLASSIC && SDL_MACOSCLASSIC_SYS6 */
