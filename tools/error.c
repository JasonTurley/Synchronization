#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void print_and_exit(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void* ec_malloc(size_t size)
{
    void* ret = malloc(size);

    if (ret == NULL) {
        print_and_exit("Malloc failed");
    }

    return ret;
}