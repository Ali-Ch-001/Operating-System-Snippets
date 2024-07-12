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
    char *fifo = "/tmp/myfifo";
    char buf[MAX_BUF];
    char operator;
    int operand1, operand2;


    mkfifo(fifo, 0666);


    fd = open(fifo, O_WRONLY);


    printf("Enter operator and two operands: ");
    scanf("%c %d %d", &operator, &operand1, &operand2);


    sprintf(buf, "%c %d %d", operator, operand1, operand2);
    write(fd, buf, strlen(buf)+1);


    close(fd);


    fd = open(fifo, O_RDONLY);


    read(fd, buf, MAX_BUF);


    int result = atoi(buf);


    printf("Result: %d\n", result);


    close(fd);


    unlink(fifo);

    return 0;
}

