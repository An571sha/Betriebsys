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

} queue_t;

void int_queue(queue_t *t){

    node_t *temp = malloc(sizeof(node_t));
    temp->next = NULL;
    t->head = t->tail = NULL;
}

void enque(queue_t *t, int value){

    node_t *temp = malloc(sizeof(node_t));
    assert(temp !=NULL);

    temp->value = value;
    temp->next = NULL;

/*
    if(t->tail == NULL) {
        t->head = t->tail = temp;
        return;
    }
*/

    t->tail->next = temp;
    t->tail = temp;
}

int deque(queue_t *t, int *value) {

    node_t *temp = t->head;
    node_t *new_head = temp->next;

    if(new_head == NULL){
        return -1;
    }

    *value = new_head->value;
    t->head = new_head;
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
    printQueue(&t);

}