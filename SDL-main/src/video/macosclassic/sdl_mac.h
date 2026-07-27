/* Shared declarations for the Classic Mac OS video driver. */

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

#if TARGET_API_MAC_CARBON
#if TARGET_RT_MAC_MACHO
#include <Carbon/Carbon.h>
#else
#include "../../thread/macosclassic/MacThreads.h"
#undef SIGHUP
#undef SIGURG
#undef SIGPOLL
#include <Carbon.h>
#endif
#else
#include "../../thread/macosclassic/MacThreads.h"
#undef SIGHUP
#undef SIGURG
#undef SIGPOLL
#include <Quickdraw.h>
#include <QDOffscreen.h>
#include <MacWindows.h>
#include <Dialogs.h>
#endif


/* Define MAC_DEBUG locally when diagnosing the Toolbox backend. */

#define QUICKDRAW_BLIT 1

/* Default window size */
#define PLATFORM_SCREEN_WIDTH 640 
#define PLATFORM_SCREEN_HEIGHT 480 
#define PLATFORM_SCREEN_DEPTH 32 

#define WINDOW_OFFSET_X 4
#define WINDOW_OFFSET_Y 40


/* State shared by the video, event, mouse, and OpenGL modules. */
extern int macmoddown;
extern WindowPtr macwindow;
extern CGrafPtr macport;
extern int myDepth;
extern SDL_Window *sdlw;
extern int mac_window_active;
#if !TARGET_API_MAC_CARBON
extern QDGlobals *theQD;
#endif


extern void handleKeyboardEvent(EventRecord *event,int what);
extern void Mac_PollKeyboard(void);
extern void Mac_ResetKeyboardState(void);
extern void Mac_InitAppleEvents(void);
extern void Mac_QuitAppleEvents(void);
extern int Mac_InitMouse(void);
extern void Mac_QuitMouse(void);
extern int Mac_InputSprocketPoll(int *dx, int *dy);
extern int Mac_InputSprocketIsActive(void);
extern void Mac_InputSprocketSetCapture(int enabled);
extern void Mac_InputSprocketSetForeground(int active);
extern int Mac_IsRelativeMouseMode(void);
extern void Mac_CenterMouse(void);
extern void Mac_ResetMouseTracking(void);
extern void Mac_ForceShowCursor(void);
extern void Mac_SetWindowActive(int active);
extern int Mac_IsFrontProcess(void);
extern void Mac_ProcessDrawSprocketEvent(EventRecord *event);
extern int Mac_GL_SetDrawableActive(int active);
extern void Mac_GL_Update(void);

extern int glLoadLibrary(_THIS, const char *name);
void *glGetProcAddress(_THIS, const char *proc);
extern SDL_GLContext glCreateContext(_THIS, SDL_Window *window);
extern int glSetSwapInterval(_THIS, int interval);
extern int glSwapWindow(_THIS, SDL_Window *window);
extern int glMakeCurrent(_THIS, SDL_Window * window, SDL_GLContext context);
extern void glUpdateWindow(_THIS, SDL_Window *window);
extern void glDeleteContext(_THIS, SDL_GLContext context);
extern void glUnloadLibrary(_THIS);

#endif

#endif
