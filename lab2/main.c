#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include <ctime.h>
#include "header.h"




int main(int argc , char*argv[])
{

int n = argc-3;
int order = atoi(argv[argc-2]);

int position = atoi(argv[argc-1]);
int arr[n];
int i, k ,temp;
k = 1;

for(i = 0 ; i < n ; i++)
{
temp = atoi(argv[k]);
arr[i] = temp;
k++;
}


print(arr, n);
sort(arr, n , order);
findHighest(arr, n , position , order);



return 0;
}
