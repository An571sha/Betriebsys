//
// Created by Animesh Sharma on 13.12.19.
//

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include "mythreads.h"

typedef struct counter_tc {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
     c->value = 0;
     Pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
     Pthread_mutex_lock(&c->lock);
     c->value++;
     Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->value--;
    Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) {
     Pthread_mutex_lock(&c->lock);
     int rc = c->value;
     Pthread_mutex_unlock(&c->lock);
     return rc;
}

//updating with one or multiple threads
//is for loop affected by interrputs, if yes, do i need to lock it?
void* worker(void *c){
    for(int i=0; i<5; i++){
        increment(c);
    }

    for(int i = 0; i<5; i++){
        decrement(c);
    }

    return c;
}

void* print_char (void *arg) {
    counter_t *c= (counter_t *)arg;
    Pthread_mutex_lock(&c->lock);
    printf("%c", c->value++);
    Pthread_mutex_unlock(&c->lock);
    return arg;
}

int main() {
    pthread_t p0,p1;

    counter_t counter0,counter1;
    long sum = 0;
    struct timespec time_start,time_stop;

    init(&counter0);
    init(&counter1);
    //measuring with one thread now
    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    Pthread_create(&p0, NULL, worker, &counter0);
    Pthread_create(&p1, NULL, worker, &counter1);
    Pthread_join(p0,NULL);
    Pthread_join(p1,NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

    sum = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        sum += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    sum = (sum - time_start.tv_nsec);

    printf("werte %ld ns\n", sum/10);


    return 0;


}


