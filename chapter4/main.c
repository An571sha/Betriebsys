#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <x86intrin.h>
#include <time.h>
//#include <w32api/lm.h>

#define BILLION 1E9


int main(int argc, char *argv[]) {

    int x = 100;
    int input;
    printf("Enter number between 1 and 7: ");
    scanf("%d", &input);
    if (input == 1) {
        aufgabe1(&x);
    }
    if (input == 2) {
        aufgabe2();
    }
    if (input == 3) {
        aufgabe3();
    }
    if (input == 6) {
        rdtsc();
    }
    if (input == 7) {
        clockRealtime();
    }
    if (input == 8) {
        test();
    }

    printf("\nx = %d", x);

    return 0;
}
    
    void test() {
        int *c1 = NULL;
        int c2;

        c2 = *c1;
    }

    void aufgabe1(int *ptr) {
        printf("parent 1 (pid:%d)\n", (int) getpid());
        //int x = 100;
        int rc = fork();
        if (rc < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
        } else if (rc == 0) {
            //child (new process)
            *ptr = 30;
            //printf("child 1(pid:%d) x = %d\n", (int) getpid(), x);
        } else {
            //parent goes down this path (main)
            *ptr = 50;
            //printf("hello, I am parent of %d (pid:%d) x = %d\n", rc, (int) getpid(), x);
        }
        //printf("which process am i %d x = %d \n", (int) getpid(), *ptr);
    }

void aufgabe2 () {
    close(STDERR_FILENO);
    int openResult = open("./text.txt", O_CREAT|O_WRONLY);
    printf("(result:%d)\n", openResult);
    printf("hello world (pid:%d\n)", (int)getpid());
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        printf("hello, i am child(pid:%d)\n", (int)getpid());
        printf("(result:%d)\n", openResult);
    } else {
        int rc_wait = wait(NULL);
        printf("hello i am parent of %d (rc_wait:%d) (pid:%d)\n", rc, rc_wait, (int) getpid());
        printf("(result:%d)\n", openResult);
    }
    printf("yo");
}
void aufgabe3 () {
    char * ls_args[] = {"dir", NULL};
    //execute the program
    execv(   ls_args[0],     ls_args);
    //only get here on error
    perror("execv");
    return;
    
}
void zeroByteRead () {
    for (int i = 0; i < 1000; ++i) {
        getpid();
    }
}
void emptyque () {
    for (int i = 0; i < 1000; ++i) {
    }
}
void rdtsc () {
    unsigned long startTime, stopTime, diffTime;
    startTime = _rdtsc();
    zeroByteRead();
    stopTime = _rdtsc();
    diffTime = (stopTime - startTime) / 1000;
    printf("time: %lu \n", diffTime);
}
void clockRealtime () {
    struct timespec start, stop;
    double accum, mikro;
    /*
     * if (clock_gettime( CLOCK_REALTIME, &start) == -1) {
        perror("clock gettime");
        exit( EXIT_FAILURE );
    }
    system( argv[1]);
    if ( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
        perror("clock gettime");
        exit( EXIT_FAILURE );
    }
     */

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    zeroByteRead();
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);

    long result = stop.tv_nsec;
    if (start.tv_nsec > stop.tv_nsec) {
        result += ((stop.tv_sec - start.tv_sec) *1000000000);
    }
    long result1 = result - start.tv_nsec;

    printf("result = %ld\n", result1);

    clock_gettime(CLOCK_MONOTONIC_RAW, &start);
    emptyque();
    clock_gettime(CLOCK_MONOTONIC_RAW, &stop);

    result = stop.tv_nsec;
    if (start.tv_nsec > stop.tv_nsec) {
        result += ((stop.tv_sec - start.tv_sec) *1000000000);
    }
    long result2 = result - start.tv_nsec;

    long finalResult = result1 - result2;

    finalResult = finalResult/1000;


    /*accum = ( (double)stop.tv_sec - (double)start.tv_sec )
            + ( (double)stop.tv_nsec - (double)start.tv_nsec )
            / BILLION;*/

    /*mikro = (stop.tv_sec - start.tv_sec) *1000;
    mikro += ((double)stop.tv_nsec - (double)start.tv_nsec) /100000;
    mikro = mikro/1000;
    accum = accum/1000;
     */
    printf("nanosec = %ld\n", finalResult);
    return;
}