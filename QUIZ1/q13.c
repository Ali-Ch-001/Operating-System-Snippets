#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void lap_timer(int lap_time, int num_laps);
void total_timer(int lap_time, int num_laps);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <lap_time> <num_laps>\n", argv[0]);
        return 1;
    }
    
    int lap_time = atoi(argv[1]);
    int num_laps = atoi(argv[2]);
    
    pid_t pid = fork();
    
    if (pid < 0) {
        printf("Failed to create child process\n");
        return 1;
    } else if (pid == 0) {
        lap_timer(lap_time, num_laps);
    } else {
        total_timer(lap_time, num_laps);
    }
    
    return 0;
}

void lap_timer(int lap_time, int num_laps) {
    int lap_count = 0;
    
    while (lap_count < num_laps) {
        printf("Lap %d time: %d seconds\n", lap_count + 1, lap_time);
        lap_count++;
        sleep(lap_time);
        
    }
    
    exit(0);
}

void total_timer(int lap_time, int num_laps) {
    int total_time = 0;
    int status;
    
    while (wait(&status) > 0) {
        total_time += WEXITSTATUS(status);
        
        
    }
    total_time = lap_time*num_laps;
    printf("Total time: %d seconds\n", total_time);
}


