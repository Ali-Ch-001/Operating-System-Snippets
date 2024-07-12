

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    char *input_file = argv[1];
    char *fifo_file = "myfifo";

    mkfifo(fifo_file, 0666);

    int fd = open(fifo_file, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    FILE *fp = fopen(input_file, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int num;
    while (fscanf(fp, "%d", &num) == 1) {
        char buf[20];
        sprintf(buf, "%d", num);
        write(fd, buf, sizeof(buf));
    }

    fclose(fp);
    close(fd);

    return 0;
}

