#include <stdio.h>

#include <pthread.h>

int balance = 0;
pthread_mutex_t lock;

void* worker(void* arg) {
    pthread_mutex_lock(&lock);
    balance++; // unprotected access
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    pthread_create(&p, NULL, worker, NULL);
    pthread_mutex_lock(&lock);
    balance++;
    pthread_mutex_unlock(&lock);
    pthread_join(p, NULL);
    printf("%d \n", balance);
    return 0;
}
