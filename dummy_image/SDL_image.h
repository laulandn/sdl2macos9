
#include "SDL.h"


/* hack that looks and sorta works like SDL_image */


#define IMG_INIT_PNG 1


#ifdef __cplusplus
extern "C" {
#endif


extern int IMG_Init(int flags);

extern char *IMG_GetError();

extern SDL_Surface *IMG_Load_RW(SDL_RWops *src,const char *name);

extern int IMG_SavePNG(SDL_Surface *s,const char *name);


#define IMG_Load(file)   IMG_Load_RW(SDL_RWFromFile(file, "rb"), 1)


#ifdef __cplusplus
}
#endif
