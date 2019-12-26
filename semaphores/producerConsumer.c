#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX 10

int buffer[MAX];
int fill = 0;
int use = 0;
int counter = 0;
sem_t full;
sem_t empty;
sem_t mutex;

typedef struct wert_t{
    int i;
} wert;


void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    printf("fill - %d\n", fill);
    counter++;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    printf("use - %d\n", use);
    counter--;
    return tmp;
}

void producer(int loops){
    for (int i = 0; i < loops; i++) {

        sem_wait(&empty);
        sem_wait(&mutex);
        put(i);
        sem_post(&mutex);
        sem_post(&full);

    }

}

void consumer(int loops){
    int tmp = 0;
    for (int i = 0; i < loops; i++) {
        sem_wait(&full);
        sem_wait(&mutex);
        tmp = get();
        sem_post(&mutex);
        sem_post(&empty);
        printf("tmp - %d\n", tmp);
    }
}

void* worker(void* args){
    wert *ct = (wert *) args;
    producer(ct ->i);
    consumer(ct ->i);
    return (void*) NULL;
}

int main() {
    pthread_t p0,p1;

    wert t1,t2;
    t1.i = 10;
    t2.i = 10;

    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);

    pthread_create(&p0, NULL, worker, &t1);
    pthread_create(&p1, NULL, worker, &t2);

    return 0;
}