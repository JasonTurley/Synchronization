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
typedef struct {
    unsigned int value;
    int pshared;
    mutex_t *mutex;
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
 * Increments (unlocks) the semaphore pointed to by `sem`. If the semaphore's
 * value consequently becomes greater than zero, then another process or
 * thread blocked in a sem_wait() call will be woken up and proceed to lock
 * the semaphore. 
 */
void sem_post(sem_t *sem);

/**
 * Decrements (locks) the semaphore pointed to by `sem`. If the semaphore's
 * value is greater than zero, then the decrement proceeds, and the function
 * returns, immediately. 
 *
 * If the semaphore currently has the value zero, then the call blocks until
 * either it becomes possible to perform the decrement (i.e. the semaphore's
 * value rises above zero), or a signal handler interrupts the call.
 */
void sem_wait(sem_t *sem);

/**
 * Destroys the unnamed semaphore at the address pointer to by `sem`.
 */
void sem_destroy(sem_t *sem);
