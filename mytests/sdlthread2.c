#include <SDL.h>
#include <SDL_thread.h>
#include <stdio.h> // For printf

#define WHERE stdout

int flag=0;

// The function that the thread will execute
static int thread_function(void *ptr) {
    fprintf(stderr,"Hello from the thread!\n"); fflush(stderr);
    flag=1;
    SDL_Delay(500); // Simulate some work
    return 0; // Return value of the thread
}

int main(int argc, char *argv[]) {
    freopen("stdout.txt","w",stdout);
    freopen("stderr.txt","w",stderr);
    fprintf(WHERE,"Going to SDL_Init...\n"); fflush(WHERE);
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO/*SDL_INIT_EVERYTHING*/) != 0) {
        printf("Could not initialize SDL2! %s\n", SDL_GetError());
        return 1;
    }

    fprintf(WHERE,"flag is %d...\n",flag); fflush(WHERE);
    fprintf(WHERE,"thread_function is %08lx...\n",(long)thread_function); fflush(WHERE);
    fprintf(WHERE,"Going to SDL_CreateThread...\n"); fflush(WHERE);
    // Create a thread
    SDL_Thread *thread = SDL_CreateThread(thread_function, "MyThread", (void *)1/*NULL*/);
    if (thread == NULL) {
        printf("Could not create thread! %s\n", SDL_GetError());
        return 1;
    }
    fprintf(WHERE,"flag is %d...\n",flag); fflush(WHERE);

    fprintf(WHERE,"Would do main thread work here...\n"); fflush(WHERE);
    // Do other work in the main thread (e.g., rendering, event handling)
    // ... main thread loop ...
    
    fprintf(WHERE,"flag is %d...\n",flag); fflush(WHERE);
    fprintf(WHERE,"Going to SDL_WaitThread...\n"); fflush(WHERE);
    // Wait for the thread to finish
    SDL_WaitThread(thread, NULL);
    fprintf(WHERE,"flag is %d...\n",flag); fflush(WHERE);

    fprintf(WHERE,"Going to SDL_Quit...\n"); fflush(WHERE);
    // Clean up SDL
    SDL_Quit();

    return 0;
}
