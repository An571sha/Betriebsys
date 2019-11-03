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
#include <sched.h>
#define __BUFFER_SIZE 4 // Used to store data through a pipe sent by the child process

long removeCalculatedOverHeadTime();
int createTwoPipesAndMeasureContextSwitch();

int main(int argc, char **argv) {
    createTwoPipesAndMeasureContextSwitch();
    return 0;
}

int createTwoPipesAndMeasureContextSwitch(){
/*    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(__CHOSEN_CPU, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
    {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }*/

    // Create 2 pipes in advance for the parent and child processes (IPC)
    // One for a data exchange and one to exchange the measured time
    int pipe_time[2] = {0, 0};
    long messwerte[1000];
    long sum = 0;
    struct timespec time_stop;
    struct timespec time_start;

    if (pipe(pipe_time) < 0)
    {
        perror("ERROR: pipe (time)\n");
        return EXIT_FAILURE;
    }

    // Create a child process
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("ERROR: fork\n");
        return EXIT_FAILURE;
    }
    else if (pid == 0) // child
    {
        // Make sure this child process is also tied to one core only, i.e., the core that the parent is tied to
        /*      cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(__CHOSEN_CPU, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("ERROR: sched_setaffinity (main)\n");
            return EXIT_FAILURE;
        }*/

        close(pipe_time[0]);
        for (size_t i = 0; i < 1000; ++i)
        {
            clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);
            write(pipe_time[1], &time_stop, sizeof(struct timespec));
        }

        close(pipe_time[1]);
    }
    else // parent
    {

        // Make the OS perform a couple of context switches by accounting for random events, i.e., other OS related activities
/*        for (size_t i = 0; i < 1000; ++i) {
            clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

            read(pipe_data[0], buffer,__BUFFER_SIZE); // this is where a context-switch is likely issued by the OS due to the pipe being empty at first, and the parent being blocked

        }*/
        close(pipe_time[1]);
        for (size_t i = 0; i < 1000; ++i) {

            clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

            read(pipe_time[0], &time_stop, sizeof(struct timespec));

            messwerte[i] = time_stop.tv_nsec;

            if (time_start.tv_nsec > time_stop.tv_nsec) {
                messwerte[i] += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
            }

            messwerte[i] = (messwerte[i] - time_start.tv_nsec);

            sum += messwerte[i];

            printf("werte %ld ns\n", messwerte[i]);
        }

        // Display the result
        printf("A context switch takes %ld ns\n", (sum - removeCalculatedOverHeadTime())/1000);

        close(pipe_time[0]);
        wait(NULL);
    }

    return 0;
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