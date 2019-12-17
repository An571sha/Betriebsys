#include <stdio.h>
#include <pthread.h>
#include "mythreads.h"

#define NUMCPUS 5
#define ITERATIONS 1000000
#define THRESHOLD 2

typedef struct counter_t{

    int global;
    pthread_mutex_t globalLock;
    int local[NUMCPUS];
    pthread_mutex_t glock[NUMCPUS];
    int threshold;

}counter_t;


typedef struct __cthread
{
    counter_t * counter;
    int threadID;
    int amt;

}  cthread;


void init(counter_t *c , int threshold) {
    c -> threshold = threshold;
    c -> global = 0;
    Pthread_mutex_init(&c-> globalLock, NULL);
    int i = 0;
    for(i=0; i< NUMCPUS; i++) {
        c->local[i] = 0;
        Pthread_mutex_init(&c-> glock[i], NULL);
    }
}

void update(counter_t *c , int threadID, int amt) {
    Pthread_mutex_lock(&c -> glock[threadID]);
    c -> local[threadID] += amt;

    if(c -> local[threadID] >= c-> threshold){
        Pthread_mutex_lock(&c->globalLock);
        c->global += c->local[threadID];
        Pthread_mutex_unlock(&c->globalLock);
        c->local[threadID] = 0;
    }
    Pthread_mutex_unlock(&c -> glock[threadID]);
}

int get(counter_t *c){
    Pthread_mutex_lock(&c ->globalLock);
    int val = c->global;
    Pthread_mutex_unlock(&c -> globalLock);
    return val;
}

void* worker(void *arg){
    cthread * ct = (cthread *) arg;
    for (int i=0; i < ITERATIONS; i++) {
        update(ct->counter, ct->threadID, ct->amt);
    }
    return (void *) NULL;

}


int main() {
    pthread_t p0,p1,p2,p3,p4;
    counter_t counter;
    cthread cp0, cp1, cp2, cp3, cp4;

    cp0.counter = &counter;
    cp0.threadID = 0;
    cp0.amt = 1;

    cp1.counter = &counter;
    cp1.threadID = 1;
    cp1.amt = 1;

    cp2.counter = &counter;
    cp2.threadID = 2;
    cp2.amt = 1;

    cp3.counter = &counter;
    cp3.threadID = 3;
    cp3.amt = 1;

    cp4.counter = &counter;
    cp4.threadID = 4;
    cp4.amt = 1;


    init(&counter, THRESHOLD);

    struct timespec time_start,time_stop;
    long sum = 0;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    pthread_create(&p0, NULL, worker,&cp0);
    pthread_create(&p1, NULL, worker,&cp1);
    pthread_create(&p2, NULL, worker,&cp2);
    pthread_create(&p3, NULL, worker,&cp3);
    pthread_create(&p4, NULL, worker,&cp4);
    pthread_join(p0,NULL);
    Pthread_join(p1,NULL);
    Pthread_join(p2,NULL);
    Pthread_join(p3,NULL);
    Pthread_join(p4,NULL);

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

    sum = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        sum += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    sum = (sum - time_start.tv_nsec);

    printf("time taken %ld ns\n", sum / (ITERATIONS));

    printf("%s %d \n", "counter value", get(cp4.counter));


    return 0;
}

