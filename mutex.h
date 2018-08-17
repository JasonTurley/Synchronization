/**
 * Declaration of a mutex and mutex attribute.
 * @date (created) 8.15.18
 */

#pragma once
#include <stdlib.h>

/**
 * Mutex attribute types
 */
typedef enum {NORMAL, ERRORCHECK, RECURSIVE, ADAPTIVE} TYPE;

/**
 * Struct representing a mutex
 */
typedef struct mutex_t {
    int locked;
    unsigned int refcnt;        // reference count for recursive mutex
    int tid;                    // thread associated with this mutex
    TYPE type;                  // attribute settings
} mutex_t;

/**
 * Struct representing a mutex attribute
 */
typedef struct attr_t {
    TYPE type;
} attr_t;

/**
 * Initializes the given mutex `mutex` with attributes specified by `attr`. 
 * If `attr` is NULL, the mutex is created as a default (fast) mutex
 * that prioritizes speed over correctness. Upon success, the mutex becomes
 * allocated and unlocked.
 * 
 * If successful, returns 0. Otherwise returns an error number.
 */
int mutex_init(mutex_t *mutex, attr_t *attr);

/**
 * Attempts to lock to mutex object. If `mutex` is already locked, then the 
 * calling thread shall block until the mutex is available (i.e. unlocked).
 * The operation returns with `mutex` locked an owned by the calling thread.
 * 
 * If the mutex type is NORMAL, then the mutex prioritizes speed over correctness.
 * Meaning no deadlock detection or error checking.
 * 
 * If the mutex type is ERRORCHECK, then attempting to relock the same mutex 
 * causes an error.
 * 
 * If the mutex type if RECURSIVE, then the mutex utilizes a lock count. When
 * a thread first acquires the mutex, the count is set to once. Each subsequent
 * relock increments the counter instead of raising an error.
 * 
 */
void mutex_lock(mutex_t *mutex);

/**
 * Releases the given mutex.
 *
 * For RECURSIVE type mutexes, the mutex shall be released only once the 
 * reference count reaches zero.
 */
void mutex_unlock(mutex_t *mutex);

/**
 * Destroys the mutex object referenced by `mutex`; effectively uninitializing 
 * it. A destroyed mutex may be  reinitialized by `mutex_init`.
 * 
 * Note: Attempting to destroy a locked mutex results in undefined behavior.
 * If successful, returns 0. Otherwise returns an error number.
 */
void mutex_destroy(mutex_t *mutex);

/**
 * Locks the mutex by performing a busy wait spin lock.
 */
void spin_lock(mutex_t *mutex);