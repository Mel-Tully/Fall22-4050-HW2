#include <stdio.h>
#include <stdlib.h>
#include "MOM.c"

int main(void)
{
    int array[] = {0, 4, 3, 1, 78, 3, 92, 1, 7, 10};
    int length = 10;

    MergeSort(array, 0, 9, 10);

    printf("why doesnt it come back\n");

    for(int i = 0; i < length; i++)
    {
        printf(array[i] + " ");
    }

    return(0);
}