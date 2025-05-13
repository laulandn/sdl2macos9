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

#if defined(SDL_JOYSTICK_AMIGAINPUT)

#include "SDL_joystick.h"
#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"
#include "../../video/amigaos4/SDL_os4library.h"

#include "SDL_events.h"

#include <amigainput/amigainput.h>
#include <proto/amigainput.h>

#include "../../main/amigaos4/SDL_os4debug.h"

#define MAX_JOYSTICKS 32
#define MAX_AXES 8
#define MAX_BUTTONS 16
#define MAX_HATS 8

#define BUFFER_OFFSET(buffer, offset) (((int32 *)buffer)[offset])

/* Per-joystick data private to driver */
struct joystick_hwdata
{
    AIN_DeviceHandle   *handle;

    uint32              axisBufferOffset[MAX_AXES];
    int32               axisData[MAX_AXES];
    TEXT                axisName[MAX_AXES][32];

    uint32              buttonBufferOffset[MAX_BUTTONS];
    int32               buttonData[MAX_BUTTONS];

    uint32              hatBufferOffset[MAX_HATS];
    int32               hatData[MAX_HATS];
};

struct JoystickInfo
{
    AIN_DeviceID id;
    const char *name;
};

struct JoystickData
{
    APTR context;
    uint32 count;
    struct JoystickInfo ids[MAX_JOYSTICKS];
};

// TODO: get rid of static data
static struct JoystickData joystickData;

static struct Library   *SDL_AIN_Base;
static struct AIN_IFace *SDL_IAIN;

/*
 * Convert AmigaInput hat data to SDL hat data.
 */
static Uint8
AMIGAINPUT_MapHatData(const int hat_data)
{
    switch (hat_data) {
        case 1:  return SDL_HAT_UP;
        case 2:  return SDL_HAT_UP | SDL_HAT_RIGHT;
        case 3:  return SDL_HAT_RIGHT;
        case 4:  return SDL_HAT_DOWN | SDL_HAT_RIGHT;
        case 5:  return SDL_HAT_DOWN;
        case 6:  return SDL_HAT_DOWN | SDL_HAT_LEFT;
        case 7:  return SDL_HAT_LEFT;
        case 8:  return SDL_HAT_UP | SDL_HAT_LEFT;
        default: return SDL_HAT_CENTERED;
    }
}

/*
 * Callback to enumerate joysticks
 */
static BOOL
AMIGAINPUT_EnumerateJoysticks(AIN_Device *device, void *UserData)
{
    if (joystickData.count < MAX_JOYSTICKS) {
        dprintf("id=%lu, type=%ld, axes=%ld, buttons=%ld\n",
            joystickData.count,
            (int32)device->Type,
            (int32)device->NumAxes,
            (int32)device->NumButtons);

        if (device->Type == AINDT_JOYSTICK) {
            /* AmigaInput can report devices even when there's no
             * physical stick present. We take some steps to try and
             * ignore such bogus devices.
             *
             * First, check whether we have a useful number of axes and buttons
             */
            if ((device->NumAxes > 0) && (device->NumButtons > 0)) {
                /* Then, check whether we can actually obtain the device */
                AIN_DeviceHandle *handle = SDL_IAIN->AIN_ObtainDevice(joystickData.context, device->DeviceID);

                if (handle) {
                    /* Okay. This appears to be a valid device. We'll report it to SDL. */
                    struct JoystickInfo* joy = &joystickData.ids[joystickData.count];
                    joy->id   = device->DeviceID;
                    joy->name = SDL_strdup(device->DeviceName);

                    dprintf("Found joystick #%lu (AI ID=%lu) '%s'\n", joystickData.count, joy->id, joy->name);

                    joystickData.count++;

                    SDL_IAIN->AIN_ReleaseDevice(joystickData.context, handle);

                    return TRUE;
                } else {
                    dprintf("Failed to obtain joystick '%s' (AI ID=%lu) - ignoring\n", device->DeviceName, device->DeviceID);
                }
            } else {
                dprintf("Joystick '%s' (AI ID=%lu) has no axes/buttons - ignoring\n", device->DeviceName, device->DeviceID);
            }
        }
    }
    return FALSE;
}

static BOOL
AMIGAINPUT_OpenLibrary(void)
{
    dprintf("Called\n");

    SDL_AIN_Base = OS4_OpenLibrary("AmigaInput.library", 51);

    if (SDL_AIN_Base) {
        SDL_IAIN = (struct AIN_IFace *)OS4_GetInterface(SDL_AIN_Base);

        if (!SDL_IAIN) {
            OS4_CloseLibrary(&SDL_AIN_Base);
        }
    } else {
        dprintf("Failed to open AmigaInput.library\n");
    }

    return SDL_AIN_Base != NULL;
}

static void
AMIGAINPUT_CloseLibrary(void)
{
    dprintf("Called\n");

    OS4_DropInterface((void *)&SDL_IAIN);
    OS4_CloseLibrary(&SDL_AIN_Base);
}

/* Function to scan the system for joysticks.
 * It should return 0, or -1 on an unrecoverable fatal error.
 */
static int
AMIGAINPUT_Init(void)
{
    if (AMIGAINPUT_OpenLibrary()) {
        joystickData.context = SDL_IAIN->AIN_CreateContext(1, NULL);

        if (joystickData.context) {
            const BOOL result = SDL_IAIN->AIN_EnumDevices(joystickData.context, AMIGAINPUT_EnumerateJoysticks, NULL);

            dprintf("EnumDevices returned %d\n", result);
            dprintf("Found %lu joysticks\n", joystickData.count);

            if (result) {
                /*

                NOTE: AI doesn't seem to handle hotplugged/removed joysticks very well.
                Report only devices detected at startup to SDL.

                */
                for (uint32 i = 0; i < joystickData.count; i++) {
                    dprintf("Add joystick %lu\n", i);
                    SDL_PrivateJoystickAdded(i);
                }
            }

            return 0;
        } else {
            dprintf("Failed to create AmigaInput context\n");
        }
    }

    return -1;
}

static int
AMIGAINPUT_GetCount(void)
{
    return joystickData.count;
}

static void
AMIGAINPUT_Detect(void)
{
    //dprintf("Called\n");
}

/* Function to get the device-dependent name of a joystick */
static const char *
AMIGAINPUT_GetDeviceName(int device_index)
{
    return joystickData.ids[device_index].name;
}

static const char*
AMIGAINPUT_GetDevicePath(int device_index)
{
    return NULL;
}

static int
AMIGAINPUT_GetDeviceSteamVirtualGamepadSlot(int device_index)
{
    return 0;
}

static int
AMIGAINPUT_GetDevicePlayerIndex(int device_index)
{
    return device_index;
}

static void
AMIGAINPUT_SetDevicePlayerIndex(int device_index, int player_index)
{
    dprintf("Not implemented\n");
}

static SDL_JoystickID
AMIGAINPUT_GetDeviceInstanceID(int device_index)
{
    //dprintf("device_index %d\n", device_index);
    return device_index;
}

static void
AMIGAINPUT_SwapAxis(struct joystick_hwdata * hwdata, int a, int b)
{
    // Back up the original position axis data
    TEXT tmpstr[32];
    const uint32 tmpoffset = hwdata->axisBufferOffset[a];
    strlcpy(tmpstr, hwdata->axisName[a], sizeof(tmpstr));

    // Move this one to original
    hwdata->axisBufferOffset[a] = hwdata->axisBufferOffset[b];
    strlcpy(hwdata->axisName[a], hwdata->axisName[b], 32);

    // Put the old original here
    hwdata->axisBufferOffset[b] = tmpoffset;
    strlcpy(hwdata->axisName[b], tmpstr, 32);
}

/* Function to open a joystick for use.
   The joystick to open is specified by the index field of the joystick.
   This should fill the nbuttons and naxes fields of the joystick structure.
   It returns 0, or -1 if there is an error.
 */
static int
AMIGAINPUT_Open(SDL_Joystick * joystick, int device_index)
{
    const AIN_DeviceID id = joystickData.ids[joystick->instance_id].id;
    AIN_DeviceHandle *handle = SDL_IAIN->AIN_ObtainDevice(joystickData.context, id);

    dprintf("Opening joystick #%d (AI ID=%lu)\n", joystick->instance_id, id);

    if (handle) {
        joystick->hwdata = SDL_calloc(1, sizeof(struct joystick_hwdata));

        if (joystick->hwdata) {
            struct joystick_hwdata *hwdata = joystick->hwdata;
            uint32 num_axes = 0;
            uint32 num_buttons = 0;
            uint32 num_hats = 0;

            BOOL result = TRUE;

            hwdata->handle  = handle;
            joystick->name  = (char *)joystickData.ids[joystick->instance_id].name;

            /* Query number of axes, buttons and hats the device has */
            result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_NUMAXES,    0, &num_axes, 4);
            result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_NUMBUTTONS, 0, &num_buttons, 4);
            result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_NUMHATS,    0, &num_hats, 4);

            // dprintf ("Found %d axes, %d buttons, %d hats\n", num_axes, num_buttons, num_hats);

            joystick->naxes    = num_axes < MAX_AXES       ? num_axes    : MAX_AXES;
            joystick->nbuttons = num_buttons < MAX_BUTTONS ? num_buttons : MAX_BUTTONS;
            joystick->nhats    = num_hats < MAX_HATS       ? num_hats    : MAX_HATS;

            // Ensure all axis names are null terminated
            for (int i = 0; i < MAX_AXES; i++) {
                hwdata->axisName[i][0] = 0;
            }

            /* Query offsets in ReadDevice buffer for axes' data */
            for (int i = 0; i < joystick->naxes; i++) {
                result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_AXIS_OFFSET, i, &(hwdata->axisBufferOffset[i]), 4);
                result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_AXISNAME,    i, &(hwdata->axisName[i][0]), 32 );
            }

            // Sort the axes so that X and Y come first
            for (int i = 0; i < joystick->naxes; i++) {
                if ((strcasecmp(&hwdata->axisName[i][0], "X-Axis") == 0) && (i != 0)) {
                    dprintf("Swap X-axis\n");
                    AMIGAINPUT_SwapAxis(hwdata, 0, i);
                    continue;
                }

                if ((strcasecmp(&hwdata->axisName[i][0], "Y-Axis") == 0) && (i != 1)) {
                    dprintf("Swap Y-axis\n");
                    AMIGAINPUT_SwapAxis(hwdata, 1, i);
                    continue;
                }
            }

            /* Query offsets in ReadDevice buffer for buttons' data */
            for (int i = 0; i < joystick->nbuttons; i++) {
                result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_BUTTON_OFFSET, i, &(hwdata->buttonBufferOffset[i]), 4);
            }

            /* Query offsets in ReadDevice buffer for hats' data */
            for (int i = 0; i < joystick->nhats; i++) {
                result = result && SDL_IAIN->AIN_Query(joystickData.context, id, AINQ_HAT_OFFSET, i, &(hwdata->hatBufferOffset[i]), 4);
            }

            if (result) {
                dprintf("Successful\n");
                return 0;
            }
        }

        SDL_IAIN->AIN_ReleaseDevice(joystickData.context, handle);
    }

    SDL_SetError("Failed to open device\n");
    dprintf("Failed\n");

    return -1;
}

/* Function to update the state of a joystick - called as a device poll.
 * This function shouldn't update the joystick structure directly,
 * but instead should call SDL_PrivateJoystick*() to deliver events
 * and update joystick device state.
 */
static void
AMIGAINPUT_Update(SDL_Joystick * joystick)
{
    struct joystick_hwdata *hwdata = joystick->hwdata;
    void                   *buffer;

    //dprintf("Called joystick %p, hwdata %p\n", joystick, hwdata);

    /*
     * Poll device for data
     */
    if (hwdata && SDL_IAIN->AIN_ReadDevice(joystickData.context, hwdata->handle, &buffer)) {
        /* Extract axis data from buffer and notify SDL of any changes
         * in axis state
         */
        for (int i = 0; i < joystick->naxes; i++) {
            int axisdata = BUFFER_OFFSET(buffer, hwdata->axisBufferOffset[i]);

            /* Clamp axis data to 16-bits to work around possible AI driver bugs */
            if (axisdata > 32767) {
                axisdata = 32767;
            }

            if (axisdata < -32768) {
                axisdata = -32768;
            }

            if (axisdata != hwdata->axisData[i]) {
                SDL_PrivateJoystickAxis(joystick, i, (Sint16)axisdata);
                hwdata->axisData[i] = axisdata;
                //dprintf("Send axis %d\n", i);
            }
        }

        /* Extract button data from buffer and notify SDL of any changes
         * in button state
         *
         * Note: SDL doesn't support analog buttons.
         */
        for (int i = 0; i < joystick->nbuttons; i++) {
            const int buttondata = BUFFER_OFFSET(buffer, hwdata->buttonBufferOffset[i]);

            if (buttondata != hwdata->buttonData[i]) {
                SDL_PrivateJoystickButton(joystick, i, buttondata ? SDL_PRESSED : SDL_RELEASED);
                hwdata->buttonData[i] = buttondata;
                //dprintf("Send button %d\n", i);
            }
        }

        /* Extract hat data from buffer and notify SDL of any changes
         * in hat state
         */
        for (int i = 0; i < joystick->nhats; i++) {
            const int hatdata = BUFFER_OFFSET(buffer, hwdata->hatBufferOffset[i]);

            if (hatdata != hwdata->hatData[i]) {
                SDL_PrivateJoystickHat(joystick, i, AMIGAINPUT_MapHatData(hatdata));
                hwdata->hatData[i] = hatdata;
                //dprintf("Send hat %d\n", i);
            }
        }
    }
}

/* Function to close a joystick after use */
static void
AMIGAINPUT_Close(SDL_Joystick * joystick)
{
    dprintf("Closing joystick #%d (AI ID=%lu)\n", joystick->instance_id, joystickData.ids[joystick->instance_id].id);

    SDL_IAIN->AIN_ReleaseDevice(joystickData.context, joystick->hwdata->handle);

    SDL_free(joystick->hwdata);
    joystick->hwdata = NULL;
}

/* Function to perform any system-specific joystick related cleanup */
static void
AMIGAINPUT_Quit(void)
{
    for (uint32 i = 0; i < joystickData.count; i++) {
        SDL_free((char *)joystickData.ids[i].name);
    }

    joystickData.count = 0;

    if (joystickData.context) {
        SDL_IAIN->AIN_DeleteContext(joystickData.context);
        joystickData.context = NULL;
    }

    AMIGAINPUT_CloseLibrary();
}

static SDL_JoystickGUID
AMIGAINPUT_GetDeviceGUID(int device_index)
{
    Uint16 vendor = 0;
    Uint16 product = 0;
    Uint16 version = 0;
    Uint8 signature = 0;
    Uint8 data = 0;
    const char *vendorName = NULL;

    return SDL_CreateJoystickGUID(SDL_HARDWARE_BUS_USB,
                                  vendor,
                                  product,
                                  version,
                                  vendorName,
                                  joystickData.ids[device_index].name,
                                  signature,
                                  data);
}

static int
AMIGAINPUT_Rumble(SDL_Joystick * joystick, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble)
{
    dprintf("Called\n");
    return SDL_Unsupported();
}

static int
AMIGAINPUT_RumbleTriggers(SDL_Joystick * joystick, Uint16 left_rumble, Uint16 right_rumble)
{
    dprintf("Called\n");
    return SDL_Unsupported();
}

static Uint32
AMIGAINPUT_GetCapabilities(SDL_Joystick * joystick)
{
    return 0;
}

static int
AMIGAINPUT_SetLED(SDL_Joystick * joystick, Uint8 red, Uint8 green, Uint8 blue)
{
    dprintf("Called\n");
    return SDL_Unsupported();
}

static int
AMIGAINPUT_SendEffect(SDL_Joystick *joystick, const void *data, int size)
{
    dprintf("Called\n");
    return SDL_Unsupported();
}

static int
AMIGAINPUT_SetSensorsEnabled(SDL_Joystick * joystick, SDL_bool enabled)
{
    dprintf("Called\n");
    return SDL_Unsupported();
}

static SDL_bool
AMIGAINPUT_GetGamepadMapping(int device_index, SDL_GamepadMapping * out)
{
    dprintf("Called\n");
    return SDL_FALSE;
}

SDL_JoystickDriver SDL_AMIGAINPUT_JoystickDriver =
{
    AMIGAINPUT_Init,
    AMIGAINPUT_GetCount,
    AMIGAINPUT_Detect,
    AMIGAINPUT_GetDeviceName,
    AMIGAINPUT_GetDevicePath,
    AMIGAINPUT_GetDeviceSteamVirtualGamepadSlot,
    AMIGAINPUT_GetDevicePlayerIndex,
    AMIGAINPUT_SetDevicePlayerIndex,
    AMIGAINPUT_GetDeviceGUID,
    AMIGAINPUT_GetDeviceInstanceID,
    AMIGAINPUT_Open,
    AMIGAINPUT_Rumble,
    AMIGAINPUT_RumbleTriggers,
    AMIGAINPUT_GetCapabilities,
    AMIGAINPUT_SetLED,
    AMIGAINPUT_SendEffect,
    AMIGAINPUT_SetSensorsEnabled,
    AMIGAINPUT_Update,
    AMIGAINPUT_Close,
    AMIGAINPUT_Quit,
    AMIGAINPUT_GetGamepadMapping
};

#endif /* SDL_JOYSTICK_AMIGAINPUT */

/* vi: set ts=4 sw=4 expandtab: */
