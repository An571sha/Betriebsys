#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>

#define NUMPAGES 16
#define PAGE_SIZE 4096

int main() {

    struct timespec time_start, time_stop, start, end;
    int i, size = 10000;
    long elapsedTime;
    float *timeArrayStart, *timeArrayStop, *dif;


    int jump = PAGE_SIZE / sizeof(int); //1k int
    int a[NUMPAGES*jump];
    //a = (int *) malloc((NUMPAGES * jump * sizeof(int));
    //int *a = (int *) calloc(NUMPAGES * jump, sizeof(int));
    //timeArrayStart = (long *) malloc(size * sizeof(long));



    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(3, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0) {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }
    //loop time
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int k = 0; k < size; k++) {
        for (int l = 0; l < NUMPAGES * jump; l += jump) {
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    unsigned long loop = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

    //TLB time
    for (int j = 0; j < size; ++j) {
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);
        for (i = 0; i < NUMPAGES * jump; i += jump) {
            a[i] += 1;
        }
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);
        elapsedTime = time_stop.tv_nsec;

        if (time_start.tv_nsec > time_stop.tv_nsec) {
            elapsedTime += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
        }

        elapsedTime = elapsedTime - time_start.tv_nsec;
        elapsedTime = elapsedTime - loop;
        printf("%ldns\n", elapsedTime);

    }
    printf("loopTime: %ld" loop);

/*
    elapsedTime = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        elapsedTime += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    elapsedTime = elapsedTime - time_start.tv_nsec;

    printf("%ldns\n", elapsedTime);
*/
    return 0;
}