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

#include "SDL_os4library.h"
#include "SDL_version.h"

#include "../../main/amigaos4/SDL_os4debug.h"
#include "../../thread/amigaos4/SDL_systhread_c.h"

#include <proto/exec.h>

// These symbols are required when libSDL2.so is loaded manually using elf.library (RebelSDL).
struct ExecIFace* IExec;
struct Interface* INewlib;
struct DOSIFace* IDOS;
struct ElfIFace* IElf;
struct ApplicationIFace* IApplication;
struct TextClipIFace* ITextClip;
struct GraphicsIFace* IGraphics;
struct LayersIFace* ILayers;
struct IntuitionIFace* IIntuition;
struct IconIFace* IIcon;
struct WorkbenchIFace* IWorkbench;
struct KeymapIFace* IKeymap;
struct DiskfontIFace* IDiskfont;
struct LocaleIFace* ILocale;

static struct Library* NewlibBase;
static struct Library* DOSBase;
static struct Library* ElfBase;
static struct Library* ApplicationBase;
static struct Library* TextClipBase;
static struct Library* GfxBase;
static struct Library* LayersBase;
static struct Library* IntuitionBase;
static struct Library* IconBase;
static struct Library* WorkbenchBase;
static struct Library* KeymapBase;
static struct Library* DiskfontBase;
static struct Library* LocaleBase;

static BOOL newlibOpened = FALSE;
static BOOL dosOpened = FALSE;
static BOOL elfOpened = FALSE;
static BOOL applicationOpened = FALSE;
static BOOL textClipOpened = FALSE;
static BOOL graphicsOpened = FALSE;
static BOOL layersOpened = FALSE;
static BOOL intuitionOpened = FALSE;
static BOOL iconOpened = FALSE;
static BOOL workbenchOpened = FALSE;
static BOOL keymapOpened = FALSE;
static BOOL diskfontOpened = FALSE;
static BOOL localeOpened = FALSE;

static int initCount = 0;

static void
OS4_LogVersion(void)
{
    SDL_version version;

    SDL_GetVersion(&version);

    dprintf("*** SDL %d.%d.%d ***\n", version.major, version.minor, version.patch);

#ifdef __AMIGADATE__
    dprintf("Build date: " __AMIGADATE__ "\n");
#endif
}

void OS4_INIT(void)
{
    // IExec is required for dprintf!
    if (IExec) {
        dprintf("IExec %p\n", IExec);
    } else {
        IExec = ((struct ExecIFace *)((*(struct ExecBase **)4)->MainInterface));
        dprintf("IExec %p initialized\n", IExec);
    }

    if (initCount > 0) {
        dprintf("initCount %d - skip re-initialization\n", initCount);
        return;
    }

    if (IDOS) {
        dprintf("IDOS %p\n", IDOS);
    } else {
        DOSBase = OS4_OpenLibrary("dos.library", 53);

        if (DOSBase) {
            IDOS = (struct DOSIFace *)OS4_GetInterface(DOSBase);
            dprintf("IDOS %p initialized\n", IDOS);
            dosOpened = IDOS != NULL;
        }
    }

    if (INewlib) {
        dprintf("INewlib %p\n", INewlib);
    } else {
        NewlibBase = OS4_OpenLibrary("newlib.library", 53);

        if (NewlibBase) {
            INewlib = OS4_GetInterface(NewlibBase);
            dprintf("INewlib %p initialized\n", INewlib);
            newlibOpened = INewlib != NULL;
        }
    }

    if (IElf) {
        dprintf("IElf %p\n", IElf);
    } else {
        ElfBase = OS4_OpenLibrary("elf.library", 53);

        if (ElfBase) {
            IElf = (struct ElfIFace *)OS4_GetInterface(ElfBase);
            dprintf("IElf %p initialized\n", IElf);
            elfOpened = IElf != NULL;
        }
    }

    if (IApplication) {
        dprintf("IApplication %p\n", IApplication);
    } else {
        ApplicationBase = OS4_OpenLibrary("application.library", 53);

        if (ApplicationBase) {
            // Needs special interface
            IApplication = (struct ApplicationIFace *)IExec->GetInterface(ApplicationBase, "application", 2, NULL);

            dprintf("IApplication %p initialized\n", IApplication);
            applicationOpened = IApplication != NULL;
        }
    }

    if (ITextClip) {
        dprintf("ITextClip %p\n", ITextClip);
    } else {
        TextClipBase = OS4_OpenLibrary("textclip.library", 53);

        if (TextClipBase) {
            ITextClip = (struct TextClipIFace *)OS4_GetInterface(TextClipBase);
            dprintf("ITextClip %p  initialized\n", ITextClip);
            textClipOpened = ITextClip != NULL;
        }
    }

    if (IGraphics) {
        dprintf("IGraphics %p\n", IGraphics);
    } else {
        GfxBase = OS4_OpenLibrary("graphics.library", 54);

        if (GfxBase) {
            IGraphics = (struct GraphicsIFace *)OS4_GetInterface(GfxBase);
            dprintf("IGraphics %p initialized\n", IGraphics);
            graphicsOpened = IGraphics != NULL;
        }
    }

    if (ILayers) {
        dprintf("ILayers %p\n", ILayers);
    } else {
        LayersBase = OS4_OpenLibrary("layers.library", 53);

        if (LayersBase) {
            ILayers = (struct LayersIFace *)OS4_GetInterface(LayersBase);
            dprintf("ILayers %p initialized\n", ILayers);
            layersOpened = ILayers != NULL;
        }
    }

    if (IIntuition) {
        dprintf("IIntuition %p\n", IIntuition);
    } else {
        IntuitionBase = OS4_OpenLibrary("intuition.library", 53);

        if (IntuitionBase) {
            IIntuition = (struct IntuitionIFace *)OS4_GetInterface(IntuitionBase);
            dprintf("IIntuition %p initialized\n", IIntuition);
            intuitionOpened = IIntuition != NULL;
        }
    }

    if (IIcon) {
        dprintf("IIcon %p\n", IIcon);
    } else {
        IconBase = OS4_OpenLibrary("icon.library", 53);

        if (IconBase) {
            IIcon = (struct IconIFace *)OS4_GetInterface(IconBase);
            dprintf("IIcon %p initialized\n", IIcon);
            iconOpened = IIcon != NULL;
        }
    }

    if (IWorkbench) {
        dprintf("IWorkbench %p\n", IWorkbench);
    } else {
        WorkbenchBase = OS4_OpenLibrary("workbench.library", 53);

        if (WorkbenchBase) {
            IWorkbench = (struct WorkbenchIFace *)OS4_GetInterface(WorkbenchBase);
            dprintf("IWorkbench %p initialized\n", IWorkbench);
            workbenchOpened = IWorkbench != NULL;
        }
    }

    if (IKeymap) {
        dprintf("IKeymap %p\n", IKeymap);
    } else {
        KeymapBase = OS4_OpenLibrary("keymap.library", 53);

        if (KeymapBase) {
            IKeymap = (struct KeymapIFace *)OS4_GetInterface(KeymapBase);
            dprintf("Ikeymap %p initialized\n", IKeymap);
            keymapOpened = IKeymap != NULL;
        }
    }

    if (IDiskfont) {
        dprintf("IDiskfont %p\n", IDiskfont);
    } else {
        DiskfontBase = OS4_OpenLibrary("diskfont.library", 53);

        if (DiskfontBase) {
            IDiskfont = (struct DiskfontIFace *)OS4_GetInterface(DiskfontBase);
            dprintf("IDiskfont %p initialized\n", IDiskfont);
            diskfontOpened = IDiskfont != NULL;
        }
    }

    if (ILocale) {
        dprintf("ILocale %p\n", ILocale);
    } else {
        LocaleBase = OS4_OpenLibrary("locale.library", 53);

        if (LocaleBase) {
            ILocale = (struct LocaleIFace *)OS4_GetInterface(LocaleBase);
            dprintf("ILocale %p initialized\n", ILocale);
            localeOpened = ILocale != NULL;
        }
    }

    OS4_LogVersion();
    OS4_InitThreadSubSystem();

    initCount++;

    dprintf("initCount %d\n", initCount);
}

void OS4_QUIT(void)
{
    if (initCount < 1) {
        dprintf("initCount %d - skip quitting\n", initCount);
        return;
    }

    OS4_QuitThreadSubSystem();

    if (localeOpened) {
        OS4_DropInterface((struct Interface**)&ILocale);
    }

    if (diskfontOpened) {
        OS4_DropInterface((struct Interface**)&IDiskfont);
    }

    if (keymapOpened) {
        OS4_DropInterface((struct Interface**)&IKeymap);
    }

    if (workbenchOpened) {
        OS4_DropInterface((struct Interface**)&IWorkbench);
    }

    if (iconOpened) {
        OS4_DropInterface((struct Interface**)&IIcon);
    }

    if (intuitionOpened) {
        OS4_DropInterface((struct Interface**)&IIntuition);
    }

    if (layersOpened) {
        OS4_DropInterface((struct Interface**)&ILayers);
    }

    if (graphicsOpened) {
        OS4_DropInterface((struct Interface**)&IGraphics);
    }

    if (textClipOpened) {
        OS4_DropInterface((struct Interface**)&ITextClip);
    }

    if (applicationOpened) {
        OS4_DropInterface((struct Interface**)&IApplication);
    }

    if (elfOpened) {
        OS4_DropInterface((struct Interface**)&IElf);
    }

    if (newlibOpened) {
        OS4_DropInterface(&INewlib);
    }

    if (dosOpened) {
        OS4_DropInterface((struct Interface**)&IDOS);
    }

    OS4_CloseLibrary(&LocaleBase);
    OS4_CloseLibrary(&DiskfontBase);
    OS4_CloseLibrary(&KeymapBase);
    OS4_CloseLibrary(&WorkbenchBase);
    OS4_CloseLibrary(&IconBase);
    OS4_CloseLibrary(&IntuitionBase);
    OS4_CloseLibrary(&LayersBase);
    OS4_CloseLibrary(&GfxBase);
    OS4_CloseLibrary(&TextClipBase);
    OS4_CloseLibrary(&ApplicationBase);
    OS4_CloseLibrary(&ElfBase);
    OS4_CloseLibrary(&NewlibBase);
    OS4_CloseLibrary(&DOSBase);

    initCount--;

    dprintf("initCount %d\n", initCount);
}

struct Library *
OS4_OpenLibrary(STRPTR name, ULONG version)
{
    struct Library* lib = IExec->OpenLibrary(name, version);

    dprintf("Opening '%s' version %lu %s (address %p)\n",
        name, version, lib ? "succeeded" : "FAILED", lib);

    return lib;
}

struct Interface *
OS4_GetInterface(struct Library * lib)
{
    struct Interface* interface = IExec->GetInterface(lib, "main", 1, NULL);

    dprintf("Getting interface for libbase %p %s (address %p)\n",
        lib, interface ? "succeeded" : "FAILED", interface);

    return interface;
}

void
OS4_DropInterface(struct Interface ** interface)
{
    if (interface && *interface) {
        dprintf("Dropping interface %p\n", *interface);
        IExec->DropInterface(*interface);
        *interface = NULL;
    }
}

void
OS4_CloseLibrary(struct Library ** library)
{
    if (library && *library) {
        dprintf("Closing library %p\n", *library);
        IExec->CloseLibrary(*library);
        *library = NULL;
    }
}

#endif
