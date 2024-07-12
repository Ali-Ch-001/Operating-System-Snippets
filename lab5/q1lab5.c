#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <sys/wait.h>

#define BUFFER_SIZE 25

int main()
{
    int pipefd[2];
    char buffer[BUFFER_SIZE];
    pid_t pid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { 
        close(pipefd[1]); 

        int n = read(pipefd[0], buffer, BUFFER_SIZE);
        for (int i = 0; i < n; i++) {
            if (islower(buffer[i]))
                buffer[i] = toupper(buffer[i]);
            else if (isupper(buffer[i]))
                buffer[i] = tolower(buffer[i]);
        }
     
        printf("Child process received: %s\n", buffer);
        close(pipefd[0]);
    } else { 
    int status;
    printf("\nParent ID :%d",getppid());
        printf("\nChlid ID :%d",getpid());
        close(pipefd[0]); 

        char message[BUFFER_SIZE] = "Hi There";
        printf("\nParent process sent: %s\n", message);

        write(pipefd[1], message, BUFFER_SIZE);
        close(pipefd[1]);
        wait(&status);
        
    }

    return 0;
}

