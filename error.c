#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void throw_error(char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

void* ec_malloc(size_t size)
{
    void* ret = malloc(size);

    if (ret == NULL) {
        throw_error("Malloc failed");
    }

    return ret;
}