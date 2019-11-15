#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#define NUMPAGES 4
#define PAGE_SIZE 4096
int main() {

    struct timespec time_start, time_stop;
    int i, *a, size;
    long elapsedTime;
    float *timeArrayStart, *timeArrayStop, *dif;

    size = 20000;
    a = (int *)malloc(10 * sizeof(int));
    timeArrayStart = (long *)malloc(size * sizeof(long));
    timeArrayStop = (long *)malloc(size * sizeof(long));

    int jump = PAGE_SIZE / sizeof(int); //1k int

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
    {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }

    for (int j = 0; j < size; ++j) {

        clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);
    for (i = 0; i < NUMPAGES * jump; i += jump) {
        //a[i] += 1;
        //printf("%d \n", a[i]);
    }
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);
        elapsedTime = time_stop.tv_nsec;

        if (time_start.tv_nsec > time_stop.tv_nsec) {
            elapsedTime += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
        }

        elapsedTime = elapsedTime - time_start.tv_nsec;

        printf("%ldns\n", elapsedTime);

    }

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