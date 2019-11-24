#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sched.h>
#include <errno.h>
#include <limits.h>

/** a simple time measure  **/

int main(int argc, char * argv[]) {

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(3, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
    {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }



    //int *a = malloc(PAGE_SIZE);
    const size_t ARRLEN = 5E6;
    int *a = calloc(sizeof(int), ARRLEN);
    if (a == NULL) {
        perror("ERROR: calloc\n");
        return EXIT_FAILURE;
    }

    struct timespec time_start,time_stop;
    long sum = 0 ;
    long numberOfTrials;
    long numberOfPages;

    errno = 0;
    numberOfTrials = strtol(argv[1],NULL,10);

    numberOfPages = strtol(argv[2], NULL,10);

    if (numberOfPages == 0 || numberOfTrials == 0) {

        printf("Enter a positive number");

    } else if (numberOfPages < 0 || numberOfTrials < 0) {

        printf("Enter a positive number");

    } else if ((errno == ERANGE && (numberOfPages == LONG_MAX || numberOfPages == LONG_MIN))|| (errno != 0)) {
            perror("strtol input Error");
            exit(EXIT_FAILURE);
    }

    long jump = numberOfPages/ sizeof(int);


    clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

    for (long j=0; j < numberOfTrials; j++) {

        //If size of a page is 4096 and integer size is 4 bytes
        //no of entries in a page will be, at 1025 a new page thus miss could occur.
        //the loop should go through each integer entry in a page times the number of page
        for (long i = 0; i < numberOfPages * jump; i += jump) {
            a[i] += 1;
        }

    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);

    sum = time_stop.tv_nsec;

    if (time_start.tv_nsec > time_stop.tv_nsec) {
        sum += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
    }

    sum = (sum - time_start.tv_nsec);

    printf("werte %ld ns \n", (sum)/(numberOfPages * numberOfTrials));

/*    //write in csv
    FILE *fptr = fopen("result.csv", "a+");
    if (fptr == NULL)
    {
        printf("Could not open file");
        return 0;
    }
    fprintf(fptr,"%ld,%ld\n",numberOfPages,(sum)/(numberOfPages * numberOfTrials));

    fclose(fptr);
*/
    free(a);

    return (sum)/(numberOfPages * numberOfTrials);
}