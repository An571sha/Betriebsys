#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {

    int x = 100;
    int input;
    printf("Enter number between 1 and 5: ");
    scanf("%d", &input);
    if (input == 1) {
        aufgabe1(&x);
    }
    if (input == 2) {
        aufgabe2(argv);
    }
    if (input == 3) {
        aufgabe3();
    }

    printf("x = %d ", x);

    return 0;
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

void aufgabe2 (char *argv) {
    close(STDERR_FILENO);
    open(".p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc == 0) {
        execvp(argv[0], argv);
    } else {
        int rc_wait = wait(NULL);
    }
    printf("yo");
}
void aufgabe3 () {
        int rc = fork();
        if (rc < 0) {
            // fork failed
            fprintf(stderr, "fork failed\n");
            exit(1);
            } else if (rc == 0) {
            // child: redirect standard output to a file
            close(STDOUT_FILENO);
            open("./p4.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
            // now exec "wc"...
            char *myargs[3];
            myargs[0] = strdup("wc"); // program: wc (word count)
            myargs[1] = strdup("p4.c"); // arg: file to count
            myargs[2] = NULL; // mark end of array
            execvp(myargs[0], myargs); // runs word count
            } else {
            // parent goes down this path (main)
            int rc_wait = wait(NULL);
            }

}
