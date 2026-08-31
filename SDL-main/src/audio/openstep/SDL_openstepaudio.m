/* OPENSTEP SoundKit output backend for SDL2. The common SDL2 audio core owns
   the callback thread and converts input to this driver's S16MSB device
   format; this backend retains only queued SoundKit buffers. */
#include "../../SDL_internal.h"

#ifdef SDL_AUDIO_DRIVER_OPENSTEP

#import <SoundKit/SoundKit.h>
#import <sound/sound.h>

#include "SDL_audio.h"
#include "SDL_timer.h"
#include "../SDL_sysaudio.h"
#include "SDL_openstepaudio.h"

static void OPENSTEPAUDIO_DrainOne(_THIS)
{
    const int slot = _this->hidden->head;
    if (_this->hidden->count > 0) {
        if (SNDWait(_this->hidden->tags[slot]) != SND_ERR_NONE) {
            SDL_SetError("OPENSTEP SoundKit wait failed");
        }
        SDL_free(_this->hidden->sounds[slot]);
        _this->hidden->sounds[slot] = NULL;
        _this->hidden->head = (slot + 1) % OPENSTEP_AUDIO_QUEUE_SLOTS;
        --_this->hidden->count;
    }
}

static int OPENSTEPAUDIO_OpenDevice(_THIS, const char *devname)
{
    (void)devname;
    if (_this->iscapture) {
        return SDL_Unsupported();
    }
    if (_this->spec.freq != 22050 && _this->spec.freq != 44100) {
        _this->spec.freq = 44100;
    }
    if (_this->spec.channels < 1 || _this->spec.channels > 2) {
        _this->spec.channels = 2;
    }
    _this->spec.format = AUDIO_S16MSB;
    _this->spec.samples = (Uint16)(_this->spec.freq / 4);
    SDL_CalculateAudioSpec(&_this->spec);

    _this->hidden = (struct SDL_PrivateAudioData *)SDL_calloc(1, sizeof(*_this->hidden));
    if (_this->hidden == NULL) {
        return SDL_OutOfMemory();
    }
    _this->hidden->mixlen = _this->spec.size;
    _this->hidden->mixbuf = (Uint8 *)SDL_malloc(_this->hidden->mixlen);
    if (_this->hidden->mixbuf == NULL) {
        SDL_free(_this->hidden);
        _this->hidden = NULL;
        return SDL_OutOfMemory();
    }
    SDL_memset(_this->hidden->mixbuf, _this->spec.silence, _this->hidden->mixlen);
    _this->hidden->delay_ms = (_this->spec.samples * 1000) / _this->spec.freq;
    if (_this->hidden->delay_ms == 0) {
        _this->hidden->delay_ms = 1;
    }
    return 0;
}

static Uint8 *OPENSTEPAUDIO_GetDeviceBuf(_THIS)
{
    return _this->hidden->mixbuf;
}

static void OPENSTEPAUDIO_PlayDevice(_THIS)
{
    SNDSoundStruct *sound;
    int slot;
    int error;

    if (_this->hidden->count == OPENSTEP_AUDIO_QUEUE_SLOTS) {
        OPENSTEPAUDIO_DrainOne(_this);
    }
    sound = (SNDSoundStruct *)SDL_malloc(sizeof(*sound) + _this->hidden->mixlen);
    if (sound == NULL) {
        SDL_OutOfMemory();
        return;
    }
    sound->magic = SND_MAGIC;
    sound->dataLocation = sizeof(*sound);
    sound->dataSize = _this->hidden->mixlen;
    sound->dataFormat = SND_FORMAT_LINEAR_16;
    sound->samplingRate = _this->spec.freq;
    sound->channelCount = _this->spec.channels;
    SDL_memcpy(((Uint8 *)sound) + sizeof(*sound), _this->hidden->mixbuf, _this->hidden->mixlen);

    ++_this->hidden->next_tag;
    if (_this->hidden->next_tag <= 0) {
        _this->hidden->next_tag = 1;
    }
    error = SNDStartPlaying(sound, _this->hidden->next_tag, 0, 0, SND_NULL_FUN, SND_NULL_FUN);
    if (error != SND_ERR_NONE) {
        SDL_free(sound);
        SDL_SetError("OPENSTEP SoundKit play failed (%d)", error);
        return;
    }
    slot = (_this->hidden->head + _this->hidden->count) % OPENSTEP_AUDIO_QUEUE_SLOTS;
    _this->hidden->sounds[slot] = sound;
    _this->hidden->tags[slot] = _this->hidden->next_tag;
    ++_this->hidden->count;
}

static void OPENSTEPAUDIO_WaitDevice(_THIS)
{
    if (_this->hidden->count >= OPENSTEP_AUDIO_QUEUE_AHEAD) {
        OPENSTEPAUDIO_DrainOne(_this);
    }
}

static void OPENSTEPAUDIO_CloseDevice(_THIS)
{
    if (_this->hidden != NULL) {
        while (_this->hidden->count > 0) {
            OPENSTEPAUDIO_DrainOne(_this);
        }
        SDL_free(_this->hidden->mixbuf);
        SDL_free(_this->hidden);
        _this->hidden = NULL;
    }
}

static SDL_bool OPENSTEPAUDIO_Init(SDL_AudioDriverImpl *impl)
{
    impl->OpenDevice = OPENSTEPAUDIO_OpenDevice;
    impl->WaitDevice = OPENSTEPAUDIO_WaitDevice;
    impl->PlayDevice = OPENSTEPAUDIO_PlayDevice;
    impl->GetDeviceBuf = OPENSTEPAUDIO_GetDeviceBuf;
    impl->CloseDevice = OPENSTEPAUDIO_CloseDevice;
    impl->OnlyHasDefaultOutputDevice = SDL_TRUE;
    impl->SupportsNonPow2Samples = SDL_TRUE;
    return SDL_TRUE;
}

AudioBootStrap OPENSTEPAUDIO_bootstrap = {
    "openstep", "OPENSTEP SoundKit output driver", OPENSTEPAUDIO_Init, SDL_FALSE
};

#endif
