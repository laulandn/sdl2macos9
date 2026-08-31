/* OPENSTEP SDL2 video backend private state.
   This header deliberately contains no SDL1 video API or public extension. */
#ifndef SDL_openstepvideo_h_
#define SDL_openstepvideo_h_

#include "../SDL_sysvideo.h"

/* Objective-C objects remain opaque to the SDL core. Their ownership is
   confined to the native backend implementation. */
typedef struct SDL_OpenStepVideoData
{
    void *autorelease_pool;
    void *application;
    /* Lazily-created, retained transparent NSCursor used by SDL_ShowCursor
       when the standard SDL cursor visibility state is disabled. */
    void *invisible_cursor;
    /* The general pasteboard revision observed by the SDL event pump. */
    int clipboard_count;
    /* The latest NSFlagsChanged state.  Some OPENSTEP console paths omit
       these bits from the following keyDown:/keyUp: event. */
    unsigned int modifier_flags;
} SDL_OpenStepVideoData;

typedef struct SDL_OpenStepWindowData
{
    SDL_Window *sdl_window;
    void *window;
    void *view;
    void *bitmap;
    void *cursor;
    void *framebuffer_pixels;
    void *present_pixels;
    int framebuffer_pitch;
    int width;
    int height;
    float restore_x;
    float restore_y;
    float restore_w;
    float restore_h;
    float fullscreen_restore_x;
    float fullscreen_restore_y;
    float fullscreen_restore_w;
    float fullscreen_restore_h;
    float fullscreen_restore_content_w;
    float fullscreen_restore_content_h;
    void *gl_contexts;
    SDL_bool presenting;
    SDL_bool has_restore_frame;
    SDL_bool has_fullscreen_restore_frame;
} SDL_OpenStepWindowData;

#endif /* SDL_openstepvideo_h_ */
