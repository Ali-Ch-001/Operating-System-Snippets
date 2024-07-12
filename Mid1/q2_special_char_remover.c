#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main() {
    char *fifo_file = "myfifo";

    int fd = open(fifo_file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    int fd_out = open(fifo_file, O_WRONLY);
    if (fd_out == -1) {
        perror("open");
        return 1;
    }

    char c;
    while (read(fd, &c, sizeof(c)) > 0) {
        if (isdigit(c)) {
            write(fd_out, &c, sizeof(c));
        }
    }

    close(fd);
    close(fd_out);

    system("./arranger");

    return 0;
}



