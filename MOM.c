#include <stdio.h>
#include <stdlib.h>
//#include "MOM.h"


void Merge(int ** arr, int l, int mid, int r);

//need to update method types
void Partition(int * array, int p) //do we need length
{

}

int * readInValues()
{
    //open file
    //scan file to obtain number of elements (or just put elems into a linked list)
    //malloc array space
    //iterate thru file again to make an array
    //set length val to be the total length of the array

}

//need to update method types
void MOMSelect(int * array, int k, int l) //l is for length
{
    

}

//temp method for testing
void printArray(int * array, int length)
{
    for(int i = 0; i < length; i++)
    {
        printf("%i ", array[i]);
    }
    printf("\n");
}

/*Do we need to also pass a pointer to an array for this to work properly? */
void MergeSort(int * array, int l, int r, int length) //Not sure if the length is needed
{
   // int mid = (l+r)/2;

    if((l<r))
    {
        int mid = (l+r)/2;

        if((mid - l) > 1)
            MergeSort(array, l, mid, 10);

        if((r - mid) > 1)
            MergeSort(array, mid, r, 10);

        Merge(&array, l, mid, r);
    }

}

/* Merge method passes the pointer to the array so that it can modify the array itself */
void Merge(int ** arr, int l, int mid, int r) 
{

    printf("merging\n");

    int * array  = *arr; //dereferencing the pointer
    int l1 = mid -l + 1;
    int l2 = r-mid;

    int * a1 = (int *)malloc(sizeof(int) * (l1));
    int * a2 = (int *)malloc(sizeof(int) * (l2));

    for(int i = 0; i <= mid; i++)
    {
        a1[i] = array[i];
    }

    for(int i = mid+1; i < r; i++)
    {
        a2[i] = array[i];
    }

    for(int i = l; i < r; i++)
    {
        printf("im doing something\n");
        if(a1[i] <= a2[i])
        {
            array[i] = a1[i];
        }
        if(a2[i] < a1[i])
        {
            array[i] = a2[i];
        }
    }

    free(a1);
    free(a2);

}




