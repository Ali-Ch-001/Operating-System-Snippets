#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char *fifo = "handler_fifo";
    char buf[MAX_BUF];

    
    mkfifo(fifo, 0666);

    
    fd = open(fifo, O_WRONLY);

   
    char message[] = "Hi There";
    write(fd, message, strlen(message)+1);

    
    close(fd);


    fd = open(fifo, O_RDONLY);

    
    read(fd, buf, MAX_BUF);

    
    printf("Received: %s\n", buf);

    
    close(fd);

   
    unlink(fifo);

    return 0;
}

