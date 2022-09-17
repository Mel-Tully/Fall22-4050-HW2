#include stdio.h
#include stdlib.h
//#include "MOM.h"

typedef struct listElem list;

struct listElem //idk if this will be necessary
{
    list * next;
    int length;
}

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

/*Do we need to also pass a pointer to an array for this to work properly? */
void MergeSort(int * array, int l, int r, int length) //Not sure if the length is needed
{
    if(l<r)
    {
        int mid = (l+r)/2;

        MergeSort(array, l, mid);
        MergeSort(array, mid, r);

        Merge(&array, l, mid, r);
    }

}

/* Merge method passes the pointer to the array so that it can modify the array itself */
void Merge(int ** arr, int l, int mid, int r) 
{
    int * array  = *arr; //dereferencing the pointer

    int * a1 = malloc(sizeof(int)* (mid-l +1));
    int * a2 = malloc(sizeof(int)* (r-mid));


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
        if(a1[i] <= a2[i])
        {
            array[i] = a1[i];
        }
        if(a2[i] < a1[i])
        {
            array[i] = a2[i];
        }
    }

}




