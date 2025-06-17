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

#include "SDL_mosmouse.h"
#include "SDL_mosvideo.h"

#include "../../events/SDL_mouse_c.h"
#include "SDL_hints.h"

#include <cybergraphx/cybergraphics.h>
#include <devices/input.h>
#include <intuition/pointerclass.h>
#include <proto/cybergraphics.h>
#include <proto/exec.h>
#include <proto/graphics.h>
#include <proto/dos.h>
#include <dos/rdargs.h>

MOS_GlobalMouseState globalMouseState;

static SDL_Cursor *
MOS_CreateCursor(SDL_Surface * surface, int hot_x, int hot_y)
{
	D("[%s]\n", __FUNCTION__);
	SDL_MOSCursor *cursor = SDL_malloc(sizeof(*cursor));

	if (cursor) {
		SDL_MOSCursor *ac = SDL_malloc(sizeof(*ac));
		struct BitMap *bmp;

		cursor->Cursor.next = NULL;
		cursor->Cursor.driverdata = &cursor->Pointer;
		cursor->Pointer.offx = hot_x;
		cursor->Pointer.offy = hot_y;

		bmp = AllocBitMap(surface->w, surface->h, 32, BMF_MINPLANES | BMF_CLEAR | BMF_SPECIALFMT | SHIFT_PIXFMT(PIXFMT_ARGB32), NULL);

		if (bmp != NULL) {
			struct RastPort rp;

			InitRastPort(&rp);
			rp.BitMap = bmp;

			if (SDL_LockSurface(surface) == 0) {
				WritePixelArray(surface->pixels, 0, 0, surface->pitch, &rp, 0, 0, surface->w, surface->h, RECTFMT_ARGB);
				Object *mouseptr = NewObject(NULL,POINTERCLASS,
								POINTERA_BitMap, bmp,
								POINTERA_XOffset, -hot_x,
								POINTERA_YOffset, -hot_y,
								TAG_DONE);

				cursor->Pointer.mouseptr = mouseptr;
				SDL_UnlockSurface(surface);
			}

			FreeBitMap(bmp);
		} else {
			SDL_free(cursor);
			cursor = NULL;
		}
	}

	return &cursor->Cursor;
}

static SDL_Cursor *
MOS_CreateSystemCursor(SDL_SystemCursor id)
{
	SDL_Cursor *cursor = SDL_malloc(sizeof(*cursor));
	//D("[%s]\n", __FUNCTION__);

	if (cursor) {
		size_t type = POINTERTYPE_NORMAL;
		cursor->next = NULL;
		switch (id) {
			default:
			case SDL_SYSTEM_CURSOR_ARROW:     type = POINTERTYPE_NORMAL; break;
			case SDL_SYSTEM_CURSOR_IBEAM:     type = POINTERTYPE_SELECTTEXT; break;
			case SDL_SYSTEM_CURSOR_WAIT:      type = POINTERTYPE_BUSY; break;
			case SDL_SYSTEM_CURSOR_CROSSHAIR: type = POINTERTYPE_AIMING; break;
			case SDL_SYSTEM_CURSOR_WAITARROW: type = POINTERTYPE_WORKING; break;
			case SDL_SYSTEM_CURSOR_SIZENWSE:  type = POINTERTYPE_DIAGONALRESIZE2; break;
			case SDL_SYSTEM_CURSOR_SIZENESW:  type = POINTERTYPE_DIAGONALRESIZE1; break;
			case SDL_SYSTEM_CURSOR_SIZEWE:    type = POINTERTYPE_HORIZONTALRESIZE; break;
			case SDL_SYSTEM_CURSOR_SIZENS:    type = POINTERTYPE_VERTICALRESIZE; break;
			case SDL_SYSTEM_CURSOR_SIZEALL:   type = POINTERTYPE_MOVE; break;
			case SDL_SYSTEM_CURSOR_NO:        type = POINTERTYPE_NOTAVAILABLE; break;
			case SDL_SYSTEM_CURSOR_HAND:      type = POINTERTYPE_SELECTLINK; break;
		}

		cursor->driverdata = (APTR)type;
	} else {
		SDL_OutOfMemory();
	}

	return cursor;
}

static void
MOS_FreeCursor(SDL_Cursor *cursor)
{
	D("[%s] 0x%08lx\n", __FUNCTION__, cursor);

	if (!IS_SYSTEM_CURSOR(cursor))
		if (((SDL_MOSCursor *)cursor)->Pointer.mouseptr)
			DisposeObject(((SDL_MOSCursor *)cursor)->Pointer.mouseptr);

	SDL_free(cursor);
}

static int
MOS_ShowCursor(SDL_Cursor * cursor)
{
	SDL_VideoDevice *video = SDL_GetVideoDevice();
	SDL_VideoData *data = (SDL_VideoData *)video->driverdata;
	//D("[%s] 0x%08lx\n", __FUNCTION__, cursor);

	if (IS_SYSTEM_CURSOR(cursor)) {
		size_t type = cursor ? (size_t)cursor->driverdata : POINTERTYPE_INVISIBLE;

		if (data->CurrentPointer != cursor) {
			SDL_WindowData *wd;
			size_t pointertags[] = { WA_PointerType, type, TAG_DONE };

			ForeachNode(&data->windowlist, wd) {
				if (wd->win) {
                    SetAttrsA(wd->win, (struct TagItem *)&pointertags);
                }
            }
		}
	} else {
		SDL_MOSCursor *ac = (SDL_MOSCursor *)cursor;
		SDL_WindowData *wd;

		ForeachNode(&data->windowlist, wd) {
            if (wd->win) {
                if (ac->Pointer.mouseptr) {
                    SetWindowPointer(wd->win, WA_Pointer, (size_t)ac->Pointer.mouseptr, TAG_DONE);
                }
            }
        }
	}

	data->CurrentPointer = cursor;

	return 0;
}

static void
MOS_WarpMouse(SDL_Window * window, int x, int y)
{
	SDL_WindowData *data = (SDL_WindowData *)window->driverdata;
	struct Window *win;

	BOOL warpHostPointer;
	warpHostPointer = !SDL_GetRelativeMouseMode() && (window == SDL_GetMouseFocus());

	if (warpHostPointer) {

		if ((win = data->win)) {
			struct MsgPort *port;
			struct IOStdReq *req;

			port = CreateMsgPort();
			if (port) {
				req = CreateIORequest(port, sizeof(*req));
				if (req) {
					if (OpenDevice("input.device", 0, (struct IORequest *)req, 0) == 0) {
						struct InputEvent ie = { 0 };
						struct IEPointerPixel newpos = { 0 };

						newpos.iepp_Screen = win->WScreen;
						newpos.iepp_Position.X = x + win->BorderLeft + win->LeftEdge;
						newpos.iepp_Position.Y = y + win->BorderTop + win->TopEdge;

						ie.ie_EventAddress = &newpos;
						ie.ie_NextEvent = NULL;
						ie.ie_Class = IECLASS_NEWPOINTERPOS;
						ie.ie_SubClass = IESUBCLASS_PIXEL;
						ie.ie_Code = IECODE_NOBUTTON;
						ie.ie_Qualifier = 0;

						req->io_Data = &ie;
						req->io_Length = sizeof(ie);
						req->io_Command = IND_WRITEEVENT;

						DoIO((struct IORequest *)req);
						CloseDevice((struct IORequest *)req);
					}
				}

				DeleteMsgPort(port);
			}
		}
	} else {
		SDL_SendMouseMotion(window,0, SDL_GetRelativeMouseMode(), x, y);
	}
}

static int
MOS_SetRelativeMouseMode(SDL_bool enabled)
{
	D("[%s]\n", __FUNCTION__);
	
	SDL_VideoDevice *video = SDL_GetVideoDevice();
	SDL_VideoData *data = (SDL_VideoData *)video->driverdata;
	SDL_WindowData *wd;
	size_t or_mask, and_mask;

	if (enabled) {
		or_mask = IDCMP_DELTAMOVE;
		and_mask = ~0;
	} else {
		or_mask = 0;
		and_mask = ~IDCMP_DELTAMOVE;
	}

	ForeachNode(&data->windowlist, wd)
		if (wd->win)
			ModifyIDCMP(wd->win, (wd->win->IDCMPFlags | or_mask) & and_mask);

	return 0;
}

static Uint32
MOS_GetDoubleClickTimeInMillis(_THIS)
{
    Uint32 interval = 500;

    struct RDArgs rda;
    SDL_memset(&rda, 0, sizeof(rda));
    rda.RDA_Source.CS_Buffer = (STRPTR)SDL_LoadFile("ENV:sys/mouse.conf", (size_t *)&rda.RDA_Source.CS_Length);
    if (rda.RDA_Source.CS_Buffer) {
        LONG *array[4] = {0};
        if (ReadArgs("Pointer/K,RMBEmulationQualifier/K,DoubleClickS/N/K,DoubleClickM/N/K,/F", (LONG *)array, &rda)) {
			if (array[2] != 0L && array[3] != 0L)
            	interval = *array[2] * 1000 + *array[3] / 1000;

	    	FreeArgs(&rda);
        }
        SDL_free(rda.RDA_Source.CS_Buffer);
    }

    return interval;
}

static Uint32
MOS_GetGlobalMouseState(int *x, int *y)
{
    Uint32 buttons = 0;

    if (x) {
        *x = globalMouseState.x;
    }

    if (y) {
        *y = globalMouseState.y;
    }

    if (globalMouseState.buttonPressed[SDL_BUTTON_LEFT]) {
        buttons |= SDL_BUTTON_LMASK;
    }

    if (globalMouseState.buttonPressed[SDL_BUTTON_MIDDLE]) {
        buttons |= SDL_BUTTON_MMASK;
    }

    if (globalMouseState.buttonPressed[SDL_BUTTON_RIGHT]) {
        buttons |= SDL_BUTTON_RMASK;
    }
    
    if (globalMouseState.buttonPressed[SDL_BUTTON_X1]) {
        buttons |= SDL_BUTTON_X1MASK;
    }

    return buttons;
}

void
MOS_InitMouse(_THIS)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	char buffer[16];

	mouse->CreateCursor = MOS_CreateCursor;
	mouse->CreateSystemCursor = MOS_CreateSystemCursor;
	mouse->ShowCursor = MOS_ShowCursor;
	mouse->FreeCursor = MOS_FreeCursor;
	mouse->WarpMouse = MOS_WarpMouse;
	mouse->SetRelativeMouseMode = MOS_SetRelativeMouseMode;
    mouse->GetGlobalMouseState = MOS_GetGlobalMouseState;

	SDL_SetDefaultCursor(MOS_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	SDL_SetHint(SDL_HINT_MOUSE_DOUBLE_CLICK_TIME,  SDL_uitoa(MOS_GetDoubleClickTimeInMillis(_this), buffer, 10));
}

void
MOS_QuitMouse(_THIS)
{
	SDL_Mouse *mouse = SDL_GetMouse();
	//D("[%s]\n", __FUNCTION__);

	if ( mouse->def_cursor ) {
		SDL_free(mouse->def_cursor);
		mouse->def_cursor = NULL;
		mouse->cur_cursor = NULL;
	}
}
