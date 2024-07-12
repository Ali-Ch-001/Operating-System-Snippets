#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%s", str);

    printf("You entered: %s", str);
    
    sleep(2);
    
    char *args[]={"./reverse",str,NULL};
    execv(args[0],args);

    return 0;
}

