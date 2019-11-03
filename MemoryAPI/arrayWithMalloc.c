#include <stdio.h>
#include <stdlib.h>

void aufgabe5();
void aufgabe6();

int main(int argc, char* argv[]) {
    int alter;
    printf("Enter a number between 5 to 7: \n");
    scanf("%d", &alter);

    switch(alter){
        case 5:
            aufgabe5();
            break;
        case 6:
            aufgabe6();
            break;

        default:
            printf("enter something between 5 to 7 you cunt \n");
            break;
    }
    return 0;

}

void aufgabe5() {
    int *data = (size_t) malloc(100 * sizeof(int));
    data[100] = 0;
    printf("Frage 5 \n");
    printf("data[100]: %d \n", data[100]);
}
void aufgabe6() {
    int *data = (size_t) malloc(100 * sizeof(int));
    //data[100] = 0;
    free(data);
    printf("Frage 6 \n");
    for (int i = 0; i < 100; i++) {
        printf("data[100]: %d \n", data[i]);
    }
}
