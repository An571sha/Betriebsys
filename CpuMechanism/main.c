#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

void readFromSorceAndCalculateCost();
void performZeroByteRead();

int main(int argc, char **argv) {
    readFromSorceAndCalculateCost();
    return 0;
}

void readFromSorceAndCalculateCost(){
    struct timeval timer_start,timer_end;

    //starting the timer
    gettimeofday(&timer_start, NULL);
    // number of seconds elapsed since 1.1.1970
    printf("start time = %ld microseconds \n", timer_start.tv_sec + timer_start.tv_usec);

    performZeroByteRead();

    //ending the timer
    gettimeofday(&timer_end, NULL);
    printf("end time = %ld microseconds \n", timer_end.tv_sec + timer_end.tv_usec);

    long timeElapsed = (timer_end.tv_sec - timer_start.tv_sec);
    printf("Time elapsed =  %ld microseconds\n",
           ((timer_end.tv_sec - timer_start.tv_sec)*1000000L +timer_end.tv_usec) - timer_start.tv_usec
    );}

void performZeroByteRead(){
    for (int i=0; i < 1000000; i++) {
        read(0,NULL,0);
    }
}