//
// Created by Animesh Sharma on 13.12.19.
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

typedef struct node_t{

    int value;
    struct node_t *next;

} node_t;

typedef struct queue_t{

    node_t *head;
    node_t *tail;
    pthread_mutex_t head_lock, tail_lock;

} queue_t;

typedef struct wert_t{

    queue_t *q;
    int i;
    

} wert_t;

void int_queue(queue_t *t){

    node_t *temp = malloc(sizeof(node_t));
    temp->next = NULL;
    t->head = t->tail = NULL;
    pthread_mutex_init(&t -> head_lock, NULL);
    pthread_mutex_init(&t -> tail_lock, NULL);
}

void enque(queue_t *t, int value){

    node_t *temp = malloc(sizeof(node_t));
    assert(temp !=NULL);

    temp->value = value;
    temp->next = NULL;
    if(t->tail == NULL) {

        pthread_mutex_lock(&t -> head_lock);
        pthread_mutex_lock(&t -> tail_lock);

        t->head = t->tail = temp;
        pthread_mutex_unlock(&t -> head_lock);
        pthread_mutex_unlock(&t -> tail_lock);
        return;
    }

    pthread_mutex_lock(&t -> tail_lock);
    t->tail->next = temp;
    t->tail = temp;
    pthread_mutex_unlock(&t -> tail_lock);

}

void* worker(void *arg) {
    wert_t *ct = (wert_t *) arg;
    enque(ct->q,ct->i);
    return (void *) NULL;
}

int dequeWithValue(queue_t *t, int *value) {
    pthread_mutex_lock(&t -> head_lock);
    node_t *temp = t->head;
    node_t *new_head = temp->next;

    if(new_head == NULL){
        pthread_mutex_unlock(&t -> head_lock);
        return -1;
    }

    *value = new_head->value;
    t->head = new_head;
    pthread_mutex_unlock(&t -> head_lock);
    free(temp);
    return 0;
}

int deque(queue_t *t){
    pthread_mutex_lock(&t -> head_lock);
    node_t *temp = t->head;

    if(t->head == NULL) {
        pthread_mutex_unlock(&t -> head_lock);
        return -1;
    }

    if(t->head == t->tail) {
        pthread_mutex_lock(&t -> tail_lock);
        t->head = t->tail = NULL;
        pthread_mutex_unlock(&t -> head_lock);
        pthread_mutex_unlock(&t -> tail_lock);

    } else {
        t->head = t->head->next;
        pthread_mutex_unlock(&t -> head_lock);

    }

    free(temp);
    return 0;

}

void printQueue(queue_t *t){
    int iterator = 0;
    node_t *tmp = (node_t *)malloc(sizeof(node_t));
    tmp = t->head;
    while(tmp != NULL){
        iterator += 1;
        printf("Queue node %d: data val %d ptr %p front ptr %p\n", iterator, tmp->value, tmp, tmp->next);
        tmp = tmp->next;
    }
    free(tmp);
}

int main() {

    queue_t t;
    wert_t wert0,wert1,wert2,wert3;
    pthread_t p0,p1,p2,p3,p4;



    wert0.q = &t;
    wert0.i = 10;

    wert1.q = &t;
    wert1.i = 20;

    wert2.q = &t;
    wert2.i = 30;

    wert3.q = &t;
    wert3.i = 40;


    int_queue(&t);
    long sum = 0;
    struct timespec time_start,time_stop;

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    pthread_create(&p0, NULL, worker, &wert0);
    pthread_create(&p1, NULL, worker, &wert1);
    pthread_create(&p2, NULL, worker, &wert2);
    pthread_create(&p3, NULL, worker, &wert3);
    pthread_join(p0,NULL);
    pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    pthread_join(p3,NULL);


/*
    enque(&t,10);
    enque(&t,20);
    enque(&t,30);
    enque(&t,40);
    deque(&t);
*/


    clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

    sum = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        sum += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    sum = (sum - time_start.tv_nsec);

    printQueue(&t);

    printf("Time Taken %ld ns\n", sum);


}