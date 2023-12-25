#include <stdio.h>
#include <stdlib.h>

#define COLS 60
#define ROWS 30

int main(){
    int quit = 0;
    while(!quit){
        printf("-");
    }
    printf("+\n");

    for(int j = 0; j < ROWS; j++){
        printf("|");
        for(int i=0; i < COLS; i++){
            printf(".");
        }
        printf("|\n");
    }

    printf("+");
    for(int i=0; i < COLS; i++){
        printf("-");
    }
    printf("+\n");
}