// Zoe Spriggs, Melissa Tully
// CS 4050
// HW 2

#include <stdlib.h>
#include <stdio.h>
#include "input_error.h"
#include "linked_list.h"
#include "MOM.h"

void cleanup(FILE * fp, Linked_list_t * input, int * input_arr);

void cleanup(FILE * fp, Linked_list_t * input, int * input_arr)
{
    free_linked_list(input);
    free(input_arr); //will sometimes attempt to free a null pointer
    if (fclose(fp) == EOF)
    {
        printf("INPUT_FILE_FAILED_TO_CLOSE\n");
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
}

int main(int argc, char *argv[])
{
    char last_line[20]; //last read line from text file input
    int which_smallest; //x-th small number to return, based on the first line
    int last_value; //most recent integer read from input file, excuding which_smallest
    int return_value;

    // Check for correct number of command line arguements
    if (argc != 2)
    {
        printf("INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS\n");
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }

    // Open file
    FILE * fp = fopen(argv[1], "r");
    if (fp == NULL)
    {
        printf("INPUT_FILE_FAILED_TO_OPEN\n");
        exit(INPUT_FILE_FAILED_TO_OPEN);
    }

    // Find and store x, where x is the x-th smallest number in the list of integers

    if (fgets(last_line, 20, fp) == NULL)
    {
        printf("PARSING_ERROR_EMPTY_FILE\n");
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    printf("%s", last_line);
    which_smallest = strtol(last_line, NULL, 20);
    
    if (which_smallest <= 0)
    {
        printf("PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED\n");
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }

    // Generate linked list of the remainder of the file
    Linked_list_t * input = new_linked_list();

    while (1)
    {
        if (fgets(last_line, 20, fp) == NULL) break; //break if empty line
        last_value = strtol(last_line, NULL, 10);

        if (last_value <= 0)
        {
            cleanup(fp, input, NULL);
            printf("PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED\n");
            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
        }

        insert_at_head(input, last_value);
    }

    // Copy linked_list into array;
    int * input_arr = malloc((size_t)(input->size * sizeof(int)));
    Node_t * current_node = input->head;
    for (size_t i = 0; i < input->size; i++)
    {
        input_arr[i] = current_node->number;
        current_node = current_node->next;
    }

    

    printf("size: %i\tfinal index: %i\n", input->size, input_arr[input->size - 1]);

    if (which_smallest < input->size) return_value = -1;

    // Run Median of Medians
    return_value = MOMSelect(input, which_smallest, input->size);

    printf("%i\n", return_value);

    cleanup(fp, input, input_arr);
}