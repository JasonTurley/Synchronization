/**
 * Handles error checking
 */
#pragma once
typedef unsigned long size_t;

/**
 * TODO: Custom error numbers for mutex?
 */

/**
 * Prints error message `msg` to stderr and exits process.
 */
void print_and_exit(char *msg);

/**
 * An error checked wrapper function for malloc. Allocates space for 
 * `size` bytes. 
 * 
 * Upon success, returns valid memory. Otherwise throws error and exits.
 */
void* ec_malloc(size_t size);