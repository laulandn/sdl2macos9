#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h> // For printf

int flag=0;

// The function that the thread will execute
static int thread_function(void *ptr) {
    printf("Hello from the thread!\n");
    flag=1;
    SDL_Delay(500); // Simulate some work
    return 0; // Return value of the thread
}

int main(int argc, char *argv[]) {
    fprintf(stderr,"Going to SDL_Init...\n"); fflush(stderr);
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO/*SDL_INIT_EVERYTHING*/) != 0) {
        printf("Could not initialize SDL2! %s\n", SDL_GetError());
        return 1;
    }

    fprintf(stderr,"flag is %d...\n",flag); fflush(stderr);
    fprintf(stderr,"thread_function is %08lx...\n",(long)thread_function); fflush(stderr);
    fprintf(stderr,"Going to SDL_CreateThread...\n"); fflush(stderr);
    // Create a thread
    SDL_Thread *thread = SDL_CreateThread(thread_function, "MyThread", (void *)NULL);
    if (thread == NULL) {
        printf("Could not create thread! %s\n", SDL_GetError());
        return 1;
    }
    fprintf(stderr,"flag is %d...\n",flag); fflush(stderr);

    fprintf(stderr,"Would do main thread work here...\n"); fflush(stderr);
    // Do other work in the main thread (e.g., rendering, event handling)
    // ... main thread loop ...
    
    fprintf(stderr,"flag is %d...\n",flag); fflush(stderr);
    fprintf(stderr,"Going to SDL_WaitThread...\n"); fflush(stderr);
    // Wait for the thread to finish
    SDL_WaitThread(thread, NULL);
    fprintf(stderr,"flag is %d...\n",flag); fflush(stderr);

    // Clean up SDL
    SDL_Quit();

    return 0;
}
