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

    
    pid_t pid = fork();

    if (pid < 0) {
        
        printf("Failed to create child process.\n");
        return 1;
    } else if (pid == 0) {
        
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
        printf("Sorted array by child process with ID %d:\n", getpid());
        for (int i = 0; i < 10; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        
        int status;
        waitpid(pid, &status, 0);
    }

    return 0;
}

