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

#if SDL_VIDEO_DRIVER_AMIGAOS4

/* NOTE: shaped windows need compositing enabled for the GUI! */

#include <proto/graphics.h>
#include <proto/layers.h>
#include <proto/intuition.h>

#include "SDL_os4video.h"
#include "SDL_os4shape.h"
#include "SDL_os4window.h"

#include "SDL_shape.h"
#include "../SDL_shape_internals.h"
#include "SDL_assert.h"

#include "../../main/amigaos4/SDL_os4debug.h"

SDL_WindowShaper*
OS4_CreateShaper(SDL_Window * window)
{
    SDL_WindowData *windowdata = window->driverdata;
    SDL_WindowShaper *result = NULL;
    LONG compositing = FALSE;

    dprintf("Called %p\n", window);

    LONG r = IIntuition->GetScreenAttrs(windowdata->syswin->WScreen,
        SA_Compositing, &compositing,
        TAG_DONE);

    if (r != 0) {
        dprintf("Failed to query compositing mode\n");
    }

    if (compositing) {
        result = SDL_malloc(sizeof(SDL_WindowShaper));

        if (result) {
            SDL_ShapeData *data = SDL_malloc(sizeof(SDL_ShapeData));

            result->window = window;
            result->mode.mode = ShapeModeDefault;
            result->mode.parameters.binarizationCutoff = 1;
            result->userx = 0;
            result->usery = 0;

            if (data) {
                int resized_properly;

                data->width = 0;
                data->height = 0;
                data->bitmap = NULL;
                data->sysbm = NULL;
                data->cliprect = NULL;

                result->driverdata = data;

                window->shaper = result;
                resized_properly = OS4_ResizeWindowShape(window);

                SDL_assert(resized_properly == 0);
            } else {
                dprintf("Failed to allocate driver data\n");
                SDL_SetError("Failed to allocate driver data");
                SDL_free(result);
                result = NULL;
            }
        } else {
            //SDL_SetError("Failed to create shaper");
            dprintf("Failed to create shaper\n");
            SDL_SetError("Failed to create shaper");
        }
    } else {
        dprintf("Compositing not enabled!\n");
        SDL_SetError("Compositing not enabled");
    }

    return result;
}

static struct BitMap *
OS4_MakeAlphaBitMap(void * source, int width, int height)
{
    struct BitMap *sysbm = IGraphics->AllocBitMapTags(
        width,
        height,
        8,
        BMATags_PixelFormat, PIXF_ALPHA8,
        BMATags_Displayable, TRUE,
        TAG_DONE);

    dprintf("Creating alpha bitmap %d*%d, source %p\n", width, height, source);

    if (sysbm) {
        uint32 bytesperrow;
        APTR baseaddress;

        APTR lock = IGraphics->LockBitMapTags(sysbm,
            LBM_BaseAddress, &baseaddress,
            LBM_BytesPerRow, &bytesperrow,
            TAG_DONE);

        if (lock) {
            int y;
            uint8 *src = source;

            for (y = 0; y < height; y++) {
                int x;
                uint8 *dst = (uint8 *)baseaddress + y * bytesperrow;

                for (x = 0; x < width; x++) {
                    *dst++ = *src++;
                }
            }

            IGraphics->UnlockBitMap(lock);
        } else {
            dprintf("Failed to lock bitmap\n");
            IGraphics->FreeBitMap(sysbm);
            sysbm = NULL;
        }
    } else {
        dprintf("Failed to allocate alpha bitmap\n");
        return NULL;
    }

    return sysbm;
}

static struct ClipRect*
OS4_SetAlphaLayer(struct Window * window, SDL_ShapeData * data)
{
    struct ClipRect *cliprect;
    struct ClipRect *oldCliprect = NULL;

    ILayers->LockLayerInfo(&window->WScreen->LayerInfo);

    if (data->cliprect) {
        dprintf("Freeing old clip rect\n");
        // Also bitmap is freed by FreeClipRect
        ILayers->FreeClipRect(&window->WScreen->LayerInfo, data->cliprect);
    }

    cliprect = ILayers->AllocClipRect(&window->WScreen->LayerInfo);

    if (cliprect && data->sysbm) {
        cliprect->BitMap = data->sysbm;

        // TODO: anything else to be done?
        cliprect->bounds.MinX = 0;
        cliprect->bounds.MinY = 0;
        cliprect->bounds.MaxX = data->width - 1;
        cliprect->bounds.MaxY = data->height - 1;

        oldCliprect = ILayers->ChangeLayerAlpha(window->WLayer, cliprect, NULL);
        //IIntuition->SetWindowAttrs(window, WA_AlphaClips, cliprect, TAG_DONE); //TODO: which method is better?
    } else {
        dprintf("Failed to allocate cliprect\n");
    }

    ILayers->UnlockLayerInfo(&window->WScreen->LayerInfo);

    if (oldCliprect == (struct ClipRect *)-1) {
        dprintf("Failed to install layer alpha\n");
    }

    return cliprect;
}

void
OS4_DestroyShape(_THIS, SDL_Window * window)
{
    SDL_WindowShaper *shaper = window->shaper;

    dprintf("Called for '%s'\n", window->title);

    if (shaper && shaper->driverdata) {
        SDL_ShapeData *data = shaper->driverdata;
        SDL_WindowData *windowdata = window->driverdata;
        struct Window *syswin = windowdata->syswin;

        if (data->cliprect) {
            ILayers->LockLayerInfo(&syswin->WScreen->LayerInfo);

            dprintf("Freeing cliprect %p\n", data->cliprect);

            // Also bitmap is freed by FreeClipRect
            ILayers->FreeClipRect(&syswin->WScreen->LayerInfo, data->cliprect);
            data->cliprect = NULL;

            ILayers->UnlockLayerInfo(&syswin->WScreen->LayerInfo);
        }

        if (data->bitmap) {
            dprintf("Freeing SDL bitmap %p\n", data->bitmap);
            SDL_free(data->bitmap);
            data->bitmap = NULL;
        }

        dprintf("Freeing shape data %p\n", data);

        SDL_free(data);
        shaper->driverdata = NULL;
    } else {
        dprintf("No shaper or shape data\n");
        return;
    }
}

int
OS4_SetWindowShape(SDL_WindowShaper * shaper, SDL_Surface * shape, SDL_WindowShapeMode * shape_mode)
{
    if (shaper && shape && shape_mode && shaper->driverdata) {
        SDL_ShapeData *data = shaper->driverdata;
        SDL_WindowData *windowdata = shaper->window->driverdata;

        if (shape->format->Amask == 0 && SDL_SHAPEMODEALPHA(shape_mode->mode)) {
            dprintf("Shape doesn't have alpha channel\n");
            SDL_SetError("Shape doesn't have alpha channel");
            return -2;
        }

        if (shape->w != shaper->window->w || shape->h != shaper->window->h) {
            dprintf("Shape vs. window dimensions mismatch\n");
            SDL_SetError("Shape vs. window dimensions mismatch");
            return -3;
        }

        if (data->bitmap) {
            SDL_CalculateShapeBitmap(shaper->mode, shape, data->bitmap, 1);

            data->sysbm = OS4_MakeAlphaBitMap(data->bitmap, shape->w, shape->h);
            if (!data->sysbm) {
                dprintf("Failed to allocate alpha bitmap\n");
                SDL_SetError("Failed to allocate alpha bitmap");
                return -4;
            }

            if (!(data->cliprect = OS4_SetAlphaLayer(windowdata->syswin, data))) {
                dprintf("Failed to allocate clip rect\n");
                SDL_SetError("Failed to allocate clip rect");
                return -5;
            }

            dprintf("New alpha layer applied for window '%s'\n", shaper->window->title);
            return 0;
        } else {
            dprintf("Source bitmap nullptr\n");
            SDL_SetError("Source bitmap nullptr");
            return -6;
        }

    } else {
        dprintf("No shaper, shape or shape_mode\n");
        SDL_SetError("No shaper, shape or shape_mode");
        return -7;
    }
}

int
OS4_ResizeWindowShape(SDL_Window * window)
{
    if (window->shaper) {
        SDL_ShapeData *data = window->shaper->driverdata;

        if (data) {
            dprintf("Called for '%s' %d * %d\n", window->title, window->w, window->h);

            if (data->width != window->w ||
                data->height != window->h || data->bitmap == NULL) {

                Uint32 bitmapsize = window->w * window->h;

                data->width = window->w;
                data->height = window->h;

                if (data->bitmap) {
                    SDL_free(data->bitmap);
                }

                data->bitmap = SDL_malloc(bitmapsize);

                if (data->bitmap) {
                    SDL_memset(data->bitmap, 0, bitmapsize);
                } else {
                    dprintf("Failed to allocate memory for shaped-window bitmap\n");
                    return SDL_SetError("Failed to allocate memory for shaped-window bitmap");
                }
            } else {
                dprintf("Resize ignored\n");
            }

            //window->shaper->userx = window->x;
            //window->shaper->usery = window->y;
            //SDL_SetWindowPosition(window, -1000, -1000);//??
            return 0;
        } else {
            dprintf("No shape data\n");
            SDL_SetError("No shape data");
            return -1;
        }
    } else {
        dprintf("Window has no shaper\n");
        SDL_SetError("Window has no shaper");
        return -1;
    }
}

#endif /* SDL_VIDEO_DRIVER_AMIGAOS4 */

/* vi: set ts=4 sw=4 expandtab: */
