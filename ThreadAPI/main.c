#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct { int a; int b; } myarg_t;
typedef struct { int x; int y; } myret_t;
pthread_mutex_t mutex;


void* mythread(void *arg) {
   // pthread_t p;
    pthread_mutex_lock (&mutex);
    myret_t *rvals = malloc(sizeof(myret_t));
    rvals->x = 100;
    rvals->y = 200;
    pthread_mutex_unlock (&mutex);
    // pthread_join(p, (void **) &rvals);
    return (void *) rvals;

}

void* test(void *arg) {
   // pthread_t p;
    pthread_mutex_lock (&mutex);
    myret_t *rvals = malloc(sizeof(myret_t));
    rvals->x = 101;
    rvals->y = 201;
    pthread_mutex_unlock (&mutex);
    // pthread_join(p, (void **) &rvals);
    return (void *) rvals;

}

int main() {

    pthread_t p;
    myret_t *rvals;

    pthread_mutex_init (&mutex, NULL);

    pthread_create(&p, NULL, mythread, NULL);

    pthread_join(p, (void **) &rvals);

    pthread_create(&p, NULL, test, NULL);

    pthread_join(p, (void **) &rvals);

    printf("returned %d %d\n", rvals->x, rvals->y);

    free(rvals);
    return 0;
}
