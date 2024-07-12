#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void create_child(int id, int num_processes) {
    printf("Child process %d: ID=%d, parent ID=%d\n", id, getpid(), getppid());
    if (id == num_processes) {
        exit(0);
    }
    pid_t pid = fork();
    if (pid < 0) {
        printf("Failed to create child process %d.\n", id+1);
        exit(1);
    } else if (pid == 0) {
        create_child(id+1, num_processes);
    }
    wait(NULL);
}

int main(int argc, char *argv[]) {
    
    if (argc != 2) {
        printf("Please provide a single integer between 1 and 10 as command line argument.\n");
        return 1;
    }
    int num_processes = atoi(argv[1]);
    if (num_processes < 1 || num_processes > 10) {
        printf("Please provide a single integer between 1 and 10 as command line argument.\n");
        return 1;
    }

 
    pid_t pid = fork();
    if (pid < 0) {
        printf("Failed to create child process 1.\n");
        return 1;
    } else if (pid == 0) {
        create_child(1, num_processes);
    }
    wait(NULL);

    return 0;
}


