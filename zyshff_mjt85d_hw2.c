// Zoe Spriggs, Melissa Tully
// CS 4050
// HW 2

#include <stdlib.h>
#include <stdio.h>
#include "input_error.h"
#include "linked_list.h"

int main(int argc, char *argv[])
{
    // Check for correct number of command line arguements
    if (argc != 1)
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
    char last_line[20];
    int which_smallest;

    fgets(last_line, 20, fp);
    which_smallest = strtol(last_line, NULL, 10);

    if (which_smallest <= 0)
    {
        exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
    }

    Linked_list_t * input = malloc(sizeof(Linked_list_t));
    input->head = NULL;
    input->size = 0;



    // Cleanup
    if (fclose(fp) == EOF)
    {
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
    
    free_linked_list(input);
}