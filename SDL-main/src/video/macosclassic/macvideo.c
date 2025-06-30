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
#include "sdl_mac.h"

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC


#ifndef SDL_MAIN_NEEDED
#define STDOUT_FILE	"stdout.txt"
#define STDERR_FILE	"stderr.txt"
#endif


/* Globals are evil...these belong in driver data slash impl vars/params! */
// TODO: Move all these into the "impl" things
WindowPtr macwindow=NULL;
CGrafPtr macport=NULL;
PixMapPtr thePM=NULL;
/**/
char *mypixels=NULL;
int myWidth,myHeight,myDepth;
/**/
SDL_VideoDevice *sdlvdev=NULL;
SDL_VideoDisplay *sdlvdisp=NULL;
SDL_Window *sdlw=NULL;
/**/
window_impl_t   *timpl=NULL;
SDL_VideoDevice *tdevice=NULL;


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
    struct Rect WindowBox;
    SDL_DisplayMode m;

/*printf("This should show up on the SIOUX console...\n");*/

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

#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic videoInit...\n"); fflush(stderr);
#endif

  myWidth=PLATFORM_SCREEN_WIDTH;
  myHeight=PLATFORM_SCREEN_HEIGHT;
  myDepth=PLATFORM_SCREEN_DEPTH;
  /* Creating window here so I have screen dims...this belongs in in createWindow obs */
#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic Going to NewCWindow...\n"); fflush(stderr);
#endif
  WindowBox.top=40;  WindowBox.left=4;
  WindowBox.bottom=myHeight+40;  WindowBox.right=myWidth+4;
  macwindow=NewCWindow(NULL,&WindowBox,(ConstStr255Param)"\pMac SDL2 Window",true,noGrowDocProc+8,(WindowPtr)(-1L),true,0L);
#ifdef __MWERKS__
  macport=(CGrafPtr)macwindow;
#else
  macport=GetWindowPort(macwindow);
#endif
  SetPort((GrafPtr)macport);
  thePM=NULL;
  /*macoffworld=macwindow;*/
  ShowWindow((WindowPtr)macwindow);
#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic Window done\n"); fflush(stderr);
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
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic sdlvdisp is %0lx8\n",(long)sdlvdisp); fflush(stderr);
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
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic videoQuit...\n"); fflush(stderr);
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
    //window_impl_t   *impl;
    //int             size[2];
    int             numbufs;
    //int             format;
    //int             usage;

    timpl = SDL_calloc(1, sizeof(*timpl));
    if (!timpl) {
        fprintf(stderr,"timpl was null!\n"); fflush(stderr);
        return -1;
    }
    
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic createWindow...\n"); fflush(stderr);
#endif

    /* Create a native window.*/
    /*if (screen_create_window(&impl->window, context) < 0) {
        goto fail;
    }*/

    /* Set the native window's size to match the SDL window. */
    //size[0] = window->w;
    //size[1] = window->h;
    
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic requested win is %dx%d\n",window->w,window->h); fflush(stderr);
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
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic sdlw at %08lx\n",(long)sdlw); fflush(stderr);
#endif

    window->driverdata = timpl;
    return 0;

/*
fail:
    if (impl->window) {
        screen_destroy_window(impl->window);
    }

    SDL_free(impl);
    return -1;
*/
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
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
    /*screen_buffer_t buffer;*/
    
    Rect r; 
    //QDErr err;
    //int good;
  
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic createWindowFramebuffer...\n"); fflush(stderr);
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
     r.left=0; r.top=0;
     r.bottom=myHeight; r.right=myWidth;
     mypixels=calloc(1,myWidth*myHeight*(myDepth/8));
#ifdef MAC_DEBUG
  fprintf(stderr,"macosclassic mypixels at %lx\n",(long)mypixels); fflush(stderr);
#endif
    thePM=(PixMapPtr)calloc(1,sizeof(PixMap));
    thePM->bounds.top=0;  thePM->bounds.bottom=myHeight;
    thePM->bounds.left=0; thePM->bounds.right=myWidth;
    thePM->rowBytes=(1L<<15)|(myWidth*(myDepth/8));
    thePM->baseAddr=(char *)mypixels;
    thePM->hRes=72;  thePM->vRes=72;
    thePM->pixelSize=myDepth;
    thePM->cmpCount=1;  thePM->cmpSize=myDepth;
    thePM->pmVersion=0;
    thePM->pixelType=RGBDirect;
    thePM->packType=0;  thePM->packSize=0;    
#if TARGET_API_MAC_CARBON
    thePM->pixelFormat='ABGR';
    thePM->pmTable=NULL;  /* TODO what goes here? */
    thePM->pmExt=NULL;
#else
    thePM->planeBytes=0; /* Offset in bytes to next plane */
    thePM->pmTable=(*macport->portPixMap)->pmTable;
    thePM->pmReserved=0;
#endif
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic thePM at %lx\n",(long)thePM); fflush(stderr);
#endif
         /*GetGWorld(&origPort, &origDevice);
  fprintf(stderr,"macosclassic origPort at %lx\n",(long)origPort); fflush(stderr);
  fprintf(stderr,"macosclassic origDevice at %lx\n",(long)origDevice); fflush(stderr);
  err=NewGWorld(&macoffworld,8,&r,NULL,NULL,keepLocal);
  if(err!=noErr) {
    fprintf(stderr,"QDErr was %d!\n",err); fflush(stderr);
     exit(0);
    }
  fprintf(stderr,"macosclassic new gworld at %lx\n",(long)macoffworld); fflush(stderr);
  SetGWorld(macoffworld,NULL);
  offPixMapHandle=GetGWorldPixMap(macoffworld);
  fprintf(stderr,"macosclassic offPixMapHandle at %lx\n",(long)offPixMapHandle); fflush(stderr);
  good=LockPixels(offPixMapHandle);
  if(good) { fprintf(stderr,"DId LockPixels...\n"); fflush(stderr); }
  else {
  printf(stderr,"LockPixels failed!\n");  fflush(stderr); exit(0);
  }
  */
  /*mypixels=(*offPixMapHandle)->baseAddr;*/
  /*SetGWorld(origPort,origDevice);*/
  /*UnlockPixels(macoffworld);*/
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
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;

#ifdef QUICKDRAW_BLIT
  const BitMap *srcBits=NULL;  
  const BitMap *dstBits=NULL;
  Rect msr;  Rect mdr; 
#else
  unsigned long bytesToCopy;
  char *src;
  char *dest;
#endif
 
#ifdef MAC_DEBUG
    /*fprintf(stderr,"macosclassic updateWindowFramebuffer...\n"); fflush(stderr);*/
#endif

    /*screen_buffer_t buffer;*/

    /*if (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS,
                                      (void **)&buffer) < 0) {
        return -1;
    }*/

    /*screen_post_window(impl->window, buffer, numrects, (int *)rects, 0);
    screen_flush_context(context, 0);*/
    
  /* We ignore the rects parameter, and just blit the whole screen  */
  
#ifdef QUICKDRAW_BLIT
  /*SetGWorld(macoffworld,NULL);*/
  SetPort((GrafPtr)macport);
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
  //fprintf(stderr,"QDError is %d\n",QDError());
#else
  src=mypixels;
  dest=
  bytesToCopy=myWidth*myHeight*(myDepth/8);
  for(t-0;t<bytesToCopy;t++) {
    *(dest+t)=*(src+t);
  }
#endif
    return 0;
}

/**
 * Runs the main event loop.
 * @param   _THIS
 */
static void pumpEvents(_THIS)
{
  EventRecord event;
  int etype,val;

#ifdef MAC_DEBUG
  /*fprintf(stderr,"macosclassic pumpEvents...\n"); fflush(stderr);*/
#endif

  val=EventAvail(everyEvent,&event);
  if(val) {
	GetNextEvent(everyEvent,&event);
    etype=event.what;
    /*fprintf(stderr,"macosclassic what=%d\n",event.what); fflush(stderr);*/
    switch(etype) {
      case nullEvent: break;
      case kHighLevelEvent:
        /* Handle this eventually... */
        break;
      case activateEvt:
        /* Just skip for now */
        break;
      case updateEvt:
        SetPort((GrafPtr)GetWindowPort((WindowPtr)event.message));
        BeginUpdate((WindowPtr)event.message);
        EndUpdate((WindowPtr)event.message);
        DrawGrowIcon((WindowPtr)event.message);
        break;
      case mouseDown:
        fprintf(stderr,"macosclassic mouseDown!\n"); fflush(stderr);
        SDL_SendMouseButton(sdlw,1,1,SDL_BUTTON_LEFT);
        break;
      case mouseUp:
        fprintf(stderr,"macosclassic mouseUp!\n"); fflush(stderr);
        SDL_SendMouseButton(sdlw,1,0,SDL_BUTTON_LEFT);
        break;
      case autoKey:
        /*fprintf(stderr,"macosclassic autoKey!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
        break;
	  case keyDown:
        /*fprintf(stderr,"macosclassic keyDown!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
        break;
	  case keyUp:
        /*fprintf(stderr,"macosclassic keyUp!\n"); fflush(stderr);*/
        handleKeyboardEvent(&event,etype);
	    break;
	  default:
#ifdef MAC_DEBUG
	    fprintf(stderr,"macosclassic mac event.what=%d skipped!\n",etype); fflush(stderr);
#endif
	    break;
	}
  }


}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void setWindowSize(_THIS, SDL_Window *window)
{
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
    int             size[2];

    size[0] = window->w;
    size[1] = window->h;

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic setWindowSize to %dx%d...\n",window->w,window->h); fflush(stderr);
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
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
   // const int       visible = 1;

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic showWindow...\n"); fflush(stderr);
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
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
    //const int       visible = 0;

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic hideWindow...\n"); fflush(stderr);
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

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic destroyWindow...\n"); fflush(stderr);
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
    fprintf(stderr,"macosclassic deleteDevice device is %lx...\n",(long)device); fflush(stderr);
    if(device) SDL_free(device);
    /* TODO cleanup here */
    fprintf(stderr,"macosclassic more cleanup would go here...\n"); fflush(stderr);
}

/**
 * Creates the QNX video plugin used by SDL.
 * @param   devindex    Unused
 * @return  Initialized device if successful, NULL otherwise
 */
static SDL_VideoDevice *createDevice(int devindex)
{
    //SDL_VideoDevice *device;

#ifndef SDL_MAIN_NEEDED
    freopen (STDOUT_FILE, "w", stdout);
    freopen (STDERR_FILE, "w", stderr);
#endif

#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic createDevice...\n"); fflush(stderr);
#endif

    tdevice = (SDL_VideoDevice *)SDL_calloc(1, sizeof(SDL_VideoDevice));
    if (!tdevice) {
        fprintf(stderr,"Didn't create tdevice!\n"); fflush(stderr);
        return NULL;
    }
    
    sdlvdev=tdevice;
    sdlvdisp=NULL;
    sdlw=NULL;
    
    tdevice->driverdata = NULL;  /* Eventually these'll be the globals, etc */
    
    tdevice->VideoInit = videoInit;
    tdevice->VideoQuit = videoQuit;
    /**/
    tdevice->CreateSDLWindow = createWindow;
    /**/
    tdevice->SetWindowSize = setWindowSize;
    /**/
    tdevice->ShowWindow = showWindow;
    tdevice->HideWindow = hideWindow;
    /**/
    tdevice->DestroyWindow = destroyWindow;
    tdevice->CreateWindowFramebuffer = createWindowFramebuffer;
    tdevice->UpdateWindowFramebuffer = updateWindowFramebuffer;

    tdevice->PumpEvents = pumpEvents;

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

    tdevice->free = deleteDevice;
    return tdevice;
}

#if !TARGET_API_MAC_CARBON
/* Since we don't initialize QuickDraw, we need to get a pointer to qd */
struct QDGlobals *theQD = NULL;
#endif

/* Exported to the macmain code */
void SDL_InitQuickDraw(struct QDGlobals *the_qd)
{
#if !TARGET_API_MAC_CARBON
        theQD = the_qd;
#endif
}

void cleanupMac()
{   
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic cleanupMac...\n"); fflush(stderr);
#endif 
  /*
   TODO
  */
  if(timpl) { free(timpl); timpl=NULL; }
  if(tdevice) { free(tdevice); tdevice=NULL; }
/* TODO: Cleanup any windows, or anything else alloc'd...like this...
  if(amigawindow) { CloseWindow(amigawindow); amigawindow=NULL; }
  if(amigascreen) { CloseScreen(amigascreen); amigascreen=NULL; }
  if(theBM) { FreeBitMap(theBM); theBM=NULL; }
  if(CyberGfxBase) { CloseLibrary(CyberGfxBase); CyberGfxBase=NULL; }
  if(IntuitionBase) { CloseLibrary(&IntuitionBase->LibNode); IntuitionBase=NULL; }
*/
  if(mypixels) { free(mypixels); mypixels=NULL; }
}

void exitCleanly(int result)
{
#ifdef MAC_DEBUG
    fprintf(stderr,"macosclassic exitCleanly...\n"); fflush(stderr);
#endif
  cleanupMac();
  exit(result);
}

VideoBootStrap Mac_bootstrap = {
    "macosclassic", "Mac Screen",
    (struct SDL_VideoDevice * (*)())createDevice,
    NULL /* no ShowMessageBox implementation */
};

#endif
