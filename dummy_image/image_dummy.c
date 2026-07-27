/* hack that looks and sorta works like SDL_image */

#include <SDL_image.h>


int IMG_Init(int flags)
{
  fprintf(stderr,"IMG_Init('%d')...\n",flags);  fflush(stderr);
  return 1;
}


char *IMG_GetError()
{
  fprintf(stderr,"IMG_GetError()...\n");  fflush(stderr);
  return NULL;
}


SDL_Surface *IMG_Load_RW(SDL_RWops *src,const char *n)
{
  SDL_Surface *s=NULL;
  fprintf(stderr,"IMG_Load_RW(src,'%s')...\n",n);  fflush(stderr);
  s=SDL_LoadBMP(n);
  if(!s) fprintf(stderr,"SDL_LoadBMP_RW failed!\n");  fflush(stderr);
  return s;
}


int IMG_SavePNG(SDL_Surface *s,const char *name)
{
  fprintf(stderr,"IMG_SavePNG()...\n");  fflush(stderr);
  return 0;
}

