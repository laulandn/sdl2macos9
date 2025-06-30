#include <SDL.h>
#include <stdio.h>

SDL_sem *counter_semaphore = NULL; // The semaphore
int shared_counter = 0; // The shared resource

int worker_thread(void *data) {
    for (int i = 0; i < 5; ++i) {
        // Wait on the semaphore before accessing the shared counter
        SDL_SemWait(counter_semaphore);

        // Access and modify the shared counter
        shared_counter++;
        printf("Thread %s: shared_counter = %d\n", (char*)data, shared_counter);

        // Signal the semaphore to release the resource
        SDL_SemPost(counter_semaphore);

        // Simulate some work
        SDL_Delay(100);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    freopen("stdout.txt","w",stdout);
    freopen("stderr.txt","w",stderr);
    // Initialize SDL threads subsystem
    if (SDL_Init(0/*SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC | SDL_INIT_GAMECONTROLLER*/) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create a semaphore with an initial value of 1 (allows one thread at a time)
    counter_semaphore = SDL_CreateSemaphore(1);
    if (counter_semaphore == NULL) {
        fprintf(stderr, "SDL_CreateSemaphore failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Create multiple worker threads
    SDL_Thread *thread1 = SDL_CreateThread(worker_thread, "Thread 1", (void*)"Thread 1");
    SDL_Thread *thread2 = SDL_CreateThread(worker_thread, "Thread 2", (void*)"Thread 2");

    // Wait for threads to finish
    SDL_WaitThread(thread1, NULL);
    SDL_WaitThread(thread2, NULL);

    // Destroy the semaphore
    SDL_DestroySemaphore(counter_semaphore);

    // Quit SDL
    SDL_Quit();

    return 0;
}
