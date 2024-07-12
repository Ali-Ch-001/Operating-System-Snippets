#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <first_name>\n", argv[0]);
        return 1;
    }
    
    char *name = argv[1];
    int length = 0;
    
    while (*name != '\0') {
        length++;
        name++;
    }
    
    printf("Length of %s is %d\n", argv[1], length);
    
    return 0;
}

