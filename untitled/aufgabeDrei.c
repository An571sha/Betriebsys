//
// Created by Animesh Sharma on 14.10.19.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>

int aufgabeDreiMitSemaphores();

int main(int argc, char *argv[]) {
    aufgabeDreiMitSemaphores();
}

int aufgabeDreiMitSemaphores(){
    sem_t *sem1;
    sem_t *sem2;

    sem1 = sem_open("/semaphore1", O_CREAT, 0644, 0);
    sem2 = sem_open("/semaphore2", O_CREAT, 0644, 1);

    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);

    } else if (rc == 0) {
        //child
        sem_wait(sem2);
        // printf("Hello");
        write(1, "hello ", 6); // 1 is standard output
        sem_post(sem1);

    } else if(rc > 0) {
        //Parent
        sem_wait(sem1);
        // printf("Goodbye");
        write(1, "Goodbye", 7);
        sem_post(sem2);
    }

    // Close the Semaphores
    sem_close(sem1);
    sem_unlink("/semaphore1");
    sem_close(sem2);
    sem_unlink("/semaphore2");
    return 0;
}