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
//is for loop affected by interrupts, if yes, do i need to lock it?
void* worker(void *c){
    for(int i=0; i<100; i++){
        increment(c);
    }

    return c;
}


int main() {
   pthread_t p0,p1,p2,p3,p4,p5;

    counter_t counter0,counter1,counter2,counter3,counter4,counter5;
    long sum = 0;
    struct timespec time_start,time_stop;

    init(&counter0);
    init(&counter1);
    init(&counter2);
    init(&counter3);
    init(&counter4);
    init(&counter5);

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    Pthread_create(&p0, NULL, worker, &counter0);
    Pthread_create(&p1, NULL, worker, &counter1);
    Pthread_create(&p2, NULL, worker, &counter2);
   // Pthread_create(&p3, NULL, worker, &counter3);
  //  Pthread_create(&p4, NULL, worker, &counter4);
  //  Pthread_create(&p5, NULL, worker, &counter5);
    Pthread_join(p0, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
  //  Pthread_join(p3, NULL);
  //  Pthread_join(p4, NULL);
  //  Pthread_join(p5, NULL);*/

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

    sum = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        sum += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    sum = (sum - time_start.tv_nsec);

    printf("werte %ld ns\n", sum/10);
    printf("incremented counter %d \n ", get(&counter1));

    return 0;


}


