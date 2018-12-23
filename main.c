#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "sem.h"
#include "mutex.h"

#define NUM_THREADS 10
#define NUM_ITERS 1000

mutex_t mutex;
attr_t attr;
sem_t sem;

int main()
{
    mutex_attr_init(&attr);
    mutex_attr_settype(&attr, ERRORCHECK);
    mutex_init(&mutex, NULL);


    sem_init(&sem, 0, 0);
    sem_post(&sem);
    sem_wait(&sem);
    sem_post(&sem);

    printf("Done.\n");

    // TODO further test synchronization tools
    return 0;
}
