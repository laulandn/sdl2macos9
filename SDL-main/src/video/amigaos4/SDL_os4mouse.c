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

#include <proto/exec.h>
#include <proto/intuition.h>
#include <intuition/pointerclass.h>

#include "SDL_os4mouse.h"
#include "SDL_os4video.h"
#include "SDL_os4window.h"

#include "SDL_hints.h"
#include "../../events/SDL_mouse_c.h"

#include "../../main/amigaos4/SDL_os4debug.h"

#include <devices/input.h>

static SDL_Cursor *hiddenCursor;

typedef struct SDL_CursorData {
    int hot_x;
    int hot_y;
    ULONG type;
    Object *object;
    Uint32 *imageData;
} SDL_CursorData;

static UWORD fallbackPointerData[2 * 16] = { 0 };

static struct BitMap fallbackPointerBitMap = { 2, 16, 0, 2, 0,
    { (PLANEPTR)fallbackPointerData, (PLANEPTR)(fallbackPointerData + 16) } };


OS4_GlobalMouseState globalMouseState;

static Uint32
OS4_GetDoubleClickTimeInMillis(_THIS)
{
    struct Preferences preferences;
    Uint32 interval;

    IIntuition->GetPrefs(&preferences, sizeof(preferences));

    interval =  preferences.DoubleClick.Seconds * 1000 +
                preferences.DoubleClick.Microseconds / 1000;

    dprintf("Doubleclick time %d ms\n", interval);

    return interval;
}

static SDL_Cursor*
OS4_CreateCursorInternal()
{
    SDL_Cursor *cursor = SDL_calloc(1, sizeof(SDL_Cursor));

    //dprintf("Called\n");

    if (cursor) {
        SDL_CursorData *data = SDL_calloc(1, sizeof(SDL_CursorData));

        if (data) {
            cursor->driverdata = data;
        } else {
            dprintf("Failed to create cursor data\n");
        }
    } else {
        dprintf("Failed to create cursor\n");
    }

    return cursor;

}

static SDL_Cursor*
OS4_CreateDefaultCursor()
{
    SDL_Cursor *cursor = OS4_CreateCursorInternal();

    dprintf("%p\n", cursor);

    if (cursor && cursor->driverdata) {
        SDL_CursorData *data = cursor->driverdata;

        data->type = POINTERTYPE_NORMAL;
    }

    return cursor;
}

static Uint32*
OS4_CopyImageData(SDL_Surface * surface)
{
    const size_t bytesPerRow = surface->w * sizeof(Uint32);
    Uint32* buffer = SDL_malloc(bytesPerRow * surface->h);

    dprintf("Copying cursor data %d*%d from surface %p to buffer %p\n",
        surface->w, surface->h, surface, buffer);

    if (buffer) {
        if (SDL_MUSTLOCK(surface)) {
            SDL_LockSurface(surface);
        }

        Uint8* source = surface->pixels;
        Uint32* destination = buffer;
        int y;

        for (y = 0; y < surface->h; y++) {
            SDL_memcpy(destination, source, bytesPerRow);
            destination += surface->w;
            source += surface->pitch;
        }

        if (SDL_MUSTLOCK(surface)) {
            SDL_UnlockSurface(surface);
        }
    } else {
        dprintf("Failed to allocate memory\n");
    }

    return buffer;
}

static SDL_Cursor*
OS4_CreateCursor(SDL_Surface * surface, int hot_x, int hot_y)
{
    SDL_Cursor *cursor = OS4_CreateCursorInternal();

    dprintf("Surface %p, cursor %p, hot_x %d, hot_y %d\n", surface, cursor, hot_x, hot_y);

    if (cursor && cursor->driverdata) {
        if (surface->w > 64) {
            dprintf("Invalid width %d\n", surface->w);
        } else if (surface->h > 64) {
            dprintf("Invalid height %d\n", surface->h);
        } else {
            Uint32* buffer = OS4_CopyImageData(surface);

            /* We need to pass some compatibility parameters
            even though we are going to use just ARGB pointer */

            Object *object = IIntuition->NewObject(
                NULL,
                POINTERCLASS,
                POINTERA_BitMap, &fallbackPointerBitMap,
                POINTERA_XOffset, hot_x,
                POINTERA_YOffset, hot_y,
                POINTERA_WordWidth, 1,
                POINTERA_XResolution, POINTERXRESN_SCREENRES,
                POINTERA_YResolution, POINTERYRESN_SCREENRES,
                POINTERA_ImageData, buffer,
                POINTERA_Width, surface->w,
                POINTERA_Height, surface->h,
                TAG_DONE);

            if (object) {
                dprintf("Object %p\n", object);
                SDL_CursorData *data = cursor->driverdata;
                data->object = object;
                data->imageData = buffer;
            } else {
                dprintf("Failed to create pointer object\n");
            }
        }
    }

    return cursor;
}

static void
OS4_CreateHiddenCursor()
{
    dprintf("Called\n");

    /* Create invisible 1*1 cursor because system version (POINTERTYPE_NONE) has a shadow */

    SDL_Surface *surface = SDL_CreateRGBSurface(0, 1, 1, 32,
        0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);

    if (surface) {
        SDL_FillRect(surface, NULL, 0x0);

        hiddenCursor = OS4_CreateCursor(surface, 0, 0);

        SDL_FreeSurface(surface);
    } else {
        dprintf("Failed to create surface for hidden cursor\n");
    }
}


static ULONG
OS4_MapCursorIdToNative(SDL_SystemCursor id)
{
    switch (id) {
        case SDL_SYSTEM_CURSOR_ARROW: return POINTERTYPE_NORMAL;
        //case SDL_SYSTEM_CURSOR_IBEAM: return POINTERTYPE_SELECT; 54.21
        case SDL_SYSTEM_CURSOR_WAITARROW:
        case SDL_SYSTEM_CURSOR_WAIT: return POINTERTYPE_BUSY;
        case SDL_SYSTEM_CURSOR_CROSSHAIR: return POINTERTYPE_CROSS;
        case SDL_SYSTEM_CURSOR_SIZENWSE: return POINTERTYPE_NORTHWESTSOUTHEASTRESIZE;
        case SDL_SYSTEM_CURSOR_SIZENESW: return POINTERTYPE_NORTHEASTSOUTHWESTRESIZE;
        case SDL_SYSTEM_CURSOR_SIZEWE: return POINTERTYPE_EASTWESTRESIZE;
        case SDL_SYSTEM_CURSOR_SIZENS: return POINTERTYPE_NORTHSOUTHRESIZE;
        case SDL_SYSTEM_CURSOR_NO: return POINTERTYPE_NOTALLOWED;
        case SDL_SYSTEM_CURSOR_HAND: return POINTERTYPE_HAND;
        //
        case SDL_SYSTEM_CURSOR_SIZEALL:
        default:
            dprintf("Unknown mapping from type %d\n", id);
            return POINTERTYPE_NORMAL;
    }
}

static SDL_Cursor*
OS4_CreateSystemCursor(SDL_SystemCursor id)
{
    SDL_Cursor *cursor = OS4_CreateCursorInternal();

    //dprintf("Called %d\n", id);

    if (cursor && cursor->driverdata) {
        SDL_CursorData *data = cursor->driverdata;

        data->type = OS4_MapCursorIdToNative(id);
    }

    return cursor;
}

static void
OS4_SetPointerObjectOrTypeForWindow(struct Window * window, ULONG type, Object * object)
{
    if (object || type) {
        dprintf("Setting pointer object %p (type %lu) for window %p\n", object, type, window);
    }

    if (window) {
        if (object) {
            IIntuition->SetWindowPointer(
                window,
                WA_Pointer, object,
                TAG_DONE);
        } else {
            IIntuition->SetWindowPointer(
                window,
                WA_PointerType, type,
                TAG_DONE);
        }
    }
}

static void
OS4_SetPointerForEachWindow(ULONG type, Object * object)
{
    _THIS = SDL_GetVideoDevice();

    SDL_Window *sdlwin;

    for (sdlwin = _this->windows; sdlwin; sdlwin = sdlwin->next) {
        SDL_WindowData *data = sdlwin->driverdata;

        OS4_SetPointerObjectOrTypeForWindow(data->syswin, type, object);
    }
}

void
OS4_ResetCursorForWindow(struct Window * window)
{
    dprintf("Called\n");

    if (window) {
        // Restore normal system pointer
        IIntuition->SetWindowPointer(
            window,
            WA_Pointer, NULL,
            TAG_DONE);
    }
}

void
OS4_RestoreSdlCursorForWindow(struct Window * window)
{
    dprintf("Called\n");

    // Restore SDL-configured cursor (possibly hidden)

    Object* object = NULL;
    ULONG type = POINTERTYPE_NONE;

    SDL_Mouse* mouse = SDL_GetMouse();
    if (mouse->cursor_shown) {
        SDL_Cursor *cursor = mouse->cur_cursor;
        if (cursor) {
            SDL_CursorData *data = cursor->driverdata;
            if (data) {
                type = data->type;
                object = data->object;
            } else {
                dprintf("NULL data\n");
            }
        } else {
            dprintf("NULL cursor\n");
        }
    } else {
        SDL_CursorData *data = hiddenCursor->driverdata;
        if (data) {
            object = data->object;
        } else {
            dprintf("NULL data\n");
        }
    }

    OS4_SetPointerObjectOrTypeForWindow(window, type, object);
}

static int
OS4_ShowCursor(SDL_Cursor * cursor)
{
    ULONG type = POINTERTYPE_NORMAL;
    Object *object = NULL;

    if (cursor) {
        SDL_CursorData *data = cursor->driverdata;

        //dprintf("Called %p %p\n", cursor, data);

        if (data) {
            type = data->type;
            object = data->object;
        } else {
            dprintf("No cursor data\n");
            return -1;
        }
    } else {
        dprintf("Hiding cursor\n");

        type = POINTERTYPE_NONE;

        if (hiddenCursor) {
            SDL_CursorData *data = hiddenCursor->driverdata;

            if (data) {
                object = data->object;
            }
        }
    }

    OS4_SetPointerForEachWindow(type, object);

    return 0;
}

static void
OS4_FreeCursor(SDL_Cursor * cursor)
{
    SDL_CursorData *data = cursor->driverdata;

    dprintf("Called %p\n", cursor);

    if (data) {
        if (data->object) {
            SDL_Mouse *mouse = SDL_GetMouse();

            if (mouse->cur_cursor == cursor) {
                dprintf("Reset to POINTERTYPE_NONE before object disposal\n");
                OS4_SetPointerForEachWindow(POINTERTYPE_NONE, NULL);
            }

            IIntuition->DisposeObject(data->object);
            data->object = NULL;
        }

        if (data->imageData) {
            SDL_free(data->imageData);
            data->imageData = NULL;
        }

        SDL_free(data);
        cursor->driverdata = NULL;
    }
}

void
OS4_RefreshCursorState(void)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    if (mouse) {
        dprintf("Mouse shown %d\n", mouse->cursor_shown);
        // Force cursor redraw
        SDL_SetCursor(NULL);
    }
}

static int
OS4_WarpMouseInternal(struct Screen *screen, int x, int y)
{
    SDL_VideoDevice *device = SDL_GetVideoDevice();
    SDL_VideoData *videoData = device->driverdata;
    int result = -1;

    if (videoData->inputReq != NULL) {
        struct InputEvent     *fakeEvent;

        /* We move the Workbench pointer by stuffing mouse
         * movement events in input.device's queue.
         *
         * This in turn will cause mouse movement events to be
         * sent back to us
         */

        fakeEvent = (struct InputEvent *)OS4_SaveAllocPooled(
            device, sizeof(struct InputEvent) + sizeof(struct IEPointerPixel));

        if (fakeEvent) {
            struct IEPointerPixel *neoPix = (struct IEPointerPixel *) (fakeEvent + 1);

            neoPix->iepp_Screen = screen ? screen : videoData->publicScreen;
            neoPix->iepp_Position.Y = y;
            neoPix->iepp_Position.X = x;

            fakeEvent->ie_EventAddress = (APTR)neoPix;
            fakeEvent->ie_NextEvent    = NULL;
            fakeEvent->ie_Class        = IECLASS_NEWPOINTERPOS;
            fakeEvent->ie_SubClass     = IESUBCLASS_PIXEL;
            fakeEvent->ie_Code         = IECODE_NOBUTTON;
            fakeEvent->ie_Qualifier    = 0;

            videoData->inputReq->io_Data    = (APTR)fakeEvent;
            videoData->inputReq->io_Length  = sizeof(struct InputEvent);
            videoData->inputReq->io_Command = IND_WRITEEVENT;

            dprintf("Sending input event\n");

            IExec->DoIO((struct IORequest *)videoData->inputReq);

            OS4_SaveFreePooled(device, (void *)fakeEvent,
                sizeof(struct InputEvent) + sizeof(struct IEPointerPixel));

            result = 0;
        }
    }

    return result;
}

static int
OS4_WarpMouseGlobal(int x, int y)
{
    dprintf("Warping mouse to %d, %d\n", x, y);

    return OS4_WarpMouseInternal(NULL, x, y);
}

static void
OS4_WarpMouse(SDL_Window * window, int x, int y)
{
    SDL_WindowData *winData = window->driverdata;
    struct Window *syswin = winData->syswin;

    SDL_bool relativeMouseMode = SDL_GetRelativeMouseMode();

    /* If the host mouse pointer is outside of the SDL window or the SDL
     * window is inactive then we just need to warp SDL's notion of where
     * the pointer position is - we don't need to move the Workbench
     * pointer. In the former case, we don't pass mass movements on to
     * to the app anyway and in the latter case we don't receive mouse
     * movements events anyway.
     */
    BOOL warpHostPointer = !relativeMouseMode && (window == SDL_GetMouseFocus());

    dprintf("Warping mouse to %d, %d\n", x, y);

    if (warpHostPointer) {
        struct Screen *screen = (window->flags & SDL_WINDOW_FULLSCREEN) ?
            syswin->WScreen : NULL;

        OS4_WarpMouseInternal(screen,
            x + syswin->BorderLeft + syswin->LeftEdge,
            y + syswin->BorderTop + syswin->TopEdge);
    } else {
        /* Just warp SDL's notion of the pointer position */
        SDL_SendMouseMotion(window, 0, relativeMouseMode, x, y);
    }
}

static int
OS4_SetRelativeMouseMode(SDL_bool enabled)
{
    return 0;
}

static Uint32
OS4_GetGlobalMouseState(int * x, int * y)
{
    uint32 buttons = 0;

    if (x) {
        *x = globalMouseState.x;
    }

    if (y) {
        *y = globalMouseState.y;
    }

    //dprintf("%d, %d\n", *x, *y);

    if (globalMouseState.buttonPressed[SDL_BUTTON_LEFT]) {
        buttons |= SDL_BUTTON_LMASK;
    }

    if (globalMouseState.buttonPressed[SDL_BUTTON_MIDDLE]) {
        buttons |= SDL_BUTTON_MMASK;
    }

    if (globalMouseState.buttonPressed[SDL_BUTTON_RIGHT]) {
        buttons |= SDL_BUTTON_RMASK;
    }

    return buttons;
}

void
OS4_InitMouse(_THIS)
{
    SDL_Mouse *mouse = SDL_GetMouse();
    char buffer[16];

    mouse->CreateCursor = OS4_CreateCursor;
    mouse->CreateSystemCursor = OS4_CreateSystemCursor;
    mouse->ShowCursor = OS4_ShowCursor;
    mouse->FreeCursor = OS4_FreeCursor;
    mouse->WarpMouse = OS4_WarpMouse;
    mouse->WarpMouseGlobal = OS4_WarpMouseGlobal;
    mouse->SetRelativeMouseMode = OS4_SetRelativeMouseMode;
    //mouse->CaptureMouse = OS4_CaptureMouse;
    mouse->GetGlobalMouseState = OS4_GetGlobalMouseState;

    SDL_SetDefaultCursor(OS4_CreateDefaultCursor());

    OS4_CreateHiddenCursor();

    SDL_SetHint(SDL_HINT_MOUSE_DOUBLE_CLICK_TIME,
        SDL_uitoa(OS4_GetDoubleClickTimeInMillis(_this), buffer, 10));
}

void
OS4_QuitMouse(_THIS)
{
    SDL_Mouse *mouse = SDL_GetMouse();

    if (mouse->def_cursor) {
        OS4_FreeCursor(mouse->def_cursor);
        mouse->def_cursor = NULL;
    }

    if (hiddenCursor) {
        OS4_FreeCursor(hiddenCursor);
        hiddenCursor = NULL;
    }

    mouse->cur_cursor = NULL;
}

#endif /* SDL_VIDEO_DRIVER_AMIGAOS4 */

/* vi: set ts=4 sw=4 expandtab: */
