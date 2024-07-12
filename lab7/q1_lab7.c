#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    int fd_in, fd_out;
    ssize_t nread;
    char buf[4096];

    if (argc < 2) {
        printf("Usage: %s input.txt\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd_out == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (dup2(fd_out, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }

    while ((nread = read(fd_in, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, nread) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (nread == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    if (close(fd_in) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    if (close(fd_out) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}

