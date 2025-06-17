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

#include "SDL_mosmodes.h"
#include "SDL_mosvideo.h"

#include <machine/endian.h>

#include <cybergraphx/cybergraphics.h>
#include <intuition/extensions.h>
#include <intuition/monitorclass.h>
#include <proto/alib.h>
#include <proto/cybergraphics.h>
#include <proto/graphics.h>
#include <proto/intuition.h>
#include <proto/screennotify.h>
#include <proto/exec.h>

static int
MOS_GetRefreshRate(struct Screen *s)
{
    D("[%s]\n", __FUNCTION__);
    ULONG freq = 60;

    if (s) {

        ULONG modeid = getv(s, SA_DisplayID);
        APTR handle = FindDisplayInfo(modeid);
        if (handle) {
            struct MonitorInfo mi;

            if (GetDisplayInfoData(handle, (UBYTE *)&mi, sizeof(mi), DTAG_MNTR, 0) >= sizeof(mi))
                if (mi.TotalRows)
                    freq = (ULONG)(1000000000L / ((FLOAT)mi.TotalColorClocks * 280.0 * (FLOAT)mi.TotalRows / 1000.0) + 5.0);
        }
    }
	return freq;
}

static Uint32
MOS_SDLPixelFormatToDepth(Uint32 pixfmt)
{
	switch (pixfmt) {
		case SDL_PIXELFORMAT_INDEX8:
			return 8;

		case SDL_PIXELFORMAT_RGB555:
			return 15;

		case SDL_PIXELFORMAT_RGB565:
		case SDL_PIXELFORMAT_BGR565:
			return 16;

		case SDL_PIXELFORMAT_RGB888:
		case SDL_PIXELFORMAT_BGR888:
			return 24;

		default:
		case SDL_PIXELFORMAT_ARGB8888:
		case SDL_PIXELFORMAT_BGRA8888:
		case SDL_PIXELFORMAT_RGBA8888:
			return 32;
	}
}

static Uint32
MOS_GetSDLPixelFormat(Uint32 pixfmt, Uint32 default_pixfmt)
{
	switch (pixfmt) {
		case PIXFMT_LUT8   : 
			return SDL_PIXELFORMAT_INDEX8;
		case PIXFMT_BGR15:	 // 		case PIXFMT_RGB15X : 
		case PIXFMT_BGR15PC:	
			return default_pixfmt; //
		case PIXFMT_RGB15PC: 
		case PIXFMT_RGB15  : 
			return SDL_PIXELFORMAT_RGB555;
		case PIXFMT_RGB16  : 
		case PIXFMT_RGB16PC: 
			return SDL_PIXELFORMAT_RGB565;
		case PIXFMT_BGR16  : 
		case PIXFMT_BGR16PC: 
			return SDL_PIXELFORMAT_BGR565;
		case PIXFMT_RGB24  : 
			return SDL_PIXELFORMAT_RGB888;
		case PIXFMT_BGR24  : 
			return SDL_PIXELFORMAT_BGR888;
		case PIXFMT_ARGB32 : 
			return SDL_PIXELFORMAT_ARGB8888;
		case PIXFMT_BGRA32 : 
			return SDL_PIXELFORMAT_BGRA8888;
		case PIXFMT_RGBA32 : 
			return SDL_PIXELFORMAT_RGBA8888;
		default            : 
			return SDL_PIXELFORMAT_BGRA8888;
	}
}

#define MAX_SDL_PIXEL_FORMATS 15

static const struct
{
	Uint32 PixFmt, NewPixFmt;
} pixelformats[MAX_SDL_PIXEL_FORMATS] =
{
	{ PIXFMT_LUT8, SDL_PIXELFORMAT_INDEX8 },
	{ PIXFMT_RGB15, SDL_PIXELFORMAT_RGB555 },
	{ PIXFMT_RGB15X, SDL_PIXELFORMAT_RGB555 },
	{ PIXFMT_BGR15, SDL_PIXELFORMAT_BGR555 },
	{ PIXFMT_RGB15PC, SDL_PIXELFORMAT_RGB555 },
	{ PIXFMT_BGR15PC, SDL_PIXELFORMAT_BGR555 },
	{ PIXFMT_RGB16, SDL_PIXELFORMAT_RGB565 },
	{ PIXFMT_BGR16, SDL_PIXELFORMAT_BGR565 },
	{ PIXFMT_RGB16PC, SDL_PIXELFORMAT_RGB565 },
	{ PIXFMT_BGR16PC, SDL_PIXELFORMAT_BGR565 },
	{ PIXFMT_RGB24, SDL_PIXELFORMAT_RGB888 },
	{ PIXFMT_BGR24, SDL_PIXELFORMAT_BGR888 },
	{ PIXFMT_ARGB32, SDL_PIXELFORMAT_ARGB8888 },
	{ PIXFMT_BGRA32, SDL_PIXELFORMAT_BGRA8888 },
	{ PIXFMT_RGBA32, SDL_PIXELFORMAT_RGBA8888 },
};

int
MOS_InitModes(_THIS)
{
	D("[%s]\n", __FUNCTION__);
	Uint32 pixfmt = SDL_PIXELFORMAT_BGRA8888;
	int width = 1920, height = 1080, dispcount = 0;
	SDL_VideoDisplay display;
	SDL_DisplayMode mode;
	Object **monitors;
	STRPTR monitorname = NULL;
	struct Screen *s;
	APTR mon = NULL;

	SDL_zero(display);

	mode.w = 1920;
	mode.h = 1080;
	mode.refresh_rate = 60;
	mode.format = SDL_PIXELFORMAT_BGRA8888;
	mode.driverdata = NULL;

	s = LockPubScreen(NULL);

	if (s) {
		SDL_DisplayModeData *modedata;

		// This is not actual view size but virtual screens are so 90s
		width = s->Width;
		height = s->Height;

		pixfmt = MOS_GetSDLPixelFormat(getv(s, SA_PixelFormat), SDL_PIXELFORMAT_BGRA8888);
		mon = (APTR)getv(s, SA_MonitorObject);

		modedata = SDL_malloc(sizeof(*modedata));

		if (modedata) {
			modedata->monitor = mon;

			mode.format = pixfmt;
			mode.w = width;
			mode.h = height;
			mode.refresh_rate = (int)MOS_GetRefreshRate(s) / 1000;
			mode.driverdata = SDL_malloc(4);

			display.desktop_mode = mode;
			display.current_mode = mode;
			display.driverdata = modedata;
			GetAttr(MA_MonitorName, mon, (ULONG*)&monitorname);
			display.name = monitorname;

			SDL_AddVideoDisplay(&display, SDL_FALSE);
			dispcount++;

			mode.driverdata = NULL;

			D("[%s] Added Workbench screen - monitor=%d - name='%s'\n", __FUNCTION__, mon, display.name);
		}
		UnlockPubScreen(NULL, s);
	}

	// Add other monitors (not desktop)
	if ((monitors = GetMonitorList(NULL))) {
		APTR m;
		int i, j;

		for (i = 0; (m = monitors[i]); i++) {
			
			if (m != mon) {
				D("[%s] Add other monitors = %d\n", __FUNCTION__, monitors[i]);
				SDL_DisplayModeData *modedata = SDL_malloc(sizeof(*modedata));

				if (modedata) {
					ULONG *fmt = (ULONG *)getv(m, MA_PixelFormats);

					for (j = MAX_SDL_PIXEL_FORMATS - 1; j >= 0; j--) {
						pixfmt = pixelformats[j].PixFmt;

						if (fmt[pixfmt]) {
							mode.format = pixelformats[j].NewPixFmt;
							D("[%s] Add %ld/%ld pixfmt %ld\n", __FUNCTION__, mode.w, mode.h, mode.format);
							break;
						}
					}

					modedata->monitor = m;

					display.desktop_mode = mode;
					display.current_mode = mode;
					display.driverdata = modedata;
					GetAttr(MA_MonitorName, m, (ULONG*)&monitorname);
					display.name = monitorname;
					//display.name = (char *)getv(mon, MA_MonitorName);

					D("[%s] Add video display '%s'\n", __FUNCTION__, display.name);

					SDL_AddVideoDisplay(&display, SDL_FALSE);
					dispcount++;
				}
			}
		}

		FreeMonitorList(monitors);
	}

	return dispcount > 0 ? 0 : -1;
}

void
MOS_GetDisplayModes(_THIS, SDL_VideoDisplay * sdl_display)
{
	SDL_DisplayModeData *md = sdl_display->driverdata;
	D("[%s]\n", __FUNCTION__);

	if (md) {
		Object **modes = GetMonitorModesList(md->monitor, NULL);
		if (modes) {
			int modei = 0;
			while (modes[modei]) {
				SDL_DisplayMode mode = sdl_display->desktop_mode;
				Boopsiobject *amode = modes[modei++];
				ULONG modeid = INVALID_ID;
				STRPTR name = NULL;
				ULONG width = 0;
				ULONG height = 0;
				ULONG pixelfmt = PIXFMT_ARGB32;
				GetAttr(MA_Mode_Name, amode, (ULONG*)&name);
				GetAttr(MA_Mode_ModeID, amode, (ULONG*)&modeid);
				GetAttr(MA_Mode_Width, amode, (ULONG*)&width);
				GetAttr(MA_Mode_Height, amode, (ULONG*)&height);
				GetAttr(MA_Mode_PixelFormat, amode, (ULONG*)&pixelfmt);

				mode.w = width;
				mode.h = height;
				float vert = 0, hori = 0;
				DoMethod(amode, MM_Mode_GetRefreshFrequencies, &hori, &vert);
				mode.refresh_rate = (int)hori;
				mode.format = MOS_GetSDLPixelFormat(pixelfmt,SDL_PIXELFORMAT_BGRA8888);

				//D("[%s] Mode %s - pixelfmt %ld\n", __FUNCTION__, name, pixelfmt);
				mode.driverdata = sdl_display->desktop_mode.driverdata ? SDL_malloc(4) : NULL;
				SDL_AddDisplayMode(sdl_display, &mode);
			}
			FreeMonitorModesList(modes);					
		}
	}
				
}

int
MOS_GetScreen(_THIS, BYTE fullscreen, SDL_bool support3d)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	struct Screen *screen;
	int use_wb_screen = 0;
	ULONG openError = 0;
	

	if (!fullscreen && data->ScrMonName == NULL) {
		data->CustomScreen = NULL;
		screen = LockPubScreen(NULL);
		use_wb_screen = 1;
		D("[%s] Use Ambient Screen (Workbench)\n", __FUNCTION__);

	} else {

		screen = OpenScreenTags(NULL,
				/*support3d ? SA_3DSupport : TAG_IGNORE, TRUE,*/
				SA_GammaControl, TRUE,
				SA_Width, data->ScrWidth,
				SA_Height, data->ScrHeight,
				SA_Depth, data->ScrDepth,
				data->ScrMonName ? SA_MonitorName : TAG_IGNORE , data->ScrMonName,
				SA_Quiet, TRUE,
				SA_ShowTitle, FALSE,
				SA_Title, (IPTR)"SDL2",
				SA_AdaptSize, TRUE,
				SA_ErrorCode, (ULONG)&openError,
				TAG_DONE);

		if (screen)
			data->CustomScreen = screen;
	}

	if (screen == NULL) {
		if (data->ScrMonName != NULL)
			screen = LockPubScreen("Workbench");

		if (screen == NULL) {
			switch (openError) {
            case OSERR_NOMONITOR:
                SDL_SetError("Monitor for display mode not available");
                break;
            case OSERR_NOCHIPS:
                SDL_SetError("Newer custom chips required");
                break;
            case OSERR_NOMEM:
            case OSERR_NOCHIPMEM:
                SDL_OutOfMemory();
                break;
            case OSERR_PUBNOTUNIQUE:
                SDL_SetError("Public screen name not unique");
                break;
            case OSERR_UNKNOWNMODE:
            case OSERR_TOODEEP:
                SDL_SetError("Unknown display mode");
                break;
            case OSERR_ATTACHFAIL:
                SDL_SetError("Attachment failed");
                break;
            default:
				SDL_SetError("Failed to get screen.");
				break;
			}
			return -1;
		}
		use_wb_screen = 1;
	}

	data->WScreen = screen;

	if (use_wb_screen) {
		data->ScreenNotifyHandle = AddWorkbenchClient(&data->ScreenNotifyPort, -20);
	}

	if (data->ScreenSaverSuspendCount) {
		size_t i;

		for (i = data->ScreenSaverSuspendCount; i > 0; i--)
			SetAttrs(screen, SA_StopBlanker, TRUE, TAG_DONE);
	}

	return 0;
}

int
MOS_SetDisplayMode(_THIS, SDL_VideoDisplay *display, SDL_DisplayMode *mode)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

	D("[%s]\n", __FUNCTION__);

	MOS_CloseWindows(_this);
	MOS_CloseDisplay(_this);

	data->sdlpixfmt = mode->format;
	data->ScrMonName = NULL;

	// NULL means non-WB mode
	data->ScrWidth = mode->w;
	data->ScrHeight = mode->h;
	data->ScrDepth = MOS_SDLPixelFormatToDepth(mode->format);

	if (mode->driverdata == NULL) {
		data->ScrMonName = display->name;
		D("[%s] Use monitor %s\n", __FUNCTION__, data->ScrMonName);
	}

    return 0;
}

int
MOS_GetDisplayBounds(_THIS, SDL_VideoDisplay * display, SDL_Rect * rect)
{
	
	rect->x = 0;
    rect->y = 0;
    rect->w = display->current_mode.w;
    rect->h = display->current_mode.h;

    return 0;
}
