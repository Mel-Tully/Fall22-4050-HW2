#include <stdlib.h>
#include <stdio.h>

#include "input_error.h"

int main(int argc, char *argv[])
{
    // Check for correct number of command line arguements
    if (argc != 1)
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }

    // Open file
    FILE * fp = fopen(argv[1], "r");



    //Cleanup
    if(fclose(fp) == EOF)
    {
        exit(INPUT_FILE_FAILED_TO_CLOSE);
    }
}