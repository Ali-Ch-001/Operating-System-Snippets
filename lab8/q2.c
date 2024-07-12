#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int sum = 0;

void *summation(void *arg) {
    int n = *(int*)arg;
    for (int i = 1; i <= n; i++) {
        sum += i;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    pthread_t thread;
    
    pthread_create(&thread, NULL, summation, &n);
    pthread_join(thread, NULL);
    
    printf("The summation of %d is %d.\n", n, sum);
    
    return 0;
}

