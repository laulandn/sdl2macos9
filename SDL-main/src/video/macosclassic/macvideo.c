/* Classic Mac OS video driver, originally derived from SDL's QNX driver. */

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
#include "../../events/SDL_windowevents_c.h"
#include "sdl_mac.h"
#ifdef TARGET_OS_OSX
#else
#include <Displays.h>
#include <Processes.h>
#endif
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
#include <DrawSprocket.h>
#endif

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC


extern void SDL_Mac_pumpEvents(_THIS);

/* State shared with the Classic event, mouse, and OpenGL modules. */
WindowPtr macwindow=NULL;
CGrafPtr macport=NULL;
static PixMapPtr thePM=NULL;
static char *mypixels=NULL;
static int drawWidth,drawHeight;
static int myWidth,myHeight;
int myDepth;
static int screenWidth,screenHeight;
static void cleanupMac(void);
static SDL_VideoDevice *sdlvdev=NULL;
static SDL_VideoDisplay *sdlvdisp=NULL;
SDL_Window *sdlw=NULL;
static SDL_VideoDevice *tdevice=NULL;

/* DrawSprocket owns an exclusive display context while SDL is in true
   fullscreen. AGL manages its own buffers, so OpenGL contexts need only one
   DrawSprocket page. */
static GDHandle mac_display_device;
static DisplayIDType mac_display_id;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static DSpContextReference mac_dsp_context;
static int mac_dsp_started;
static int mac_dsp_active;
static CGrafPtr mac_dsp_back_buffer;
static PixMapHandle mac_dsp_back_pixmap;
static int mac_dsp_software_buffer;
static int mac_dsp_page_flipping;
#endif
static int mac_fullscreen_window;
static int macwindow_visible;
static int mac_gl_reattach_pending;
static Rect mac_windowed_bounds;
static int mac_windowed_bounds_valid;

static void Mac_SetNativeWindowTitle(WindowPtr window, const char *title)
{
  Str255 ptitle; /* MJS */
  size_t length = title ? SDL_strlen(title) : 0;

  if (length > 255) length = 255;
  ptitle[0] = (unsigned char)length;
  if (length) SDL_memcpy(ptitle + 1, title, length); /* MJS */
  SetWTitle(window, ptitle); /* MJS */
}

static void Mac_GetWindowGlobalBounds(Rect *bounds)
{
  Rect local;
  Point point;

  if (!bounds || !macport) return;
#if TARGET_API_MAC_CARBON
  GetPortBounds(macport, &local);
#else
  local = macport->portRect;
#endif
  SetPort((GrafPtr)macport);
  point.h = local.left;
  point.v = local.top;
  LocalToGlobal(&point);
  bounds->left = point.h;
  bounds->top = point.v;
  point.h = local.right;
  point.v = local.bottom;
  LocalToGlobal(&point);
  bounds->right = point.h;
  bounds->bottom = point.v;
}

static WindowPtr Mac_NewNativeWindow(const Rect *bounds, int fullscreen,
                                     const char *title)
{
  WindowPtr window;
  short proc_id = fullscreen ? plainDBox : noGrowDocProc + 8;

  window = NewCWindow(NULL, bounds, (ConstStr255Param)"\pMac SDL2 Window",
                      false, proc_id, (WindowPtr)(-1L),
                      fullscreen ? false : true, 0L);
  if (window) Mac_SetNativeWindowTitle(window, title);
  return window;
}

static int Mac_ReplaceNativeWindow(SDL_Window *window, const Rect *bounds,
                                   int fullscreen)
{
  WindowPtr old_window = macwindow;
  WindowPtr new_window;
  int was_visible = macwindow_visible;
  int was_active = mac_window_active;

  new_window = Mac_NewNativeWindow(bounds, fullscreen,
                                   window ? window->title : NULL);
  if (!new_window) return SDL_SetError("Unable to create Classic fullscreen window");

#ifdef SDL_VIDEO_OPENGL
  if (Mac_GL_SetDrawableActive(0) < 0) {
    Mac_GL_SetDrawableActive(1);
    DisposeWindow(new_window);
    return -1;
  }
#endif

  macwindow = new_window;
#ifdef __MWERKS__
  macport = (CGrafPtr)macwindow;
#else
  macport = GetWindowPort(macwindow);
#endif
  SetPort((GrafPtr)macport);
  if (old_window) DisposeWindow(old_window);

  myWidth = bounds->right - bounds->left;
  myHeight = bounds->bottom - bounds->top;
  drawWidth = myWidth;
  drawHeight = myHeight;
  mac_fullscreen_window = fullscreen ? 1 : 0;

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
  if (fullscreen && mac_dsp_active) {
    ShowWindow(macwindow);
    SelectWindow(macwindow);
    macwindow_visible = 1;
  } else 
#endif
  if (was_visible) {
    ShowWindow(macwindow);
    if (was_active) SelectWindow(macwindow);
  }
  if (was_active) {
#ifdef SDL_VIDEO_OPENGL
    if (Mac_GL_SetDrawableActive(1) < 0) {
      mac_gl_reattach_pending = 1;
      return -1;
    }
    mac_gl_reattach_pending = 0;
#endif
  }
  return 0;
}

static void Mac_UpdateDisplayMetrics(void)
{
  PixMapHandle pixmap;
  Rect bounds;

  mac_display_device = GetMainDevice();
  if (!mac_display_device) return;
  pixmap = (**mac_display_device).gdPMap;
  if (!pixmap) return;
  bounds = (**mac_display_device).gdRect;
  screenWidth = bounds.right - bounds.left;
  screenHeight = bounds.bottom - bounds.top;
  myDepth = (**pixmap).pixelSize;
}

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static void Mac_InitDSpAttributes(DSpContextAttributes *attributes,
                                  int width, int height, int depth)
{
  OptionBits depth_mask = depth == 16 ? kDSpDepthMask_16 : kDSpDepthMask_32;

  SDL_zero(*attributes);
  attributes->displayWidth = (UInt32)width;
  attributes->displayHeight = (UInt32)height;
  attributes->colorNeeds = kDSpColorNeeds_Require;
  attributes->displayDepthMask = depth_mask;
  attributes->backBufferDepthMask = depth_mask;
  attributes->displayBestDepth = (UInt32)depth;
  attributes->backBufferBestDepth = (UInt32)depth;
  attributes->pageCount = 1;
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static int Mac_FindDSpMode(int width, int height, int depth, int *refresh_rate)
{
  DSpContextReference context;
  DSpContextAttributes attributes;
  OSStatus error;

  if (!mac_dsp_started) return 0;
  error = DSpGetFirstContext(mac_display_id, &context);
  while (error == noErr) {
    if (DSpContext_GetAttributes(context, &attributes) == noErr &&
        attributes.displayWidth == (UInt32)width &&
        attributes.displayHeight == (UInt32)height &&
        attributes.displayBestDepth == (UInt32)depth) {
      Fixed frequency = attributes.frequency;
      if (!frequency) DSpContext_GetMonitorFrequency(context, &frequency);
      if (refresh_rate) {
        *refresh_rate = frequency ? (int)((frequency + 0x8000L) >> 16) : 60;
      }
      return 1;
    }
    error = DSpGetNextContext(context, &context);
  }
  return 0;
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static void Mac_AddDSpModes(SDL_VideoDisplay *display)
{
  DSpContextReference context;
  DSpContextAttributes attributes;
  OSStatus error;

  if (!mac_dsp_started) return;
  error = DSpGetFirstContext(mac_display_id, &context);
  while (error == noErr) {
    if (DSpContext_GetAttributes(context, &attributes) == noErr &&
        (attributes.displayBestDepth == 16 ||
         attributes.displayBestDepth == 32)) {
      SDL_DisplayMode mode;
      Fixed frequency = attributes.frequency;

      if (!frequency) DSpContext_GetMonitorFrequency(context, &frequency);
      SDL_zero(mode);
      mode.w = (int)attributes.displayWidth;
      mode.h = (int)attributes.displayHeight;
      mode.refresh_rate =
          frequency ? (int)((frequency + 0x8000L) >> 16) : 60;
      mode.format = attributes.displayBestDepth == 16
                        ? SDL_PIXELFORMAT_RGB555
                        : SDL_PIXELFORMAT_RGB888;
#ifdef MAC_DEBUG
      fprintf(stderr,"Adding mode %d by %d rate %d format %ld\n",mode.w,mode.h,mode.refresh_rate,mode.format); fflush(stderr);
#endif
      SDL_AddDisplayMode(display, &mode);
    }
    error = DSpGetNextContext(context, &context);
  }
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static void Mac_ReleaseSoftwareBackBuffer(void)
{
  if (mac_dsp_back_pixmap) UnlockPixels(mac_dsp_back_pixmap);
  if (mac_dsp_software_buffer) mypixels = NULL;
  mac_dsp_back_pixmap = NULL;
  mac_dsp_back_buffer = NULL;
  mac_dsp_software_buffer = 0;
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static OSStatus Mac_ReleaseDSpContext(void)
{
    OSStatus first_error = noErr;
    OSStatus error;

  Mac_ReleaseSoftwareBackBuffer();
  mac_dsp_page_flipping = 0;
  if (!mac_dsp_context) return noErr;
    if (mac_dsp_active) {
        DSpContext_FadeGammaOut(NULL, NULL);
        error = DSpContext_SetState(mac_dsp_context, kDSpContextState_Inactive);
        if (error != noErr) {
            first_error = error;
        } else {
            mac_dsp_active = 0;
        }
        DSpContext_FadeGammaIn(NULL, NULL);
    }
    error = DSpContext_Release(mac_dsp_context);
    if (first_error == noErr && error != noErr) first_error = error;
    if (error == noErr) {
        mac_dsp_context = NULL;
        mac_dsp_active = 0;
    }
    Mac_UpdateDisplayMetrics();
    return first_error;
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
void Mac_ProcessDrawSprocketEvent(EventRecord *event)
{
    Boolean processed = false;
    OSStatus error;

    if (!mac_dsp_started || !event || event->what != osEvt ||
        ((event->message >> 24) & 0xff) != suspendResumeMessage) {
        return;
    }

    /* DrawSprocket temporarily restores the desktop display on suspend and
       reapplies the reserved context on resume. Apple requires every process
       switch event to pass through DSpProcessEvent. */
    error = DSpProcessEvent(event, &processed);
    if (error != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: DSpProcessEvent failed (%ld)",
                    (long)error);
    }
}
#endif

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static void Mac_ShutdownDrawSprocket(void)
{
    OSStatus error;

    error = Mac_ReleaseDSpContext();
    if (error != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: failed to release DrawSprocket context (%ld)",
                    (long)error);
    }
    if (mac_dsp_started) {
        error = DSpShutdown();
        if (error != noErr) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "macosclassic: DSpShutdown failed (%ld)",
                        (long)error);
        }
        mac_dsp_started = 0;
    }
  mac_dsp_context = NULL;
  mac_dsp_active = 0;
  mac_dsp_page_flipping = 0;
  mac_display_id = 0;
}
#endif

int Mac_IsFrontProcess(void)
{
  ProcessSerialNumber current;
  ProcessSerialNumber front;
  Boolean same = false;

  return GetCurrentProcess(&current) == noErr &&
         GetFrontProcess(&front) == noErr &&
         SameProcess(&current, &front, &same) == noErr && same;
}

#if !TARGET_API_MAC_CARBON
/* Since we don't initialize QuickDraw, we need to get a pointer to qd */
#if !TARGET_API_MAC_CARBON
struct QDGlobals *theQD = NULL;
#endif
#endif

static int openTheWindow(int w,int h)
{
    struct Rect WindowBox;

  myWidth=w; myHeight=h;

#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic Going to NewCWindow...\n"); fflush(stderr);
#endif
  WindowBox.top=WINDOW_OFFSET_Y;  WindowBox.left=WINDOW_OFFSET_X;
  WindowBox.bottom=myHeight+WINDOW_OFFSET_Y;  WindowBox.right=myWidth+WINDOW_OFFSET_X;
  macwindow=Mac_NewNativeWindow(&WindowBox, 0, "Mac SDL2 Window");
  if(!macwindow) {
    return SDL_SetError("Unable to create Classic Mac OS window");
  }
#ifdef __MWERKS__
  macport=(CGrafPtr)macwindow;
#else
  macport=GetWindowPort(macwindow);
#endif
  SetPort((GrafPtr)macport);
  thePM=NULL;
  mac_fullscreen_window=0;
  macwindow_visible=0;
#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic Window done\n"); fflush(stderr);
#endif
  return 0;
}

/**
 * Initializes the Classic Mac OS video driver.
 * @param   _THIS
 * @return  0 if successful, -1 on error
 */
static int videoInit(_THIS)
{
    SDL_VideoDisplay display;
    SDL_DisplayMode m;
    GDHandle gDev;
    PixMapHandle gdpm;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    OSStatus dsp_error;
    NumVersion dsp_version;
#endif

#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic videoInit...\n"); fflush(stderr);
#endif

  myWidth=PLATFORM_SCREEN_WIDTH;
  myHeight=PLATFORM_SCREEN_HEIGHT;
  myDepth=PLATFORM_SCREEN_DEPTH;

#if !TARGET_API_MAC_CARBON
  if (!theQD)
    return SDL_SetError("Classic Toolbox initialization is unavailable");
  myWidth=theQD->screenBits.bounds.right;
  myHeight=theQD->screenBits.bounds.bottom;
#endif

  /* SDL exposes the main display only.  Use its GDevice explicitly so the
     DrawSprocket display ID and the desktop mode always describe the same
     monitor, even if another device happened to be current. */
  gDev=GetMainDevice();
  if(!gDev)
    return SDL_SetError("Unable to get the main Classic display");
  gdpm=(**gDev).gdPMap;
  if(!gdpm)
    return SDL_SetError("The main Classic display has no pixel map");

  /* The display mode advertised to SDL must match the active QuickDraw
     device rather than using a hard-coded pixel depth. */
  myDepth=(**gdpm).pixelSize;
  if(myDepth!=16 && myDepth!=32) {
    return SDL_SetError("Unsupported Classic display depth: %d",myDepth);
  }

  mac_display_device = gDev;
  myWidth = (**gDev).gdRect.right - (**gDev).gdRect.left;
  myHeight = (**gDev).gdRect.bottom - (**gDev).gdRect.top;

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
#ifdef MAC_DEBUG
  fprintf(stderr,"Starting DrawSprocket...\n"); fflush(stderr);
#endif
  /* DSpFindBestContextOnDisplayID arrived in DrawSprocket 1.7, but Apple
     documents a context-reservation bug before 1.7.3. Older installations
     keep the existing windowed desktop path without fullscreen modes. */
  dsp_error = DSpStartup();
  if (dsp_error == noErr) {
    dsp_version = DSpGetVersion();
    if ((dsp_version.majorRev > 1 ||
         (dsp_version.majorRev == 1 && dsp_version.minorAndBugRev >= 0x73)) &&
        DMGetDisplayIDByGDevice(gDev, &mac_display_id, false) == noErr) {
      mac_dsp_started = 1;
      SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                   "macosclassic: DrawSprocket %x.%02x ready",
                   (unsigned)dsp_version.majorRev,
                   (unsigned)dsp_version.minorAndBugRev);
    } else {
      dsp_error = DSpShutdown();
      if (dsp_error != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: DSpShutdown failed (%ld)",
                    (long)dsp_error);
      }
      SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                  "macosclassic: DrawSprocket 1.7.3 display support unavailable");
    }
  } else {
    SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                "macosclassic: DSpStartup failed (%ld); fullscreen disabled",
                (long)dsp_error);
  }
#ifdef MAC_DEBUG
  fprintf(stderr,"DrawSprocket ready\n"); fflush(stderr);
#endif
#endif

  drawWidth=myWidth;  drawHeight=myHeight;
  screenWidth=myWidth; screenHeight=myHeight;

  SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
               "macosclassic: using display %dx%dx%d",
               myWidth, myHeight, myDepth);

    SDL_zero(display);
    SDL_zero(m);

    m.w=myWidth;
    m.h=myHeight;    

    if (SDL_AddVideoDisplay(&display, SDL_FALSE) < 0) {
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
        Mac_ShutdownDrawSprocket();
#endif
        return -1;
    }
    
    sdlvdisp=&sdlvdev->displays[0];
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic sdlvdisp is %0lx8\n",(long)sdlvdisp); fflush(stderr);
#endif

    m.w=myWidth;
    m.h=myHeight;
    m.refresh_rate=60;
    if(myDepth==16) m.format=SDL_PIXELFORMAT_RGB555;
    else m.format=SDL_PIXELFORMAT_RGB888;

    SDL_AddDisplayMode(sdlvdisp,&m);
    SDL_SetCurrentDisplayMode(sdlvdisp,&m);
    SDL_SetDesktopDisplayMode(sdlvdisp,&m);

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
#ifdef MAC_DEBUG
    fprintf(stderr,"Adding DrawSprocket modes...\n"); fflush(stderr);
#endif
    Mac_AddDSpModes(sdlvdisp);
#endif

    _this->num_displays = 1;
    Mac_InitAppleEvents();
    if (Mac_InitMouse() < 0) {
        Mac_QuitAppleEvents();
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
        Mac_ShutdownDrawSprocket();
#endif
        return -1;
    }
    return 0;
}

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
static int setDisplayMode(_THIS, SDL_VideoDisplay *display,
                          SDL_DisplayMode *mode)
{
    DSpContextAttributes attributes;
    DSpContextAttributes actual;
    DSpContextReference context = NULL;
    OSStatus error;
    int was_active = mac_window_active;
    int restoring_desktop;
    int software_pages;
    int requested_depth;

    (void)_this;
    if (!display || !mode) return SDL_SetError("Invalid Classic display mode");

#ifdef MAC_DEBUG
    fprintf(stderr,"setDisplayMode...\n"); fflush(stderr);
#endif

    restoring_desktop =
        mode->w == display->desktop_mode.w &&
        mode->h == display->desktop_mode.h &&
        mode->format == display->desktop_mode.format;

    if (restoring_desktop) {
#ifdef SDL_VIDEO_OPENGL
        if (Mac_GL_SetDrawableActive(0) < 0) {
            Mac_GL_SetDrawableActive(1);
            return -1;
        }
#endif
        error = Mac_ReleaseDSpContext();
#ifdef SDL_VIDEO_OPENGL
        if (error != noErr) {
            if (was_active) Mac_GL_SetDrawableActive(1);
            return SDL_SetError("Unable to restore Classic display mode (%ld)",
                                (long)error);
        }
#endif
        mac_gl_reattach_pending = was_active ? 1 : 0;
        SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                     "macosclassic: restored the desktop display mode");
        return 0;
    }

    if (mode->format == SDL_PIXELFORMAT_RGB555)
        requested_depth = 16;
    else if (mode->format == SDL_PIXELFORMAT_RGB888)
        requested_depth = 32;
    else
        requested_depth = 0;
    if (!mac_dsp_started || !requested_depth ||
        !Mac_FindDSpMode(mode->w, mode->h, requested_depth, NULL)) {
        return SDL_SetError("Unsupported Classic fullscreen mode %dx%dx%d",
                            mode->w, mode->h,
                            (int)SDL_BITSPERPIXEL(mode->format));
    }

#ifdef SDL_VIDEO_OPENGL
    if (Mac_GL_SetDrawableActive(0) < 0) {
        Mac_GL_SetDrawableActive(1);
        return -1;
    }
#endif
    error = Mac_ReleaseDSpContext();
#ifdef SDL_VIDEO_OPENGL
    if (error != noErr) {
        if (was_active) Mac_GL_SetDrawableActive(1);
        return SDL_SetError("Unable to release the previous DrawSprocket mode (%ld)",
                            (long)error);
    }
#endif

    software_pages = sdlw && !(sdlw->flags & SDL_WINDOW_OPENGL);

    Mac_InitDSpAttributes(&attributes, mode->w, mode->h, requested_depth);
    if (mode->refresh_rate > 0)
        attributes.frequency = (Fixed)((long)mode->refresh_rate << 16);

    /* Optional buffering is requested only when reserving the selected
       context. Requiring it during the search would reject contexts that
       DrawSprocket can support with software buffering. */
    error = DSpFindBestContext(&attributes, &context);
    if (error != noErr || !context) {
#ifdef SDL_VIDEO_OPENGL
        if (was_active) Mac_GL_SetDrawableActive(1);
#endif
        return SDL_SetError("DSpFindBestContext failed (%ld)", (long)error);
    }

    /* Reject a merely close result before reserving it. */
    error = DSpContext_GetAttributes(context, &actual);
    if (error != noErr || actual.displayWidth != (UInt32)mode->w ||
        actual.displayHeight != (UInt32)mode->h ||
        actual.displayBestDepth != (UInt32)requested_depth) {
#ifdef SDL_VIDEO_OPENGL
        if (was_active) Mac_GL_SetDrawableActive(1);
#endif
        return SDL_SetError("DrawSprocket context is not exact %dx%dx%d mode",
                            mode->w, mode->h, requested_depth);
    }

    if (software_pages) {
        attributes.pageCount = 2;
        attributes.contextOptions |= kDSpContextOption_PageFlip;
    }
    error = DSpContext_Reserve(context, &attributes);
    if (error != noErr) {
        /* This warning means the reservation succeeded but the game must ask
           the user before switching.  SDL has no confirmation UI in this
           backend, so release the still-inactive context immediately. */
        if (error == kDSpConfirmSwitchWarning) {
            OSStatus release_error = DSpContext_Release(context);
            if (release_error != noErr) {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                            "macosclassic: DSpContext_Release failed (%ld)",
                            (long)release_error);
            }
        }
#ifdef SDL_VIDEO_OPENGL
        if (was_active) Mac_GL_SetDrawableActive(1);
#endif
        if (error == kDSpConfirmSwitchWarning)
            return SDL_SetError("DrawSprocket mode switch requires confirmation");
        return SDL_SetError("DSpContext_Reserve failed (%ld)", (long)error);
    }

    mac_dsp_context = context;
    error = DSpContext_FadeGammaOut(NULL, NULL);
    if (error != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: DSpContext_FadeGammaOut failed (%ld)",
                    (long)error);
    }
    error = DSpContext_SetState(context, kDSpContextState_Active);
    if (error != noErr) {
        OSStatus release_error = Mac_ReleaseDSpContext();
        if (release_error != noErr) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "macosclassic: failed to release inactive context (%ld)",
                        (long)release_error);
        }
#ifdef SDL_VIDEO_OPENGL
        if (was_active) Mac_GL_SetDrawableActive(1);
#endif
        if (error == kDSpConfirmSwitchWarning)
            return SDL_SetError("DrawSprocket mode switch requires confirmation");
        return SDL_SetError("DSpContext_SetState(active) failed (%ld)",
                            (long)error);
    }

    mac_dsp_active = 1;
    mac_dsp_page_flipping = software_pages;
    error = DSpContext_FadeGammaIn(NULL, NULL);
    if (error != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: DSpContext_FadeGammaIn failed (%ld)",
                    (long)error);
    }
    Mac_UpdateDisplayMetrics();
    if (screenWidth != mode->w || screenHeight != mode->h ||
        myDepth != requested_depth) {
        Mac_ReleaseDSpContext();
#ifdef SDL_VIDEO_OPENGL
        if (was_active) Mac_GL_SetDrawableActive(1);
#endif
        return SDL_SetError("DrawSprocket activated %dx%dx%d, expected %dx%dx%d",
                            screenWidth, screenHeight, myDepth,
                            mode->w, mode->h, requested_depth);
    }

    /* SetWindowFullscreen replaces the decorated Toolbox window after SDL
       commits this mode.  Keep AGL detached until it has the final drawable. */
    mac_gl_reattach_pending = was_active ? 1 : 0;
    SDL_LogDebug(SDL_LOG_CATEGORY_VIDEO,
                 "macosclassic: activated DrawSprocket %dx%dx%d",
                 mode->w, mode->h, requested_depth);
    return 0;
}
#endif

static void setWindowFullscreen(_THIS, SDL_Window *window,
                                SDL_VideoDisplay *display,
                                SDL_bool fullscreen)
{
    Rect bounds;
    GDHandle device;

    (void)_this;
    (void)display;
    if (!window || !macwindow) return;

    if (fullscreen) {
        if (!mac_fullscreen_window) {
            if (!mac_windowed_bounds_valid) {
                Mac_GetWindowGlobalBounds(&mac_windowed_bounds);
                mac_windowed_bounds_valid = 1;
            }
            device = GetMainDevice();
            if (!device) {
                SDL_SetError("Unable to get the Classic main display");
                return;
            }
            bounds = (**device).gdRect;
            if (Mac_ReplaceNativeWindow(window, &bounds, 1) < 0) {
                SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                            "macosclassic: fullscreen window failed: %s",
                            SDL_GetError());
            }
        }
    } else if (mac_fullscreen_window) {
        if (mac_windowed_bounds_valid) {
            bounds = mac_windowed_bounds;
        } else {
            bounds.left = WINDOW_OFFSET_X;
            bounds.top = WINDOW_OFFSET_Y;
            bounds.right = bounds.left + window->windowed.w;
            bounds.bottom = bounds.top + window->windowed.h;
        }
        if (Mac_ReplaceNativeWindow(window, &bounds, 0) < 0) {
            SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                        "macosclassic: windowed restore failed: %s",
                        SDL_GetError());
        } else {
            mac_windowed_bounds_valid = 0;
        }
    }
}

static void videoQuit(_THIS)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic videoQuit...\n"); fflush(stderr);
#endif
    cleanupMac();
}

static void destroyWindowFramebuffer(_THIS, SDL_Window *window)
{
    (void)_this;
    (void)window;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    if (mac_dsp_software_buffer) {
        Mac_ReleaseSoftwareBackBuffer();
        mypixels = NULL;
    }
#endif
    if (thePM) {
        SDL_free(thePM);
        thePM = NULL;
    }
    if (mypixels) {
        SDL_free(mypixels);
        mypixels = NULL;
    }
}

/**
 * Creates a new native Screen window and associates it with the given SDL
 * window.
 * @param   _THIS
 * @param   window  SDL window to initialize
 * @return  0 if successful, -1 on error
 */
static int createWindow(_THIS, SDL_Window *window)
{
    if (sdlw || macwindow)
        return SDL_SetError("The Classic Mac OS backend supports one window");

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic createWindow...\n"); fflush(stderr);
#endif

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic requested win is %dx%d\n",window->w,window->h); fflush(stderr);
#endif

    if (!macwindow && openTheWindow(window->w, window->h) < 0) {
        return -1;
    }

    SizeWindow(macwindow,window->w,window->h,TRUE);

    drawWidth=window->w; drawHeight=window->h;
    myWidth=window->w; myHeight=window->h;
#ifdef SDL_VIDEO_OPENGL
    glUpdateWindow(_this, window);
#endif
    Mac_GetWindowGlobalBounds(&mac_windowed_bounds);
    mac_windowed_bounds_valid = 1;

    sdlw=window;
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic sdlw at %08lx\n",(long)sdlw); fflush(stderr);
#endif

    window->driverdata = macwindow;
    return 0;
}

/**
 * Gets a pointer to the Screen buffer associated with the given window. Note
 * that the buffer is actually created in createWindow().
 * @param       _THIS
 * @param       window  SDL window to get the buffer for
 * @param[out]  pixles  Holds a pointer to the window's buffer
 * @param[out]  format  Holds the pixel format for the buffer
 * @param[out]  pitch   Holds the number of bytes per line
 * @return  0 if successful, -1 on error
 */
static int createWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format,
                        void ** pixels, int *pitch)
{
    size_t buffer_size;
    int framebuffer_pitch;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    OSStatus dsp_error;
    PixMapPtr dsp_pixmap;
#endif

    if (!window || !format || !pixels || !pitch)
      return SDL_SetError("Invalid Classic framebuffer request");
    if (!macwindow && openTheWindow(window->w, window->h) < 0)
      return -1;
    if (myDepth != 16 && myDepth != 32)
      return SDL_SetError("Unsupported Classic framebuffer depth: %d", myDepth);

    destroyWindowFramebuffer(_this, window);
    myWidth = window->w;
    myHeight = window->h;
    drawWidth = myWidth;
    drawHeight = myHeight;

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    if (mac_dsp_active && mac_fullscreen_window && mac_dsp_page_flipping &&
        !(window->flags & SDL_WINDOW_OPENGL)) {
      dsp_error = DSpContext_GetBackBuffer(mac_dsp_context,
                                            kDSpBufferKind_Normal,
                                            &mac_dsp_back_buffer);
      if (dsp_error != noErr || !mac_dsp_back_buffer)
        return SDL_SetError("Unable to get DrawSprocket back buffer (%ld)",
                            (long)dsp_error);
#if TARGET_API_MAC_CARBON
      mac_dsp_back_pixmap = GetPortPixMap(mac_dsp_back_buffer);
#else
      mac_dsp_back_pixmap = mac_dsp_back_buffer->portPixMap;
#endif
      if (!mac_dsp_back_pixmap || !LockPixels(mac_dsp_back_pixmap)) {
        Mac_ReleaseSoftwareBackBuffer();
        return SDL_SetError("Unable to lock DrawSprocket back buffer");
      }
      dsp_pixmap = *mac_dsp_back_pixmap;
      if (!dsp_pixmap ||
          (dsp_pixmap->pixelSize != 16 && dsp_pixmap->pixelSize != 32)) {
        Mac_ReleaseSoftwareBackBuffer();
        return SDL_SetError("DrawSprocket provided an unsupported back buffer");
      }
      mypixels = GetPixBaseAddr(mac_dsp_back_pixmap);
      *pixels = mypixels;
      *pitch = dsp_pixmap->rowBytes & 0x3fff;
      *format = dsp_pixmap->pixelSize == 16
                    ? SDL_PIXELFORMAT_RGB555
                    : SDL_PIXELFORMAT_RGB888;
      mac_dsp_software_buffer = 1;
      return 0;
    }
#endif

    framebuffer_pitch = (myWidth * (myDepth / 8) + 3) & ~3;
    if (framebuffer_pitch <= 0 || framebuffer_pitch >= 0x4000)
      return SDL_SetError("Classic framebuffer row is too wide");
    if ((size_t)myHeight > ((size_t)-1) / (size_t)framebuffer_pitch)
      return SDL_SetError("Classic framebuffer is too large");
    buffer_size = (size_t)framebuffer_pitch * (size_t)myHeight;
    mypixels=(char *)SDL_calloc(1,buffer_size);
    if (!mypixels) {
      return SDL_OutOfMemory();
    }
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic mypixels at %08lx %lu bytes\n",
            (long)mypixels, (unsigned long)buffer_size); fflush(stderr);
#endif
    thePM=(PixMapPtr)SDL_calloc(1,sizeof(PixMap));
    if (!thePM) {
      SDL_free(mypixels);
      mypixels = NULL;
      return SDL_OutOfMemory();
    }
    thePM->bounds.top=0;  thePM->bounds.bottom=myHeight;
    thePM->bounds.left=0; thePM->bounds.right=myWidth;
    thePM->rowBytes=(1L<<15)|framebuffer_pitch;
    thePM->baseAddr=(char *)mypixels;
    thePM->hRes=72L<<16;  thePM->vRes=72L<<16;
    thePM->pixelSize=myDepth;
    /* Direct-color PixMaps always describe three RGB components. */
    thePM->cmpCount=3;
    thePM->cmpSize=(myDepth == 16) ? 5 : 8;
    thePM->pmVersion=0;
    thePM->pixelType=RGBDirect;
    thePM->packType=0;  thePM->packSize=0;    
#if TARGET_API_MAC_CARBON
    thePM->pixelFormat = myDepth == 16
                             ? k16BE555PixelFormat
                             : k32ARGBPixelFormat;
    thePM->pmTable=NULL; 
    thePM->pmExt=NULL;
#else
    thePM->planeBytes=0; 
    thePM->pmTable=(*macport->portPixMap)->pmTable;
    thePM->pmReserved=0;
#endif

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic thePM at %08lx\n",(long)thePM); fflush(stderr);
#endif

    *pixels=mypixels;
    *pitch=framebuffer_pitch;
    if(myDepth==16) *format = SDL_PIXELFORMAT_RGB555;
    if(myDepth==32) *format = SDL_PIXELFORMAT_RGB888;
    return 0;
}

/**
 * Informs the window manager that the window needs to be updated.
 * @param   _THIS
 * @param   window      The window to update
 * @param   rects       An array of reectangular areas to update
 * @param   numrects    Rect array length
 * @return  0 if successful, -1 on error
 */
static int updateWindowFramebuffer(_THIS, SDL_Window *window, const SDL_Rect *rects,
                        int numrects)
{
    const BitMap *src_bits;
    const BitMap *dst_bits;
    int i;

    (void)_this;
    if (!window || !macport)
      return SDL_SetError("Classic framebuffer has no native window");

#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    if (mac_dsp_software_buffer) {
      OSStatus error;
      PixMapPtr pixmap;

      UnlockPixels(mac_dsp_back_pixmap);
      mac_dsp_back_pixmap = NULL;
      mac_dsp_back_buffer = NULL;

      error = DSpContext_SwapBuffers(mac_dsp_context, NULL, NULL);
      if (error == noErr)
        error = DSpContext_GetBackBuffer(mac_dsp_context,
                                         kDSpBufferKind_Normal,
                                         &mac_dsp_back_buffer);
      if (error != noErr || !mac_dsp_back_buffer) {
        mac_dsp_software_buffer = 0;
        mypixels = NULL;
        return SDL_SetError("Unable to swap DrawSprocket buffers (%ld)",
                            (long)error);
      }
#if TARGET_API_MAC_CARBON
      mac_dsp_back_pixmap = GetPortPixMap(mac_dsp_back_buffer);
#else
      mac_dsp_back_pixmap = mac_dsp_back_buffer->portPixMap;
#endif
      if (!mac_dsp_back_pixmap || !LockPixels(mac_dsp_back_pixmap)) {
        Mac_ReleaseSoftwareBackBuffer();
        mypixels = NULL;
        return SDL_SetError("Unable to lock the DrawSprocket back buffer");
      }

      pixmap = *mac_dsp_back_pixmap;
      mypixels = GetPixBaseAddr(mac_dsp_back_pixmap);
      if (window->surface) {
        window->surface->pixels = mypixels;
        window->surface->pitch = pixmap->rowBytes & 0x3fff;
      }
      return 0;
    }
#endif

    if (!thePM)
      return SDL_SetError("Classic framebuffer is not initialized");

    SetPort((GrafPtr)macport);
    src_bits = (const BitMap *)thePM;
#if TARGET_API_MAC_CARBON
    dst_bits = GetPortBitMapForCopyBits(macport);
#else
    dst_bits = (const BitMap *)&((GrafPtr)macwindow)->portBits;
#endif

    if (mac_fullscreen_window) {
      Rect source_bounds = thePM->bounds;
      Rect window_bounds;

#if TARGET_API_MAC_CARBON
      GetPortBounds(macport, &window_bounds);
#else
      window_bounds = macport->portRect;
#endif
      CopyBits(src_bits, dst_bits, &source_bounds, &window_bounds,
               srcCopy, NULL);
      return 0;
    }

    if (!rects || numrects <= 0) {
      Rect bounds = thePM->bounds;
      CopyBits(src_bits, dst_bits, &bounds, &bounds, srcCopy, NULL);
      return 0;
    }

    for (i = 0; i < numrects; ++i) {
      Rect bounds;

      bounds.left = (short)SDL_max(rects[i].x, 0);
      bounds.top = (short)SDL_max(rects[i].y, 0);
      bounds.right = (short)SDL_min(rects[i].x + rects[i].w, drawWidth);
      bounds.bottom = (short)SDL_min(rects[i].y + rects[i].h, drawHeight);
      if (bounds.left < bounds.right && bounds.top < bounds.bottom)
        CopyBits(src_bits, dst_bits, &bounds, &bounds, srcCopy, NULL);
    }
    return 0;
}


static void setWindowTitle(_THIS, SDL_Window *window)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic setWindowTitle %s...\n",window->title); fflush(stderr);
#endif
    if (macwindow) Mac_SetNativeWindowTitle(macwindow, window->title);
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void setWindowSize(_THIS, SDL_Window *window)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic setWindowSize to %dx%d...\n",window->w,window->h); fflush(stderr);
#endif

    if (!macwindow) return;
    SizeWindow(macwindow,window->w,window->h,TRUE);

    drawWidth=window->w; drawHeight=window->h;
    myWidth=window->w; myHeight=window->h;
#ifdef SDL_VIDEO_OPENGL
    glUpdateWindow(_this, window);
#endif

    if (!mac_fullscreen_window) {
        Mac_GetWindowGlobalBounds(&mac_windowed_bounds);
        mac_windowed_bounds_valid = 1;
    }
    if (mac_gl_reattach_pending && mac_window_active) {
#ifdef SDL_VIDEO_OPENGL
        if (Mac_GL_SetDrawableActive(1) == 0)
            mac_gl_reattach_pending = 0;
#endif
    }

    /* SDL_OnWindowResized invalidates the surface. The next
       SDL_GetWindowSurface call recreates a correctly sized framebuffer. */
}

/**
 * Makes the native window associated with the given SDL window visible.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void showWindow(_THIS, SDL_Window *window)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic showWindow...\n"); fflush(stderr);
#endif

    if (macwindow) {
        ShowWindow(macwindow);
        macwindow_visible = 1;
        SDL_SendWindowEvent(window, SDL_WINDOWEVENT_SHOWN, 0, 0);
      if (Mac_IsFrontProcess()) {
        SelectWindow(macwindow);
        Mac_SetWindowActive(1);
      } else {
        Mac_SetWindowActive(0);
      }
    }
}

/**
 * Makes the native window associated with the given SDL window invisible.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void hideWindow(_THIS, SDL_Window *window)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic hideWindow...\n"); fflush(stderr);
#endif

    Mac_SetWindowActive(0);
    if (macwindow) HideWindow(macwindow);
    macwindow_visible = 0;
}

/**
 * Destroys the native window associated with the given SDL window.
 * @param   _THIS
 * @param   window  SDL window that is being destroyed
 */
static void destroyWindow(_THIS, SDL_Window *window)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic destroyWindow...\n"); fflush(stderr);
#endif

    Mac_SetWindowActive(0);
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    if (Mac_ReleaseDSpContext() != noErr) {
        SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO,
                    "macosclassic: failed to restore DrawSprocket during window destruction");
    }
#endif
    window->driverdata = NULL;
    destroyWindowFramebuffer(_this, window);
    if (macwindow) {
        DisposeWindow(macwindow);
        macwindow = NULL;
        macport = NULL;
    }
    if (window == sdlw) sdlw = NULL;
    mac_window_active = 0;
    macwindow_visible = 0;
    mac_fullscreen_window = 0;
    mac_windowed_bounds_valid = 0;
    mac_gl_reattach_pending = 0;
}

/**
 * Frees the plugin object created by createDevice().
 * @param   device  Plugin object to free
 */
static void deleteDevice(SDL_VideoDevice *device)
{
    cleanupMac();
    if(device) SDL_free(device);
    if (device == tdevice) tdevice = NULL;
}

/**
 * Creates the Classic Mac OS video device used by SDL.
 * @param   devindex    Unused
 * @return  Initialized device if successful, NULL otherwise
 */
static SDL_VideoDevice *createDevice(int devindex)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic createDevice...\n"); fflush(stderr);
#endif

    tdevice = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!tdevice) {
        SDL_OutOfMemory();
        return NULL;
    }
    
    sdlvdev=tdevice;
    sdlvdisp=NULL;
    sdlw=NULL;
    
    tdevice->driverdata = NULL;  /* Eventually these'll be the globals, etc */
    
    tdevice->VideoInit = videoInit;
    tdevice->VideoQuit = videoQuit;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
    tdevice->SetDisplayMode = setDisplayMode;
#endif
    /**/
    tdevice->CreateSDLWindow = createWindow;
    /**/
    tdevice->SetWindowSize = setWindowSize;
    tdevice->SetWindowTitle = setWindowTitle;
    tdevice->SetWindowFullscreen = setWindowFullscreen;
    /**/
    tdevice->ShowWindow = showWindow;
    tdevice->HideWindow = hideWindow;
    /**/
    tdevice->DestroyWindow = destroyWindow;
    tdevice->CreateWindowFramebuffer = createWindowFramebuffer;
    tdevice->UpdateWindowFramebuffer = updateWindowFramebuffer;
    tdevice->DestroyWindowFramebuffer = destroyWindowFramebuffer;

    tdevice->PumpEvents = SDL_Mac_pumpEvents;

#ifdef SDL_VIDEO_OPENGL
    tdevice->GL_LoadLibrary = glLoadLibrary;
    tdevice->GL_GetProcAddress = glGetProcAddress;
    tdevice->GL_UnloadLibrary = glUnloadLibrary;
    tdevice->GL_CreateContext = glCreateContext;
    tdevice->GL_MakeCurrent = glMakeCurrent;
    /**/
    tdevice->GL_SetSwapInterval = glSetSwapInterval;
    /**/
    tdevice->GL_SwapWindow = glSwapWindow;
    tdevice->GL_DeleteContext = glDeleteContext;
    /**/
#endif

    tdevice->free = deleteDevice;
    return tdevice;
}

/* Exported to the macmain code */
void SDL_InitQuickDraw(struct QDGlobals *the_qd)
{
#if !TARGET_API_MAC_CARBON
        theQD = the_qd;
#endif
}

static void cleanupMac(void)
{   
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic cleanupMac...\n"); fflush(stderr);
#endif 
  if(sdlw) Mac_SetWindowActive(0);
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
  Mac_ShutdownDrawSprocket();
#endif
  Mac_QuitMouse();
  Mac_QuitAppleEvents();
  if(thePM) { SDL_free(thePM); thePM=NULL; }
  if(mypixels) { SDL_free(mypixels); mypixels=NULL; }
  if(macwindow) { DisposeWindow(macwindow); macwindow=NULL; }
  macport=NULL;
  sdlw=NULL;
  mac_window_active=0;
  mac_display_device=NULL;
  mac_display_id=0;
#ifdef SDL_MACOSCLASSIC_DRAWSPROCKET
  mac_dsp_back_buffer=NULL;
  mac_dsp_back_pixmap=NULL;
  mac_dsp_software_buffer=0;
  mac_dsp_page_flipping=0;
#endif
  macwindow_visible=0;
  mac_fullscreen_window=0;
  mac_windowed_bounds_valid=0;
  mac_gl_reattach_pending=0;
}

VideoBootStrap Mac_bootstrap = {
    "macosclassic", "Mac Screen",
    (struct SDL_VideoDevice * (*)())createDevice,
    NULL /* no ShowMessageBox implementation */
};

#endif
