// Zoe Spriggs, Melissa Tully
// CS 4050
// HW 2

#include <stdlib.h>
#include <stdio.h>
#include "input_error.h"

/** Struct Definitions **/

typedef struct node
{
    int number;
    struct node *next;
} Node_t;

typedef struct linked_list
{
    int size;
    Node_t * head;
} Linked_list_t;


/*** Function Delcarations ***/

/* Main-Specific Helper Functions */

void Main_Cleanup(FILE * fp, Linked_list_t * input, int * input_arr);

/* Linked List Helper Functions */

/// @brief Creates a new, empty linked list.
/// @return A pointer to an empty list with size of zero and a null head
Linked_list_t * New_Linked_List();

/// @brief Frees the linked_list, including all of its nodes.
/// @param list The list to be freed
void Free_Linked_List(Linked_list_t * list);

/// @brief Inserts the node value at the head of the given linked list.
/// @param list The list to insert the given value into
/// @param node_value a non-negative integer
void insert_at_head(Linked_list_t * list, int node_value);

/// @brief Turns a linked list of integers into an integer array.
/// @param input A nonzero linked list of integers
/// @return An integer array
int * List_to_Array(Linked_list_t * input);

/* Median of Medians Functions */

/// @brief Estimates the median using Median of Medians algorithm, then partitions the given array 
///         and recurses until the kth smallest element is discovered.
/// @param array The given array for which we need to find the kth smallest element
/// @param l The length of the array
/// @param k The element index for which the element value is to be obtained
/// @return An integer corresponding to the k-th smallest integer in the array
int MOM_Select(int * array, int l, int k);

/// @brief  Helper method for MOM_Select that organizes an array into three partitions, and returns 
///         the partition that k is in.
/// @param array The array that is to be partitioned
/// @param l The length of the array
/// @param k The element index for which the element value is to be obtained
/// @param L The linked list representing the left side of the array
/// @param R The linked list representing the right side of the array
/// @param p The (or actual) median value
/// @param median_occurences The number of occurences of p, ie, representing the middle of the array
/// @return An integer corresponding with the value of the k-th smallest integer in the list
int MOM_Helper(int * array, int l, int k, Linked_list_t * L,  Linked_list_t * R, int p, int * median_occurences); 

/// @brief Estimates the median of an array using the Median of Medians algorithm.
/// @param The array 
/// @param The size of the array
/// @return The estimate of the median of the array
int Find_Median(int * array, int size);

/// @brief Finds the median of a small subset of a larger array using Merge_Sort.
/// @param array The array that is to be sorted
/// @param l The leftmost index of the section of the array that is to be sorted.
/// @param r The rightmost index of the section of the array that is to be sorted  
/// @return The median of the array 
int Median_Of_Small_Array(int * array, int l, int r);

/// @brief Sorts an array of integers from lowest to highest value.
/// @param array The array that is to be sorted
/// @param left The leftmost index of the array that is to be sorted
/// @param right The rightmost index of the array that is to be sorted
void Merge_Sort(int * array, int left, int right); 

/// @brief Merges two sections of an array into one sorted array.
/// @param arr A pointer to an array
/// @param l The leftmost index of the first section
/// @param mid The middle (between l and r) index of the section of the array that is to be merged
///             i.e. the final index of the left array, and the index before the start of the right array
/// @param r The rightmost index of the second section 
void Merge(int ** arr, int l, int mid, int r); 

int main(int argc, char *argv[])
{
    char last_line[20]; //last read line from text file input
    int which_smallest; //x-th small number to return, based on the first line
    int last_value; //most recent integer read from input file, excuding which_smallest
    int return_value; //the x-th smallest number, based on the input file

    // Check for correct number of command line arguements
    if (argc != 2)
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }

    // Open file
    FILE * fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        exit(INPUT_FILE_FAILED_TO_OPEN);
    }

    // Find and store x, where x is the x-th smallest number in the list of integers
    if (fgets(last_line, 20, fp) == NULL)
    {
        exit(PARSING_ERROR_EMPTY_FILE);
    }

    which_smallest = strtol(last_line, NULL, 10);
    
    if (which_smallest <= 0)
    {
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }

    // Generate linked list of the remainder of the file
    Linked_list_t * input = New_Linked_List(); //input will be in reverse order of the text file

    while (1)
    {
        if (fgets(last_line, 20, fp) == NULL)
        {
            break; //break if empty line
        }

        last_value = strtol(last_line, NULL, 10);

        if (last_value <= 0)
        {
            Main_Cleanup(fp, input, NULL);
            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
        }

        insert_at_head(input, last_value);
    }

    if (which_smallest < input->size) //if valid k
    {
        // Copy linked_list into array
        int * input_arr = malloc((size_t)(input->size * sizeof(int)));
        Node_t * current_node = input->head;
        for (size_t i = 0; i < input->size; i++)
        {
            input_arr[i] = current_node->number;
            current_node = current_node->next;
        }

        // Run Median of Medians
        return_value = MOM_Select(input_arr, input->size, which_smallest);

        Main_Cleanup(fp, input, input_arr);
    }
    else
    {
        Main_Cleanup(fp, input, NULL);
        return_value = -1;
    }

    printf("%i\n", return_value);
}


/*** Function Definitions ***/

/* Main-Specific Helper Functions */

void Main_Cleanup(FILE * fp, Linked_list_t * input, int * input_arr)
{
    Free_Linked_List(input);
    free(input_arr); //will sometimes attempt to free a null pointer
    if (fclose(fp) == EOF)
    {
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
}

/* Linked List Helper Functions */

Linked_list_t * New_Linked_List()
{
    Linked_list_t * input = malloc(sizeof(Linked_list_t));
    input->head = NULL;
    input->size = 0;
    return input;
}

void Free_Linked_List(Linked_list_t * list)
{
    Node_t * new_head;
    while (list->size > 0)
    {
        new_head = list->head->next;
        free(list->head);
        list->head = new_head;
        list->size = list->size - 1;
    }

    free(list);
}

void insert_at_head(Linked_list_t * list, int node_value)
{
    Node_t * new_node = malloc(sizeof(Node_t));
    new_node->next = list->head;
    new_node->number = node_value;
    list->head = new_node;
    list->size = list->size + 1;
}

int * List_to_Array(Linked_list_t * input)
{
    int * arr = malloc((size_t)(input->size * sizeof(int)));
    Node_t * current_node = input->head;
    for (size_t i = 0; i < input->size; i++)
    {
        arr[i] = current_node->number;
        current_node = current_node->next;
    }

    return arr;
}

/* Median of Medians Functions */

int MOM_Select(int * array, int l, int k) 
{
    int result;
    
    if(l < 50)
    {
        Merge_Sort(array, 0, l-1);
        return array[k-1];
    }

    Linked_list_t * L = New_Linked_List();
    Linked_list_t * R = New_Linked_List();
    int median = Find_Median(array, l);
    int median_occurences = 0;

    result = MOM_Helper(array, l, k, L, R, median, &median_occurences);

    Free_Linked_List(L);
    Free_Linked_List(R);

    return result;
}

int MOM_Helper(int * array, int l, int k, Linked_list_t * L,  Linked_list_t * R, int p, int * median_occurences) 
{
    // Sort array elements into L and R
    for(int i = 0; i < l; i++)
    {
        if(array[i] < p)
        {
            insert_at_head(L, array[i]);
        }
        else if(array[i] == p)
        {
            *median_occurences = *median_occurences + 1;
        }
        else 
        {
            insert_at_head(R, array[i]);
        }
    }

    if(k <= L->size)
    {
        return MOM_Select(List_to_Array(L), L->size, k);
    }
    else if(k > (L->size + *median_occurences))
    {
        return MOM_Select(List_to_Array(R), R->size, k - (L->size + *median_occurences));
    }
    else
        return p;
}

int Find_Median(int * array, int size)
{
    int median; //the median to be returned

    if(size < 50)
    {  
        median = Median_Of_Small_Array(array, 0, size-1);
        return median;
    }

    int notDivBy5 = 1; //is array size divisible by 5 (default: true)
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

        leftValue = i * 5;
        rightValue = leftValue + smallSize - 1;

        //Sorts and determines the median of groups of 5 in place
        medians[i] = Median_Of_Small_Array(array, leftValue, rightValue);
    }

    median = Find_Median(medians, numMedians);
    
    free(medians);

    return median;
}

int Median_Of_Small_Array(int * array, int l, int r)
{
    Merge_Sort(array, l, r);
    int midIndex = (r+l)/2;
    return array[midIndex];
}

/* Sorts an array using a recursive divide and conquer method. 
    Parameters are an integer array, the leftmost index of the array to be sorted, 
    and the rightmost index of the array.  */
void Merge_Sort(int * array, int left, int right)
{
    if((right-left) >= 1) // check paramaters
    {
        int mid = (left+right)/2;
        Merge_Sort(array, left, mid);
        Merge_Sort(array, mid+1, right);
        Merge(&array, left, mid, right);
    }
}

/*  Merges two arrays in sorted order (helper method for Merge_Sort)
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

