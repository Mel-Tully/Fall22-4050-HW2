#include <stdlib.h>
#include <stdio.h>

#include "input_error.h"

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }

    FILE fp = fopen(argv[1], )
}