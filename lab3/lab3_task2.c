#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    if (argc != 11) {
        printf("Please provide 10 integers as command line arguments.\n");
        return 1;
    }

   
    int arr[10];
    for (int i = 1; i < argc; i++) {
        arr[i-1] = atoi(argv[i]);
    }

   
    pid_t pid1 = fork();

    if (pid1 < 0) {
        
        printf("Failed to create first child process.\n");
        return 1;
    } else if (pid1 == 0) {
        
        printf("Child 1 process ID: %d\n", getpid());
        printf("Parent process ID: %d\n", getppid());
        int temp;
        for (int i = 0; i < 10; i++) {
            for (int j = i+1; j < 10; j++) {
                if (arr[j] < arr[i]) {
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
        printf("Sorted array by child 1 process:\n");
        for (int i = 0; i < 10; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        
        pid_t pid2 = fork();

        if (pid2 < 0) {
            
            printf("Failed to create second child process.\n");
            return 1;
        } else if (pid2 == 0) {
            
            printf("Child 2 process ID: %d\n", getpid());
            printf("Parent process ID: %d\n", getppid());
            int temp;
            for (int i = 0; i < 10; i++) {
                for (int j = i+1; j < 10; j++) {
                    if (arr[j] > arr[i]) {
                        temp = arr[i];
                        arr[i] = arr[j];
                        arr[j] = temp;
                    }
                }
            }
            printf("Sorted array by child 2 process:\n");
            for (int i = 0; i < 10; i++) {
                printf("%d ", arr[i]);
            }
            printf("\n");
        } else {
            
            int status;
            waitpid(pid1, &status, 0);
            waitpid(pid2, &status, 0);
        }
    }

    return 0;
}

