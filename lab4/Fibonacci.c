#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./Fibonacci n\n");
        return 1;
    }

    int n = atoi(argv[1]);
    int a = 0, b = 1, c, i;

    printf("Fibonacci series:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
    printf("\n");

    return 0;
}

