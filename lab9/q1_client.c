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

    int fd, shmid;
    key_t key;
    char *shm;
    char buf[100];

    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    
    key = ftok("shmfile", 65);
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if(shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // attach shared memory segment
    shm = shmat(shmid, NULL, 0);
    if(shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }

    
    fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        perror("open");
        exit(1);
    }

    
    while(read(fd, buf, sizeof(buf)) > 0) {
        char *ptr = strtok(buf, " \n");
        while(ptr != NULL) {
            strncpy(shm, ptr, strlen(ptr));
            shm += strlen(ptr) + 1;
            ptr = strtok(NULL, " \n");
        }
    }

   
    strncpy(shm, "-1", 2);

    
    shmdt(shm);

    
    close(fd);

    return 0;
}

