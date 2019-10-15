//
// Created by Animesh Sharma on 14.10.19.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
int aufgabeZweiTeilEins();
int aufgabeZweiTeilZwei();

int main(int argc, char *argv[]) {
   //aufgabeZweiTeilEins();
    aufgabeZweiTeilZwei();
}

int aufgabeZweiTeilEins(){
    int openResult = open("./answer.txt", O_CREAT|O_WRONLY);
    printf("(file_Descriptor:%d)\n",(int) openResult);
    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("(file_Descriptor:%d)\n",(int) openResult);
    } else {
        // parent goes down this path (main)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int) getpid());
        printf("(file_Descriptor:%d)\n",(int) openResult);
    }
    return 0;
}

int aufgabeZweiTeilZwei() {

    int file_descriptor = open("./answer.txt", O_CREAT | O_WRONLY);
    printf("(file_Descriptor:%d)\n",(int) file_descriptor);

    int rc = fork();
    if (rc < 0) {
        // fork failed
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        //write on the file descriptor in child
        write(file_descriptor,"Writng something in child",50);
        printf("(file_Descriptor:%d)\n",(int) file_descriptor);
    } else {
        // parent goes down this path (main)
        wait(NULL);
        printf("hello, I am parent of %d (pid:%d)\n",rc, (int) getpid());
        //writing the file descriptor in parent
        write(file_descriptor,"Writng something in parent",50);
        printf("(file_Descriptor:%d)\n",(int) file_descriptor);
    }
    return 0;
}