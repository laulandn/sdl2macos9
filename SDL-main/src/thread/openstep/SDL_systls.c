#include "../../SDL_internal.h"

#include "../SDL_thread_c.h"

/*
 * OPENSTEP 4.2 cthreads has no usable compiler TLS facility.  SDL's generic
 * fallback therefore provides the storage, but it assumes that the platform
 * has initialized its mutex before the first error path.  SDL_SetError() can
 * be reached before SDL_CreateThread() on a normal SDL_Init() call, so make
 * that initialization lazy and serialized here.
 */
static SDL_SpinLock openstep_tls_init_lock;
static SDL_bool openstep_tls_initialized;

static void
OpenStep_InitTLSData(void)
{
    SDL_AtomicLock(&openstep_tls_init_lock);
    if (!openstep_tls_initialized) {
        SDL_Generic_InitTLSData();
        openstep_tls_initialized = SDL_TRUE;
    }
    SDL_AtomicUnlock(&openstep_tls_init_lock);
}

void SDL_SYS_InitTLSData(void)
{
    OpenStep_InitTLSData();
}

SDL_TLSData *SDL_SYS_GetTLSData(void)
{
    OpenStep_InitTLSData();
    return SDL_Generic_GetTLSData();
}

int SDL_SYS_SetTLSData(SDL_TLSData *data)
{
    OpenStep_InitTLSData();
    return SDL_Generic_SetTLSData(data);
}

void SDL_SYS_QuitTLSData(void)
{
    SDL_AtomicLock(&openstep_tls_init_lock);
    if (openstep_tls_initialized) {
        SDL_Generic_QuitTLSData();
        openstep_tls_initialized = SDL_FALSE;
    }
    SDL_AtomicUnlock(&openstep_tls_init_lock);
}
