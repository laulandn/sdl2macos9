#include <SDL.h>
#include <stdio.h>

int thread_function(void* data) {
    int thread_id = (int)(intptr_t)data; // Cast void* back to int
    printf("Thread %d started\n", thread_id);
    for (int i = 0; i < 5; ++i) {
        printf("Thread %d: Count %d\n", thread_id, i);
        SDL_Delay(500);
    }
    printf("Thread %d finished\n", thread_id);
    return 0;
}

int main(int argc, char* argv[]) {
    freopen("stdout.txt","w",stdout);
    freopen("stderr.txt","w",stderr);
    fprintf(stderr,"Going to SDL_Init...\n"); fflush(stderr);
    SDL_Init(0/*SDL_INIT_VIDEO | SDL_INIT_TIMER*/);

    fprintf(stderr,"thread_function is %08lx...\n",(long)thread_function); fflush(stderr);
    fprintf(stderr,"Going to create threads...\n"); fflush(stderr);
    SDL_Thread* thread1 = SDL_CreateThread(thread_function, "Thread 1", (void*)1);
    SDL_Thread* thread2 = SDL_CreateThread(thread_function, "Thread 2", (void*)2);

    fprintf(stderr,"Going to wait threads...\n"); fflush(stderr);
    SDL_WaitThread(thread1, NULL);
    SDL_WaitThread(thread2, NULL);

    fprintf(stderr,"Going to SDL_Quit...\n"); fflush(stderr);
    SDL_Quit();
    return 0;
}
