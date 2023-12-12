#include <stdio.h>
#include <stdlib.h>

#include "../include/error_handling.h"

void error_handling(char* message)
{
    fputs(message, stderr);
    exit(1);
}
