#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *worker(void *arg) {
    printf("Thread ID: %lu, Process ID: %d\n", pthread_self(), getpid());
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int num_threads = atoi(argv[1]);
    pthread_t threads[num_threads];
    
    for (int i = 0; i < num_threads; i++) {
        pthread_create(&threads[i], NULL, worker, NULL);
    }
    
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return 0;
}


