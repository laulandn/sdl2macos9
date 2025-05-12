/* MacOS9 Note: This code was based on the QNX driver
   solely because it was the smallest and easiest to understand.
   Below is the original copyright message */

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
#include "sdl_amiga.h"

#include <cybergraphics/cybergraphics.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/intuition.h>

#ifdef SDL_VIDEO_DRIVER_AMIGAOS3

#define QUICKDRAW_BLIT 1

#ifndef SDL_MAIN_NEEDED
#define STDOUT_FILE	"stdout.txt"
#define STDERR_FILE	"stderr.txt"
#endif


/* Globals are evil...these belong in driver data slash impl vars/params! */
struct Window *amigawindow=NULL;
struct RastPort *amigaport=NULL;
struct BitMap *theBM=NULL;
char *mypixels=NULL;
int myWidth,myHeight,myDepth;
SDL_VideoDevice *sdlvdev;
SDL_VideoDisplay *sdlvdisp;
SDL_Window *sdlw;


/*static screen_context_t context;
static screen_event_t   event;*/

/**
 * Initializes the QNX video plugin.
 * Creates the Screen context and event handles used for all window operations
 * by the plugin.
 * @param   _THIS
 * @return  0 if successful, -1 on error
 */
static int videoInit(_THIS)
{
    SDL_VideoDisplay display;
    struct NewWindow nw;
    int iflags;
    SDL_DisplayMode m;

/*printf("This should show up on the SIOUX console...\n");*/

    /*
#ifndef SDL_MAIN_NEEDED
#if !TARGET_API_MAC_CARBON
	InitGraf    (&qd.thePort);
	InitFonts   ();
	InitWindows ();
	InitMenus   ();
	InitDialogs (nil);
#endif
	InitCursor ();

	FlushEvents(everyEvent,0);
	SetEventMask(everyEvent & ~autoKeyMask);
#if !TARGET_API_MAC_CARBON
	MaxApplZone ();
#endif
	MoreMasters ();
	MoreMasters ();
#endif
*/

#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 videoInit...\n"); fflush(stderr);
#endif

  myWidth=PLATFORM_SCREEN_WIDTH;
  myHeight=PLATFORM_SCREEN_HEIGHT;
  myDepth=PLATFORM_SCREEN_DEPTH;
  /* Creating window here so I have screen dims...this belongs in in createWindow obs */
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 Going to OpenWindowTags...\n"); fflush(stderr);
#endif
  nw.LeftEdge=0;  nw.TopEdge=0;  nw.Width=myWidth;  nw.Height=myHeight;
  nw.DetailPen=2;  nw.BlockPen=1;  nw.Title=(unsigned char *)"Amiga SDL2 Window";
  /* Set all event flags correctly */
  iflags=0;
  iflags|=(IDCMP_VANILLAKEY|IDCMP_RAWKEY);
  iflags|=IDCMP_CLOSEWINDOW;
  iflags|=(IDCMP_NEWSIZE|IDCMP_CHANGEWINDOW);
  iflags|=IDCMP_ACTIVEWINDOW;
  iflags|=IDCMP_INACTIVEWINDOW;
  iflags|=IDCMP_MOUSEBUTTONS;
  iflags=WFLG_GIMMEZEROZERO|WFLG_ACTIVATE|WFLG_DRAGBAR|
  WFLG_DEPTHGADGET|WFLG_RMBTRAP;
  //iflags|=(WFLG_BORDERLESS|WFLG_BACKDROP);
  iflags|=WFLG_SIZEGADGET;
  iflags|=WFLG_CLOSEGADGET;
  nw.Flags=iflags;
  nw.Type=WBENCHSCREEN;
  nw.FirstGadget=NULL;  nw.CheckMark=NULL;
  nw.Screen=NULL; /* Is this ok? */
  nw.BitMap=NULL;  nw.MaxWidth=8192;  nw.MaxHeight=8192;
  nw.MinWidth=50;  nw.MinHeight=20;     /* WARN: should check big enuff */
  amigawindow=(struct Window *)OpenWindowTags(&nw,WA_AutoAdjust,TRUE, TAG_DONE);
  if(!amigawindow) {
    fprintf(stderr,"amigaos3 Couldn't open window!\n"); fflush(stderr);
    exitCleanly(0);
  }
  amigaport=amigawindow->RPort;
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 Window done\n"); fflush(stderr);
#endif

    /*if (screen_create_context(&context, 0) < 0) {
        return -1;
    }*/

    /*if (screen_create_event(&event) < 0) {
        return -1;
    }*/

    SDL_zero(display);

    m.w=myWidth;
    m.h=myHeight;    

    if (SDL_AddVideoDisplay(&display, SDL_FALSE) < 0) {
        return -1;
    }
    
    sdlvdisp=&sdlvdev->displays[0];
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 sdlvdisp is %0lx8\n",(long)sdlvdisp); fflush(stderr);
#endif

/*offPixMapHandle=NULL;*/

    m.w=myWidth;
    m.h=myHeight;
    m.refresh_rate=60;
    m.format=SDL_PIXELFORMAT_RGB888;    

    SDL_AddDisplayMode(sdlvdisp,&m);
    SDL_SetCurrentDisplayMode(sdlvdisp,&m);
    SDL_SetDesktopDisplayMode(sdlvdisp,&m);

    _this->num_displays = 1;
    return 0;
}

static void videoQuit(_THIS)
{
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 videoQuit...\n"); fflush(stderr);
#endif
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
    window_impl_t   *impl;
    int             size[2];
    int             numbufs;
    int             format;
    int             usage;

    impl = SDL_calloc(1, sizeof(*impl));
    if (!impl) {
        fprintf(stderr,"impl was null!\n"); fflush(stderr);
        return -1;
    }
    
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 createWindow...\n"); fflush(stderr);
#endif

    /* Create a native window.*/
    /*if (screen_create_window(&impl->window, context) < 0) {
        goto fail;
    }*/

    /* Set the native window's size to match the SDL window. */
    size[0] = window->w;
    size[1] = window->h;
    
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 requested win is %dx%d\n",window->w,window->h); fflush(stderr);
#endif

    /*if (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE,
                                      size) < 0) {
        goto fail;
    }*/

    /*if (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE,
                                      size) < 0) {
        goto fail;
    }*/

    /* Create window buffer(s). */
    if (window->flags & SDL_WINDOW_OPENGL) {
        /*if (glGetConfig(&impl->conf, &format) < 0) {
            goto fail;
        }*/
        numbufs = 2;

        /*usage = SCREEN_USAGE_OPENGL_ES2;
        if (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_USAGE,
                                          &usage) < 0) {
            return -1;
        }*/
    } else {
        /*format = SCREEN_FORMAT_RGBX8888;*/
        numbufs = 1;
    }

    /* Set pixel format.*/
    /*if (screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_FORMAT,
                                      &format) < 0) {
        goto fail;
    }*/

    /* Create buffer(s).*/
    /*if (screen_create_window_buffers(impl->window, numbufs) < 0) {
        goto fail;
    }*/
    
    sdlw=window;
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 sdlw at %08lx\n",(long)sdlw); fflush(stderr);
#endif

    window->driverdata = impl;
    return 0;

fail:
    /*if (impl->window) {
        screen_destroy_window(impl->window);
    }*/

    SDL_free(impl);
    return -1;
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
    window_impl_t   *impl = (window_impl_t *)window->driverdata;
    /*screen_buffer_t buffer;*/
 
    struct BitMap *friendbmap=amigaport->BitMap;   
    int bformat=BMF_MINPLANES|BMF_DISPLAYABLE;
  
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 createWindowFramebuffer...\n"); fflush(stderr);
#endif

    /* Get a pointer to the buffer's memory.*/
    /*if (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS,
                                      (void **)&buffer) < 0) {
        return -1;
    }*/

    /*if (screen_get_buffer_property_pv(buffer, SCREEN_PROPERTY_POINTER,
                                      pixels) < 0) {
        return -1;
    }*/

    /* Set format and pitch.*/
    /*if (screen_get_buffer_property_iv(buffer, SCREEN_PROPERTY_STRIDE,
                                      pitch) < 0) {
        return -1;
    }*/
    
    /* Hand build window sized pixmap */
    /*
     r.left=0; r.top=0;
     r.bottom=myHeight; r.right=myWidth;*/
    bformat=bformat|=BMF_SPECIALFMT | (PIXFMT_RGB16 << 24);
    theBM=AllocBitMap(myWidth,myHeight,myDepth,bformat,friendbmap);
    if(!theBM) {
      fprintf(stderr,"amigaos3 didn't get theBM \n"); fflush(stderr);
      exitCleanly(0);
    }
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 theBM at %lx\n",(long)theBM); fflush(stderr);
#endif
  /* This is wrong */
     mypixels=calloc(1,myWidth*myHeight*(myDepth/8));
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 mypixels at %lx\n",(long)mypixels); fflush(stderr);
#endif
    *pixels=mypixels;
    *pitch=myWidth*(myDepth/8);
    *format = SDL_PIXELFORMAT_RGB888;
    
    /*sdlw=window;*/
    
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
    window_impl_t   *impl = (window_impl_t *)window->driverdata;

/*
#ifdef QUICKDRAW_BLIT
  const BitMap *srcBits=NULL;  
  const BitMap *dstBits=NULL;
  Rect msr;  Rect mdr; 
#else
  unsigned long bytesToCopy;
  char *src;
  char *dest;
#endif
*/

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 updateWindowFramebuffer...\n"); fflush(stderr);
#endif

    /*screen_buffer_t buffer;*/

    /*if (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS,
                                      (void **)&buffer) < 0) {
        return -1;
    }*/

    /*screen_post_window(impl->window, buffer, numrects, (int *)rects, 0);
    screen_flush_context(context, 0);*/
    
  /* We ignore the rects parameter, and just blit the whole screen  */
 
   /* 
#ifdef QUICKDRAW_BLIT
  *SetGWorld(macoffworld,NULL);*
  msr.top=0; msr.left=0; 
  msr.bottom=myHeight;  msr.right=myWidth;
  mdr.top=0; mdr.left=0; 
  mdr.bottom=myHeight;  mdr.right=myWidth;
  srcBits=(BitMap *)thePM;
#if TARGET_API_MAC_CARBON
  dstBits=GetPortBitMapForCopyBits(macwindow);
#else
  dstBits=(BitMap *)&((GrafPtr)macwindow)->portBits;
#endif
  CopyBits(srcBits,dstBits,&msr,&mdr,srcCopy,NULL);
#else
  src=mypixels;
  dest=
  bytesToCopy=myWidth*myHeight*(myDepth/8);
  for(t-0;t<bytesToCopy;t++) {
    *(dest+t)=*(src+t);
  }
#endif
*/

    return 0;
}

/**
 * Runs the main event loop.
 * @param   _THIS
 */
static void pumpEvents(_THIS)
{
  //EventRecord event;
  int etype,val;

#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 pumpEvents...\n"); fflush(stderr);
#endif

  fprintf(stderr,"Exiting as we don't handle events yet!\n"); fflush(stderr);
  exitCleanly(0);
  /*
  val=EventAvail(everyEvent,&event);
  if(val) {
	GetNextEvent(everyEvent,&event);
    etype=event.what;
    *fprintf(stderr,"amigaos3 what=%d\n",event.what); fflush(stderr);*
    switch(etype) {
      case nullEvent: break;
      case kHighLevelEvent:
        * Handle this eventually... *
        break;
      case activateEvt:
        * Just skip for now *
        break;
      case updateEvt:
        SetPort((GrafPtr)GetWindowPort((WindowPtr)event.message));
        BeginUpdate((WindowPtr)event.message);
        EndUpdate((WindowPtr)event.message);
        DrawGrowIcon((WindowPtr)event.message);
        break;
      case mouseDown:
        fprintf(stderr,"amigaos3 mouseDown!\n"); fflush(stderr);
        SDL_SendMouseButton(sdlw,1,1,SDL_BUTTON_LEFT);
        break;
      case mouseUp:
        fprintf(stderr,"amigaos3 mouseUp!\n"); fflush(stderr);
        SDL_SendMouseButton(sdlw,1,0,SDL_BUTTON_LEFT);
        break;
      case autoKey:
        *fprintf(stderr,"amigaos3 autoKey!\n"); fflush(stderr);*
        handleKeyboardEvent(&event,etype);
        break;
	  case keyDown:
        *fprintf(stderr,"amigaos3 keyDown!\n"); fflush(stderr);*
        handleKeyboardEvent(&event,etype);
        break;
	  case keyUp:
        *fprintf(stderr,"amigaos3 keyUp!\n"); fflush(stderr);*
        handleKeyboardEvent(&event,etype);
	    break;
	  default:
#ifdef AMIGA_DEBUG
	    fprintf(stderr,"amigaos3 mac event.what=%d skipped!\n",etype); fflush(stderr);
#endif
	    break;
	}
  }
*/

}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void setWindowSize(_THIS, SDL_Window *window)
{
    window_impl_t   *impl = (window_impl_t *)window->driverdata;
    int             size[2];

    size[0] = window->w;
    size[1] = window->h;

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 setWindowSize to %dx%d...\n",window->w,window->h); fflush(stderr);
#endif

    /*screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SIZE, size);
    screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_SOURCE_SIZE,
                                  size);*/
                                  
    /* TODO: Resize the window, change myWidth/myDepth, recreate the pixmap */
}

/**
 * Makes the native window associated with the given SDL window visible.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void showWindow(_THIS, SDL_Window *window)
{
    window_impl_t   *impl = (window_impl_t *)window->driverdata;
    const int       visible = 1;

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 showWindow...\n"); fflush(stderr);
#endif

    /*screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE,
                                  &visible);*/
    /* TODO: ShowWindow the mac window */
}

/**
 * Makes the native window associated with the given SDL window invisible.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void hideWindow(_THIS, SDL_Window *window)
{
    window_impl_t   *impl = (window_impl_t *)window->driverdata;
    const int       visible = 0;

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 hideWindow...\n"); fflush(stderr);
#endif

    /*screen_set_window_property_iv(impl->window, SCREEN_PROPERTY_VISIBLE,
        &visible);*/
    /* TODO: hide the mac window */
}

/**
 * Destroys the native window associated with the given SDL window.
 * @param   _THIS
 * @param   window  SDL window that is being destroyed
 */
static void destroyWindow(_THIS, SDL_Window *window)
{
    window_impl_t   *impl = (window_impl_t *)window->driverdata;

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 destroyWindow...\n"); fflush(stderr);
#endif

    if (impl) {
        /*screen_destroy_window(impl->window);*/
        window->driverdata = NULL;
    }
    /* TODO: Close mac window, maybe dump pixmap and pixels? */
}

/**
 * Frees the plugin object created by createDevice().
 * @param   device  Plugin object to free
 */
static void deleteDevice(SDL_VideoDevice *device)
{
    fprintf(stderr,"amigaos3 deleteDevice...\n"); fflush(stderr);
    SDL_free(device);
    cleanupAmiga();
}

/**
 * Creates the QNX video plugin used by SDL.
 * @param   devindex    Unused
 * @return  Initialized device if successful, NULL otherwise
 */
static SDL_VideoDevice *createDevice(int devindex)
{
    SDL_VideoDevice *device;

#ifndef SDL_MAIN_NEEDED
    freopen (STDOUT_FILE, "w", stdout);
    freopen (STDERR_FILE, "w", stderr);
#endif

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 createDevice...\n"); fflush(stderr);
#endif

    device = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!device) {
        fprintf(stderr,"Didn't create device!\n"); fflush(stderr);
        return NULL;
    }
    
    sdlvdev=device;
    sdlvdisp=NULL;
    sdlw=NULL;
    
    device->driverdata = NULL;  /* Eventually these'll be the globals, etc */
    
    device->VideoInit = videoInit;
    device->VideoQuit = videoQuit;
    /**/
    device->CreateSDLWindow = createWindow;
    /**/
    device->SetWindowSize = setWindowSize;
    /**/
    device->ShowWindow = showWindow;
    device->HideWindow = hideWindow;
    /**/
    device->DestroyWindow = destroyWindow;
    device->CreateWindowFramebuffer = createWindowFramebuffer;
    device->UpdateWindowFramebuffer = updateWindowFramebuffer;

    device->PumpEvents = pumpEvents;

    device->GL_LoadLibrary = glLoadLibrary;
    device->GL_GetProcAddress = glGetProcAddress;
    device->GL_UnloadLibrary = glUnloadLibrary;
    device->GL_CreateContext = glCreateContext;
    device->GL_MakeCurrent = glMakeCurrent;
    /**/
    device->GL_SetSwapInterval = glSetSwapInterval;
    /**/
    device->GL_SwapWindow = glSwapWindow;
    device->GL_DeleteContext = glDeleteContext;
    /**/

    device->free = deleteDevice;
    return device;
}


void cleanupAmiga()
{
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 cleanupAmiga...\n"); fflush(stderr);
#endif
  if(amigawindow) { CloseWindow(amigawindow); amigawindow=NULL; }
  if(theBM) { FreeBitMap(theBM); theBM=NULL; }
  if(mypixels) { free(mypixels); mypixels=NULL; }
}

void exitCleanly(int result)
{
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 exitCleanly...\n"); fflush(stderr);
#endif
  cleanupAmiga();
  exit(result);
}

VideoBootStrap Amiga_bootstrap = {
    "amigaos3", "Amiga Screen",
    (struct SDL_VideoDevice * (*)())createDevice,
    NULL /* no ShowMessageBox implementation */
};

#endif
