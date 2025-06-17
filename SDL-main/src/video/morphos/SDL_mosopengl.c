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

#if SDL_VIDEO_DRIVER_MORPHOS

#include "SDL_error.h"
#include "SDL_syswm.h"
#include "../SDL_sysvideo.h"
#include "SDL_mosvideo.h"
#include "SDL_mosmodes.h"
#include "SDL_moswindow.h"
#include "../../core/morphos/SDL_library.h"

#include <proto/exec.h>
#include <proto/tinygl.h>
#include <proto/intuition.h>
#include <proto/graphics.h>

#include <tgl/gl.h>
#include <tgl/gla.h>

GLContext *__tglContext;

extern struct SDL_Library *SDL2Base;

int
MOS_GL_LoadLibrary(_THIS, const char *path)
{

	if (!TinyGLBase)
		TinyGLBase = OpenLibrary("tinygl.library", 53); 

	if (TinyGLBase) {
			if (!LIB_MINVER(TinyGLBase, 53, 8))		
			{
				SDL_SetError("Failed to open tinygl.library 53.8+");
				return -1;
			}
			if (SDL2Base->MyTinyGLBase)				
				*SDL2Base->MyTinyGLBase = TinyGLBase;	
			
			return 0;
	} else 
		SDL_SetError("Failed to open tinygl.library 53+");

	return -1;
}

void *
MOS_GL_GetProcAddress(_THIS, const char *proc)
{
	void *func = NULL;
	func = tglGetProcAddress(proc);
	if (!func) {
    	SDL_SetError("Couldn't find OpenGL symbol");
		return NULL;
    }
	return func;
}

void
MOS_GL_UnloadLibrary(_THIS)
{
	D("[%s]\n", __FUNCTION__);

	if (SDL2Base->MyTinyGLBase && *SDL2Base->MyTinyGLBase && TinyGLBase) {
		CloseLibrary(TinyGLBase);
		*SDL2Base->MyTinyGLBase = TinyGLBase = NULL;
	}
}

static void
MOS_GL_FreeBitMap(_THIS, SDL_Window *window)
{
    D("[%s]\n", __FUNCTION__);
    SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
    if (data->bitmap != NULL) {
        FreeBitMap(data->bitmap);
        data->bitmap = NULL;
    }
}

static SDL_bool
MOS_GL_AllocBitmap(_THIS, SDL_Window * window)
{
	D("[%s]\n", __FUNCTION__);
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;

	if (data->bitmap != NULL)
		MOS_GL_FreeBitMap(_this, window);
	
	struct BitMap * friend_bitmap = data->win->RPort->BitMap;
	ULONG depth = GetBitMapAttr(friend_bitmap, BMA_DEPTH);

	int w = getv(data->win, WA_InnerWidth);
	int h = getv(data->win, WA_InnerHeight);
	
	D("[%s] AllocBitMap w=%d h=%d depth=%d\n", __FUNCTION__, w, h, (int)depth);
	
	return (data->bitmap = AllocBitMap(w, h, depth, BMF_MINPLANES|BMF_DISPLAYABLE|BMF_3DTARGET, friend_bitmap)) != NULL;
}

static SDL_bool
MOS_GL_InitContext(_THIS, SDL_Window * window)
{
	D("[%s]\n", __FUNCTION__);
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
	
	if (data->__tglContext != NULL) {
		GLADestroyContext(data->__tglContext);
		data->__tglContext = NULL;
        MOS_GL_FreeBitMap(_this, window);
	}

	struct TagItem tgltags[] =
	{
		{TAG_IGNORE, 0},
		{TGL_CONTEXT_STENCIL, TRUE},
		{TAG_DONE}
	};	

	if (MOS_GL_AllocBitmap(_this, window)) {	
		tgltags[0].ti_Tag = TGL_CONTEXT_BITMAP;
		tgltags[0].ti_Data = (IPTR)data->bitmap;
	} else {
		D("[%s] Failed to AllocBitmap !", __FUNCTION__);	
		return SDL_FALSE;
	}
		
	// Initialize new context
 	int success = GLAInitializeContext(__tglContext, tgltags);
	if (success) {
		data->__tglContext = __tglContext;
		
		// Clean Screen
		if (!window->flags & SDL_WINDOW_FULLSCREEN) {
			GLClearColor(__tglContext, 0.0f, 0.0f, 0.0f, 1.0f);
			GLClear(__tglContext, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}
		return SDL_TRUE;	
	}

	return SDL_FALSE;		
}

SDL_GLContext
MOS_GL_CreateContext(_THIS, SDL_Window * window)
{
    D("[%s]\n", __FUNCTION__);
	SDL_WindowData *data = window->driverdata;
	
	GLContext *glcont = GLInit();
	if (glcont) {
		__tglContext = glcont;
#ifdef TGL_CONTEXT_VERSION_53_9
		if (SDL2Base->MyGetMaximumContextVersion)
		{
			unsigned int contextversion;
			contextversion = SDL2Base->MyGetMaximumContextVersion(TinyGLBase);

			if (contextversion == TGL_CONTEXT_VERSION_53_1)
			{
				TGLEnableNewExtensions(__tglContext, 0);
			}
			else if (contextversion >= TGL_CONTEXT_VERSION_53_9)
			{
				TGLSetContextVersion(__tglContext, contextversion);
			}
		}
#endif
		if (MOS_GL_InitContext(_this, window)) {
			D("[%s] MOS_GL_InitContext SUCCES 0x%08lx, data->__tglContext=0x%08lx\n", __FUNCTION__, glcont, data->__tglContext);

			*SDL2Base->MyGLContext = glcont;
			
			GLClearColor(glcont, 0.0f, 0.0f, 0.0f, 1.0f);
			GLClear(glcont, GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			
			return glcont;
		} else {
			D("[%s] MOS_GL_InitContext FAILED 0x%08lx, data->__tglContext=0x%08lx\n", __FUNCTION__, glcont, data->__tglContext);

            MOS_GL_FreeBitMap(_this, window);
			GLClose(glcont);
			*SDL2Base->MyGLContext = data->__tglContext = __tglContext = NULL;
			
			SDL_SetError("Couldn't initialize TinyGL context");
		}
	} else {
		SDL_SetError("Couldn't create TinyGL context");
	}

	return NULL;
}

int
MOS_GL_MakeCurrent(_THIS, SDL_Window * window, SDL_GLContext context)
{
	D("[%s] context 0x%08lx\n", __FUNCTION__, context);
    if (window && context) {
        *SDL2Base->MyGLContext = __tglContext = context;
    }
	return 0;
}

void
MOS_GL_GetDrawableSize(_THIS, SDL_Window *window, int *width, int *height)
{
    
	SDL_WindowData *data = window->driverdata;
    int w = 0;
    int h = 0;
    if (data->win) {
			w = data->win->Width - data->win->BorderLeft - data->win->BorderRight;
			h = data->win->Height - data->win->BorderTop - data->win->BorderBottom;
	}
   // D("[%s] System window size (%d * %d), SDL window size (%d * %d)\n", __FUNCTION__, w, h, window->w, window->h);
    if (width)
        *width = w;
    if (height)
        *height = h;


}

int
MOS_GL_SetSwapInterval(_THIS, int interval)
{
	SDL_VideoData *data = _this->driverdata;
	
	switch (interval) {
		case 0:
		case 1:
			// always VSYNC in fullscreen
			data->vsyncEnabled = /*data->CustomScreen != NULL ? TRUE : */(interval ? TRUE : FALSE);
			return 0;
		default:
			return -1;
	}	
}

int
MOS_GL_GetSwapInterval(_THIS)
{
	SDL_VideoData *data = _this->driverdata;
	return data->vsyncEnabled ? 1 : 0;
}

int
MOS_GL_SwapWindow(_THIS, SDL_Window * window)
{
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;

	if (!data->win || !data->__tglContext || !__tglContext)
		return 0;

	SDL_VideoData *video = _this->driverdata;
	if (video->vsyncEnabled && data->win->WScreen) {
		BOOL displayed = getv(data->win->WScreen, SA_Displayed);
		if (displayed) {
			WaitBOVP(&data->win->WScreen->ViewPort);
		}
	}
	
	GLASwapBuffers(data->__tglContext);
	
	if (data->bitmap != NULL) {
		
		BltBitMapRastPort(data->bitmap, 0, 0, data->win->RPort, data->win->BorderLeft, data->win->BorderTop, 
				window->w, window->h, 0xc0);
	}
	
	
	return 0;
}

void
MOS_GL_DeleteContext(_THIS, SDL_GLContext context)
{
	D("[%s] context 0x%08lx\n", __FUNCTION__, context);

	if (TinyGLBase != NULL && context) {
		SDL_Window *sdlwin;

		for (sdlwin = _this->windows; sdlwin; sdlwin = sdlwin->next) {

			SDL_WindowData *data = sdlwin->driverdata;

			if (data->__tglContext == context) {
                D("[%s] Found TinyGL context 0x%08lx, clearing window binding\n", __FUNCTION__, context);
                GLADestroyContext(context);
				data->__tglContext = NULL;
                MOS_GL_FreeBitMap(_this, sdlwin);
			}
		}
		GLClose(context);
		*SDL2Base->MyGLContext = __tglContext = NULL;
	}
}

int
MOS_GL_ResizeContext(_THIS, SDL_Window *window)
{
	
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
	D("[%s] Context=0x%08lx data->__tglContext=0x%08lx\n", __FUNCTION__, __tglContext, data->__tglContext);
	if (data->__tglContext == NULL || __tglContext == NULL || data->win == NULL) {
		return -1;
	}
	
	return (MOS_GL_InitContext(_this, window) ? 0 : -1);
}

#endif /* SDL_VIDEO_DRIVER_MORPHOS */
