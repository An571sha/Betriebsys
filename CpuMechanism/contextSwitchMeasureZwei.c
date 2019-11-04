//
// Created by Animesh Sharma on 04.11.19.
//
// Unix system libraries
#define _GNU_SOURCE
#include <sched.h>
#include <unistd.h>
#include <sys/types.h>

// C standard libraries
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define __CHOSEN_CPU 3 // Select a CPU core to tie the parent and child processes in
#define __BUFFER_SIZE 4 // Used to store data through a pipe sent by the child process
#define __NUMBER_OF_ITERATIONS 1E4 // The number of (desired) context switches per process (parent and child)

int main()
{
    // Make sure this parent process is tied to one core only
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
    int pipe_data[2] = {0, 0};
    int pipe_time[2] = {0, 0};

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
        CPU_SET(__CHOSEN_CPU, &mask);
        if (sched_setaffinity(0, sizeof(cpu_set_t), &mask) < 0)
        {
            perror("ERROR: sched_setaffinity (main)\n");
            return EXIT_FAILURE;
        }*/

        close(pipe_data[0]); // make it unidirectional (write only)
        struct timespec time_stop;

        // Make the OS perform a coupe of context switches by accounting for random events, i.e., other OS related activities
        for (size_t i = 0; i < __NUMBER_OF_ITERATIONS; ++i)
        {
            write(pipe_data[1], "abc", __BUFFER_SIZE); // send something off to the parent through this pipe
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
        char buffer[__BUFFER_SIZE] = "";
        struct timespec time_stop;
        close(pipe_data[1]); // make it unidirectional (read only)

        // Start time measurement
        struct timespec time_start;
        clock_gettime(CLOCK_MONOTONIC_RAW, &time_start);

        // Make the OS perform a couple of context switches by accounting for random events, i.e., other OS related activities
        for (size_t i = 0; i < __NUMBER_OF_ITERATIONS; ++i)
        {
            read(pipe_data[0], buffer, __BUFFER_SIZE); // this is where a context-switch is likely issued by the OS due to the pipe being empty at first, and the parent being blocked
        }

        // Extract the time measurement from the child through this pipe
        read(pipe_time[0], &time_stop, sizeof(struct timespec));


        // Display the result
        printf("A context switch takes %f ns\n", ((double)((time_stop.tv_sec * 1E9 + time_stop.tv_nsec) - (time_start.tv_sec * 1E9 + time_start.tv_nsec))) / (2 * __NUMBER_OF_ITERATIONS));

        // Clean up
        close(pipe_data[0]);
        close(pipe_time[0]);
    }

    return EXIT_SUCCESS;
}
