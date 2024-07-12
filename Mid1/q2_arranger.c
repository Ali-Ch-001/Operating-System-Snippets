#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100

int compare_ints(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int data[BUFFER_SIZE];
    int num_ints_read = 0;

    
    int num;
    while (scanf("%d", &num) == 1 && num_ints_read < BUFFER_SIZE) {
        data[num_ints_read++] = num;
    }

    
    qsort(data, num_ints_read, sizeof(int), compare_ints);

    
    FILE *output_file = fopen("output.txt", "w");
    if (output_file == NULL) {
        perror("Failed to open output file");
        return 1;
    }

    for (int i = 0; i < num_ints_read; i++) {
        fprintf(output_file, "%d ", data[i]);
    }

    fclose(output_file);

    return 0;
}

