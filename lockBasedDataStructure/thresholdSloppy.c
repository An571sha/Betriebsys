#include <stdio.h>
#include <pthread.h>
#include "mythreads.h"

#define NUMCPUS 4

typedef struct counter_t{

    int global;
    pthread_mutex_t globalLock;
    int local[NUMCPUS];
    pthread_mutex_t glock[NUMCPUS];
    int threshold;

}counter_t;

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

    if( c -> local[threadID] >= c-> threshold){
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

void* worker(counter_t *c, int threadID, int amt){
    int j = 0;
    printf("%s %d \n", "Starting thread", threadID);

    for(j = 0; j < 1000000; j++) {
        update(c,threadID, amt);
    }
    printf("%s %d \n", "Done with thread", threadID);
    return NULL;

}


int main() {
    pthread_t p0,p1,p2,p3,p4,p5;
    counter_t counter;
    init(&counter, 100);
    Pthread_create(&p0, NULL, worker(&counter,0,1),NULL);
    Pthread_create(&p1, NULL, worker(&counter,1,1),NULL);
    Pthread_create(&p2, NULL, worker(&counter,2,1),NULL);
    Pthread_create(&p3, NULL, worker(&counter,3,1),NULL);
    Pthread_create(&p4, NULL, worker(&counter,4,1),NULL);
    Pthread_create(&p5, NULL, worker(&counter,5,1),NULL);
    printf("%s,%d", "Global Counter = ",get(&counter));
    Pthread_join(p0,NULL);
    printf("%s,%d", "Global Counter = ",get(&counter));
    Pthread_join(p1,NULL);
    Pthread_join(p2,NULL);
    Pthread_join(p3,NULL);
    Pthread_join(p4,NULL);
    Pthread_join(p5,NULL);
    return 0;
}

