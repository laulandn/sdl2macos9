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
#include <proto/application.h>
#include <proto/wb.h>
#include <proto/graphics.h>
#include <proto/layers.h>
#include <proto/intuition.h>
#include <proto/icon.h>
#include <proto/keymap.h>
#include <proto/dos.h>
#include <proto/textclip.h>

#include "SDL_video.h"
#include "SDL_hints.h"

#include "../SDL_sysvideo.h"
#include "../SDL_pixels_c.h"
#include "../../events/SDL_events_c.h"

#include "SDL_os4video.h"
#include "SDL_os4events.h"
#include "SDL_os4framebuffer.h"
#include "SDL_os4mouse.h"
#include "SDL_os4locale.h"
#include "SDL_os4opengl.h"
#include "SDL_os4opengles2.h"
#include "SDL_os4shape.h"
#include "SDL_os4messagebox.h"
#include "SDL_os4modes.h"
#include "SDL_os4keyboard.h"
#include "SDL_os4library.h"

#include "../../main/amigaos4/SDL_os4debug.h"

#define CATCOMP_NUMBERS
#include "../../../amiga-extra/locale_generated.h"

static int OS4_VideoInit(_THIS);
static void OS4_VideoQuit(_THIS);

SDL_bool (*OS4_ResizeGlContext)(_THIS, SDL_Window * window) = NULL;
void (*OS4_UpdateGlWindowPointer)(_THIS, SDL_Window * window) = NULL;

static SDL_bool
OS4_CheckInterfaces(_THIS)
{
    dprintf("Checking interfaces\n");

    if (IGraphics && ILayers && IIntuition && IIcon &&
        IWorkbench && IKeymap && ITextClip && IDOS && IApplication) {

        dprintf("All library interfaces OK\n");

        return SDL_TRUE;

    }

    dprintf("Library interface check failed\n");

    return SDL_FALSE;
}

static void
OS4_FindApplicationName(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    size_t size;
    const size_t maxPathLen = 255;
    char pathBuffer[maxPathLen];

    if (IDOS->GetCliProgramName(pathBuffer, maxPathLen - 1)) {
        dprintf("GetCliProgramName: '%s'\n", pathBuffer);
    } else {
        dprintf("Failed to get CLI program name, checking task node\n");

        struct Task* me = IExec->FindTask(NULL);
        SDL_snprintf(pathBuffer, maxPathLen, "%s", ((struct Node *)me)->ln_Name);
    }

    size = SDL_strlen(pathBuffer) + 1;

    data->appName = SDL_malloc(size);

    if (data->appName) {
        SDL_snprintf(data->appName, size, pathBuffer);
    }

    dprintf("Application name: '%s'\n", data->appName);
}

static void
OS4_SuspendScreenSaver(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    if (data->appId) {
        const BOOL state = (_this->suspend_screensaver == SDL_FALSE);
        const BOOL result = IApplication->SetApplicationAttrs(data->appId,
                                                              APPATTR_AllowsBlanker, state,
                                                              TAG_DONE);
        if (result) {
            dprintf("Blanker %s\n", state ? "enabled" : "disabled");
        } else {
            dprintf("Failed to configure blanker\n");
        }
    }
}

static void
OS4_RegisterApplication(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    const char* description = OS4_GetString(MSG_APP_APPLICATION);
    const char* hint = SDL_GetHint(SDL_HINT_APP_NAME);
    if (hint) {
        description = hint;
    }

    data->appId = IApplication->RegisterApplication(data->appName,
                                                    REGAPP_Description, description,
                                                    TAG_DONE);

    if (data->appId) {
        dprintf("Registered application '%s' with description '%s' and id %lu\n",
                data->appName,
                description,
                data->appId);
    } else {
        dprintf("Failed to register application\n");
    }
}

static void
OS4_UnregisterApplication(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    BOOL result = IApplication->UnregisterApplication(data->appId,
                                                      TAG_DONE);

    if (result) {
        dprintf("Unregistered application with id %lu\n", data->appId);
    } else {
        dprintf("Failed to unregister application\n");
    }
}

static SDL_bool
OS4_AllocSystemResources(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    dprintf("Called\n");

    if (!OS4_CheckInterfaces(_this)) {
        return SDL_FALSE;
    }

    OS4_InitLocale();
    OS4_FindApplicationName(_this);
    OS4_RegisterApplication(_this);

    if (!(data->userPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE))) {
        SDL_SetError("Couldn't allocate message port");
        return SDL_FALSE;
    }

    if (!(data->appMsgPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE))) {
        SDL_SetError("Couldn't allocate AppMsg port");
        return SDL_FALSE;
    }

    /* Create the pool we'll be using (Shared, might be used from threads) */
    if (!(data->pool = IExec->AllocSysObjectTags(ASOT_MEMPOOL,
        ASOPOOL_MFlags,    MEMF_SHARED,
        ASOPOOL_Threshold, 16384,
        ASOPOOL_Puddle,    16384,
        ASOPOOL_Protected, TRUE,
        TAG_DONE))) {

        SDL_SetError("Couldn't allocate pool");
        return SDL_FALSE;
    }

    /* inputPort, inputReq and and input.device are created for WarpMouse functionality. (In SDL1
    they were created in library constructor for an unknown reason) */
    if (!(data->inputPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE))) {

        SDL_SetError("Couldn't allocate input port");
        return SDL_FALSE;
    }

    if (!(data->inputReq = IExec->AllocSysObjectTags(ASOT_IOREQUEST,
                                             ASOIOR_Size,       sizeof(struct IOStdReq),
                                             ASOIOR_ReplyPort,  data->inputPort,
                                             TAG_DONE))) {

        SDL_SetError("Couldn't allocate input request");
        return SDL_FALSE;
    }

    if (IExec->OpenDevice("input.device", 0, (struct IORequest *)data->inputReq, 0))
    {
        SDL_SetError("Couldn't open input.device");
        return SDL_FALSE;
    }

    IInput = (struct InputIFace *)OS4_GetInterface((struct Library *)data->inputReq->io_Device);
    if (!IInput) {
        SDL_SetError("Failed to get IInput interface");
        return SDL_FALSE;
    }

    return SDL_TRUE;
}

static void
OS4_FreeSystemResources(_THIS)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    dprintf("Called\n");

    OS4_DropInterface((void *)&IInput);

    if (data->inputReq) {
        dprintf("Closing input.device\n");
        //IExec->AbortIO((struct IORequest *)data->inputReq);
        //IExec->WaitIO((struct IORequest *)data->inputReq);
        IExec->CloseDevice((struct IORequest *)data->inputReq);

        dprintf("Freeing IORequest\n");
        IExec->FreeSysObject(ASOT_IOREQUEST, (void *)data->inputReq);
    }

    if (data->inputPort) {
        dprintf("Freeing MsgPort\n");
        IExec->FreeSysObject(ASOT_PORT, (void *)data->inputPort);
    }

    if (data->pool) {
        dprintf("Freeing memory pool\n");
        IExec->FreeSysObject(ASOT_MEMPOOL, data->pool);
    }

    if (data->appMsgPort) {
        struct Message *msg;

        dprintf("Replying app messages\n");

        while ((msg = IExec->GetMsg(data->appMsgPort))) {
            IExec->ReplyMsg((struct Message *) msg);
        }

        dprintf("Freeing app message port\n");

        IExec->FreeSysObject(ASOT_PORT, data->appMsgPort);
    }

    if (data->userPort) {
        dprintf("Freeing user port\n");
        IExec->FreeSysObject(ASOT_PORT, data->userPort);
    }

    if (data->appName) {
        SDL_free(data->appName);
    }

    if (data->appId) {
        OS4_UnregisterApplication(_this);
    }

    OS4_QuitLocale();
}

static void
OS4_DeleteDevice(SDL_VideoDevice * device)
{
    dprintf("Called\n");

    OS4_FreeSystemResources(device);

    SDL_free(device->driverdata);
    SDL_free(device);
}

static void
OS4_SetMiniGLFunctions(SDL_VideoDevice * device)
{
    device->GL_GetProcAddress = OS4_GL_GetProcAddress;
    device->GL_UnloadLibrary = OS4_GL_UnloadLibrary;
    device->GL_MakeCurrent = OS4_GL_MakeCurrent;
    device->GL_GetDrawableSize = OS4_GL_GetDrawableSize;
    device->GL_SetSwapInterval = OS4_GL_SetSwapInterval;
    device->GL_GetSwapInterval = OS4_GL_GetSwapInterval;
    device->GL_SwapWindow = OS4_GL_SwapWindow;
    device->GL_CreateContext = OS4_GL_CreateContext;
    device->GL_DeleteContext = OS4_GL_DeleteContext;
    //device->GL_DefaultProfileConfig = OS4_GL_DefaultProfileConfig;

    OS4_ResizeGlContext = OS4_GL_ResizeContext;
    OS4_UpdateGlWindowPointer = OS4_GL_UpdateWindowPointer;
}

#if SDL_VIDEO_OPENGL_ES2
static void
OS4_SetGLESFunctions(SDL_VideoDevice * device)
{
    /* Some functions are recycled from SDL_os4opengl.c 100% ... */
    device->GL_GetProcAddress = OS4_GLES_GetProcAddress;
    device->GL_UnloadLibrary = OS4_GLES_UnloadLibrary;
    device->GL_MakeCurrent = OS4_GLES_MakeCurrent;
    device->GL_GetDrawableSize = OS4_GL_GetDrawableSize;
    device->GL_SetSwapInterval = OS4_GL_SetSwapInterval;
    device->GL_GetSwapInterval = OS4_GL_GetSwapInterval;
    device->GL_SwapWindow = OS4_GLES_SwapWindow;
    device->GL_CreateContext = OS4_GLES_CreateContext;
    device->GL_DeleteContext = OS4_GLES_DeleteContext;
    //device->GL_DefaultProfileConfig = OS4_GL(ES)_DefaultProfileConfig;

    OS4_ResizeGlContext = OS4_GLES_ResizeContext;
    OS4_UpdateGlWindowPointer = OS4_GLES_UpdateWindowPointer;
}
#endif

static SDL_bool
OS4_IsMiniGL(_THIS)
{
    if ((_this->gl_config.profile_mask == 0) &&
        (_this->gl_config.major_version == 1) &&
        (_this->gl_config.minor_version == 3)) {
            dprintf("OpenGL 1.3 requested\n");
            return SDL_TRUE;
    }

    return SDL_FALSE;
}

#if SDL_VIDEO_OPENGL_ES2
static SDL_bool
OS4_IsOpenGLES2(_THIS)
{
    if ((_this->gl_config.profile_mask == SDL_GL_CONTEXT_PROFILE_ES) &&
        (_this->gl_config.major_version == 2) &&
        (_this->gl_config.minor_version == 0)) {
            dprintf("OpenGL ES 2.0 requested\n");
            return SDL_TRUE;
    }

    return SDL_FALSE;
}
#endif

static int
OS4_LoadGlLibrary(_THIS, const char * path)
{
    dprintf("Profile_mask %d, major ver %d, minor ver %d\n",
        _this->gl_config.profile_mask,
        _this->gl_config.major_version,
        _this->gl_config.minor_version);

    if (OS4_IsMiniGL(_this)) {
        OS4_SetMiniGLFunctions(_this);
        return OS4_GL_LoadLibrary(_this, path);
    }

#if SDL_VIDEO_OPENGL_ES2
    if (OS4_IsOpenGLES2(_this)) {
        OS4_SetGLESFunctions(_this);
        return OS4_GLES_LoadLibrary(_this, path);
    }
#endif

    dprintf("Invalid OpenGL version\n");
    SDL_SetError("Invalid OpenGL version");
    return -1;
}

static void
OS4_SetFunctionPointers(SDL_VideoDevice * device)
{
    device->VideoInit = OS4_VideoInit;
    device->VideoQuit = OS4_VideoQuit;
    //device->ResetTouch = OS4_ResetTouch;

    device->GetDisplayBounds = OS4_GetDisplayBounds;
    //device->GetDisplayUsableBounds = OS4_GetDisplayUsableBounds;
    //device->GetDisplayDPI = OS4_GetDisplayDPI;

    device->GetDisplayModes = OS4_GetDisplayModes;
    device->SetDisplayMode = OS4_SetDisplayMode;

    device->CreateSDLWindow = OS4_CreateWindow;
    device->CreateSDLWindowFrom = OS4_CreateWindowFrom;
    device->SetWindowTitle = OS4_SetWindowTitle;
    //device->SetWindowIcon = OS4_SetWindowIcon;
    device->SetWindowPosition = OS4_SetWindowPosition;
    device->SetWindowSize = OS4_SetWindowSize;

    device->SetWindowMinimumSize = OS4_SetWindowMinMaxSize;
    device->SetWindowMaximumSize = OS4_SetWindowMinMaxSize;
    device->GetWindowBordersSize = OS4_GetWindowBordersSize;

    device->SetWindowOpacity = OS4_SetWindowOpacity;
    // device->SetWindowModalFor = OS4_SetWindowModalFor;
    // device->SetWindowInputFocus = OS4_SetWindowInputFocus;

    device->ShowWindow = OS4_ShowWindow;
    device->HideWindow = OS4_HideWindow;
    device->RaiseWindow = OS4_RaiseWindow;

    device->MaximizeWindow = OS4_MaximizeWindow;
    device->MinimizeWindow = OS4_MinimizeWindow;
    device->RestoreWindow = OS4_RestoreWindow;

    device->SetWindowBordered = OS4_SetWindowBordered;
    device->SetWindowResizable = OS4_SetWindowResizable;
    device->SetWindowAlwaysOnTop = OS4_SetWindowAlwaysOnTop;

    device->SetWindowFullscreen = OS4_SetWindowFullscreen;
    //device->SetWindowGammaRamp = OS4_SetWindowGammaRamp;
    //device->GetWindowGammaRamp = OS4_GetWindowGammaRamp;

    device->SetWindowMouseGrab = OS4_SetWindowMouseGrab;
    // device->SetWindowKeyboardGrab = OS4_SetWindowKeyboardGrab;

    device->DestroyWindow = OS4_DestroyWindow;

    device->CreateWindowFramebuffer = OS4_CreateWindowFramebuffer;
    device->UpdateWindowFramebuffer = OS4_UpdateWindowFramebuffer;
    device->DestroyWindowFramebuffer = OS4_DestroyWindowFramebuffer;

    //device->OnWindowEnter = OS4_OnWindowEnter;
    device->FlashWindow = OS4_FlashWindow;

    device->shape_driver.CreateShaper = OS4_CreateShaper;
    device->shape_driver.SetWindowShape = OS4_SetWindowShape;
    device->shape_driver.ResizeWindowShape = OS4_ResizeWindowShape;

    device->GetWindowWMInfo = OS4_GetWindowWMInfo;

    device->GL_LoadLibrary = OS4_LoadGlLibrary;
    OS4_SetMiniGLFunctions(device);

    device->PumpEvents = OS4_PumpEvents;
    device->SuspendScreenSaver = OS4_SuspendScreenSaver;

    //device->StartTextInput = OS4_StartTextInput;
    //device->StopTextInput = OS4_StopTextInput;
    //device->SetTextInputRect = OS4_SetTextInputRect;

    //device->SetTextInputRect = OS4_SetTextInputRect;
    //device->ShowScreenKeyboard = OS4_ShowScreenKeyboard;
    //device->HideScreenKeyboard = OS4_HideScreenKeyboard;
    //device->IsScreenKeyboardShown = OS4_IsScreenKeyboardShown;

    device->SetClipboardText = OS4_SetClipboardText;
    device->GetClipboardText = OS4_GetClipboardText;
    device->HasClipboardText = OS4_HasClipboardText;
    //device->ShowMessageBox = OS4_ShowMessageBox; Can be called without video initialization

    device->SetWindowHitTest = OS4_SetWindowHitTest;
    //device->AcceptDragAndDrop = OS4_AcceptDragAndDrop;

    device->free = OS4_DeleteDevice;
}

static SDL_VideoDevice *
OS4_CreateDevice(void)
{
    SDL_VideoDevice *device;
    SDL_VideoData *data;

    /* Initialize all variables that we clean on shutdown */
    device = (SDL_VideoDevice *) SDL_calloc(1, sizeof(SDL_VideoDevice));

    if (device) {
        data = (SDL_VideoData *) SDL_calloc(1, sizeof(SDL_VideoData));
    } else {
        data = NULL;
    }

    if (!data) {
        SDL_free(device);
        SDL_OutOfMemory();
        return NULL;
    }

    device->driverdata = data;

    if (!OS4_AllocSystemResources(device)) {
        /* If we return with NULL, SDL_VideoQuit() can't clean up OS4 stuff. So let's do it now. */
        OS4_FreeSystemResources(device);

        SDL_free(device);
        SDL_free(data);

        SDL_Unsupported();

        return NULL;
    }

    OS4_SetFunctionPointers(device);

    return device;
}

VideoBootStrap OS4_bootstrap = {
    "os4", "SDL AmigaOS 4 video driver",
    OS4_CreateDevice,
    OS4_ShowMessageBox
};

int
OS4_VideoInit(_THIS)
{
    dprintf("Called\n");

    if (OS4_InitModes(_this) < 0) {
        return SDL_SetError("Failed to initialize modes");
    }

    OS4_InitKeyboard(_this);
    OS4_InitMouse(_this);

    dprintf("Disable SDL_VIDEO_MINIMIZE_ON_FOCUS_LOSS\n");

    // We don't want SDL to change  window setup in SDL_OnWindowFocusLost()
    SDL_SetHint(SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS, "0");

    dprintf("Disable SDL_POLL_SENTINEL\n");

    // Poll sentinels added after SDL 2.0.14 cause increasing CPU load (TODO: fix)
    SDL_SetHint(SDL_HINT_POLL_SENTINEL, "0");

    if (SDL_GetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION)) {
        dprintf("User overrides SDL_FRAMEBUFFER_ACCELERATION");
    } else {
        dprintf("Disable SDL_FRAMEBUFFER_ACCELERATION\n");

        // Avoid creation of accelerated ("compositing") surfaces when using "software" driver.
        // Compositing requires PatchCompositeTags on WinUAE, for example.
        // TODO: consider reading the hint before disabling, in case user wants to force it?
        SDL_SetHint(SDL_HINT_FRAMEBUFFER_ACCELERATION, "0");
    }

    return 0;
}

void
OS4_VideoQuit(_THIS)
{
    dprintf("Called\n");

    OS4_QuitMouse(_this);
    OS4_QuitKeyboard(_this);
    OS4_QuitModes(_this);
}

void *
OS4_SaveAllocPooled(_THIS, uint32 size)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    return IExec->AllocPooled(data->pool, size);
}

void *
OS4_SaveAllocVecPooled(_THIS, uint32 size)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    return IExec->AllocVecPooled(data->pool, size);
}

void
OS4_SaveFreePooled(_THIS, void * mem, uint32 size)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    IExec->FreePooled(data->pool, mem, size);
}

void
OS4_SaveFreeVecPooled(_THIS, void * mem)
{
    SDL_VideoData *data = (SDL_VideoData *) _this->driverdata;

    IExec->FreeVecPooled(data->pool, mem);
}

/* Native window apps may be interested in calling this */
struct MsgPort *
OS4_GetSharedMessagePort()
{
    SDL_VideoDevice *vd = SDL_GetVideoDevice();

    if (vd) {
        SDL_VideoData *data = (SDL_VideoData *) vd->driverdata;
        if (data) {
            return data->userPort;
        }
    }

    return NULL;
}

#endif /* SDL_VIDEO_DRIVER_AMIGAOS4 */

/* vi: set ts=4 sw=4 expandtab: */
