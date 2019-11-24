#include <stdio.h>
#include <unistd.h>
#include <x86intrin.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>


void readFromSourceAndUseGetTimeOfDay();
void readFromSourceAndUseRtdsc();
void performZeroByteRead();
int createSinglePipeAndPrintOutput();
void readAndUseClock_gettime();
long removeCalculatedOverHeadTime();

//HOMEWORK: LIMITED DIRECT EXECUTION
int main(int argc, char **argv) {
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

    return 0;
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
