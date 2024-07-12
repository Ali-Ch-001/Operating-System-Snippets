#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>



int main(int argc, char *argv[]) 
{
    if (argc < 2) 
    {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }
    
    
    
 char *name = argv[1];
 char str[100];
 strcpy(str, argv[1]);
    int length = 0;
    
    while (*name != '\0') {
        length++;
        name++;
    }
    
    printf("Length of %s is %d\n", argv[1], length);
    
    
    char *args[]={"./sort",str,NULL};
    execv(args[0],args);
  
    
}
