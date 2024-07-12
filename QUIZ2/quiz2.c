/*

q1

FASTEST TO SLOWEST

thrid
second
first

Third Attempt: Solving the remaining n/2 matrix using two threads, the first thread solving the first n/2 matrix.
With this method, the task is split into two threads that can operate concurrently on different cores or processors. The entire execution time should be faster with parallelism than it would be using a single thread.

Second Attempt: Executing the multiplication across n*n threads.
This method computes each element of the final matrix using a different thread. Although it increases parallelism, the overhead associated with managing a large number of threads can have a negative effect on performance. As the number of threads rises, load balancing and thread synchronisation both become more difficult.


First attempt: performing the multiplication on a single thread.
This method executes the complete matrix multiplication in a single thread. Due to this lack of parallelism, it is unable to fully utilise contemporary multi-core computers. As a result, as compared to the threaded techniques, it is anticipated to have the slowest execution time. 

*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10


void* findDuplicate(void* args) {
    int* arr = (int*)args;
    int n = ARRAY_SIZE;

   
    int Result = 0;
    for (int i = 0; i < n; i++) {
        Result ^= arr[i];
    }

   
    for (int i = 1; i <= 9; i++) {
        Result ^= i;
    }

    int* result = malloc(sizeof(int));
    *result = Result;
    pthread_exit(result);
}

int main() {
    int arr[ARRAY_SIZE];

    
    printf("Enter values between 1 and 9 (one value repeated): \n");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("Enter value for index %d: ", i);
        scanf("%d", &arr[i]);
        
        if (arr[i] < 1 || arr[i] > 9) {
            printf("Invalid input! Please enter a value between 1 and 9.\n");
            exit(1);
        }
    }

    pthread_t tid;
    pthread_create(&tid, NULL, findDuplicate, (void*)arr);


    int* result;
    pthread_join(tid, (void**)&result);

    printf("Duplicate number found: %d\n", *result);

    free(result);

    return 0;
}




