#include <stdio.h>


void print(int arr[],int size)
{

int i;
for(i=0;i<size;i++)
{
printf(" %d ",arr[i]);
}
printf("\n");
}

void sort(int arr[], int n ,int order)
{

if (order == 1)
{

int i, j;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] > arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    
    
 }
 
 else if(order == 0)
 {
 
 int i, j;
    for (i = 0; i < n-1; i++)
    {
        for (j = 0; j < n-i-1; j++)
        {
            if (arr[j] < arr[j+1])
            {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
    
    
 
 }
 else
 {
 printf("\nERROR WRONG CHOICE\n");
 }

print(arr,n);

}



void findHighest(int arr[], int n , int position , int order)
{
if(order == 1)
{
printf("\n The %d highest value is %d ",position,arr[n-position]);
}
else if(order == 0)
{
printf("\n The %d highest value is %d ",position,arr[position-1]);
}

else
{
printf("\nERROR WRONG CHOICE\n");
}

}


