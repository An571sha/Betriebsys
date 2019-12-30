#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t s;

void *child(void *arg) {
    printf("child\n");
    sem_post(&s);
    // use semaphore here
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    printf("parent: begin\n");
    // init semaphore here
    pthread_create(&p, NULL, child, NULL);
    sem_wait(&s);
    // use semaphore here
    printf("parent: end\n");
    return 0;
}
