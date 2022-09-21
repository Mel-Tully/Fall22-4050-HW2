#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


/// @brief  Helper method for MOMSelect that organizes an array into three partitions, and returns 
///         partition that k is in
/// @param array The array that is to be partitioned
/// @param l The length of the array
/// @param k The element index for which the element value is to be obtained
/// @param L The linked list representing the left side of the array
/// @param R The linked list representing the right side of the array
/// @param p The (or actual) median value
/// @param median_occurences The number of occurences of p, ie, representing the middle of the array
/// @return An integer corresponding with the value of the kth smallest integer in the list
int MOMHelper(int * array, int l, int k, Linked_list_t * L,  Linked_list_t * R, int p, int * median_occurences); 

/// @brief Estimates the median using Median of Medians algorithm, then partitions the given array 
///         and recurses until the kth smallest element is discovered
/// @param array The given array for which we need to find the kth smallest element
/// @param l The length of the array
/// @param k The element iundex for which the element value is to be obtained
/// @return An integer corresponging to the kth smallest integer in the array.
int MOMSelect(int * array, int l, int k);

/// @brief Estimates the median of an array using the Median of Medians algorithm
/// @param The array 
/// @param The size of the array
/// @return The estimate of the median of the array
int FindMedian(int * array, int size);

/// @brief Finds the median of a small subset of a larger array by sorting it using MergeSort
/// @param array The array that is to be sorted
/// @param l The leftmost index of the section of the array that is to be sorted.
/// @param r The rightmost index of the section of the array that is to be sorted  
/// @return The median of the array 
int MedianOfSmallArray(int * array, int l, int r);

/// @brief Sorts an array of integers from lowest to highest value
/// @param array The array that is to be sorted
/// @param l The leftmost index of the array that is to be sorted.
/// @param r The rightmost index of the array that is to be sorted
void MergeSort(int * array, int l, int r); 

/// @brief Merges two sections of an array into one sorted array.
/// @param arr A pointer to an array
/// @param l The leftmost index of the first section
/// @param mid The middle (between l and r) index of the section of the array that is to be merged
///             i.e. the final index of the left array, and the index before the start of the right array
/// @param r The rightmost index of the second section 
void Merge(int ** arr, int l, int mid, int r); 
