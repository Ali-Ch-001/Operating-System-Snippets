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

    
    fd = open(fifo, O_RDONLY);

    
    read(fd, buf, MAX_BUF);

    
    for (int i = 0; i < strlen(buf); i++) {
        if (buf[i] >= 'a' && buf[i] <= 'z') {
            buf[i] = buf[i] - 32;
        } else if (buf[i] >= 'A' && buf[i] <= 'Z') {
            buf[i] = buf[i] + 32;
        }
    }

   
    close(fd);

    
    fd = open(fifo, O_WRONLY);

   
    write(fd, buf, strlen(buf)+1);

    
    close(fd);

    return 0;
}

