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

#include "SDL_video.h"
#include "SDL_mouse.h"
#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "SDL_hints.h"

#include "SDL_mosclipboard.h"

#include "SDL_mosframebuffer.h"
#include "SDL_moskeyboard.h"
#include "SDL_mosmodes.h"
#include "SDL_mosmouse.h"
#include "SDL_mosshape.h"
#include "SDL_mosvideo.h"
#include "SDL_moswindow.h"
#include "SDL_mosmessagebox.h"
#include "SDL_mosopengl.h"

#include <exec/execbase.h>
#include <intuition/pointerclass.h>
#include <proto/commodities.h>
#include <proto/dos.h>
#include <proto/exec.h>
#include <proto/icon.h>
#include <proto/intuition.h>
#include <proto/screennotify.h>
#include <proto/wb.h>

#include "SDL_mosevents.h"

void
MOS_CloseDisplay(_THIS)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	D("[%s] CustomScreen=0x%08lx  WScreen=0x%08lx \n", __FUNCTION__, data->CustomScreen, data->WScreen);

	if (data->CustomScreen) {
		CloseScreen(data->CustomScreen);
	}
	else if (data->WScreen) {
		if (data->ScreenSaverSuspendCount) {
			size_t i;

			for (i = data->ScreenSaverSuspendCount; i > 0; i--)
				SetAttrs(data->WScreen, SA_StopBlanker, FALSE, TAG_DONE);
		}

		UnlockPubScreen(NULL, data->WScreen);

		if (data->ScreenNotifyHandle) {
			while (!RemWorkbenchClient(data->ScreenNotifyHandle))
				Delay(10);

			data->ScreenNotifyHandle = NULL;
		}
	}

	data->CustomScreen = NULL;
	data->WScreen = NULL;
}

size_t getv(APTR obj, size_t attr)
{
	size_t val;
	GetAttr(attr, obj, (ULONG *)&val);
	return val;
}

void
MOS_HideApp(_THIS, size_t with_app_icon)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	D("[%s] %siconify\n", __FUNCTION__, with_app_icon ? "" : "no ");

    SDL_WindowData *wd;
    ForeachNode(&data->windowlist, wd)
    {
        struct Window *win = wd->win;
        if (win)
            MOS_SetWindowOpacity(_this, wd->window, 0.0);
    }

	if (with_app_icon && data->AppIcon)
		data->AppIconRef = AddAppIconA(0, 0, FilePart(data->FullAppName), &data->WBPort, 0, data->AppIcon, NULL);
}

void
MOS_ShowApp(_THIS)
{
    D("[%s]\n", __FUNCTION__);

	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

	if (data->AppIconRef) {
		struct Message *msg;

		RemoveAppIcon(data->AppIconRef);
		data->AppIconRef = NULL;

		while ((msg = GetMsg(&data->WBPort)) != NULL)
			ReplyMsg(msg);
	}

    SDL_WindowData *wd;
    ForeachNode(&data->windowlist, wd)
    {
        struct Window *win = wd->win;
        if (win) {
            MOS_SetWindowOpacity(_this, wd->window, 1.0);
            MOS_WindowToFront(win);
        }
    }

}

static int
MOS_VideoInit(_THIS)
{
	D("[%s]\n", __FUNCTION__);

	if (MOS_InitModes(_this) < 0)
		return SDL_SetError("Failed to initialize modes");

	MOS_InitKeyboard(_this);
	MOS_InitMouse(_this);

	SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, SDL_FALSE);
	SDL_SetHint(SDL_HINT_GAMECONTROLLERCONFIG_FILE, "ENV:gamecontrollerdb.txt");
	SDL_SetHint(SDL_HINT_POLL_SENTINEL, "0");

	return 0;
}

static void
MOS_VideoQuit(_THIS)
{
	D("[%s]\n", __FUNCTION__);

	MOS_CloseWindows(_this);
	MOS_CloseDisplay(_this);
	MOS_QuitMouse(_this);
}

static void
MOS_DeleteDevice(SDL_VideoDevice * device)
{
	D("[%s]\n", __FUNCTION__);
	SDL_VideoData *data = (SDL_VideoData *) device->driverdata;

	FreeSignal(data->ScreenNotifyPort.mp_SigBit);
	FreeSignal(data->BrokerPort.mp_SigBit);
	FreeSignal(data->WBPort.mp_SigBit);
	FreeSignal(data->WinPort.mp_SigBit);

	if (data->BrokerRef)
		DeleteCxObjAll(data->BrokerRef);

	if (data->AppIcon)
		FreeDiskObject(data->AppIcon);

	SDL_free(data);
	SDL_free(device);
}

void
MOS_SuspendScreenSaver(_THIS)
{
	SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;
	LONG suspend = _this->suspend_screensaver;

	D("[%s] screen 0x%08lx, suspend %ld\n", __FUNCTION__, data->WScreen, suspend);

	if (suspend == 0 && data->ScreenSaverSuspendCount == 0)
		return;

	data->ScreenSaverSuspendCount += suspend ? 1 : -1;

	if (data->WScreen)
		SetAttrs(data->WScreen, SA_StopBlanker, suspend, TAG_DONE);
}

static CONST_STRPTR
MOS_GetTaskName()
{
	struct Process *task = (struct Process *)FindTask(NULL);
	STRPTR name = "SDL";

	if (task->pr_Task.tc_Node.ln_Type == NT_PROCESS || task->pr_Task.tc_Node.ln_Type == NT_TASK) {
		if (task->pr_Task.tc_Node.ln_Type == NT_PROCESS && task->pr_CLI) {
			struct CommandLineInterface *cli = (struct CommandLineInterface *)BADDR(task->pr_CLI);

			if (cli->cli_Module && cli->cli_CommandName) {
				CONST_STRPTR src = (CONST_STRPTR)BADDR(cli->cli_CommandName);
				size_t len = *src + 1;

				if (len <= 1) {
					src = "SDL";
					len = sizeof("SDL");
				} else {
					if (src[1] == '"' && src[len] == '"')
						len -= 2;

					src++;
				}

				name = SDL_malloc(len);
				if (name)
					stccpy(name, src, len);
			}
		} else {
			size_t len = strlen(task->pr_Task.tc_Node.ln_Name) + sizeof("PROGDIR:");
			name = SDL_malloc(len);
			if (name) {
				strcpy(name, "PROGDIR:");
				strcpy(name+8, task->pr_Task.tc_Node.ln_Name);
			}
		}
	}

	D("[%s] '%s'\n", __FUNCTION__, name);
	return name;
}

static void
MOS_InitPort(struct MsgPort *port)
{
	port->mp_Node.ln_Name = "SDL";
	port->mp_Flags = PA_SIGNAL;
	port->mp_SigTask = SysBase->ThisTask;
	NEWLIST(&port->mp_MsgList);
	port->mp_SigBit = AllocSignal(-1);
}

static void
MOS_InitBroker(SDL_VideoData *data)
{
	D("[%s]\n", __FUNCTION__);
	
	STRPTR name = FilePart(data->FullAppName);
	data->AppBroker.nb_Version = NB_VERSION;
	data->AppBroker.nb_Name = name;
	data->AppBroker.nb_Title = name;
	data->AppBroker.nb_Descr = "SDL";
	data->AppBroker.nb_Unique = NBU_DUPLICATE;
	data->AppBroker.nb_Flags = COF_SHOW_HIDE;
	data->AppBroker.nb_Pri = 0;
	data->AppBroker.nb_Port = &data->BrokerPort;
	data->AppBroker.nb_ReservedChannel = 0;
	data->BrokerRef = CxBroker(&data->AppBroker, NULL);
	if (data->BrokerRef)
		ActivateCxObj(data->BrokerRef, 1);
}

static SDL_VideoDevice *
MOS_CreateDevice()
{
	/* Initialize all variables that we clean on shutdown */
	SDL_VideoDevice *device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));
	D("[%s]\n", __FUNCTION__);

	if (device) {
		SDL_VideoData *data = (struct SDL_VideoData *) SDL_calloc(1, sizeof(SDL_VideoData));

		device->driverdata = data;

		if (data) {
			MOS_InitPort(&data->ScreenNotifyPort);
			MOS_InitPort(&data->BrokerPort);
			MOS_InitPort(&data->WBPort);
			MOS_InitPort(&data->WinPort);

			data->ScrNotifySig = 1 << data->ScreenNotifyPort.mp_SigBit;
			data->BrokerSig = 1 << data->BrokerPort.mp_SigBit;
			data->WBSig = 1 << data->WBPort.mp_SigBit;
			data->WinSig = 1 << data->WinPort.mp_SigBit;

			data->sdlpixfmt = SDL_PIXELFORMAT_ARGB8888;

			NEWLIST(&data->windowlist);

			data->FullAppName = MOS_GetTaskName();
			data->AppIcon = GetDiskObject((STRPTR)data->FullAppName);

			if (data->AppIcon == NULL)
				data->AppIcon = GetDiskObject((STRPTR)"ENVARC:Sys/def_SDL");

			if (data->AppIcon) {
				data->AppIcon->do_CurrentX = NO_ICON_POSITION;
				data->AppIcon->do_CurrentY = NO_ICON_POSITION;
				data->AppIcon->do_Type = 0;
			}

			MOS_InitBroker(data);

			data->VideoDevice = device;

			/* Set the function pointers */
			device->VideoInit = MOS_VideoInit;
			device->VideoQuit = MOS_VideoQuit;
			device->GetDisplayModes = MOS_GetDisplayModes;
			device->GetDisplayBounds = MOS_GetDisplayBounds;
			device->SetDisplayMode = MOS_SetDisplayMode;
			device->SuspendScreenSaver = MOS_SuspendScreenSaver;
			device->PumpEvents = MOS_PumpEvents;
			device->CreateSDLWindow = MOS_CreateWindow;
			device->CreateSDLWindowFrom = MOS_CreateWindowFrom;
			device->SetWindowTitle = MOS_SetWindowTitle;
			device->SetWindowIcon = MOS_SetWindowIcon;
			device->SetWindowPosition = MOS_SetWindowPosition;
			device->SetWindowSize = MOS_SetWindowSize;
			device->SetWindowMinimumSize = MOS_SetWindowMinimumSize;
			device->SetWindowMaximumSize = MOS_SetWindowMaximumSize;
			device->ShowWindow = MOS_ShowWindow;
			device->HideWindow = MOS_HideWindow;
			device->RaiseWindow = MOS_RaiseWindow;
			device->MaximizeWindow = MOS_MaximizeWindow;
			device->MinimizeWindow = MOS_MinimizeWindow;
			device->RestoreWindow = MOS_RestoreWindow;
			device->SetWindowBordered = MOS_SetWindowBordered;
			device->SetWindowAlwaysOnTop = MOS_SetWindowAlwaysOnTop;
			device->SetWindowFullscreen = MOS_SetWindowFullscreen;
 			device->SetWindowGammaRamp = MOS_SetWindowGammaRamp;
			device->SetWindowMouseGrab = MOS_SetWindowGrab;
			device->DestroyWindow = MOS_DestroyWindow;
			device->CreateWindowFramebuffer = MOS_CreateWindowFramebuffer;
			device->UpdateWindowFramebuffer = MOS_UpdateWindowFramebuffer;
			device->DestroyWindowFramebuffer = MOS_DestroyWindowFramebuffer;
			device->GetWindowWMInfo = MOS_GetWindowWMInfo;
			device->shape_driver.CreateShaper = MOS_CreateShaper;
			device->shape_driver.SetWindowShape = MOS_SetWindowShape;
			device->shape_driver.ResizeWindowShape = MOS_ResizeWindowShape;
			device->GL_LoadLibrary = MOS_GL_LoadLibrary;
			device->GL_GetProcAddress = MOS_GL_GetProcAddress;
			device->GL_UnloadLibrary = MOS_GL_UnloadLibrary;
			device->GL_CreateContext = MOS_GL_CreateContext;
			device->GL_MakeCurrent = MOS_GL_MakeCurrent;
			device->GL_GetDrawableSize = MOS_GL_GetDrawableSize;
			device->GL_SetSwapInterval = MOS_GL_SetSwapInterval;
			device->GL_GetSwapInterval = MOS_GL_GetSwapInterval;
			device->GL_SwapWindow = MOS_GL_SwapWindow;
			device->GL_DeleteContext = MOS_GL_DeleteContext;
			device->SetClipboardText = MOS_SetClipboardText;
			device->GetClipboardText = MOS_GetClipboardText;
			device->HasClipboardText = MOS_HasClipboardText;
			device->SetWindowResizable = MOS_SetWindowResizable;
			device->GetWindowBordersSize = MOS_GetWindowBordersSize;
			device->SetWindowOpacity = MOS_SetWindowOpacity;
			device->FlashWindow = MOS_FlashWindow;
			//device->SetWindowHitTest = MOS_SetWindowHitTest;
			device->free = MOS_DeleteDevice;

			return device;
		}

		SDL_free(device);
	}

	SDL_OutOfMemory();
	return NULL;
}

VideoBootStrap MORPHOS_bootstrap = {
	"mos", "SDL MorphOS video driver",
	MOS_CreateDevice,
    MOS_ShowMessageBox
};
