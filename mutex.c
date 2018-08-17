/**
 * Definition of a mutex.
 */

#include "mutex.h"

int mutex_init(mutex_t *mutex, attr_t *attr)
{
    mutex = (mutex_t*) malloc(sizeof(*mutex));    
    if ( !mutex ) {
        return -1;
    }

    mutex->locked = 0;
    mutex->refcnt = 0;
    mutex->tid = 0;

    if (attr) {
        mutex->type = attr->type;
    } else {
        mutex->type = NORMAL;
    }

    return 0;
}

void mutex_lock(mutex_t *mutex)
{
    if (mutex) {
        if (mutex->type == NORMAL) {
            // Default mutex does no error checking. Focuses on performance and not correctness
            spin_lock(mutex);
        }
    }
}

void mutex_unlock(mutex_t *mutex)
{
    if (mutex) {
        mutex->locked = 0;
    }
}

void spin_lock(mutex_t *mutex)
{
    while (__sync_lock_test_and_set(&mutex->locked, 1))
        while(mutex->locked);
}

void mutex_destroy(mutex_t *mutex)
{
    if (mutex) {
        mutex->locked = 0;
        mutex->refcnt = 0;
        mutex->tid = 0;

        free(mutex);
        mutex = NULL;
    }
}