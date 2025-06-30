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

#ifndef __SDL_MAC_H__
#define __SDL_MAC_H__

#include "../SDL_sysvideo.h"

#ifdef SDL_VIDEO_DRIVER_MACOSCLASSIC

#include "../../events/SDL_mouse_c.h"

/*#include <screen/screen.h>
#include <EGL/egl.h>*/

#if TARGET_API_MAC_CARBON
// These are needed for Retro68, but should otherwise be fine
#undef SIGHUP
#undef SIGURG
#undef SIGPOLL
#include <Carbon/Carbon.h>
#else
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <MacWindows.h>
#include <Dialogs.h>
#endif


#define MAC_DEBUG 1

#define QUICKDRAW_BLIT 1
//#define USE_GWORLDS 1


/* Default window size */
#define PLATFORM_SCREEN_WIDTH 640 
#define PLATFORM_SCREEN_HEIGHT 480 
#define PLATFORM_SCREEN_DEPTH 32 


/* Globals are evil...these belong in driver data slash impl vars/params! */
// TODO: Move all these into the "impl" things
extern int macmoddown;
extern WindowPtr macwindow;
extern CGrafPtr macport;
extern PixMapPtr thePM;
/**/
extern char *mypixels;
extern int myWidth;
extern int myHeight;
extern int myDepth;
/**/
extern SDL_VideoDevice *sdlvdev;
extern SDL_VideoDisplay *sdlvdisp;
extern SDL_Window *sdlw;


typedef struct
{
    /*screen_window_t window;
    EGLSurface      surface;
    EGLConfig       conf;*/
    void *nothing;
} window_impl_t;


/* Not even sure yet if this is needed... */
typedef struct
{
  void *foo;  /* nothing real yet */
} mac_gl_context;


extern void exitCleanly(int result);

extern void handleKeyboardEvent(EventRecord *event,int what);

extern int chooseFormat(/*EGLConfig egl_conf*/);
extern int glGetConfig(void /*EGLConfig*/ *pconf, int *pformat);
extern int glLoadLibrary(_THIS, const char *name);
void *glGetProcAddress(_THIS, const char *proc);
extern SDL_GLContext glCreateContext(_THIS, SDL_Window *window);
extern int glSetSwapInterval(_THIS, int interval);
extern int glSwapWindow(_THIS, SDL_Window *window);
extern int glMakeCurrent(_THIS, SDL_Window * window, SDL_GLContext context);
extern void glDeleteContext(_THIS, SDL_GLContext context);
extern void glUnloadLibrary(_THIS);

#endif

#endif
