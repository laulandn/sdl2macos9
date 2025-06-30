#include <stdio.h>
#include "./MacThreads.h"

void *thread_function(void* data) {
    int thread_id = (int)(intptr_t)data; // Cast void* back to int
    fprintf(stderr,"Thread %d started\n", thread_id);
    for (int i = 0; i < 5; ++i) {
        fprintf(stderr,"Thread %d: Count %d\n", thread_id, i);
	YieldToAnyThread();
    }
    fprintf(stderr,"Thread %d finished\n", thread_id);
    return NULL;
}

int main(int argc, char* argv[]) {
    ThreadID handle1,handle2;
    freopen("stdout.txt","w",stdout);
    freopen("stderr.txt","w",stderr);
    fprintf(stderr,"thread_function is %08lx...\n",(long)thread_function); fflush(stderr);
    fprintf(stderr,"Going to create threads...\n"); fflush(stderr);
    NewThread(kCooperativeThread,thread_function,(void *)1,0,0,NULL,&handle1);
    fprintf(stderr,"Got handle1=%d\n",handle1);
    NewThread(kCooperativeThread,thread_function,(void *)2,0,0,NULL,&handle2);
    fprintf(stderr,"Got handle2=%d\n",handle2);

    fprintf(stderr,"Going to wait threads...\n"); fflush(stderr);
    for(int t=0;t<15;t++) {
      YieldToAnyThread();
    }

    return 0;
}
