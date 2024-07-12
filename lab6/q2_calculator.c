#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_BUF 1024

int main()
{
    int fd;
    char *fifo = "/tmp/handler_fifo";
    char buf[MAX_BUF];
    int arr_size = 5;
    int arr[arr_size];

    
    fd = open(fifo, O_RDONLY);

    
    read(fd, arr, sizeof(int)*arr_size);

    
    close(fd);

    
    int sum = 0;
    for (int i = 0; i < arr_size; i++) {
        sum += arr[i];
    }

    
    fd = open(fifo, O_WRONLY);

    
    sprintf(buf, "%d", sum);
    write(fd, buf, strlen(buf)+1);

    
    close(fd);

    return 0;
}

