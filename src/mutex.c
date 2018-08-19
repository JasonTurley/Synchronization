/**
 * Definition of a mutex.
 */
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>    // pthread_self()
#include "mutex.h"
#include "error.h"

void mutex_init(mutex_t *mutex, attr_t *attr)
{
    mutex = ec_malloc(sizeof(mutex_t));    

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
                print_and_exit("Same thread attempting to relock mutex");
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
    attr = ec_malloc(sizeof(*attr));
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