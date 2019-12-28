#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX 10

int buffer[MAX];
int fill = 0;
int use = 0;
int counter = 0;
int tmp = 0;
sem_t full;
sem_t empty;
sem_t mutex;

typedef struct wert{
    int i;

} wert;

/** How can i use a @counter variable mentioned in the previous chapter with MUTEX here, i can't seem to figure it out. **/

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
    counter++;
    printf("fill - %d\n", fill);
    printf("counter - %d\n", counter);
}

int get() {
    tmp = buffer[use];
    use = (use + 1) % MAX;
    counter--;
    printf("use - %d\n", use);
    printf("counter - %d\n", counter);
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

   // producer(10);
   // consumer(10);

     pthread_create(&p0, NULL, worker, &t1);
     pthread_create(&p1, NULL, worker, &t2);
     pthread_join(p0,NULL);
     pthread_join(p1,NULL);

    return 0;
}