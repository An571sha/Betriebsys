#include <stdio.h>

#include "mythreads.h"

pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    if ((long long) arg == 0) {
	pthread_mutex_lock(&m1);
	pthread_mutex_lock(&m2);
    } else {
	pthread_mutex_lock(&m2);
	pthread_mutex_lock(&m1);
    }
    pthread_mutex_unlock(&m1);
    pthread_mutex_unlock(&m2);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    pthread_create(&p1, NULL, worker, (void *) (long long) 0);
    pthread_create(&p2, NULL, worker, (void *) (long long) 1);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    return 0;
}
