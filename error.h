/**
 * Handles error checking
 */
#pragma once
#include <stdio.h>
#include <stdlib.h>

/**
 * TODO: Custom error numbers
 */

/**
 * An error checked wrapper function for malloc. Allocates space for 
 * `size` bytes. 
 * 
 * Upon success, returns valid memory. Otherwise throws error and exits.
 */
void* ec_malloc(size_t size)
{
    void* ret = malloc(size);

    if (ret == NULL) {
        fprintf(stderr, "Malloc failed in file %s line: %u\n", __FILE__, __LINE__);
        exit(-1);
    }

    return ret;
}