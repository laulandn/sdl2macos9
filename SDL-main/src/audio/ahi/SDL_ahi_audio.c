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
#include "../../SDL_internal.h"

#include "SDL_audio.h"
#include "SDL_timer.h"
#include "../SDL_audio_c.h"
#include "../SDL_sysaudio.h"
#include "SDL_ahi_audio.h"

#include "../../core/morphos/SDL_cpu.h"

#include <sys/param.h>

#include <dos/dos.h>
#include <exec/execbase.h>
#include <proto/exec.h>

#define RESTART_CAPTURE_THRESHOLD 	 500

static Fixed AHI_Volume = 0x10000;

void AHI_Mute(ULONG mute)
{
	AHI_Volume = mute ? 0 : 0x10000;
}

static void AHI_DetectDevices(void)
{
	D("[%s]\n", __FUNCTION__);
	
	SDL_AudioSpec output, capture;
	output.freq = 44100;
	output.format = AUDIO_S16MSB;
	output.channels = 2;
	
	capture.freq = 44100;
	capture.format = AUDIO_S16MSB;
	capture.channels = 1;
	
	SDL_AddAudioDevice(SDL_FALSE, "AHI Morphos output device", &output, SDL_strdup("default"));;
	SDL_AddAudioDevice(SDL_TRUE, "AHI Morphos capture device", &capture, SDL_strdup("default"));
	
}

static void AHI_WaitDevice(_THIS)
{
	MOSAudioData *hidden = this->hidden;
	struct AHIRequest *req = &hidden->req[hidden->current_buffer];

	if (req->ahir_Std.io_Data) {
		WaitIO((struct IORequest *)req);

		req->ahir_Std.io_Data = NULL;

		GetMsg(&hidden->ahiport);
	}
}

static void AHI_PlayDevice(_THIS)
{
	MOSAudioData *hidden = this->hidden;
	struct AHIRequest *req;
	ULONG current, current2;
	
	current = hidden->current_buffer;
	current2 = current ^ 1;
	req = &hidden->req[current];

	req->ahir_Std.io_Data    = (APTR)hidden->buffers[current];
	req->ahir_Std.io_Length  = hidden->audioBufferSize;
	req->ahir_Std.io_Offset  = 0;
	req->ahir_Frequency      = this->spec.freq;
	req->ahir_Volume         = AHI_Volume; 
	req->ahir_Type           = hidden->sample_format;
	req->ahir_Position       = 0x8000;
	req->ahir_Link           = (hidden->playing ? &hidden->req[current2] : NULL);

	hidden->current_buffer = current2;
	hidden->playing = 1;

	SendIO((struct IORequest *)req);
}

static Uint8 * AHI_GetDeviceBuf(_THIS)
{
	MOSAudioData *hidden = this->hidden;
	return (Uint8 *) hidden->buffers[hidden->current_buffer];
}

static void AHI_CloseDevice(_THIS)
{
	MOSAudioData *hidden = this->hidden;

    if (hidden->buffers[0]) {
        SDL_free(hidden->buffers[0]);
        hidden->buffers[0] = NULL;
    }

    if (hidden->buffers[1]) {
        SDL_free(hidden->buffers[1]);
        hidden->buffers[1] = NULL;
    }
	
	this->hidden = NULL;

	CloseDevice((struct IORequest *)&hidden->req[0].ahir_Std);
	SDL_free(hidden);
}

static void AHI_ThreadInit(_THIS)
{
	MOSAudioData *hidden = this->hidden;

	hidden->ahiport.mp_Node.ln_Pri = 60;
	hidden->ahiport.mp_Flags = PA_SIGNAL;
	hidden->ahiport.mp_SigBit = SIGBREAKB_CTRL_E;
	hidden->ahiport.mp_SigTask = SysBase->ThisTask;

	NEWLIST(&hidden->ahiport.mp_MsgList);

	bcopy(&hidden->req[0], &hidden->req[1], sizeof(hidden->req[1]));
}

static int AHI_OpenDevice(_THIS, const char *devname)
{
	MOSAudioData *hidden;
	SDL_AudioFormat test_format;
	int sample_format = -1;

	switch (this->spec.format) {
		case AUDIO_F32LSB:
		case AUDIO_F32MSB:
		case AUDIO_S32LSB:
		 	this->spec.format = AUDIO_S32MSB;
			break;
		case AUDIO_S16LSB:
		default:
			this->spec.format = AUDIO_S16MSB;
			break;
	}
	/*if ((this->spec.format & 0xff) != 8)
		 this->spec.format = AUDIO_S16MSB;*/

	test_format = SDL_FirstAudioFormat(this->spec.format);
	
	while (sample_format < 0 && test_format) {

		switch (test_format) {
			case AUDIO_U8:
			case AUDIO_S8:
				sample_format = this->spec.channels == 1 ? AHIST_M8S : AHIST_S8S;
				break; 
			break;
			case AUDIO_S16LSB:
			case AUDIO_S16MSB:
				sample_format = this->spec.channels == 1 ? AHIST_M16S : AHIST_S16S;
				break;
			case AUDIO_S32LSB:
			case AUDIO_S32MSB:
				sample_format = this->spec.channels == 1 ? AHIST_M32S : AHIST_S32S;
				break;
			default:
				D("[%s] unsupported SDL format 0x%ld\n", __FUNCTION__, test_format);
				test_format = SDL_NextAudioFormat();
				break;
		}
	}

	if (sample_format < 0)
		return SDL_SetError("Unsupported audio format");

	D("[%s] AHI sample format is %ld\n", __FUNCTION__, sample_format);

	if (this->spec.channels > 2)
		this->spec.channels = 2;

	if (this->spec.samples > 1024) {
		this->spec.samples = MAX(this->spec.freq / 20, 256);
		this->spec.samples = (this->spec.samples + 7) & ~7;
	}

	/* Update the fragment size as size in bytes */
	SDL_CalculateAudioSpec(&this->spec);

	hidden = SDL_malloc(sizeof(MOSAudioData));

	if (hidden == NULL)
		return SDL_OutOfMemory();

	hidden->req[0].ahir_Std.io_Message.mn_ReplyPort = &hidden->ahiport;
	hidden->req[0].ahir_Std.io_Message.mn_Length = sizeof(struct AHIRequest);
	hidden->req[0].ahir_Std.io_Command = CMD_WRITE;
	hidden->req[0].ahir_Std.io_Data = NULL;
	hidden->req[0].ahir_Version = 6;

	hidden->audioBufferSize = this->spec.size;
	hidden->buffers[0] = (Uint8 *) SDL_malloc(hidden->audioBufferSize);
	hidden->buffers[1] = (Uint8 *) SDL_malloc(hidden->audioBufferSize);
	if (hidden->buffers[0] == NULL || hidden->buffers[1] == NULL) {
        SDL_SetError("No memory for audio buffer");
        return -1;
    }
	
    SDL_memset(hidden->buffers[0], this->spec.silence, hidden->audioBufferSize);
    SDL_memset(hidden->buffers[1], this->spec.silence, hidden->audioBufferSize);
	
	//hidden->convert = convert;
	hidden->current_buffer = 0;
	hidden->sample_format = sample_format;
	hidden->playing = 0;
	hidden->requestSent = SDL_FALSE;

	this->hidden = hidden;
	
	if (OpenDevice(AHINAME, 0, (struct IORequest *)&hidden->req[0].ahir_Std, 0) != 0) {
		SDL_SetError("Unable to open ahi.device unit 0! Error code %d.\n", hidden->req[0].ahir_Std.io_Error);
		return -1;
	}
	return 0;
}

static void AHI_FillCaptureRequest(struct AHIRequest *request, void *buffer, int length, int frequency, int type)
{
    request->ahir_Std.io_Message.mn_Node.ln_Pri = 60;
    request->ahir_Std.io_Data    = buffer,
    request->ahir_Std.io_Length  = length;
    request->ahir_Std.io_Command = CMD_READ;
    request->ahir_Volume = AHI_Volume;
    request->ahir_Position = 0x8000;
    request->ahir_Link = NULL;
    request->ahir_Frequency = frequency;
    request->ahir_Type = type;
}

static int AHI_CaptureFromDevice(_THIS, void *buffer, int buflen)
{
	struct AHIRequest  *request;
	MOSAudioData *hidden = this->hidden;
	Uint32 now;
	UBYTE current;
	size_t copyLen;
    void *completedBuffer;
	
	now = SDL_GetTicks();
	current = hidden->current_buffer;
	request = &hidden->req[0];
	
    if (hidden->lastCaptureTicks == 0 || (now - hidden->lastCaptureTicks) > RESTART_CAPTURE_THRESHOLD) {

	    if (hidden->requestSent)
            WaitIO((struct IORequest *)request);
		
        AHI_FillCaptureRequest(
            request,
            hidden->buffers[current],
            this->spec.size,
            this->spec.freq,
            hidden->sample_format);

        request->ahir_Std.io_Offset = 0;

        D("[%s] Start recording\n", __FUNCTION__);

        DoIO((struct IORequest *)request);
        hidden->requestSent = SDL_FALSE;
		
		current = 1 - current;

    } else {
		if (hidden->requestSent)
        	WaitIO((struct IORequest *)request);
    }

    AHI_FillCaptureRequest(
        request,
        hidden->buffers[current],
        this->spec.size,
        this->spec.freq,
        hidden->sample_format);

    SendIO((struct IORequest *)request);
    hidden->requestSent = SDL_TRUE;

	current = 1 - current;
	
    completedBuffer = hidden->buffers[current];

    copyLen = MIN(buflen, this->spec.size);

    SDL_memcpy(buffer, completedBuffer, copyLen);

    hidden->lastCaptureTicks = now;
    hidden->current_buffer = current;

    return copyLen;
}

static SDL_bool AHI_Init(SDL_AudioDriverImpl * impl)
{
	/* Set the function pointers */
	impl->DetectDevices = AHI_DetectDevices;
	impl->OpenDevice = AHI_OpenDevice;
	impl->ThreadInit = AHI_ThreadInit;
	impl->PlayDevice = AHI_PlayDevice;
	impl->WaitDevice = AHI_WaitDevice;
	impl->CaptureFromDevice = AHI_CaptureFromDevice;	
	impl->GetDeviceBuf = AHI_GetDeviceBuf;
	impl->CloseDevice = AHI_CloseDevice;

	impl->ProvidesOwnCallbackThread = SDL_FALSE;
	impl->HasCaptureSupport = SDL_TRUE;
	impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
	impl->OnlyHasDefaultCaptureDevice = SDL_TRUE;
	
	return SDL_TRUE;   /* this audio target is available. */
}

AudioBootStrap AHIAUD_bootstrap = {
    "ahi", "MorphOS AHI audio driver", AHI_Init, SDL_FALSE 
};
