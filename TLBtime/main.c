#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>

#define PAGE_SIZE 4096

int main(int argc, char **argv) {

    struct timespec start, end;
    int i, size = 1000000, numPages = 16;
    long elapsedTime;
    float *timeArrayStop, *dif;


    int jump = PAGE_SIZE / sizeof(int); //1k int

    if (argc > 1)
    {
        numPages = atoi(argv[1]);
        //size = atoi(argv[2]);
    }

    int *a = (int *) malloc(numPages * jump * sizeof(int));
    //int *a = (int *) calloc(numPages * jump, sizeof(int));

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
        for (int l = 0; l < numPages * jump; l += jump) {
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);
    unsigned long loop = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;

    //TLB time
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    for (int j = 0; j < size; ++j) {
        for (i = 0; i < numPages * jump; i += jump) {
            a[i] += 1;
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    unsigned long diff = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec - loop;
    unsigned long aver = (diff / numPages) / size;
    printf("%d,%lu\n", numPages, aver);
    return 0;
}