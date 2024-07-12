#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

volatile int laps_completed = 0 , num_laps = 0;
pid_t child_pid;
time_t start_time;

void child_handler(int sig) {
    laps_completed++;
    printf("Lap %d completed\n", laps_completed);
    if (laps_completed == num_laps) {
        kill(child_pid, SIGINT);
    }
}

void death_handler(int sig) {
    int status;
    waitpid(child_pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Child exited with status %d\n", WEXITSTATUS(status));
    } else {
        printf("Child terminated abnormally\n");
    }
    printf("Total time: %d seconds.\n", (int) (time(NULL) - start_time));
    exit(0);
}

void child_exit_handler(int sig) {
    printf("Received SIGCHLD\n");
}

int main() {
    int lap_time;
    printf("Enter the number of laps: ");
    scanf("%d", &num_laps);
    printf("Enter the lap time (in seconds): ");
    scanf("%d", &lap_time);

    signal(SIGUSR1, child_handler);
    signal(SIGINT, death_handler);
    signal(SIGCHLD, child_exit_handler);

    start_time = time(NULL);
    child_pid = fork();
    if (child_pid == 0) {
        int i;
        for (i = 0; i < num_laps; i++) {
            sleep(lap_time);
            kill(getppid(), SIGUSR1);
        }
        exit(0);
    } else if (child_pid > 0) {
        int status;
        while (1) {
            if (waitpid(child_pid, &status, WNOHANG) != 0) {
                 
                break;
            }
            sleep(1);
        }
    } else {
        perror("fork");
        exit(1);
    }

    return 0;
}

