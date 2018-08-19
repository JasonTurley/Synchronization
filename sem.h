/**
 * Declaration of a simple counting semaphore
 * @date (created) 8.17.18
 */
#pragma once
#include <pthread.h>    /* condition variable */
#include "mutex.h"

/**
 * Struct representing a semaphore
 */
typedef struct sem_t {
    unsigned int value;
    int pshared;
    mutex_t *mutex;
    pthread_cond_t *cv;
} sem_t;

/**
 * Initializes the unnamed semaphore to the address pointed to by `sem`. The
 * initial value of the semaphore is specified by `value`.
 * 
 * If the `pshared` value is a nonzero integer, than the semaphore will be
 * shared between processes, and is located in a region of shared memory (mmap, 
 * shm_open, or shmget).
 * 
 * If `pshared` is 0, then the semaphore will be located in an area shared 
 * between threads (like global space or allocated on the heap).
 */
void sem_init(sem_t *sem, int pshared, unsigned int value);

/**
 * 
 */
void sem_post(sem_t *sem);

/**
 * 
 */
void sem_wait(sem_t *sem);

/**
 * 
 */
void sem_destroy(sem_t *sem);