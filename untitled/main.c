#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include<string.h>


int forkAloneTest ();
int forkAndWaitTest();
int openAndForkTest();
int printInSequence();
int aufgabeVier();
int waitInChild();
int connectOutputWithPipe();

int main(int argc, char *argv[]) {
aufgabeVier();
}

int forkAloneTest(){
    printf("Hello, World!(pid:%d)\n",(int) getpid());
    int x = 10;
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("value of x (x:%d)\n", (int) x);
    } else {
        // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int) getpid());
        printf("value of x (x:%d)\n", (int) x);
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
/*    pid_t child_a, child_b;
    int pipefd[2];
    char fixed_str[] = "This will be output to standard out\n";
    child_a = fork();

    if(child_a < 0){
        fprintf(stderr, "fork failed\n");

        //parent process
    }  else if (child_a == 0){

        //close the reading end
        close(pipefd[0]);
        write(pipefd[1],fixed_str, 36);
        close(pipefd[1]);
        child_b = fork();

        if (child_b < 0) {
            fprintf(stderr, "fork failed\n");

            //parent process
        } else if (child_b > 0) {
            printf("parent of %d (pid:%d)\n",(int) getpid());


            //child process
        } else if (child_b == 0) {
            read(pipefd[0],fixed_str,36);
            printf("The String from pipe %s \n",fixed_str);
            close(pipefd[0]);

        }
    } else if (child_a > 0) {
        printf("parent of %d (pid:%d)\n",(int) getpid());

        //child process
    }
    return 0;*/

/*    if (child_a == 0) {
        *//* Child A code *//*
        close(pipefd[0]);          *//* Close unused read end *//*
        write(pipefd[1], "This will be output to standard out\n", 36);
        close(pipefd[1]);

    } else {
        child_b = fork();

        if (child_b == 0) {
            close(pipefd[1]);          *//* Close unused write end *//*
            while (read(pipefd[0], &buf, 1) > 0)
                write(STDOUT_FILENO, &buf, 1);
            write(STDOUT_FILENO, "\n", 1);
            close(pipefd[0]);

        } else {
            *//* Parent Code *//*
        }
    }*/
    int fd1[2];  // Used to store two ends of first pipe
    int fd2[2];  // Used to store two ends of second pipe

    char fixed_str[] = "Sharma";
    char input_str[100];
    pid_t p;

    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }

    scanf("%s", input_str);
    p = fork();

    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }

        // Parent process
    else if (p > 0)
    {
        char concat_str[100];

        close(fd1[0]);  // Close reading end of first pipe

        // Write input string and close writing end of first
        // pipe.
        write(fd1[1], input_str, strlen(input_str)+1);
        close(fd1[1]);

        // Wait for child to send a string
        wait(NULL);

        close(fd2[1]); // Close writing end of second pipe

        // Read string from child, print it and close
        // reading end.
        read(fd2[0], concat_str, 100);
        printf("Concatenated string %s\n", concat_str);
        close(fd2[0]);
    }

        // child process
    else
    {
        close(fd1[1]);  // Close writing end of first pipe

        // Read a string using first pipe
        char concat_str[100];
        read(fd1[0], concat_str, 100);

        // Concatenate a fixed string with it
        int k = strlen(concat_str);
        int i;
        for (i=0; i<strlen(fixed_str); i++)
            concat_str[k++] = fixed_str[i];

        concat_str[k] = '\0';   // string ends with '\0'

        // Close both reading ends
        close(fd1[0]);
        close(fd2[0]);

        // Write concatenated string and close writing end
        write(fd2[1], concat_str, strlen(concat_str)+1);
        close(fd2[1]);

        exit(0);
    }
}