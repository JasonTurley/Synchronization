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
    // Initialize and set mutex
    mutex_init(&mtx, NULL);
    mutex_attr_init(&attr);
    mutex_attr_settype(&attr, ERRORCHECK);

    pthread_t thread;

    // Launch threads
    for (int i = 0; i < 2; i++)
        pthread_create(&thread, NULL, test_func, &i);

    // Wait for threads to finish
    for (int i = 0; i < 2; i++)
        pthread_join(thread, NULL);

    return 0;
}
