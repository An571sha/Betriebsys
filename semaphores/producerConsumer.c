#include <stdio.h>
#include <semaphore.h>

#define MAX 1

int buffer[MAX];
int fill = 0;
int use = 0;
int loops = MAX;
sem_t full;
sem_t empty;

void put(int value) {
    buffer[fill] = value;
    fill = (fill + 1) % MAX;
}

int get() {
    int tmp = buffer[use];
    use = (use + 1) % MAX;
    return tmp;
}

void* producer(){
    sem_wait(&empty);
    put(5);
    sem_post(&full);
    return NULL;
}

void* consumer(){
    int tmp = 0;
    while (tmp != -1) {
        sem_wait(&full);
        tmp = get();
        sem_post(&empty);
        printf("%d\n", tmp);
    }

    return NULL;
}

int main() {
    sem_init(&empty, 0, MAX);
    sem_init(&full, 0, 0);
    producer();
/*    for (int i = 0; i < loops; i++) {

       }
*/
    consumer();
    return 0;
}