/* MacOS9 Note: This code was based on the QNX driver, solely because it was the smallest
   and easiest to understand. */

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

/*#include <screen/screen.h>
#include <EGL/egl.h>*/

#ifdef BUILDING_FOR_CARBON
#include <Carbon.h>
#else
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <MacWindows.h>
#endif


#define MAC_DEBUG 1


/* Default window size */
#define PLATFORM_SCREEN_WIDTH 640 
#define PLATFORM_SCREEN_HEIGHT 480 
#define PLATFORM_SCREEN_DEPTH 32 


/* Globals are evil...these belong in driver data slash impl vars/params! */
extern int macmoddown;
extern WindowPtr macwindow;
extern CGrafPtr macport;
/**/
extern char *macpixels;
extern PixMapPtr thePM;
extern int macWidth;
extern int macHeight;
extern int macDepth;
/*extern PixMapHandle offPixMapHandle;*/
/*extern GrafPtr origPort;
extern GDHandle origDevice;*/
/*extern GWorldPtr macoffworld;
extern GWorldPtr maconworld;*/
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


extern void handleKeyboardEvent(EventRecord *event,int what);

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
