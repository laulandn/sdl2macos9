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

#include "SDL_mosvideo.h"

#include <cybergraphx/cybergraphics.h>
#include <intuition/intuition.h>
#include <proto/cybergraphics.h>
#include <graphics/rpattr.h>
#include <proto/graphics.h>
//#define OLDFB

#ifndef MIN
#   define MIN(x,y) ((x)<(y)?(x):(y))
#endif


void
MOS_DestroyWindowFramebuffer(_THIS, SDL_Window * window)
{
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
#ifdef OLDFB
	if (data) {
		if (data->fb) {
			SDL_free(data->fb);
			data->fb = NULL;
		}
	}
#else
	if (data->bitmap) {
        FreeBitMap(data->bitmap);
        data->bitmap = NULL;
    }
#endif
}

int
MOS_CreateWindowFramebuffer(_THIS, SDL_Window * window, Uint32 * format,
                            void ** pixels, int *pitch)
{
	D("[%s]\n", __FUNCTION__);
#ifdef OLDFB
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
	SDL_VideoData *vd = data->videodata;
	SDL_Framebuffer *fb;
	Uint32 fmt;
	int bpr;

	/* Free the old framebuffer surface */
	MOS_DestroyWindowFramebuffer(_this, window);

	switch (vd->sdlpixfmt) {
		case SDL_PIXELFORMAT_INDEX8:
			fmt = SDL_PIXELFORMAT_INDEX8;
			bpr = (window->w + 15) & ~15;
			break;

		default:
			fmt = SDL_PIXELFORMAT_ARGB8888;
			bpr = ((window->w * 4) + 15) & ~15;
			break;
	}

	*format = fmt;
	*pitch = bpr;

	data->fb = fb = SDL_malloc(sizeof(SDL_Framebuffer) + bpr * window->h);

	if (fb) {
		fb->bpr = bpr;
		fb->pixfmt = fmt;

		*pixels = fb->buffer;
	} else {
		return SDL_OutOfMemory();
	}
#else
	APTR lock;
    APTR base_address;
    Uint32 bytes_per_row;

	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
    if (data->bitmap) {
        FreeBitMap(data->bitmap);
    }

	if (!data->win) {
        return SDL_SetError("No system window");
    }
	
    *format = SDL_PIXELFORMAT_BGRA8888;
	struct BitMap * friend_bitmap = data->win->RPort->BitMap;
	Uint32 depth =  GetBitMapAttr(friend_bitmap, BMA_DEPTH);
	data->bitmap = AllocBitMap(window->w, window->h, depth, BMF_MINPLANES|BMF_CLEAR, friend_bitmap);
	if (!data->bitmap) {
		return SDL_SetError("Failed to allocate bitmap for framebuffer");
	} 
		
	D("[%s] Allocate bitmap %d x %d x %d for framebuffer\n", __FUNCTION__, window->w, window->h, depth);
	lock = LockBitMapTags(
        data->bitmap,
        LBMI_BASEADDRESS, &base_address,
        LBMI_BYTESPERROW, &bytes_per_row,
        TAG_DONE);

    if (lock) {
        *pixels = base_address;
        *pitch = bytes_per_row;

        UnLockBitMap(lock);
    } else {
        FreeBitMap(data->bitmap);
        data->bitmap = NULL;
        return SDL_SetError("Failed to lock framebuffer bitmap");
    }

#endif
	return 0;
}

int
MOS_UpdateWindowFramebuffer(_THIS, SDL_Window * window, const SDL_Rect * rects, int numrects)
{
	SDL_WindowData *data = (SDL_WindowData *) window->driverdata;
#ifdef OLDFB 
	if (!data || !data->win || !data->fb) {
        return 0;
    }

    SDL_Framebuffer *fb = data->fb;
	struct RastPort *rp = data->win->RPort;
    struct Window *win = data->win;

	const struct IBox windowBox = {
            win->BorderLeft,
            win->BorderTop,
            win->Width - win->BorderLeft - win->BorderRight,
            win->Height - win->BorderTop - win->BorderBottom
    };
    int dx, dy, w, h;
	const SDL_Rect * r;

    for (int i = 0; i < numrects; ++i) {
        r = &rects[i];

		dx = r->x + windowBox.Left;
		dy = r->y + windowBox.Top;
		w = MIN(r->w, windowBox.Width);
		h = MIN(r->h, windowBox.Height);

		switch (fb->pixfmt) {
            case SDL_PIXELFORMAT_INDEX8:
                if (data->videodata->CustomScreen) {

                    WritePixelArray(fb->buffer, r->x, r->y, fb->bpr, rp, dx, dy, w, h, RECTFMT_RAW);
                } else {
                    WriteLUTPixelArray(fb->buffer, r->x, r->y, fb->bpr, rp, data->videodata->coltab, dx, dy, w, h, CTABFMT_XRGB8);
                }
			break;

			default:
			case SDL_PIXELFORMAT_ARGB8888:
				WritePixelArray(fb->buffer, r->x, r->y, fb->bpr, rp, dx, dy, w, h, RECTFMT_ARGB);
				break; 
		}
	}
 #else	
	if (data->bitmap && data->win) {
		
		const struct IBox windowBox = {
                data->win->BorderLeft,
                data->win->BorderTop,
                data->win->Width - data->win->BorderLeft - data->win->BorderRight,
                data->win->Height - data->win->BorderTop - data->win->BorderBottom };
		
		for (int i = 0; i < numrects; ++i) {
            const SDL_Rect * r = &rects[i];
			int dx = r->x + windowBox.Left;
			int dy = r->y + windowBox.Top;
		    int w =  MIN(r->w, windowBox.Width);
			int h = MIN(r->h, windowBox.Height);
			BltBitMapRastPort(data->bitmap,  r->x, r->y, data->win->RPort, dx, dy, w, h, 0xc0);
		}
	}
#endif  
	return 0;
}
