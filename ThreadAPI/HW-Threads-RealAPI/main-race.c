#include <stdio.h>

#include "mythreads.h"

int balance = 0;
pthread_mutex_t lock;

void* worker(void* arg) {
    Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    if (Pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    Pthread_create(&p, NULL, worker, NULL);
    Pthread_join(p, NULL);
    printf("%d \n", balance);
    return 0;
}
