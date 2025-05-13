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

#if SDL_VIDEO_RENDER_AMIGAOS4 && !SDL_RENDER_DISABLED

#include "SDL_render_compositing.h"
#include "SDL_rc_texture.h"
#include "SDL_rc_draw.h"

#include "../SDL_sysrender.h"

#include "../../video/SDL_sysvideo.h"
#include "../../video/amigaos4/SDL_os4window.h"
#include "../../video/amigaos4/SDL_os4video.h"

#include <proto/graphics.h>
#include <proto/layers.h>
#include <intuition/intuition.h>

#include "../../main/amigaos4/SDL_os4debug.h"

/* AmigaOS4 (compositing) renderer implementation

TODO:

- SDL_BlendMode_Mod: is it impossible to accelerate?
- Blended line drawing could probably be optimized

NOTE:

- compositing is used for blended rectangles and texture blitting
- blended lines and points are drawn with the CPU as compositing doesn't support these primitives
    (could try small triangles to plot a point?)
- texture color modulation is implemented by CPU

*/

typedef struct {
    float x, y;
    float s, t, w;
} OS4_Vertex;

#define MAX_QUADS 1000

static uint16_t OS4_QuadIndices[6 * MAX_QUADS];

typedef struct {
    float srcAlpha;
    float destAlpha;
    uint32 flags;
} OS4_CompositingParams;

SDL_bool
OS4_IsColorModEnabled(SDL_Texture * texture)
{
    if ((texture->color.r & texture->color.g & texture->color.b) != 255) {
        //dprintf("Color mod enabled (%d, %d, %d)\n", texture->r, texture->g, texture->b);
        return SDL_TRUE;
    }

    return SDL_FALSE;
}

struct BitMap *
OS4_AllocBitMap(SDL_Renderer * renderer, int width, int height, int depth, const char* const reason)
{
    dprintf("Allocating bitmap %d*%d*%d for %s\n", width, height, depth, reason);

    struct BitMap *bitmap = IGraphics->AllocBitMapTags(
        width,
        height,
        depth,
        BMATags_Displayable, TRUE,
        BMATags_PixelFormat, PIXF_A8R8G8B8,
        TAG_DONE);

    if (bitmap) {
        /* Fill with zeroes, similar to SW renderer surface creation */
        struct RastPort rp;
        IGraphics->InitRastPort(&rp);
        rp.BitMap = bitmap;

        IGraphics->RectFillColor(
            &rp,
            0,
            0,
            width - 1,
            height - 1,
            0x00000000); // graphics.lib v54!
    } else {
        dprintf("Failed to allocate bitmap\n");
    }

    return bitmap;
}

struct BitMap *
OS4_ActivateRenderer(SDL_Renderer * renderer)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;

    if (!data->target) {
        data->target = data->bitmap;
    }

    if (!data->target && renderer->window) {

        int width = renderer->window->w;
        int height = renderer->window->h;
        int depth = 32;

        data->target = data->bitmap = OS4_AllocBitMap(renderer, width, height, depth, "renderer");
    }

    if (!data->solidcolor) {
        int width = 1;
        int height = 1;
        int depth = 32;

        data->solidcolor = OS4_AllocBitMap(renderer, width, height, depth, "solid color");
    }

    data->rastport.BitMap = data->target;

    return data->target;
}

static void
OS4_WindowEvent(SDL_Renderer * renderer, const SDL_WindowEvent *event)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;

    dprintf("Called with event %d\n", event->event);

    if (event->event == SDL_WINDOWEVENT_SIZE_CHANGED) {

        /* Next time ActivateRenderer() is called, new bitmap will be created */
        if (data->bitmap) {

            dprintf("Freeing renderer bitmap %p\n", data->bitmap);

            IGraphics->FreeBitMap(data->bitmap);
            data->bitmap = NULL;
            data->target = NULL;
        }
    }
}

static int
OS4_GetBitMapSize(SDL_Renderer * renderer, struct BitMap * bitmap, int * w, int * h)
{
    if (bitmap) {
        if (w) {
            *w = IGraphics->GetBitMapAttr(bitmap, BMA_ACTUALWIDTH);
	        //dprintf("w=%d\n", *w);
        }
        if (h) {
            *h = IGraphics->GetBitMapAttr(bitmap, BMA_HEIGHT);
			//dprintf("h=%d\n", *h);
        }

        return 0;
    } else {
        SDL_SetError("NULL bitmap");
        return -1;
    }
}

static int
OS4_GetOutputSize(SDL_Renderer * renderer, int *w, int *h)
{
    struct BitMap * bitmap = OS4_ActivateRenderer(renderer);

    if (!bitmap) {
        SDL_SetError("OS4 renderer doesn't have an output bitmap");
        return -1;
    }

    return OS4_GetBitMapSize(renderer, bitmap, w, h);
}

/* Special function to set our 1 * 1 * 32 bitmap */
static SDL_bool
OS4_SetSolidColor(SDL_Renderer * renderer, Uint32 color)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;

    if (data->solidcolor) {
        APTR baseaddress;

        APTR lock = IGraphics->LockBitMapTags(
            data->solidcolor,
            LBM_BaseAddress, &baseaddress,
            TAG_DONE);

        if (lock) {
            *(Uint32 *)baseaddress = color;

            IGraphics->UnlockBitMap(data->solidcolor);

            return SDL_TRUE;
        } else {
            dprintf("Lock failed\n");
        }
    }

    return SDL_FALSE;
}

static uint32
OS4_ConvertBlendMode(SDL_BlendMode mode)
{
    switch (mode) {
        case SDL_BLENDMODE_NONE:
            return COMPOSITE_Src;
        case SDL_BLENDMODE_BLEND:
            return COMPOSITE_Src_Over_Dest;
        case SDL_BLENDMODE_ADD:
            return COMPOSITE_Plus;
        case SDL_BLENDMODE_MOD:
            // This is not correct, but we can't do modulation at the moment
            return COMPOSITE_Src_Over_Dest;
        default:
            dprintf("Unknown blend mode %d\n", mode);
            return COMPOSITE_Src_Over_Dest;
    }
}

static uint32
OS4_GetCompositeFlags(SDL_BlendMode mode)
{
    uint32 flags = COMPFLAG_IgnoreDestAlpha | COMPFLAG_HardwareOnly;

    if (mode == SDL_BLENDMODE_NONE) {
        flags |= COMPFLAG_SrcAlphaOverride;
    }

    return flags;
}

static void
OS4_SetupCompositing(SDL_Texture * dst, OS4_CompositingParams * params, SDL_ScaleMode scaleMode, SDL_BlendMode blendMode, Uint8 alpha)
{
    params->flags = COMPFLAG_HardwareOnly;

    if (scaleMode != SDL_ScaleModeNearest) {
        params->flags |= COMPFLAG_SrcFilter;
    }

    if (blendMode == SDL_BLENDMODE_NONE) {
        if (!dst) {
            params->flags |= COMPFLAG_SrcAlphaOverride;
        }
        params->srcAlpha = 1.0f;
    } else {
        params->srcAlpha = alpha / 255.0f;
    }

    params->destAlpha = 1.0f;
}

static void
OS4_RotateVertices(OS4_Vertex vertices[4], const double angle, const SDL_FPoint * center)
{
    int i;

    float rads = angle * M_PI / 180.0f;

    float sina = SDL_sinf(rads);
    float cosa = SDL_cosf(rads);

    for (i = 0; i < 4; ++i) {
        float x = vertices[i].x - center->x;
        float y = vertices[i].y - center->y;

        vertices[i].x = x * cosa - y * sina + center->x;
        vertices[i].y = x * sina + y * cosa + center->y;
    }
}

static void
OS4_ScaleVertices(OS4_Vertex vertices[4], const float scale_x, const float scale_y)
{
     int i;

     for (i = 0; i < 4; i++) {
         vertices[i].x *= scale_x;
         vertices[i].y *= scale_y;
     }
}

static void
OS4_FillVertexData(OS4_Vertex vertices[4], const SDL_Rect * srcrect, const SDL_Rect * dstrect,
    const double angle, const SDL_FPoint * center, const SDL_RendererFlip flip, float scale_x, float scale_y)
{
    /* Flip texture coordinates if needed */

    Uint16 left, right, top, bottom, tmp;

    left = srcrect->x;
    right = left + srcrect->w;
    top = srcrect->y;
    bottom = top + srcrect->h;

    if (flip & SDL_FLIP_HORIZONTAL) {
        tmp = left;
        left = right;
        right = tmp;
    }

    if (flip & SDL_FLIP_VERTICAL) {
        tmp = bottom;
        bottom = top;
        top = tmp;
    }

    /*

    Plan is to draw quad with two triangles:

    v0-v3
    | \ |
    v1-v2

    */

    vertices[0].x = dstrect->x;
    vertices[0].y = dstrect->y;
    vertices[0].s = left;
    vertices[0].t = top;
    vertices[0].w = 1.0f;

    vertices[1].x = dstrect->x;
    vertices[1].y = dstrect->y + dstrect->h;
    vertices[1].s = left;
    vertices[1].t = bottom;
    vertices[1].w = 1.0f;

    vertices[2].x = dstrect->x + dstrect->w;
    vertices[2].y = dstrect->y + dstrect->h;
    vertices[2].s = right;
    vertices[2].t = bottom;
    vertices[2].w = 1.0f;

    vertices[3].x = dstrect->x + dstrect->w;
    vertices[3].y = dstrect->y;
    vertices[3].s = right;
    vertices[3].t = top;
    vertices[3].w = 1.0f;

    if (angle != 0.0) {
        OS4_RotateVertices(vertices, angle, center);
    }

    if (scale_x != 1.0f || scale_y != 1.0f) {
        OS4_ScaleVertices(vertices, scale_x, scale_y);
    }
}

static int
OS4_RenderFillRects(SDL_Renderer * renderer, const SDL_Rect * points, int count, SDL_BlendMode mode,
    Uint8 a, Uint8 r, Uint8 g, Uint8 b)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;
    struct BitMap *bitmap = OS4_ActivateRenderer(renderer);
    int i, status;

    //dprintf("Called for %d rects\n", count);
    //Sint32 s = SDL_GetTicks();

    if (!bitmap) {
        return -1;
    }

    if (mode == SDL_BLENDMODE_NONE) {

        const Uint32 color = a << 24 | r << 16 | g << 8 | b;

        for (i = 0; i < count; ++i) {

            SDL_Rect clipped;

            /* Perform clipping - is it possible to use RastPort? */
            if (!SDL_IntersectRect(&points[i], &data->cliprect, &clipped)) {
                continue;
            }

            IGraphics->RectFillColor(
                &data->rastport,
                clipped.x,
                clipped.y,
                clipped.x + clipped.w - 1,
                clipped.y + clipped.h - 1,
                color); // graphics.lib v54!
        }

        status = 0;
    } else {

        Uint32 colormod;

        if (!data->solidcolor) {
            return -1;
        }

        colormod = a << 24 | r << 16 | g << 8 | b;

        // Color modulation is implemented through fill texture manipulation
        if (!OS4_SetSolidColor(renderer, colormod)) {
            return -1;
        }

        /* TODO: batch */
        for (i = 0; i < count; ++i) {

            const SDL_Rect srcrect = { 0, 0, 1, 1 };

            OS4_Vertex vertices[4];

            uint32 ret_code;

            OS4_FillVertexData(vertices, &srcrect, &points[i], 0.0, NULL, SDL_FLIP_NONE, 1.0f, 1.0f);

            ret_code = IGraphics->CompositeTags(
                OS4_ConvertBlendMode(mode),
                data->solidcolor,
                bitmap,
                COMPTAG_DestX,      data->cliprect.x,
                COMPTAG_DestY,      data->cliprect.y,
                COMPTAG_DestWidth,  data->cliprect.w,
                COMPTAG_DestHeight, data->cliprect.h,
                COMPTAG_Flags,      OS4_GetCompositeFlags(mode),
                COMPTAG_VertexArray, vertices,
                COMPTAG_VertexFormat, COMPVF_STW0_Present,
                COMPTAG_NumTriangles, 2,
                COMPTAG_IndexArray, OS4_QuadIndices,
                TAG_END);

            if (ret_code) {
                static Uint32 counter = 0;

                if ((counter++ % 100) == 0) {
                    dprintf("CompositeTags: %ld (fails: %u)\n", ret_code, counter);
                }
            }
        }

        status = 0;
    }

    //dprintf("Took %d\n", SDL_GetTicks() - s);

    return status;
}

static int
OS4_RenderCopyEx(SDL_Renderer * renderer, SDL_RenderCommand * cmd, const OS4_Vertex * vertices,
    size_t count, struct BitMap * dst)
{
    SDL_Texture * texture = cmd->data.draw.texture;
    const SDL_BlendMode mode = cmd->data.draw.blend;

    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;
    OS4_TextureData *texturedata = (OS4_TextureData *) texture->driverdata;

    struct BitMap *src = OS4_IsColorModEnabled(texture) ?
        texturedata->finalbitmap : texturedata->bitmap;

    OS4_CompositingParams params;
    uint32 ret_code;

    if (!dst) {
        return -1;
    }

    OS4_SetupCompositing(renderer->target, &params, texture->scaleMode, mode, cmd->data.draw.a);

    //dprintf("clip x %d, y %d, w %d, h %d\n", data->cliprect.x, data->cliprect.y, data->cliprect.w, data->cliprect.h);

    ret_code = IGraphics->CompositeTags(
        OS4_ConvertBlendMode(mode),
        src,
        dst,
        COMPTAG_SrcAlpha,   COMP_FLOAT_TO_FIX(params.srcAlpha),
        COMPTAG_DestAlpha,  COMP_FLOAT_TO_FIX(params.destAlpha),
        COMPTAG_DestX,      data->cliprect.x,
        COMPTAG_DestY,      data->cliprect.y,
        COMPTAG_DestWidth,  data->cliprect.w,
        COMPTAG_DestHeight, data->cliprect.h,
        COMPTAG_Flags,      params.flags,
        COMPTAG_VertexArray, vertices,
        COMPTAG_VertexFormat, COMPVF_STW0_Present,
        COMPTAG_NumTriangles, 2 * count,
        COMPTAG_IndexArray, OS4_QuadIndices,
        TAG_END);

    if (ret_code) {
        static Uint32 counter = 0;

        if ((counter++ % 100) == 0) {
            dprintf("CompositeTags: %lu (fails: %u)\n", ret_code, counter);
        }

        return SDL_SetError("CompositeTags failed");
    }

    return 0;
}

static int
OS4_RenderGeometry(SDL_Renderer * renderer, SDL_RenderCommand * cmd, const OS4_Vertex * vertices,
    struct BitMap * dst)
{
    SDL_Texture * texture = cmd->data.draw.texture;
    const SDL_BlendMode mode = cmd->data.draw.blend;

    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;
    OS4_TextureData *texturedata = (OS4_TextureData *) texture->driverdata;

    OS4_CompositingParams params;
    uint32 ret_code;

    if (!dst) {
        return -1;
    }

    OS4_SetupCompositing(renderer->target, &params, texture->scaleMode, mode, 255);

    ret_code = IGraphics->CompositeTags(
        OS4_ConvertBlendMode(mode),
        texturedata->bitmap,
        dst,
        COMPTAG_SrcAlpha,   COMP_FLOAT_TO_FIX(params.srcAlpha),
        COMPTAG_DestAlpha,  COMP_FLOAT_TO_FIX(params.destAlpha),
        COMPTAG_DestX,      data->cliprect.x,
        COMPTAG_DestY,      data->cliprect.y,
        COMPTAG_DestWidth,  data->cliprect.w,
        COMPTAG_DestHeight, data->cliprect.h,
        COMPTAG_Flags,      params.flags,
        COMPTAG_VertexArray, vertices,
        COMPTAG_VertexFormat, COMPVF_STW0_Present,
        COMPTAG_NumTriangles, cmd->data.draw.count / 3,
        TAG_END);

    if (ret_code) {
        static Uint32 counter = 0;

        if ((counter++ % 100) == 0) {
            dprintf("CompositeTags: %lu (fails: %u)\n", ret_code, counter);
        }

        return SDL_SetError("CompositeTags failed");
    }


    return 0;
}

static int
OS4_RenderReadPixels(SDL_Renderer * renderer, const SDL_Rect * rect,
                    Uint32 format, void * pixels, int pitch)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;

    struct BitMap *bitmap = OS4_ActivateRenderer(renderer);

    //dprintf("Called\n");

    if (!bitmap) {
        return -1;
    }

    if (rect->x < 0 || rect->x+rect->w > renderer->window->w ||
        rect->y < 0 || rect->y+rect->h > renderer->window->h) {
        return SDL_SetError("Tried to read outside of surface bounds");
    }

    if (format != SDL_PIXELFORMAT_ARGB8888) {
        return SDL_SetError("Unsupported pixel format");
    }

    IGraphics->ReadPixelArray(
        &data->rastport,
        rect->x,
        rect->y,
        pixels,
        0,
        0,
        pitch,
        PIXF_A8R8G8B8,
        rect->w,
        rect->h);

    return 0;
}

static int min(int a, int b)
{
    return (a < b) ? a : b;
}

static int
OS4_RenderPresent(SDL_Renderer * renderer)
{
    SDL_Window *window = renderer->window;
    struct BitMap *source = OS4_ActivateRenderer(renderer);

    //dprintf("Called\n");
    //Uint32 s = SDL_GetTicks();

    if (window && source) {
        OS4_RenderData *data = (OS4_RenderData *)renderer->driverdata;

        // TODO: should we take viewport into account?

        SDL_WindowData *windowdata = (SDL_WindowData *)window->driverdata;

        struct Window *syswin = windowdata->syswin;

        if (syswin) {

            int32 ret;
            int width;
            int height;

            //dprintf("target %p\n", data->target);

            if (data->vsyncEnabled) {
                IGraphics->WaitTOF();
            }

            ILayers->LockLayer(0, syswin->WLayer);

            width = min(window->w, syswin->Width - (syswin->BorderLeft + syswin->BorderRight));
            height = min(window->h, syswin->Height - (syswin->BorderTop + syswin->BorderBottom));

            ret = IGraphics->BltBitMapTags(
                BLITA_Source, source,
                BLITA_DestType, BLITT_RASTPORT,
                BLITA_Dest, syswin->RPort,
                BLITA_DestX, syswin->BorderLeft,
                BLITA_DestY, syswin->BorderTop,
                BLITA_Width, width,
                BLITA_Height, height,
                TAG_DONE);

            ILayers->UnlockLayer(syswin->WLayer);

            if (ret != -1) {
                dprintf("BltBitMapTags(): %ld\n", ret);
		return -1;
            }
        }
    }
    //dprintf("Took %d\n", SDL_GetTicks() - s);
    return 0;
}

static void
OS4_RenderClear(SDL_Renderer * renderer, Uint8 a, Uint8 r, Uint8 g, Uint8 b, struct BitMap * bitmap)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;
    const Uint32 color = (a << 24) | (r << 16) | (g << 8) | b;

    int width = 0;
    int height = 0;

    OS4_GetBitMapSize(renderer, bitmap, &width, &height);

    IGraphics->RectFillColor(
        &data->rastport,
        0,
        0,
        width - 1,
        height - 1,
        color); // graphics.lib v54!
}

static void
OS4_DestroyRenderer(SDL_Renderer * renderer)
{
    OS4_RenderData *data = (OS4_RenderData *) renderer->driverdata;

    if (data->bitmap) {
        dprintf("Freeing renderer bitmap %p\n", data->bitmap);

        IGraphics->FreeBitMap(data->bitmap);
        data->bitmap = NULL;
    }

    if (data->solidcolor) {
        IGraphics->FreeBitMap(data->solidcolor);
        data->solidcolor = NULL;
    }

    SDL_free(data);
}

static int
OS4_QueueNop(SDL_Renderer * renderer, SDL_RenderCommand *cmd)
{
    return 0;
}

static int
OS4_QueueDrawPoints(SDL_Renderer * renderer, SDL_RenderCommand *cmd, const SDL_FPoint * points, int count)
{
    SDL_Point *verts = (SDL_Point *) SDL_AllocateRenderVertices(renderer, count * sizeof(SDL_Point), 0, &cmd->data.draw.first);
    size_t i;

    if (!verts) {
        return -1;
    }

    cmd->data.draw.count = count;

    for (i = 0; i < count; i++, verts++, points++) {
        verts->x = (int)points->x;
        verts->y = (int)points->y;
    }

    return 0;
}

static int
OS4_QueueDrawLines(SDL_Renderer * renderer, SDL_RenderCommand *cmd, const SDL_FPoint * points, int count)
{
    return OS4_QueueDrawPoints(renderer, cmd, points, count);
}

static int
OS4_QueueFillRects(SDL_Renderer * renderer, SDL_RenderCommand *cmd, const SDL_FRect * rects, int count)
{
    SDL_Rect *verts = (SDL_Rect *) SDL_AllocateRenderVertices(renderer, count * sizeof(SDL_Rect), 0, &cmd->data.draw.first);
    size_t i;

    if (!verts) {
        return -1;
    }

    cmd->data.draw.count = count;

    for (i = 0; i < count; i++, verts++, rects++) {
        verts->x = (int)rects->x;
        verts->y = (int)rects->y;
        verts->w = SDL_max((int)rects->w, 1);
        verts->h = SDL_max((int)rects->h, 1);
    }

    return 0;
}

static int
OS4_QueueCopyEx(SDL_Renderer * renderer, SDL_RenderCommand *cmd, SDL_Texture * texture,
               const SDL_Rect * srcrect, const SDL_FRect * dstrect,
               const double angle, const SDL_FPoint *center, const SDL_RendererFlip flip, float scale_x, float scale_y)
{
    SDL_Rect final_rect;
    SDL_FPoint final_center;

    OS4_Vertex *verts = (OS4_Vertex *) SDL_AllocateRenderVertices(renderer,
        4 * sizeof(OS4_Vertex), 0, &cmd->data.draw.first);

    if (!verts) {
        return -1;
    }
    //dprintf("SRC %d, %d, %d, %d, DST %f, %f, %f, %f\n", srcrect->x, srcrect->y, srcrect->w, srcrect->h, dstrect->x, dstrect->y, dstrect->w, dstrect->h);
    cmd->data.draw.count = 1;

    final_rect.x = (int)dstrect->x;
    final_rect.y = (int)dstrect->y;
    final_rect.w = (int)dstrect->w;
    final_rect.h = (int)dstrect->h;

    final_center.x = dstrect->x + center->x;
    final_center.y = dstrect->y + center->y;

    OS4_FillVertexData(verts, srcrect, &final_rect, angle, &final_center, flip, scale_x, scale_y);

    return OS4_SetTextureColorMod(renderer, texture);
}

static int
OS4_QueueCopy(SDL_Renderer * renderer, SDL_RenderCommand * cmd, SDL_Texture * texture,
    const SDL_Rect * srcrect, const SDL_FRect *dstrect)
{
    const SDL_FPoint center = { 0.0f, 0.0f };
    return OS4_QueueCopyEx(renderer, cmd, texture, srcrect, dstrect, 0.0, &center, SDL_FLIP_NONE, 1.0f, 1.0f);
}

static int OS4_QueueGeometry(SDL_Renderer *renderer, SDL_RenderCommand *cmd, SDL_Texture *texture,
    const float *xy, int xy_stride, const SDL_Color *color, int color_stride, const float *uv, int uv_stride,
    int num_vertices, const void *indices, int num_indices, int size_indices,
    float scale_x, float scale_y)
{
    int i;
    int count = indices ? num_indices : num_vertices;
    OS4_Vertex *verts;

    /* CompositeTags vertex mode has various limitations */

    if (!texture) {
        static Uint32 counter = 0;
        if (counter++ < 10) {
            dprintf("Texture required for geometry\n");
        }
        return SDL_Unsupported();
    }

    if (color) {
        static Uint32 counter = 0;
        if (counter++ < 10) {
            dprintf("Per-vertex color modulation not supported\n");
        }
        //return SDL_Unsupported();
    }

    verts = (OS4_Vertex *) SDL_AllocateRenderVertices(renderer, count * sizeof(OS4_Vertex), 0, &cmd->data.draw.first);
    if (!verts) {
        return -1;
    }

    cmd->data.draw.count = count;
    size_indices = indices ? size_indices : 0;

    for (i = 0; i < count; i++) {
        int j;
        float *xy_;
        if (size_indices == 4) {
            j = ((const Uint32 *)indices)[i];
        } else if (size_indices == 2) {
            j = ((const Uint16 *)indices)[i];
        } else if (size_indices == 1) {
            j = ((const Uint8 *)indices)[i];
        } else {
            j = i;
        }

        xy_ = (float *)((char*)xy + j * xy_stride);

        verts->x = xy_[0] * scale_x;
        verts->y = xy_[1] * scale_y;

        float *uv_ = (float *)((char*)uv + j * uv_stride);
        verts->s = uv_[0] * texture->w;
        verts->t = uv_[1] * texture->h;
        verts->w = 1.0f;
        verts++;
    }

    return 0;
}

static void
OS4_ResetClipRect(SDL_Renderer * renderer, struct BitMap * bitmap)
{
    // CompositeTags uses cliprect: with clipping disabled, maximize it

    OS4_RenderData *data = (OS4_RenderData *)renderer->driverdata;

    int width, height;

    OS4_GetBitMapSize(renderer, bitmap, &width, &height);

    data->cliprect.x = 0;
    data->cliprect.y = 0;
    data->cliprect.w = width;
    data->cliprect.h = height;
}

static int
OS4_RunCommandQueue(SDL_Renderer * renderer, SDL_RenderCommand * cmd, void * vertices, size_t vertsize)
{
    OS4_RenderData *data = (OS4_RenderData *)renderer->driverdata;

    struct BitMap *bitmap = OS4_ActivateRenderer(renderer);

    if (!bitmap) {
        dprintf("NULL bitmap\n");
        return -1;
    }

    while (cmd) {
        switch (cmd->command) {
            case SDL_RENDERCMD_SETDRAWCOLOR:
                // Nothing to do
                break;

            case SDL_RENDERCMD_SETVIEWPORT: {
                SDL_Rect *viewport = &data->viewport;
                if (SDL_memcmp(viewport, &cmd->data.viewport.rect, sizeof(SDL_Rect)) != 0) {
                    SDL_memcpy(viewport, &cmd->data.viewport.rect, sizeof(SDL_Rect));

                    //dprintf("viewport x %d, y %d, w %d, h %d\n", viewport->x, viewport->y, viewport->w, viewport->h);

                    if (!data->cliprect_enabled) {
                        OS4_ResetClipRect(renderer, bitmap);
                    }

                    SDL_IntersectRect(viewport, &data->cliprect, &data->cliprect);
                }
                break;
            }

            case SDL_RENDERCMD_SETCLIPRECT: {
                const SDL_Rect *rect = &cmd->data.cliprect.rect;
                if (data->cliprect_enabled != cmd->data.cliprect.enabled) {
                    data->cliprect_enabled = cmd->data.cliprect.enabled;

                    //dprintf("cliprect enabled %d\n", data->cliprect_enabled);
                }

                if (SDL_memcmp(&data->cliprect, rect, sizeof(SDL_Rect)) != 0) {
                    SDL_memcpy(&data->cliprect, rect, sizeof(SDL_Rect));

                    //dprintf("cliprect x %d, y %d, w %d, h %d\n", data->cliprect.x, data->cliprect.y, data->cliprect.w, data->cliprect.h);

                    if (data->cliprect_enabled) {
                        data->cliprect.x += data->viewport.x;
                        data->cliprect.y += data->viewport.y;
                    }
                }

                if (!data->cliprect_enabled) {
                    OS4_ResetClipRect(renderer, bitmap);
                }

                SDL_IntersectRect(&data->viewport, &data->cliprect, &data->cliprect);
                break;
            }

            case SDL_RENDERCMD_CLEAR: {
                const Uint8 r = cmd->data.color.r;
                const Uint8 g = cmd->data.color.g;
                const Uint8 b = cmd->data.color.b;
                const Uint8 a = cmd->data.color.a;
                OS4_RenderClear(renderer, a, r, g, b, bitmap);
                break;
            }

            case SDL_RENDERCMD_DRAW_POINTS: {
                const Uint8 r = cmd->data.draw.r;
                const Uint8 g = cmd->data.draw.g;
                const Uint8 b = cmd->data.draw.b;
                const Uint8 a = cmd->data.draw.a;
                const size_t count = cmd->data.draw.count;
                SDL_Point *verts = (SDL_Point *)(((Uint8 *) vertices) + cmd->data.draw.first);
                const SDL_BlendMode blend = cmd->data.draw.blend;

                /* Apply viewport */
                if (data->viewport.x || data->viewport.y) {
                    int i;
                    for (i = 0; i < count; i++) {
                        verts[i].x += data->viewport.x;
                        verts[i].y += data->viewport.y;
                    }
                }

                OS4_RenderDrawPoints(renderer, verts, count, blend, a, r, g, b);
                break;
            }

            case SDL_RENDERCMD_DRAW_LINES: {
                const Uint8 r = cmd->data.draw.r;
                const Uint8 g = cmd->data.draw.g;
                const Uint8 b = cmd->data.draw.b;
                const Uint8 a = cmd->data.draw.a;
                const size_t count = cmd->data.draw.count;
                SDL_Point *verts = (SDL_Point *)(((Uint8 *) vertices) + cmd->data.draw.first);
                const SDL_BlendMode blend = cmd->data.draw.blend;

                /* Apply viewport */
                if (data->viewport.x || data->viewport.y) {
                    int i;
                    for (i = 0; i < count; i++) {
                        verts[i].x += data->viewport.x;
                        verts[i].y += data->viewport.y;
                    }
                }

                OS4_RenderDrawLines(renderer, verts, count, blend, a, r, g, b);
                break;
            }

            case SDL_RENDERCMD_FILL_RECTS: {
                const Uint8 r = cmd->data.draw.r;
                const Uint8 g = cmd->data.draw.g;
                const Uint8 b = cmd->data.draw.b;
                const Uint8 a = cmd->data.draw.a;
                const size_t count = cmd->data.draw.count;
                SDL_Rect *verts = (SDL_Rect *)(((Uint8 *) vertices) + cmd->data.draw.first);
                const SDL_BlendMode blend = cmd->data.draw.blend;

                /* Apply viewport */
                if (data->viewport.x || data->viewport.y) {
                    int i;
                    for (i = 0; i < count; i++) {
                        verts[i].x += data->viewport.x;
                        verts[i].y += data->viewport.y;
                    }
                }

                OS4_RenderFillRects(renderer, verts, count, blend, a, r, g, b);
                break;
            }

            case SDL_RENDERCMD_COPY:
            case SDL_RENDERCMD_COPY_EX: {
                OS4_Vertex *verts = (OS4_Vertex *)(((Uint8 *) vertices) + cmd->data.draw.first);
                SDL_Texture *thistexture = cmd->data.draw.texture;
                SDL_BlendMode thisblend = cmd->data.draw.blend;
                const SDL_RenderCommandType thiscmdtype = cmd->command;
                SDL_RenderCommand *finalcmd = cmd;
                SDL_RenderCommand *nextcmd = cmd->next;
                size_t count = cmd->data.draw.count;
                while (nextcmd) {
                    const SDL_RenderCommandType nextcmdtype = nextcmd->command;
                    if (nextcmdtype != thiscmdtype) {
                        break; /* can't go any further on this draw call, different render command up next. */
                    } else if (nextcmd->data.draw.texture != thistexture || nextcmd->data.draw.blend != thisblend) {
                        break; /* can't go any further on this draw call, different texture/blendmode copy up next. */
                    } else if (nextcmd->data.draw.a != cmd->data.draw.a ||
                               nextcmd->data.draw.r != cmd->data.draw.r ||
                               nextcmd->data.draw.g != cmd->data.draw.g ||
                               nextcmd->data.draw.b != cmd->data.draw.b) {
                        break; /* different color value */
                    } else if ((count + nextcmd->data.draw.count) > MAX_QUADS) {
                        break; /* Too much data for one call */
                    } else {
                        finalcmd = nextcmd; /* we can combine copy operations here. Mark this one as the furthest okay command. */
                        count += nextcmd->data.draw.count;
                    }
                    nextcmd = nextcmd->next;
                }

                /* Apply viewport */
                if (data->viewport.x || data->viewport.y) {
                    for (int i = 0; i < count * 4; i++) {
                        verts[i].x += data->viewport.x;
                        verts[i].y += data->viewport.y;
                    }
                }

                OS4_RenderCopyEx(renderer, cmd, verts, count, bitmap);
                cmd = finalcmd;
                break;
            }

            case SDL_RENDERCMD_GEOMETRY: {
                OS4_Vertex *verts = (OS4_Vertex *)(((Uint8 *) vertices) + cmd->data.draw.first);

                /* Apply viewport */
                if (data->viewport.x || data->viewport.y) {
                    const size_t count = cmd->data.draw.count;

                    int i;
                    for (i = 0; i < count; i++) {
                        verts[i].x += data->viewport.x;
                        verts[i].y += data->viewport.y;
                    }
                }

                OS4_RenderGeometry(renderer, cmd, verts, bitmap);
                break;
            }

            case SDL_RENDERCMD_NO_OP:
                break;
        }

        cmd = cmd->next;
    }

    return 0;
}

static int
OS4_SetVSync(SDL_Renderer * renderer, int vsync)
{
    OS4_RenderData *data = renderer->driverdata;

    dprintf("VSYNC %d\n", vsync);

    data->vsyncEnabled = vsync;

    return 0;
}

static void
OS4_PrecalculateIndices(void)
{
    for (int i = 0; i < MAX_QUADS; i++) {
        const int index = i * 6;
        const int vertex = i * 4;

        OS4_QuadIndices[index + 0] = vertex + 0;
        OS4_QuadIndices[index + 1] = vertex + 1;
        OS4_QuadIndices[index + 2] = vertex + 2;
        OS4_QuadIndices[index + 3] = vertex + 2;
        OS4_QuadIndices[index + 4] = vertex + 3;
        OS4_QuadIndices[index + 5] = vertex + 0;
    }
}

int
OS4_CreateRenderer(SDL_Renderer * renderer, SDL_Window * window, Uint32 flags)
{
    OS4_RenderData *data;

    dprintf("Creating renderer for '%s' (flags 0x%x)\n", window->title, flags);

    data = (OS4_RenderData *) SDL_calloc(1, sizeof(*data));
    if (!data) {
        OS4_DestroyRenderer(renderer);
        return SDL_OutOfMemory();
    }

    renderer->WindowEvent = OS4_WindowEvent;
    renderer->GetOutputSize = OS4_GetOutputSize;
    renderer->CreateTexture = OS4_CreateTexture;
    renderer->UpdateTexture = OS4_UpdateTexture;
    renderer->LockTexture = OS4_LockTexture;
    renderer->UnlockTexture = OS4_UnlockTexture;
    renderer->SetTextureScaleMode = OS4_SetTextureScaleMode;
    renderer->SetRenderTarget = OS4_SetRenderTarget;
    renderer->QueueSetViewport = OS4_QueueNop;
    renderer->QueueSetDrawColor = OS4_QueueNop;
    renderer->QueueDrawPoints = OS4_QueueDrawPoints;
    renderer->QueueDrawLines = OS4_QueueDrawLines;
    renderer->QueueFillRects = OS4_QueueFillRects;
    renderer->QueueCopy = OS4_QueueCopy;
    renderer->QueueCopyEx = OS4_QueueCopyEx;
    renderer->QueueGeometry = OS4_QueueGeometry;
    renderer->RunCommandQueue = OS4_RunCommandQueue;
    renderer->RenderReadPixels = OS4_RenderReadPixels;
    renderer->RenderPresent = OS4_RenderPresent;
    renderer->DestroyTexture = OS4_DestroyTexture;
    renderer->DestroyRenderer = OS4_DestroyRenderer;
    renderer->SetVSync = OS4_SetVSync;
    renderer->info = OS4_RenderDriver.info;

    renderer->driverdata = data;

    IGraphics->InitRastPort(&data->rastport);

    data->vsyncEnabled = flags & SDL_RENDERER_PRESENTVSYNC;

    dprintf("VSYNC: %s\n", data->vsyncEnabled ? "on" : "off");

    OS4_PrecalculateIndices();

    return 0;
}

SDL_RenderDriver OS4_RenderDriver = {
    OS4_CreateRenderer,
    {
        "compositing",
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC,
        1,
        {
            SDL_PIXELFORMAT_ARGB8888,
        },
        0,
        0
    }
};

#endif /* !SDL_RENDER_DISABLED */

/* vi: set ts=4 sw=4 expandtab: */

