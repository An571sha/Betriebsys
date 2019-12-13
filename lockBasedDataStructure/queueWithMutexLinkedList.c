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
    int_queue(&t);
    enque(&t,10);
    enque(&t,20);
    enque(&t,30);
    enque(&t,40);
    deque(&t);
    printQueue(&t);

}