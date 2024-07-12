#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create child process
    pid = fork();

    if (pid == 0) {
        // Child process
        
        // Define arguments for Fibonacci program
        char *args[] = {"./Fibonacci", "10", NULL};
        
        // Replace child process with Fibonacci program
        execv(args[0], args);
    } else if (pid > 0) {
        // Parent process
        
        // Wait for child to finish executing
        wait(&status);
        
        // Print status message
        printf("Child process finished executing.\n");
    } else {
        // Fork failed
        printf("Error: Fork failed.\n");
        return 1;
    }
    
    return 0;
}

