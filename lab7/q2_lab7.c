#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    int fd_in, fd_out;
    
    if (argc != 3) {
        fprintf(stderr, "Usage: %s input_file output_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    fd_in = open(argv[1], O_RDONLY);
    
    if (fd_in == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    fd_out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (fd_out == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd_in, 0) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    
    if (dup2(fd_out, 1) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    
    if (execlp("cat", "cat", NULL) == -1) {
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    
    return EXIT_SUCCESS;
}

