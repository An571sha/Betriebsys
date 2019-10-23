//
// Created by Animesh Sharma
//

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <inttypes.h>
#include <sched.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <string.h>

int createTwoPipesAndMeasureContextSwitch();
int timeSpentOnReadAndWrite();

int main(int argc, char **argv) {
    createTwoPipesAndMeasureContextSwitch();
    return 0;
}

int createTwoPipesAndMeasureContextSwitch(){
    int array0ForPipe[2];
    int array1ForPipe[2];

    char fixed_str_1[] = "";
    char input_str_1[15];
    long input_long_2;

    pid_t processId;
    pipe(array0ForPipe);
    pipe(array1ForPipe);

    struct timespec start, end;
    long elapsedTime1;
    long elapsedTime2;
    long totalTime;
    processId = fork();

    if (processId < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
        //parent process
    } else if (processId > 0) {
/*

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(3, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("Error: sched_setaffinity\n");
            exit(EXIT_FAILURE);
        }
*/

        //close the reading end of the first pipe
        close(array0ForPipe[0]);

        //write something on the writing end of first pipe
        write(array0ForPipe[1], fixed_str_1, (strlen(fixed_str_1)+1));

        //close the write of second pipe
        close(array1ForPipe[1]);

        //child process
    } else if (processId == 0){

  /*      cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(3, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("Error: sched_setaffinity\n");
            exit(EXIT_FAILURE);
        }*/

        //close the reading end of second pipe
        close(array1ForPipe[0]);

        //get time stamp at this point
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        //context switch occurs here as we start read from the reading end of first pipe
        read(array0ForPipe[0],input_str_1, sizeof(input_str_1));

        // get time stamp after wait and child process are done
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        //close the writing end of first pipe
        close(array0ForPipe[1]);
        close(array0ForPipe[0]);

        elapsedTime2 = end.tv_nsec;

        if (start.tv_nsec > end.tv_nsec) {
            elapsedTime2 += ((long) end.tv_sec - (long) start.tv_sec) * 1000000000;
        }

        elapsedTime2 = (elapsedTime2 - start.tv_nsec);

        printf("time required for context switch %ld ns \n",elapsedTime2);

        close(array1ForPipe[1]);

    }

    return 0;
}

int timeSpentOnReadAndWrite(){
}