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
    int arr[] = {1, 2, 3, 4, 5};
    int arr_size = sizeof(arr)/sizeof(int);

    
    mkfifo(fifo, 0666);


    fd = open(fifo, O_WRONLY);


    write(fd, arr, sizeof(int)*arr_size);


    close(fd);


    sleep(2);


    fd = open(fifo, O_RDONLY);


    read(fd, buf, MAX_BUF);


    int sum = atoi(buf);


    printf("Sum: %d\n", sum);


    close(fd);


    unlink(fifo);

    return 0;
}

