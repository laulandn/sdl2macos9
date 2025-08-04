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


#ifdef SDL_VIDEO_DRIVER_AMIGAOS3


extern void SDL_Amiga_pumpEvents(_THIS);


#ifndef SDL_MAIN_NEEDED
#define STDOUT_FILE	"stdout.txt"
#define STDERR_FILE	"stderr.txt"
#endif

#define SIGMASK(w) (1L<<((w)->UserPort->mp_SigBit))
#define GETIMSG(w) ((struct IntuiMessage *)GetMsg((w)->UserPort))

struct GfxBase *GfxBase=NULL;
struct IntuitionBase *IntuitionBase=NULL;
struct Library *CyberGfxBase=NULL;


/* Globals are evil...these belong in driver data slash impl vars/params! */
// TODO: Move all these into the "impl" things
struct Screen *amigascreen=NULL;
struct Window *amigawindow=NULL;
struct RastPort *amigaport=NULL;
struct BitMap *theBM=NULL;
/**/
char *mypixels=NULL;
int myWidth,myHeight,myDepth;
int drawWidth,drawHeight;
/**/
SDL_VideoDevice *sdlvdev=NULL;
SDL_VideoDisplay *sdlvdisp=NULL;
SDL_Window *sdlw=NULL;
/**/
window_impl_t   *timpl=NULL;
SDL_VideoDevice *tdevice=NULL;

void cleanupAmiga();

/*static screen_context_t context;
static screen_event_t   event;*/


ULONG NextDepth(ULONG Depth)
{
 switch (Depth)
  {
   case 24L: /* 24Bit not available? Try 16Bit!      */
    return 16L;
   case 16L: /* 15Bit not available? Try 15Bit!      */
    return 15L;
   default:  /* Not even 15Bit available? Forget it! */
    return 0L;
  }
}

static void openTheWindow(int w,int h)
{
    //struct NewWindow nw;
    int iflags,wflags;
#if USE_CUSTOM_SCREEN
    int DisplayID=0;
    int Depth=0;
#endif
    int sw,sh,sd;

#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 openTheWindow %dx%d\n",w,h);
#endif

  // TODO: This isn't right, if custom will ask for crazy things!
  myWidth=w; myHeight=h;

 #if USE_CUSTOM_SCREEN
   Depth=myDepth;
 while (Depth)
  {
  fprintf(stderr,"amigaos3 Depth is %d ...\n",Depth); fflush(stderr);
   if ((DisplayID=BestCModeIDTags(CYBRBIDTG_NominalWidth,myWidth,
                                  CYBRBIDTG_NominalHeight,myHeight,
                                  CYBRBIDTG_Depth,Depth,
                                  TAG_DONE))!=INVALID_ID)
    {

  fprintf(stderr,"amigaos3 BestCModIDTags got 0x%x...\n",DisplayID); fflush(stderr);
     Depth=GetCyberIDAttr(CYBRIDATTR_DEPTH,DisplayID);
     break;
    }
/* retry with less bits per pixel */
  fprintf(stderr,"amigaos3 going to NextDepth ...\n"); fflush(stderr);
   Depth=NextDepth(Depth);
  }

  amigascreen=OpenScreenTags(NULL,
                                 SA_Title,(long)"Amiga SDL2 screen",
                                 SA_DisplayID,DisplayID,
                                 SA_Depth,myDepth,
                                 TAG_DONE);
  if(!amigascreen) {
    fprintf(stderr,"amigaos3 Couldn't open screen!\n"); fflush(stderr);
    exitCleanly(0);
  }
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 amigascreen at %08lx\n",(long)amigascreen); fflush(stderr);
#endif
#else
    amigascreen=malloc(sizeof(struct Screen));
    GetScreenData(amigascreen,sizeof(struct Screen),WBENCHSCREEN,NULL);
#endif

  if(amigascreen) {
    fprintf(stderr,"amigascreen %d,%d\n",amigascreen->Width,amigascreen->Height); fflush(stderr);
    fprintf(stderr,"rastport bitmap %d,%d,%d\n",amigascreen->RastPort.BitMap->BytesPerRow,amigascreen->RastPort.BitMap->Rows,amigascreen->RastPort.BitMap->Depth); fflush(stderr);
    sw=amigascreen->Width;
    sh=amigascreen->Height;
    sd=amigascreen->RastPort.BitMap->Depth;
    if(GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_ISCYBERGFX)) {
      fprintf(stderr,"screen's rastport's bitmap is cyber!\n");
      sw=GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_WIDTH);
      sh=GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_HEIGHT);
      sd=GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_DEPTH);
      fprintf(stderr,"pixfmt=%d\n",GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_PIXFMT));
      fprintf(stderr,"bppix=%d\n",GetCyberMapAttr(amigascreen->RastPort.BitMap,CYBRMATTR_BPPIX));
    }
    //
    if(sw<myWidth) myWidth=sw; 
    if(sh<myHeight) myHeight=sh; 
    fprintf(stderr,"actual screen is %dx%dx%d\n",sw,sh,sd); fflush(stderr);
   }

  drawWidth=myWidth; drawHeight=myHeight;

  fprintf(stderr,"amigaos3 using screen %dx%dx%d\n", myWidth,myHeight,myDepth); fflush(stderr);

#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 Going to OpenWindowTags...\n"); fflush(stderr);
#endif
  //nw.LeftEdge=0;  nw.TopEdge=0;  nw.Width=myWidth;  nw.Height=myHeight;
  //nw.DetailPen=2;  nw.BlockPen=1;  nw.Title=(unsigned char *)"Amiga SDL2 Window";
  /* Set all event flags correctly */
  iflags=0;
  //iflags|=IDCMP_VANILLAKEY;
  iflags|=IDCMP_RAWKEY;
  iflags|=IDCMP_CLOSEWINDOW;
  iflags|=(IDCMP_NEWSIZE|IDCMP_CHANGEWINDOW);
  iflags|=IDCMP_ACTIVEWINDOW;
  iflags|=IDCMP_INACTIVEWINDOW;
  iflags|=IDCMP_MOUSEBUTTONS;
  iflags|=IDCMP_MOUSEMOVE;
  //iflags|=IDCMP_DELTAMOVE;
  wflags=SIMPLE_REFRESH;
  wflags|=WFLG_GIMMEZEROZERO;
  wflags|=WFLG_ACTIVATE|WFLG_DRAGBAR|WFLG_DEPTHGADGET;
  wflags|=WFLG_RMBTRAP;
  //wflags|=(WFLG_BORDERLESS|WFLG_BACKDROP);
  wflags|=WFLG_SIZEGADGET;
  wflags|=WFLG_CLOSEGADGET;
  //nw.Flags=iflags|wflags;
  //nw.Type=WBENCHSCREEN;
  //nw.FirstGadget=NULL;  nw.CheckMark=NULL;
  //nw.Screen=NULL; * Is this ok? *
  //nw.BitMap=NULL;  nw.MaxWidth=8192;  nw.MaxHeight=8192;
  //nw.MinWidth=50;  nw.MinHeight=20;     * WARN: should check big enuff *
  amigawindow=(struct Window *)OpenWindowTags(NULL/*&nw*/,
		                 WA_Title,(long)"Amiga SDL Window",
                                 WA_Flags,wflags,
				 /*WFLG_SIMPLE_REFRESH|
				 *WFLG_BORDERLESS|
				 WFLG_BACKDROP|
				 WFLG_GIMMEZEROZERO|*
                                 WFLG_SIZEGADGET|
				  WFLG_RMBTRAP|
				WFLG_DRAGBAR|
                                WFLG_DEPTHGADGET|
				  WFLG_CLOSEGADGET,*/
                                 WA_IDCMP,iflags,
                                 WA_Left,0,
                                 WA_Top,0,
                                 WA_Width,myWidth,
                                 WA_Height,myHeight,
#if USE_CUSTOM_SCREEN
				 WA_CustomScreen,(long)amigascreen,
#endif
		  WA_AutoAdjust,TRUE,
		  TAG_DONE);
  if(!amigawindow) {
    fprintf(stderr,"amigaos3 Couldn't open window!\n"); fflush(stderr);
    exitCleanly(0);
  }
  ActivateWindow(amigawindow);
  amigaport=amigawindow->RPort;
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 Window done\n"); fflush(stderr);
#endif
}

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
    //struct NewWindow nw;
    SDL_DisplayMode m;

#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 videoInit...\n"); fflush(stderr);
#endif

   if ((GfxBase=(struct GfxBase *)OpenLibrary((CONST_STRPTR)"graphics.library",39))==NULL) {
    fprintf(stderr,"amigaos3 couldn't open graphics...\n"); fflush(stderr);
    exit(20);
   }
   fprintf(stderr,"amigaos3 got graphics version %d\n",GfxBase->LibNode.lib_Version);

   if ((IntuitionBase=(struct IntuitionBase *)OpenLibrary((CONST_STRPTR)"intuition.library",39))==NULL) {
     if(GfxBase) CloseLibrary (&GfxBase->LibNode);
     fprintf(stderr,"amigaos3 couldn't open intuition...\n"); fflush(stderr);
     exit(20);
   }
   fprintf(stderr,"amigaos3 got intuition version %d\n",IntuitionBase->LibNode.lib_Version);

 if ((CyberGfxBase=(struct Library *)OpenLibrary((CONST_STRPTR)CYBERGFXNAME,41))==NULL)
  {
    if(GfxBase) CloseLibrary (&GfxBase->LibNode);
    if(IntuitionBase) CloseLibrary (&IntuitionBase->LibNode);
    fprintf(stderr,"amigaos3 couldn't open cybergfx...\n"); fflush(stderr);
    exit(20);
  }
   fprintf(stderr,"amigaos3 got cybergfx version %d\n",CyberGfxBase->lib_Version);

  myWidth=PLATFORM_SCREEN_WIDTH;
  myHeight=PLATFORM_SCREEN_HEIGHT;
  myDepth=PLATFORM_SCREEN_DEPTH;
  drawWidth=myWidth;  drawHeight=myHeight;

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
    fprintf(stderr,"amigaos3 sdlvdisp is %8lx\n",(long)sdlvdisp); fflush(stderr);
#endif

/*offPixMapHandle=NULL;*/

    m.w=myWidth;
    m.h=myHeight;
    m.refresh_rate=60;
    if(myDepth==8) {
      fprintf(stderr,"8 bit pixels not implemented yet!");
      exitCleanly(0);
    }
    if(myDepth==16) m.format=SDL_PIXELFORMAT_RGB565;
    if(myDepth==32) m.format=SDL_PIXELFORMAT_RGB888;


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
    //int             size[2];
    int             numbufs;
    //int             format;
    //int             usage;

    timpl = SDL_calloc(1, sizeof(*timpl));
    if (!timpl) {
        fprintf(stderr,"timpl was null!\n"); fflush(stderr);
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
    //size[0] = window->w;
    //size[1] = window->h;
    
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 requested win is %dx%d\n",window->w,window->h); fflush(stderr);
#endif

    if(window->w>myWidth) window->w=myWidth;
    if(window->h>myHeight) window->h=myHeight;

    if(!amigawindow) openTheWindow(window->w,window->h);
    
    ChangeWindowBox(amigawindow,0,0,window->w,window->h);

    drawWidth=window->w; drawHeight=window->h;
    myWidth=window->w; myHeight=window->h;

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

    window->driverdata = timpl;
    return 0;

/*fail:
    if (impl->window) {
        screen_destroy_window(impl->window);
    }

    SDL_free(impl);
    return -1;*/
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
    int theSize=0;
 
    //struct BitMap *friendbmap=amigaport->BitMap;   
    //int bformat=BMF_MINPLANES|BMF_DISPLAYABLE;
  
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
    
    if(!amigawindow) openTheWindow(window->w,window->h);
  
    fprintf(stderr,"myWidth x myHeight x myDepth: %dx%dx%d\n",myWidth,myHeight,myDepth); fflush(stderr);
    fprintf(stderr,"drawWidth x drawHeight: %dx%d\n",drawWidth,drawHeight); fflush(stderr);
 
    // PIXF_A8R8G8B8 maybe?
    // TODO: Don't think this bitmap is even used...
    /*bformat|=BMF_SPECIALFMT | (PIXFMT_RGB16 << 24);
    theBM=AllocBitMap(myWidth,myHeight,myDepth,bformat,friendbmap);
    if(!theBM) {
      fprintf(stderr,"amigaos3 didn't get theBM \n"); fflush(stderr);
      exitCleanly(0);
    }
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 theBM at %08lx\n",(long)theBM); fflush(stderr);
#endif*/

     theSize=myWidth*myHeight*(myDepth/8);
     mypixels=calloc(1,theSize);
#ifdef AMIGA_DEBUG
  fprintf(stderr,"amigaos3 mypixels at %08lx %d bytes\n",(long)mypixels,theSize); fflush(stderr);
#endif
    *pixels=mypixels;
    *pitch=myWidth*(myDepth/8);
    if(myDepth==8) {
      fprintf(stderr,"8 bit pixels not implemented yet!");
      exitCleanly(0);
    }
    if(myDepth==16) *format = SDL_PIXELFORMAT_RGB565;
    if(myDepth==32) *format = SDL_PIXELFORMAT_RGB888;

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


#ifdef AMIGA_DEBUG
    //fprintf(stderr,"amigaos3 updateWindowFramebuffer...\n"); fflush(stderr);
#endif

    /*screen_buffer_t buffer;*/

    /*if (screen_get_window_property_pv(impl->window, SCREEN_PROPERTY_BUFFERS,
                                      (void **)&buffer) < 0) {
        return -1;
    }*/

    /*screen_post_window(impl->window, buffer, numrects, (int *)rects, 0);
    screen_flush_context(context, 0);*/
  
    // TODO Should I lock anything here?	
    (void)WritePixelArray(mypixels,0,0,
                       myWidth*(myDepth/8),
                       amigawindow->RPort,
                       0,0,
                       drawWidth,
                       drawHeight,
                       RECTFMT_ARGB); // NOTE: That's only correct for 32 bit pixels
    // TODO Should I unlock anything here?	

    return 0;
}

static void setWindowTitle(_THIS, SDL_Window *window)
{
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 setWindowTitle %s...\n",window->title); fflush(stderr);
#endif
    SetWindowTitles(amigawindow,window->title,window->title);
}

/**
 * Updates the size of the native window using the geometry of the SDL window.
 * @param   _THIS
 * @param   window  SDL window to update
 */
static void setWindowSize(_THIS, SDL_Window *window)
{
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
    //int             size[2];

    //size[0] = window->w;
    //size[1] = window->h;

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 setWindowSize to %dx%d...\n",window->w,window->h); fflush(stderr);
#endif

    if(window->w>myWidth) window->w=myWidth;
    if(window->h>myHeight) window->h=myHeight;

    ChangeWindowBox(amigawindow,0,0,window->w,window->h);

    drawWidth=window->w; drawHeight=window->h;
    myWidth=window->w; myHeight=window->h;
 
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
    //const int       visible = 1;

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
    //window_impl_t   *impl = (window_impl_t *)window->driverdata;
    //const int       visible = 0;

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
    //SDL_VideoDevice *device;

//#ifndef SDL_MAIN_NEEDED
    freopen (STDOUT_FILE, "w", stdout);
    freopen (STDERR_FILE, "w", stderr);
//#endif

#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 createDevice...\n"); fflush(stderr);
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
    tdevice->SetWindowTitle = setWindowTitle;
    /**/
    tdevice->ShowWindow = showWindow;
    tdevice->HideWindow = hideWindow;
    /**/
    tdevice->DestroyWindow = destroyWindow;
    tdevice->CreateWindowFramebuffer = createWindowFramebuffer;
    tdevice->UpdateWindowFramebuffer = updateWindowFramebuffer;

    tdevice->PumpEvents = SDL_Amiga_pumpEvents;

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


void cleanupAmiga()
{
#ifdef AMIGA_DEBUG
    fprintf(stderr,"amigaos3 cleanupAmiga...\n"); fflush(stderr);
#endif
  // TODO: Cleanup threads if possible here?
  if(timpl) { free(timpl); timpl=NULL; }
  if(tdevice) { free(tdevice); tdevice=NULL; }
  if(amigawindow) { CloseWindow(amigawindow); amigawindow=NULL; }
  if(amigascreen) { CloseScreen(amigascreen); amigascreen=NULL; }
  if(theBM) { FreeBitMap(theBM); theBM=NULL; }
  if(mypixels) { free(mypixels); mypixels=NULL; }
  if(CyberGfxBase) { CloseLibrary(CyberGfxBase); CyberGfxBase=NULL; }
  if(IntuitionBase) { CloseLibrary(&IntuitionBase->LibNode); IntuitionBase=NULL; }
  if(GfxBase) { CloseLibrary(&GfxBase->LibNode); GfxBase=NULL; }
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
