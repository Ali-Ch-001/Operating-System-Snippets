#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    

    char str[100];
    strcpy(str, argv[1]);
    int len = strlen(str);
    
    printf("\nYou entered: %s", str);

    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }

    printf("\nReversed string: %s\n", str);
    
    
    char *args[]={"./length",str,NULL};
    execv(args[0],args);

    return 0;
}

