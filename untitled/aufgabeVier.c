//
// Created by Animesh Sharma on 15.10.19.
//
#include <stdio.h>
#include <unistd.h>
int aufgabeVier();

int main(int argc, char *argv[]) {
    aufgabeVier();
}
int aufgabeVier(){
    char* ls_args[] = { "/bin/ls" , "-l", NULL};
    //execute the program
    execv(ls_args[0], ls_args);
    //only get here on error
    perror("execv");
    return 0;
}