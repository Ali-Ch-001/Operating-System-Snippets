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


    fd = open(fifo, O_RDONLY);


    read(fd, buf, MAX_BUF);


    sscanf(buf, "%c %d %d", &operator, &operand1, &operand2);


    int result;
    switch (operator) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        default:
            printf("Invalid operator\n");
            return 1;
    }


    close(fd);
    

    fd = open(fifo, O_WRONLY);


    sprintf(buf, "%d", result);
    write(fd, buf, strlen(buf)+1);


    close(fd);

    return 0;
}

