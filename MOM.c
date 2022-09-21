#include <stdio.h>
#include <stdlib.h>
#include "MOM.h"
//#include "linked_list.h"

int MOMHelper(int * array, int l, int k, Linked_list_t * L,  Linked_list_t * R, int p, int * median_occurences) 
{
    for(int i = 0; i < l; i++)
    {
        if(array[i] < p)
        {
            insert_at_head(L, array[i]);
        }
        else if(array[i] == p)
        {
            *median_occurences++;
        }
        else 
        {
            insert_at_head(R, array[i]);
        }
    }

    if(k <= L->size)
    {
        return MOMSelect(list_to_array(L), L->size, k);
    }
    else if(k > (L->size + median_occurences))
    {
        return MOMSelect(list_to_array(R), R->size, k);
    }
    else
        return p;
}

int MOMSelect(int * array, int l, int k) 
{
    if(l < 50)
    {
        MergeSort(array, 0, l-1);
        return array[k];
    }

    Linked_list_t * L = new_linked_list();
    Linked_list_t * R = new_linked_list();
    int median = findMedian(array, l);
    int median_occurences = 0;

    return MOMHelper(array, l, k, L, R, median, &median_occurences);
}

/* There's a memory leak that needs to be fixed here, I'm not sure how to keep the important values
and also free medians array */
int FindMedian(int * array, int size)
{
    if(size < 50)
    {  
        return MedianOfSmallArray(array, 0, size-1);
    }

    int notDivBy5 = 1;
    int numMedians = 0;

    if(size%5 == 0)
    {
        notDivBy5 = 0;
    }

    int smallSize = 5;
    int leftValue = 0;
    int rightValue = 0;
    numMedians = size/5 + notDivBy5;
    
    //Creates a new array that the median of each group of 5 will be stored in
    int * medians = (int *)malloc(numMedians * sizeof(int));
    for(int i = 0; i < numMedians; i++)
    {
        if(i == (numMedians - 1) && notDivBy5)
        {
            smallSize = size % 5;
        }

        leftValue = i * smallSize;
        rightValue = leftValue + smallSize - 1;


        //Sorts and determines the median of groups of 5 in place
        medians[i] = MedianOfSmallArray(array, leftValue, rightValue-1);
    }

    return FindMedian(medians, numMedians);
}

int MedianOfSmallArray(int * array, int l, int r)
{
    MergeSort(array, l, r);
    int midIndex = (r+l)/2 + 1;

    return array[midIndex];
}

/* Sorts an array using a recursive divide and conquer method. 
    Parameters are an integer array, the leftmost index of the array to be sorted, 
    and the rightmost index of the array.  */
void MergeSort(int * array, int l, int r) //Not sure if the length is needed
{
    if((r-l) >= 1)
    {
        int mid = (l+r)/2;

        MergeSort(array, l, mid);
        MergeSort(array, mid+1, r);
        

        Merge(&array, l, mid, r);
    }

}

/*  Merges two arrays in sorted order (helper method for MergeSort)
    Merge method takes the pointer to the array so that it can modify the array itself */
void Merge(int ** arr, int l, int mid, int r) 
{
    //leftIndex and rightIndex keep track of the current indeces being merged
    int leftIndex = 0; 
    int rightIndex = 0;

    if(l == r)
    {
        return;
    }

    int * array  = *arr; 
    int l1 = (mid - l + 1) ;

    int l2 = r-mid;

    int * a1 = (int *)malloc(sizeof(int) * (l1));
    int * a2 = (int *)malloc(sizeof(int) * (l2));

    for(int i = 0; i < l1; i++)
    {
        a1[i] = array[l+i];
    }

    for(int i = 0; i < l2; i++)
    {
        a2[i] = array[mid+i+1];
    }

    leftIndex = 0;
    rightIndex = 0;

    for(int i = l; i <= r; i++)
    {
        if(leftIndex < l1 && rightIndex < l2)
        {
            if(a1[leftIndex] <= a2[rightIndex])
            {
                array[i] = a1[leftIndex];
                leftIndex++;
            }
            else if(a2[rightIndex] < a1[leftIndex])
            {
                array[i] = a2[rightIndex];
                rightIndex++;

            }
        }
        else if (leftIndex >= l1)
        {
            array[i] = a2[rightIndex];
            rightIndex++;
        }
        else if (rightIndex >= l2)
        {
            array[i] = a1[leftIndex];
            leftIndex++;
        }
    }
    free(a1);
    free(a2);

}




