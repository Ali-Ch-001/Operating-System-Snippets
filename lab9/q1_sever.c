#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <fcntl.h>

#define SHM_SIZE 1024

int main(int argc, char* argv[]) {

    int shmid;
    key_t key;
    char *shm;
    int *data;
    int sum = 0;
    float average = 0.0;
    int count = 0;

    
    key = ftok("shmfile", 65);
    shmid = shmget(key, SHM_SIZE, 0666);
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }

    
    shm = shmat(shmid, NULL, 0);
    if(shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    
    data = (int *) shm;
    int n;
    while(1) {
        n = atoi(shm);
        if(n == -1) {
            break;
        }
        sum += n;
        count++;
        shm += strlen(shm) + 1;
    }
    average = (float)sum / count;

    printf("Sum = %d\n", sum);
    printf("Average = %.2f\n", average);

    
    shmdt(shm);

    
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}

