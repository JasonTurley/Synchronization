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
int global_count = 0;

void* increment(void* unused)
{
    mutex_lock(&mutex);
    for (int i = 0; i < NUM_ITERS; i++)
        global_count++;
    mutex_unlock(&mutex);    
}

void test_mutex()
{
    pthread_t threads[NUM_THREADS];

    // Launch threads
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_create(&threads[i], NULL, increment, NULL);

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++)
        pthread_join(threads[i], NULL);

    // Validate correct output is given
    assert(global_count == NUM_ITERS * NUM_THREADS);
    
    // reset for next test
    global_count = 0;
}

int main(int argc, char const *argv[])
{
    mutex_attr_init(&attr);
    mutex_attr_settype(&attr, ERRORCHECK);
    mutex_init(&mutex, NULL);

    // Test normal, fast mutex
    test_mutex();

    // test semaphore
    sem_init(&sem, 0, 0);
    printf("Initialize semaphore\n");

    sem_post(&sem);
    sem_wait(&sem);

    return 0;
}
