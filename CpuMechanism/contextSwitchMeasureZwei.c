
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

long removeCalculatedOverHeadTime();

int main()
{
    // Make sure this parent process is tied to one core only
/*    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(0, &mask);
    if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
    {
        perror("ERROR: sched_setaffinity (main)\n");
        return EXIT_FAILURE;
    }*/

    // Create 2 pipes in advance for the parent and child processes (IPC)
    // One for a data exchange and one to exchange the measured time
    int pipe_data[2] = {0, 0};
    int pipe_time[2] = {0, 0};
    long elapsedTime = 0;
    long totalTime = 0;

    if (pipe(pipe_data) < 0)
    {
        perror("ERROR: pipe (data)\n");
        return EXIT_FAILURE;
    }
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
/*        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(0, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("ERROR: sched_setaffinity (main)\n");
            return EXIT_FAILURE;
        }*/

        close(pipe_data[0]); // make it unidirectional (write only)
        struct timespec time_stop;

        // Make the OS perform a coupe of context switches by accounting for random events, i.e., other OS related activities
        for (size_t i = 0; i < 1000; ++i)
        {
            write(pipe_data[1], "abc", 4); // send something off to the parent through this pipe
        }

        // End time measurement & pipe it through the parent
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_stop);
        close(pipe_time[0]); // make it unidirectional (write only)
        write(pipe_time[1], &time_stop, sizeof(struct timespec)); // send something off to the parent through this pipe

        // Clean up
        close(pipe_data[1]);
        close(pipe_time[1]);
    }
    else // parent
    {
        char buffer[4] = "";
        struct timespec time_stop;
        close(pipe_data[1]); // make it unidirectional (read only)

        // Start time measurement
        struct timespec time_start;
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

        // Make the OS perform a couple of context switches by accounting for random events, i.e., other OS related activities
        for (size_t i = 0; i < 4; ++i)
        {
            read(pipe_data[0], buffer, 4);
        }

        // Extract the time measurement from the child through this pipe
        read(pipe_time[0], &time_stop, sizeof(struct timespec));

        elapsedTime = time_stop.tv_nsec;

        if (time_start.tv_nsec > time_stop.tv_nsec) {
            elapsedTime += ((long) time_stop.tv_sec - (long) time_start.tv_sec) * 1000000000;
        }

        elapsedTime = (elapsedTime - time_start.tv_nsec);

         // Display the result
         printf("A context switch takes %ld ns\n", (elapsedTime - 2 * removeCalculatedOverHeadTime())/(1000));

        // Clean up
        close(pipe_data[0]);
        close(pipe_time[0]);
    }

    return EXIT_SUCCESS;
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
