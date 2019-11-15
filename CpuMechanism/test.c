//
// Created by Animesh Sharma on 05.11.19.
//
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv) {
    int *x = malloc(10 * sizeof(int));

    for(int i=0; i < 100; i++) {
        printf("%d \n", *x);
    }

    return 0;
}
