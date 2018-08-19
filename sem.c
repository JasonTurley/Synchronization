/**
 * Definition of a simple counting semaphore.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include "sem.h"
#include "error.h"

void sem_init(sem_t *sem, int pshared, unsigned int value)
{
    if (pshared == 0) {     // shared between threads
        sem = ec_malloc(sizeof(sem_t));
    } else {            // shared between processes

        // credit: https://stackoverflow.com/questions/8359322/how-to-share-semaphores-between-processes-using-shared-memory
        int fd = shm_open("shm_file", O_CREAT, O_RDWR);
        if (fd == -1) {
           throw_error("Failed to open shared memory file");
        }

        ftruncate(fd, sizeof(sem_t));
        sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, 
                    MAP_SHARED, fd, 0);
        if (sem == (void *) -1)
            throw_error("Failed to mmap memory");
    }
        sem->value = value;
        mutex_init(sem->mutex);     // normal, fast mutex

}

void sem_post(sem_t *sem)
{
    if (sem) {
        mutex_lock(sem->mutex);
        sem->value++;
        mutex_unlock(sem->mutex);
    }
}

void sem_wait(sem_t *sem)
{
    if (sem) {
        while (sem->value == 0) 
            pthread_cond_wait(sem->cv, sem->mutex);
        
        mutex_lock(sem->mutex);
        sem->value--;
        mutex_unlock(sem->mutex);
    }
}

void sem_destroy(sem_t *sem)
{
    if (sem) {
        mutex_destroy(sem->mutex);
        pthread_cond_destroy(sem->cv);
        free(sem);
        sem = NULL;
    }
}