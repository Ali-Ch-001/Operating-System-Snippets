#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int compare_chars(const void *a, const void *b) {
    return (*(char *)a - *(char *)b);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char str[100];
    strcpy(str, argv[1]);
    int len = strlen(str);

    printf("Original string: %s\n", str);

    qsort(str, len, sizeof(char), compare_chars);

    printf("Sorted string: %s\n", str);

    return 0;
}

 
 
 



 
 

