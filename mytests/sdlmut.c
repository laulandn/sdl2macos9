#include <SDL.h>
#include <stdio.h>

SDL_mutex *mutex = NULL;
int shared_data = 0;

int increment_data(void *data) {
    for (int i = 0; i < 5; ++i) {
        SDL_LockMutex(mutex);
        shared_data++;
        printf("Thread %s: shared_data = %d\n", (char*)data, shared_data);
        SDL_UnlockMutex(mutex);
        SDL_Delay(100);
    }
    return 0;
}

int main(int argc, char **argv) {
    freopen("stdout.txt","w",stdout);
    freopen("stderr.txt","w",stderr);
    if (SDL_Init(0/*SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER*/) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return 1;
    }

    mutex = SDL_CreateMutex();
    if (mutex == NULL) {
        SDL_Log("Unable to create mutex: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    //std::thread t1(increment_data);
    //std::thread t2(increment_data);
    //t1.join();
    //t2.join();
    
    SDL_Thread *thread1 = SDL_CreateThread(increment_data, "Thread 1", (void*)"Thread 1");
    SDL_Thread *thread2 = SDL_CreateThread(increment_data, "Thread 2", (void*)"Thread 2");

    // Wait for threads to finish
    SDL_WaitThread(thread1, NULL);
    SDL_WaitThread(thread2, NULL);

    SDL_Log("Final shared_data value: %d", shared_data);

    SDL_DestroyMutex(mutex);
    SDL_Quit();
    return 0;
}
