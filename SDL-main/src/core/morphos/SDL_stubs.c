/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2022 Sam Lantinga <slouken@libsdl.org>

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

#include <stdarg.h>

#define GENERATE_STUBS
#define SDL_CopyAndSwap16_REAL SDL_CopyAndSwap16
#define SDL_CopyAndSwap32_REAL SDL_CopyAndSwap32
#if !defined(SDL_SENSOR_DISABLED)
int __saveds SDL_LockSensors(void) { return 0;}
int __saveds SDL_UnlockSensors(void) { return 0;}
#define SDL_LockSensors_REAL SDL_LockSensors
#define SDL_UnlockSensors_REAL SDL_UnlockSensors
#endif
#if !defined(SDL_LOADSO_DISABLED)
int __saveds SDL_LoadObject(void) { return 0;}
int __saveds SDL_LoadFunction(void) { return 0;}
int __saveds SDL_UnloadObject(void) { return 0;}
#define SDL_LoadObject_REAL SDL_LoadObject
#define SDL_LoadFunction_REAL SDL_LoadFunction
#define SDL_UnloadObject_REAL SDL_UnloadObject
#endif
#if !defined(SDL_HIDAPIC_DISABLED)
int __saveds SDL_hid_dummy(void) { return 0;}
#define SDL_hid_ble_scan_REAL SDL_hid_dummy
#define SDL_hid_get_indexed_string_REAL SDL_hid_dummy
#define SDL_hid_get_serial_number_string_REAL SDL_hid_dummy
#define SDL_hid_get_product_string_REAL SDL_hid_dummy
#define SDL_hid_get_manufacturer_string_REAL SDL_hid_dummy
#define SDL_hid_close_REAL SDL_hid_dummy
#define SDL_hid_get_feature_report_REAL SDL_hid_dummy
#define SDL_hid_send_feature_report_REAL SDL_hid_dummy
#define SDL_hid_set_nonblocking_REAL SDL_hid_dummy
#define SDL_hid_read_REAL SDL_hid_dummy
#define SDL_hid_read_timeout_REAL SDL_hid_dummy
#define SDL_hid_write_REAL SDL_hid_dummy
#define SDL_hid_open_path_REAL SDL_hid_dummy
#define SDL_hid_open_REAL SDL_hid_dummy
#define SDL_hid_free_enumeration_REAL SDL_hid_dummy
#define SDL_hid_enumerate_REAL SDL_hid_dummy
#define SDL_hid_device_change_count_REAL SDL_hid_dummy
#define SDL_hid_exit_REAL SDL_hid_dummy
#define SDL_hid_init_REAL SDL_hid_dummy
#endif
#if !defined(SDL_HAPTIC_DISABLED)
int __saveds SDL_HapticDummy(void) { return 0;}
#define SDL_NumHaptics_REAL SDL_HapticDummy
#define SDL_HapticName_REAL SDL_HapticDummy
#define SDL_HapticOpen_REAL SDL_HapticDummy
#define SDL_HapticOpened_REAL SDL_HapticDummy
#define SDL_HapticIndex_REAL SDL_HapticDummy
#define SDL_MouseIsHaptic_REAL SDL_HapticDummy
#define SDL_HapticOpenFromMouse_REAL SDL_HapticDummy
#define SDL_JoystickIsHaptic_REAL SDL_HapticDummy
#define SDL_HapticOpenFromJoystick_REAL SDL_HapticDummy
#define SDL_HapticClose_REAL SDL_HapticDummy
#define SDL_HapticNumEffects_REAL SDL_HapticDummy
#define SDL_HapticNumEffectsPlaying_REAL SDL_HapticDummy
#define SDL_HapticQuery_REAL SDL_HapticDummy
#define SDL_HapticNumAxes_REAL SDL_HapticDummy
#define SDL_HapticEffectSupported_REAL SDL_HapticDummy
#define SDL_HapticNewEffect_REAL SDL_HapticDummy
#define SDL_HapticUpdateEffect_REAL SDL_HapticDummy
#define SDL_HapticRunEffect_REAL SDL_HapticDummy
#define SDL_HapticStopEffect_REAL SDL_HapticDummy
#define SDL_HapticDestroyEffect_REAL SDL_HapticDummy
#define SDL_HapticGetEffectStatus_REAL SDL_HapticDummy
#define SDL_HapticSetGain_REAL SDL_HapticDummy
#define SDL_HapticRumbleStop_REAL SDL_HapticDummy
#define SDL_HapticRumblePlay_REAL SDL_HapticDummy
#define SDL_HapticRumbleInit_REAL SDL_HapticDummy
#define SDL_HapticRumbleSupported_REAL SDL_HapticDummy
#define SDL_HapticStopAll_REAL SDL_HapticDummy
#define SDL_HapticSetAutocenter_REAL SDL_HapticDummy
#define SDL_HapticPause_REAL SDL_HapticDummy
#define SDL_HapticUnpause_REAL SDL_HapticDummy
#endif

#include "SDL_stubs.h"

/*********************************************************************/

/* This function must preserve all registers except r13 */
#if 1
asm
("\n"
"	.section \".text\"\n"
"	.align 2\n"
"	.type __restore_r13, @function\n"
"__restore_r13:\n"
"	lwz 13, 36(12)\n"
"	blr\n"
"__end__restore_r13:\n"
"	.size __restore_r13, __end__restore_r13 - __restore_r13\n"
);
#endif

int __saveds LIB_SDL_VSetError(const char *fmt, va_list ap)
{
	extern int SDL_VSetError(const char *fmt, va_list ap);
	return SDL_VSetError(fmt, ap);
}
