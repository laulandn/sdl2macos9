/*
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely.
*/
/* Simple program:  Move N sprites around on the screen as fast as possible */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "SDL_test_common.h"
#include "testutils.h"

static SDLTest_CommonState *state;

typedef struct
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *background;
    SDL_Texture *sprite;
    SDL_Rect sprite_rect;
    int scale_direction;
} DrawState;

DrawState *drawstates;
int done;

/* Call this instead of exit(), so we can clean up SDL: atexit() is evil. */
static void
quit(int rc)
{
    SDLTest_CommonQuit(state);
    exit(rc);
}

void Draw(DrawState *s)
{
    SDL_Rect viewport;
    SDL_Texture *target;
    SDL_Point *center = NULL;
    SDL_Point origin = { 0, 0 };

    fprintf(stderr,"Going to SDL_RenderGetViewport...\n"); fflush(stderr);
    SDL_RenderGetViewport(s->renderer, &viewport);

    fprintf(stderr,"Going to SDL_CreateTexture...\n"); fflush(stderr);
    target = SDL_CreateTexture(s->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET, viewport.w, viewport.h);
    fprintf(stderr,"Going to SDL_SetRenderTarget1...\n"); fflush(stderr);
    SDL_SetRenderTarget(s->renderer, target);

    /* Draw the background */
    fprintf(stderr,"Going to SDL_RenderCopy1...\n"); fflush(stderr);
    SDL_RenderCopy(s->renderer, s->background, NULL, NULL);

    /* Scale and draw the sprite */
    s->sprite_rect.w += s->scale_direction;
    s->sprite_rect.h += s->scale_direction;
    if (s->scale_direction > 0) {
        center = &origin;
        if (s->sprite_rect.w >= viewport.w || s->sprite_rect.h >= viewport.h) {
            s->scale_direction = -1;
        }
    } else {
        if (s->sprite_rect.w <= 1 || s->sprite_rect.h <= 1) {
            s->scale_direction = 1;
        }
    }
    s->sprite_rect.x = (viewport.w - s->sprite_rect.w) / 2;
    s->sprite_rect.y = (viewport.h - s->sprite_rect.h) / 2;

    fprintf(stderr,"Going to SDL_RenderCopyEx...\n"); fflush(stderr);
    SDL_RenderCopyEx(s->renderer, s->sprite, NULL, &s->sprite_rect, (double)s->sprite_rect.w, center, (SDL_RendererFlip)s->scale_direction);

    fprintf(stderr,"Going to SDL_SetRenderTarget2...\n"); fflush(stderr);
    SDL_SetRenderTarget(s->renderer, NULL);
    fprintf(stderr,"Going to SDL_RenderCopy2...\n"); fflush(stderr);
    SDL_RenderCopy(s->renderer, target, NULL, NULL);
    fprintf(stderr,"Going to SDL_DestroyTexture...\n"); fflush(stderr);
    SDL_DestroyTexture(target);
    /* Update the screen! */
    fprintf(stderr,"Going to SDL_RenderPresent...\n"); fflush(stderr);
    SDL_RenderPresent(s->renderer);
    /* SDL_Delay(10); */
    fprintf(stderr,"Draw done.\n"); fflush(stderr);
}

void loop(void)
{
    int i;
    SDL_Event event;

    fprintf(stderr,"loop...\n"); fflush(stderr);
    /* Check for events */
    fprintf(stderr,"Going to SDL_PollEvent...\n"); fflush(stderr);
    while (SDL_PollEvent(&event)) {
    fprintf(stderr,"Going to SDLTest_CommonEvent...\n"); fflush(stderr);   
        SDLTest_CommonEvent(state, &event, &done);
    }
    for (i = 0; i < state->num_windows; ++i) {
        if (state->windows[i] == NULL) {
            continue;
        }
    fprintf(stderr,"Going to Draw...\n"); fflush(stderr);
        Draw(&drawstates[i]);
    }
#ifdef __EMSCRIPTEN__
    if (done) {
        emscripten_cancel_main_loop();
    }
#endif
    fprintf(stderr,"loop done\n"); fflush(stderr);
}

int main(int argc, char *argv[])
{
    int i;
    int frames;
    Uint32 then, now;

    /* Enable standard application logging */
    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, SDL_INIT_VIDEO);
    if (!state) {
        return 1;
    }

    state->verbose=VERBOSE_VIDEO | VERBOSE_MODES | VERBOSE_RENDER |
                 VERBOSE_EVENT;

    fprintf(stderr,"Before SDLTest_CommonInit...\n"); fflush(stderr);

    if (!SDLTest_CommonDefaultArgs(state, argc, argv) || !SDLTest_CommonInit(state)) {
        SDLTest_CommonQuit(state);
        return 1;
    }

    fprintf(stderr,"After SDLTest_CommonInit...\n"); fflush(stderr);

    state->verbose=VERBOSE_VIDEO | VERBOSE_MODES | VERBOSE_RENDER |
                 VERBOSE_EVENT;         

    drawstates = SDL_stack_alloc(DrawState, state->num_windows);
    for (i = 0; i < state->num_windows; ++i) {
        DrawState *drawstate = &drawstates[i];

        drawstate->window = state->windows[i];
        drawstate->renderer = state->renderers[i];
        drawstate->sprite = LoadTexture(drawstate->renderer, "icon.bmp", SDL_TRUE, NULL, NULL);
        drawstate->background = LoadTexture(drawstate->renderer, "sample.bmp", SDL_FALSE, NULL, NULL);
        if (!drawstate->sprite || !drawstate->background) {
            quit(2);
        }
        SDL_QueryTexture(drawstate->sprite, NULL, NULL,
                         &drawstate->sprite_rect.w, &drawstate->sprite_rect.h);
        drawstate->scale_direction = 1;
    }

    /* Main render loop */
    frames = 0;
    then = SDL_GetTicks();
    done = 0;

#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(loop, 0, 1);
#else
    while (!done) {
        ++frames;
        loop();
    }
#endif
    /* Print out some timing information */
    now = SDL_GetTicks();
    if (now > then) {
        double fps = ((double)frames * 1000) / (now - then);
        SDL_Log("%2.2f frames per second\n", fps);
    }

    SDL_stack_free(drawstates);

    quit(0);
    return 0;
}

/* vi: set ts=4 sw=4 expandtab: */
