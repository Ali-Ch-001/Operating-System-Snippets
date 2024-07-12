#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

// Initialize semaphores and mutex
sem_t semaphore1, semaphore2;
pthread_mutex_t mutex;

// Declare variables
int X, Y, Z, W, W1, X1, Y1, Z1, S1, S2;

// Define Thread T1
void *T1(void *arg) {
    // Input X and Y
    printf("Enter X and Y:\n");
    scanf("%d %d", &X, &Y);
    
    // Compute X1 (critical section)
    pthread_mutex_lock(&mutex);
    X1 = Z + 2;
    pthread_mutex_unlock(&mutex);

    // Wait for semaphore2 to be signaled by Thread T2
    sem_wait(&semaphore2);

    // Compute Y1 (critical section)
    pthread_mutex_lock(&mutex);
    Y1 = Z1 * 5;
    pthread_mutex_unlock(&mutex);

    // Signal semaphore1 to wake up Thread T2
    sem_post(&semaphore1);

    // Wait for semaphore2 to be signaled by Thread T2
    sem_wait(&semaphore2);

    // Compute S1 (critical section)
    pthread_mutex_lock(&mutex);
    S1 = X1 + Y1;
    pthread_mutex_unlock(&mutex);

    // Signal semaphore2 to wake up Thread T2
    sem_post(&semaphore1);

    // Print S1
    printf("S1=%d\n", S1);
    
    
    pthread_exit(NULL);
}

// Define Thread T2
void *T2(void *arg) {
    // Input W and Z
    printf("Enter W and Z:\n");
    scanf("%d %d", &W, &Z);
    
    // Compute Z1 (critical section)
    pthread_mutex_lock(&mutex);
    X1 = Z + 2;
    Z1 = X1 * 2;
    pthread_mutex_unlock(&mutex);

    // Signal semaphore2 to wake up Thread T1
    sem_post(&semaphore2);

    // Wait for semaphore1 to be signaled by Thread T1
    sem_wait(&semaphore1);

    // Compute W1 (critical section)
    pthread_mutex_lock(&mutex);
    Y1 = Z1 * 5;
    W1 = Y1 + 5;
    pthread_mutex_unlock(&mutex);

    // Signal semaphore2 to wake up Thread T1
    sem_post(&semaphore2);

    // Wait for semaphore1 to be signaled by Thread T1
    sem_wait(&semaphore1);

    // Compute S2 (critical section)
    pthread_mutex_lock(&mutex);
    S2 = Z1 + W1;
    pthread_mutex_unlock(&mutex);

    // Print S2
    printf("S2=%d\n", S2);
    
    pthread_exit(NULL);
}



int main() {
    // Initialize semaphores and mutex
    sem_init(&semaphore1, 0, 0);
    sem_init(&semaphore2, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_t t1, t2;
    pthread_create(&t1, NULL, T1, NULL);
    pthread_create(&t2, NULL, T2, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy semaphores and mutex
    sem_destroy(&semaphore1);
    sem_destroy(&semaphore2);
    pthread_mutex_destroy(&mutex);

    return 0;
}

