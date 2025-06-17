/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2024 Sam Lantinga <slouken@libsdl.org>

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

#ifndef _SDL_moswindow_h
#define _SDL_moswindow_h

#ifndef EXEC_NODES_H
#include <exec/nodes.h>
#endif

//#include <tgl/gl.h>
#include <proto/gadtools.h>

enum
{
	MID_PROJECT = 0x0010,
	MID_ABOUT,
	MID_JOYSTICK,
	MID_ABOUTSYS,
	MID_HIDE,
	MID_QUIT,
	MID_OPTIONS,
	MID_MUTE,
	MID_PRIORITY,
	MID_RRENDER, MID_RRAUTO, MID_RRGL, MID_RRSOFT,
	MID_RVSYNC, MID_RVAUTO, MID_RVENABLE, MID_RVDISABLE,
	MID_RSCALER, MID_AUTO, MID_NEAREST, MID_LINEAR,
	MID_LLOGICAL, MID_LAUTO, MID_LLETTER,MID_LOVERS,
	MID_RBATCHING, MID_BAUTO, MID_BENABLE, MID_BDISABLE,
	MID_SHADERS, MID_SHADERS_AUTO, MID_SHADERS_ENABLE, MID_SHADERS_DISABLE, 
	MID_RMETHOD, MID_MDEF, MID_MPOINT, MID_MLINE, MID_MGEO
};

typedef struct
{
	Uint32 kludge1, kludge2, bpr, pixfmt;
	Uint8 buffer[0];
} SDL_Framebuffer;

typedef struct
{
	struct MinNode node;

	struct Region *region;
	SDL_Framebuffer *fb;

	SDL_Window *window;
	struct Window *win;
	struct AppWindow *appmsg;

	// Localized window title, use SDL_free() to deallocate
	char *window_title;

	struct SDL_VideoData *videodata;

	//GLContext *__tglContext;
	
	// Currently known window position and dimensions
	LONG curr_x, curr_y, curr_w, curr_h;
	int old_w, old_h, old_x, old_y;

	// Flags that must be taken into account at MOS_ShowWindow()
	Uint32 sdlflags;

	BYTE grabbed;
	BYTE first_deltamove;
	BYTE winflags;
	
	APTR menuvisualinfo;
	struct Menu *menu;
	BOOL menuactive;
	
	struct BitMap *bitmap;
	
} SDL_WindowData;

/* Is this window shown (not iconified) */
#define SDL_MOS_WINDOW_SHOWN      (1 << 0)
#define SDL_MOS_WINDOW_FULLSCREEN (1 << 1)
#define SDL_MOS_WINDOW_FULLSCREEN_DESKTOP (1 << 2)

/* SDL functions */
extern int MOS_CreateWindow(_THIS, SDL_Window * window);
extern int MOS_CreateWindowFrom(_THIS, SDL_Window * window, const void *data);
extern void MOS_SetWindowTitle(_THIS, SDL_Window * window);
extern void MOS_SetWindowIcon(_THIS, SDL_Window * window, SDL_Surface * icon);
extern void MOS_SetWindowPosition(_THIS, SDL_Window * window);
extern void MOS_SetWindowMinimumSize(_THIS, SDL_Window * window);
extern void MOS_SetWindowMaximumSize(_THIS, SDL_Window * window);
extern void MOS_SetWindowSize(_THIS, SDL_Window * window);
extern void MOS_ShowWindow(_THIS, SDL_Window * window);
extern void MOS_HideWindow(_THIS, SDL_Window * window);
extern void MOS_RaiseWindow(_THIS, SDL_Window * window);
extern void MOS_MaximizeWindow(_THIS, SDL_Window * window);
extern void MOS_MinimizeWindow(_THIS, SDL_Window * window);
extern void MOS_RestoreWindow(_THIS, SDL_Window * window);
extern void MOS_SetWindowBordered(_THIS, SDL_Window * window, SDL_bool bordered);
extern void MOS_SetWindowFullscreen(_THIS, SDL_Window * window, SDL_VideoDisplay * display, SDL_bool fullscreen);
extern int MOS_SetWindowGammaRamp(_THIS, SDL_Window * window, const Uint16 * ramp);
extern void MOS_SetWindowGrab(_THIS, SDL_Window * window, SDL_bool grabbed);
extern void MOS_DestroyWindow(_THIS, SDL_Window * window);
extern SDL_bool MOS_GetWindowWMInfo(_THIS, SDL_Window * window, struct SDL_SysWMinfo *info);
extern void MOS_ShowWindow_Internal(_THIS, SDL_Window * window);
extern void MOS_SetWindowAlwaysOnTop(_THIS, SDL_Window * window, SDL_bool on_top);
extern void MOS_SetWindowResizable (_THIS, SDL_Window * window, SDL_bool resizable);
extern int MOS_SetWindowOpacity(_THIS, SDL_Window * window, float opacity);
extern int MOS_GetWindowBordersSize(_THIS, SDL_Window * window, int * top, int * left, int * bottom, int * right);
extern int MOS_FlashWindow(_THIS, SDL_Window * window, SDL_FlashOperation);
//extern int MOS_SetWindowHitTest(SDL_Window *window, SDL_bool enabled);

/* Non-SDL functions */
extern void MOS_CloseWindows(_THIS);
extern void MOS_OpenWindows(_THIS);
extern void MOS_RecreateWindow(_THIS, SDL_Window * window);
extern void MOS_WindowToFront(struct Window *win);

#endif /* _SDL_moswindow_h */
