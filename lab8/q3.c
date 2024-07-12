#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int *fibonacci_series; 
int series_length; 
int even_count = 0; 
int odd_count = 0; 
int sum = 0; 

void *fibonacciGenerator(void *arg) {
    int n = *(int*)arg;
    fibonacci_series = (int*)malloc(n * sizeof(int));
    fibonacci_series[0] = 0;
    fibonacci_series[1] = 1;
    for (int i = 2; i < n; i++) {
        fibonacci_series[i] = fibonacci_series[i-1] + fibonacci_series[i-2];
    }
    pthread_exit(NULL);
}

void *evenCounter(void *arg) {
    for (int i = 0; i < series_length; i++) {
        if (fibonacci_series[i] % 2 == 0) {
            even_count++;
        }
    }
    pthread_exit(NULL);
}

void *oddCounter(void *arg) {
    for (int i = 0; i < series_length; i++) {
        if (fibonacci_series[i] % 2 != 0) {
            odd_count++;
        }
    }
    pthread_exit(NULL);
}

void *sumCalculator(void *arg) {
    for (int i = 0; i < series_length; i++) {
        sum += fibonacci_series[i];
    }
    FILE *fp;
    fp = fopen("sum.txt", "w");
    fprintf(fp, "%d\n", sum);
    fclose(fp);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    series_length = n;
    pthread_t fibonacci_thread, even_thread, odd_thread, sum_thread;
    
    pthread_create(&fibonacci_thread, NULL, fibonacciGenerator, &n);
    pthread_join(fibonacci_thread, NULL);
    
    pthread_create(&even_thread, NULL, evenCounter, NULL);
    pthread_join(even_thread, NULL);
    
    pthread_create(&odd_thread, NULL, oddCounter, NULL);
    pthread_join(odd_thread, NULL);
    
    pthread_create(&sum_thread, NULL, sumCalculator, NULL);
    pthread_join(sum_thread, NULL);
    
    printf("Fibonacci Series: ");
    for (int i = 0; i < series_length; i++) {
        printf("%d ", fibonacci_series[i]);
    }
    printf("\n");
    printf("Even Count: %d\n", even_count);
    printf("Odd Count: %d\n", odd_count);
    printf("Sum: %d\n", sum);
    return 0;
}

