/**
 * Definition of a mutex.
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>    // pthread_self()
#include "mutex.h"

void mutex_init(mutex_t *mutex, attr_t *attr)
{
    mutex = malloc(sizeof(*mutex));    
    if ( !mutex ) {
        fprintf(stderr, "Failed to allocate mutex\n");
       exit(-1);
    }

    mutex->locked = 0;
    mutex->refcnt = 0;
    mutex->tid = 0;

    if (attr) {
        mutex->type = attr->type;
    } else {
        mutex->type = NORMAL;
    }
}

void mutex_lock(mutex_t *mutex)
{
    if (mutex) {
        if (mutex->type == ERRORCHECK) {
            if (mutex->locked && mutex->tid == pthread_self()) {
                // Same thread attempting to relock mutex
                fprintf(stderr, "Thread %d attempting to relock mutex\n", mutex->tid);                    
                exit(-1);
            } else {
                // This is the first calling thread. Save its id
                mutex->tid = pthread_self();
            }
        }    
        // spin lock
        while (__sync_lock_test_and_set(&mutex->locked, 1))
            while (mutex->locked);
    }
}

void mutex_unlock(mutex_t *mutex)
{
    if (mutex) {
        __sync_lock_release(&mutex->locked);
    }
}

void mutex_destroy(mutex_t *mutex)
{
    free(mutex);
    mutex = NULL;
}

void mutex_attr_init(attr_t *attr)
{
    attr = malloc(sizeof(*attr));
    if (!attr) {
        fprintf(stderr, "Failed to allocate mutex attribute\n");
        exit(-1);
    }

    attr->type = NORMAL;
}

void mutex_attr_settype(attr_t *attr, int type)
{
    if (attr) {
        attr->type = type;
    }
}

void mutex_attr_destroy(attr_t *attr)
{
    free(attr);
    attr = NULL;
}