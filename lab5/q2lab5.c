#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25

int main()
{
    int pipefd1[2]; 
    int pipefd2[2]; 
    int num_elements = 5; 
    int arr[num_elements]; 
    int sum = 0; 
    pid_t pid;
    int status;

  
    if (pipe(pipefd1) == -1 || pipe(pipefd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        close(pipefd1[1]); 
        close(pipefd2[0]); 

        int size = sizeof(int) * num_elements;
        int n = read(pipefd1[0], arr, size); 
        for (int i = 0; i < num_elements; i++) {
            sum += arr[i];
        }
        write(pipefd2[1], &sum, sizeof(sum));
        close(pipefd1[0]);
        close(pipefd2[1]);
        exit(EXIT_SUCCESS);
    } else { 
        close(pipefd1[0]); 
        close(pipefd2[1]); 

        int x;
        for (int i = 0; i < num_elements; i++) 
        {
           
            arr[i] = rand()%500;
        }

        int size = sizeof(int) * num_elements;
        write(pipefd1[1], arr, size); 
        close(pipefd1[1]);

        int n = read(pipefd2[0], &sum, sizeof(sum)); 
        printf("Sum Recevied from child: %d\n", sum);
        close(pipefd2[0]);

        wait(&status);
        
    }

    return 0;
}

