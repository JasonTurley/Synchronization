#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include "mutex.h"

mutex_t mtx;
attr_t attr;

void* test_func(void* arg)
{
    int tid = *(int *)arg;
    printf("Thread %d entered\n", tid);

    mutex_lock(&mtx);
    printf("Thread %d exited\n", tid);
    mutex_unlock(&mtx);
}

int main(int argc, char const *argv[])
{
    mutex_init(&mtx, NULL);

    pthread_t threads[2];

    // Launch threads
    for (int i = 0; i < 2; i++)
        pthread_create(&threads[i], NULL, test_func, &i);

    // Wait for threads to finish
    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
