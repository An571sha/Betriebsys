#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include<string.h>


int aufgabeEins();
int forkAndWaitTest();
int openAndForkTest();
int printInSequence();
int aufgabeVier();
int waitInChild();
int connectOutputWithPipe();

int main(int argc, char *argv[]) {
     //forkAndWaitTest();
     //forkAloneTest();
     //openAndForkTest();
     //printInSequence();
     // waitInChild();
    int input;
    printf( "Enter the values : 1 für Aufgabe1, 2 für Aufgabe 2 usw \n");
    scanf("%d", &input);
    if(input == 1){
        aufgabeEins();
    } else if (input == 2){

    } else if(input == 3){

    } else if( input ==  4){

    }

}

int aufgabeEins(){
    int x = 10;
    printf("Parent prints %d \n", x);
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        x = 50;
        printf("child process has the value of x (x:%d)\n", (int) x);
    } else {
        // parent goes down this path (main)
        x = 30;
        printf("parent process has the value of x (x:%d)\n", (int) x);
    }
    return 0;
} 

int forkAndWaitTest(){
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
         fprintf(stderr, "fork failed\n");
         exit(1);
         } else if (rc == 0) { // child (new process)
         printf("hello, I am child (pid:%d)\n", (int) getpid());
         } else { // parent goes down this path (main)
         int rc_wait = wait(NULL);
         printf("hello, I am parent of %d (rc_wait:%d) (pid:%d)\n",
                   rc, rc_wait, (int) getpid());
         }
     return 0;
}

int openAndForkTest(){
    int openResult = open("./answer.txt", O_CREAT|O_WRONLY);
    printf("(result:%d)\n",(int) openResult);
    printf("hello world (pid:%d)\n", (int) getpid());
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("(result:%d)\n",(int) openResult);
    } else {
        // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int) getpid());
        printf("(result:%d)\n",(int) openResult);
    }
    return 0;
}

//no way we can ensure child before parent 100% without calling wait()
int printInSequence(){
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("child (pid:%d)\n", (int) getpid());
        printf("Hello\n");
    } else {
        // parent goes down this path (main)
        wait(NULL);
        printf("parent of %d (pid:%d)\n",
               rc, (int) getpid());
        printf("Goodbye\n");
    }
    return 0;
}

int aufgabeVier(){
    char * ls_args[] = { "/bin/ls" , "-l", NULL};
    //execute the program
    execv(   ls_args[0],     ls_args);
    //only get here on error
    perror("execv");
    return 2;
}
int waitInChild(){
    printf("Hello, World!(pid:%d)\n",(int) getpid());
    int rc = fork();
    if (rc < 0) { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) { // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        int rc_wait = wait(NULL);
        printf("rc_wait %d",(rc_wait));
    } else { // parent goes down this path (main)
        printf("hello, I am parent of(pid:%d)\n",
               (int) getpid());
    }
    return 0;
}
int connectOutputWithPipe(){
    int array0ForPipe[2];
    int array1ForPipe[2];

    char fixed_str_1[] = "Sharma";
    char fixed_str_2[] = "Animesh";
    char input_str_1[15];
    char input_str_2[15];

    pid_t processId;
    pipe(array0ForPipe);
    pipe(array1ForPipe);

    struct timeval start, end;
    double elapsedTime;


    processId = fork();

    if (processId < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;

        //parent process
    } else if (processId > 0) {

        //close the reading end of the first pipe
        close(array0ForPipe[0]);

        //write on the writing end of first pipe
        write(array0ForPipe[1], fixed_str_1, (strlen(fixed_str_1)+1));

        //close the write of second pipe
        close(array1ForPipe[1]);

        //wait for child process to write on array1ForPipe
        wait(NULL);

        //read from the reading end of second pipe
        read(array1ForPipe[0],input_str_2, sizeof(input_str_2));

        //print from the second pipe
        printf("parent prints %s \n", input_str_2);

        //child process
    } else {

        //close the reading end of second pipe
        close(array1ForPipe[0]);

        //read from the reading end of first pipe
        read(array0ForPipe[0],input_str_1, sizeof(input_str_1));

        //print from the first pipe
        printf("child prints %s \n", input_str_1);

        //close the writing end of first pipe
        close(array0ForPipe[1]);

        //write on the writing end of second pipe
        write(array1ForPipe[1], fixed_str_2, (strlen(fixed_str_2)+1));

    }

    return 0;
}