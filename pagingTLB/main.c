#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define PAGE_SIZE 4096
#define NUMPAGES 16

/** a simple time measure  **/

int main() {

    /*
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
    {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }*/

    //int *a = malloc(PAGE_SIZE);
    int *a = malloc(10 * sizeof(int));
    struct timespec time_start,time_stop;
    int sum = 0 ;
    long messwerte[1000];
    int jump = PAGE_SIZE/ sizeof(int);

    for (int j=0; j < 1000; j++){

        clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

        for ( int i=0; i< NUMPAGES * jump; i+=jump) {
            //printf("value of i %d \n", i);
            sum+=a[i];
        }

        clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

        messwerte[j] = time_stop.tv_nsec;

        if (time_start.tv_nsec > time_stop.tv_nsec) {
            messwerte[j] += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
        }

        messwerte[j] = (messwerte[j] - time_start.tv_nsec);

        messwerte[j];

        printf("werte %ld ns\n", messwerte[j]);
    }
    return 0;
}