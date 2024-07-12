#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int arr[5][5];
    int i, j, sum_upper = 0, sum_lower = 0;
    
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            arr[i][j] = (rand() % 1000) + 1;
        }
    }
    
    
    pid_t pid = fork();
    
    if (pid < 0) { 
        fprintf(stderr, "Fork failed\n");
        return 1;
    }
    else if (pid == 0) { // Child process
        int freq[1000] = {0};
        printf("Child process ID: %d\n", getpid());
        printf("Parent process ID: %d\n", getppid());
        
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                freq[arr[i][j] - 1]++;
            }
        }
        
        printf("Frequencies:\n");
        for (i = 0; i < 1000; i++) {
            if (freq[i] > 0) {
                printf("NUMBER %d: FREQUENCY: %d\n", i + 1, freq[i]);
            }
        }
    }
    else { 
        printf("Parent process ID: %d\n", getpid());
        printf("Child process ID: %d\n", pid);
        
        for (i = 0; i < 5; i++) {
            for (j = 0; j < 5; j++) {
                if (i <= j) {
                    sum_upper += arr[i][j];
                }
                if (i >= j) {
                    sum_lower += arr[i][j];
                }
            }
        }
        
        printf("Upper triangular sum: %d\n", sum_upper);
        printf("Lower triangular sum: %d\n", sum_lower);
        
        wait(NULL); 
    }
    
    return 0;
}

