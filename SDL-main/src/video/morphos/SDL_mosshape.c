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

#include "../SDL_sysvideo.h"

#include "SDL_mosshape.h"
#include "SDL_moswindow.h"

#include <intuition/extensions.h>
#include <proto/graphics.h>
#include <proto/intuition.h>

SDL_WindowShaper*
MOS_CreateShaper(SDL_Window *window)
{
	D("[%s]\n", __FUNCTION__);
	SDL_WindowShaper *result;

	if ((result = SDL_malloc(sizeof(*result)))) {
		result->window = window;
		result->mode.mode = ShapeModeDefault;
		result->mode.parameters.binarizationCutoff = 1;
		result->userx = window->x;
		result->usery = window->y;
		result->driverdata = NULL;

		window->shaper = result;
	} else {
		SDL_OutOfMemory();
	}

	return result;
}

int
MOS_ResizeWindowShape(SDL_Window* window)
{
	D("[%s]\n", __FUNCTION__);
	SDL_WindowShaper *shaper = window->shaper;

	shaper->userx = window->x;
	shaper->usery = window->y;

	return 0;
}

static void
MOS_ShapeToRegion(struct Region *region, SDL_Surface *shape, const SDL_WindowShapeMode mode)
{
	D("[%s]\n", __FUNCTION__);
	Uint32 y, bpr = shape->format->BytesPerPixel, pitch;
	const Uint8 *pixels;
	SDL_Color key;

	D("[%s] mode: %ld\n", __FUNCTION__, mode.mode);

	if (SDL_MUSTLOCK(shape))
		SDL_LockSurface(shape);

	pixels = shape->pixels;
	pitch = shape->pitch;

	for (y = 0; y < shape->h; y++) {
		struct Rectangle rect;
		int x, have_transp = 0;

		for (x = 0; x < shape->w; x++) {
			Uint32 pixel_value = 0, mask_value = 0;
			Uint8 *pixel = (Uint8 *)(pixels) + (y * pitch) + (x * bpr);
			Uint8 r, g, b, alpha;

			switch (bpr) {
				case 1:
					pixel_value = *(Uint8*)pixel;
					break;

				case 2:
					pixel_value = *(Uint16*)pixel;
					break;

				case 3:
					pixel_value = *(Uint32*)pixel & (~shape->format->Amask);
					break;

				case 4:
					pixel_value = *(Uint32*)pixel;
					break;
			}

			SDL_GetRGBA(pixel_value, shape->format, &r, &g, &b, &alpha);

			switch (mode.mode) {
				case ShapeModeDefault:
					mask_value = (alpha >= 1 ? 1 : 0);
					break;

				case ShapeModeBinarizeAlpha:
					mask_value = (alpha >= mode.parameters.binarizationCutoff ? 1 : 0);
					break;

				case ShapeModeReverseBinarizeAlpha:
					mask_value = (alpha <= mode.parameters.binarizationCutoff ? 1 : 0);
					break;

				case ShapeModeColorKey:
					key = mode.parameters.colorKey;
					mask_value = ((key.r != r || key.g != g || key.b != b) ? 1 : 0);
					break;
			}

			if (have_transp == 0) {
				if (mask_value == 0) {
					rect.MinX = x;
					rect.MinY = y;
					rect.MaxY = y;
					have_transp = 1;
				}
			} else {
				if (mask_value == 1) {
					rect.MaxX = x - 1;
					have_transp = 0;
					OrRectRegion(region, &rect);
				}
			}
		}

		if (have_transp) {
			rect.MaxX = shape->w - 1;
			OrRectRegion(region, &rect);
		}
	}

	if (SDL_MUSTLOCK(shape))
		SDL_UnlockSurface(shape);
}

int
MOS_SetWindowShape(SDL_WindowShaper *shaper, SDL_Surface *shape, SDL_WindowShapeMode *mode)
{
	SDL_WindowData *data = shaper->window->driverdata;
	struct Region *old = data->region;
	struct Region *region = NewRegion();

	D("[%s] shaper: 0x%08lx, window: 0x%08lx, driverdata: 0x%08lx, old: 0x%08lx\n", __FUNCTION__, shaper, shaper->window, data, old);

	if (region) {
		data->region = region;

		MOS_ShapeToRegion(region, shape, shaper->mode);

		if (data->win) {
			size_t tags[] = { TRANSPCONTROL_REGION, (size_t)region, TAG_DONE };
			D("[%s] Set transparency region (0x%08lx)\n", __FUNCTION__, region);
			TransparencyControl(data->win, TRANSPCONTROLMETHOD_INSTALLREGION, (struct TagItem *)&tags);
		}

		D("[%s] DisposeRegion(0x%08lx)\n", __FUNCTION__, old);

		if (old)
			DisposeRegion(old);
	}

	return 0;
}
