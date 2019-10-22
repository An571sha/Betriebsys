#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>
#include <string.h>
#include <time.h>
#include <sched.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>


void readFromSourceAndUseGetTimeOfDay();
void readFromSourceAndUseRtdsc();
void performZeroByteRead();
int createSinglePipeAndPrintOutput();
int createTwoPipesAndMeasureContextSwitch();
void readAndUseClock_gettime();
long removeCalculatedOverHeadTime();

//HOMEWORK: LIMITED DIRECT EXECUTION
int main(int argc, char **argv) {
   // readFromSourceAndUseGetTimeOfDay();
   // readFromSourceAndUseRtdsc();
   // createSinglePipeAndPrintOutput();
   createTwoPipesAndMeasureContextSwitch();
  //  readAndUseClock_gettime();
    return 0;
}



void readAndUseClock_gettime(){
    struct timespec start, end;
    long elapsedTime;

    //starting the timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    performZeroByteRead();

    //ending the timer
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    elapsedTime = end.tv_nsec;

    if (start.tv_nsec > end.tv_nsec) {
        elapsedTime += ((long) end.tv_sec - (long) start.tv_sec) * 1000000000;
    }

    elapsedTime = (elapsedTime - start.tv_nsec) - removeCalculatedOverHeadTime();

    printf("time required for syscal %ld ns \n", (elapsedTime/1000));
}

void performZeroByteRead(){

    for (int i = 0; i < 1000; i++) {
        getpid();
    }
}

long removeCalculatedOverHeadTime(){
    struct timespec start, end;
    long elapsedTime;

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for (int i = 0; i < 1000; i++) {

    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    elapsedTime = end.tv_nsec;

    if (start.tv_nsec > end.tv_nsec) {
        elapsedTime += ((long) end.tv_sec - (long) start.tv_sec) * 1000000000;
    }

    elapsedTime = elapsedTime - start.tv_nsec;

    return elapsedTime;
}

void readFromSourceAndUseRtdsc(){
  unsigned long startTime, endTime, timeElapsed;
   startTime = _rdtsc();
   printf("start cycle count = %ld \n", startTime);

   performZeroByteRead();

   endTime = _rdtsc();
   printf("end cycle count = %ld \n", endTime);

   timeElapsed = endTime - startTime;
   printf("Time elapsed =  %ld \n", timeElapsed);
}

int createSinglePipeAndPrintOutput(){
    //for pipe the output of arrayForPiped1 becomes the input for arrayForPiped0
    int arrayForPipe[2];

    char fixed_str[] = "Animesh";
    char input_str[15];

    pid_t processId;
    //create pipe
    pipe(arrayForPipe);
    //fork the process after creating the pipe
    processId = fork();

    if (processId < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
    //child process
    else if (processId == 0) {
        //close the reading end
        close(arrayForPipe[0]);
        //write on the writing end
        write(arrayForPipe[1], fixed_str, (strlen(fixed_str)+1));

        //parent process
    } else {
        //close the writing end
        close(arrayForPipe[1]);
        //read from read end
        read(arrayForPipe[0],input_str, sizeof(input_str));
        wait(NULL);
        printf("result from pipe read %s", input_str);
    }

    return 0;
}

int createTwoPipesAndMeasureContextSwitch(){

    int array0ForPipe[2];
    int array1ForPipe[2];

    char fixed_str_1[] = "Sharma";
    char fixed_str_2[] = "Animesh";
    char input_str_1[15];
    char input_str_2[15];

    pid_t processId;
    pipe(array0ForPipe);
    pipe(array1ForPipe);

    struct timespec start, end;
    long elapsedTime;
    processId = fork();

    if (processId < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;

        //parent process
    } else if (processId > 0) {

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(3, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("Error: sched_setaffinity\n");
            exit(EXIT_FAILURE);
        }

        //close the reading end of the first pipe
        close(array0ForPipe[0]);

        //write on the writing end of first pipe
        write(array0ForPipe[1], fixed_str_1, (strlen(fixed_str_1)+1));

        //close the write of second pipe
        close(array1ForPipe[1]);

        //get time stamp at this point
        clock_gettime(CLOCK_MONOTONIC_RAW, &start);

        //wait for child process to write on array1ForPipe
        wait(NULL);

        // get time stamp after wait and child process are done
        clock_gettime(CLOCK_MONOTONIC_RAW, &end);

        //read from the reading end of second pipe
        read(array1ForPipe[0],input_str_2, sizeof(input_str_2));

        //print from the second pipe
        //printf("parent prints %s \n", input_str_2);

        elapsedTime = end.tv_nsec;

        if (start.tv_nsec > end.tv_nsec) {
            elapsedTime += ((long) end.tv_sec - (long) start.tv_sec) * 1000000000;
        }

        elapsedTime = (elapsedTime - start.tv_nsec);


        printf("time required for context switch  %ld ns \n", elapsedTime);

        //child process
    } else {

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(3, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("Error: sched_setaffinity\n");
            exit(EXIT_FAILURE);
        }
        
        //close the reading end of second pipe
        close(array1ForPipe[0]);

        //read from the reading end of first pipe
        read(array0ForPipe[0],input_str_1, sizeof(input_str_1));

        //print from the first pipe
        //printf("child prints %s \n", input_str_1);

        //close the writing end of first pipe
        close(array0ForPipe[1]);

        //write on the writing end of second pipe
        write(array1ForPipe[1], fixed_str_2, (strlen(fixed_str_2)+1));

    }

    return 0;
}