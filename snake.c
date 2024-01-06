#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define COLS 60
#define ROWS 30
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

void gotoxy(int x, int y){
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int main(){
    
    int x[1000], y[1000];
    int food_x = rand() % (COLS - 2) + 1;
    int food_y = rand() % (ROWS - 2) + 1; 
    int length = 5;
    int score = 0;
    int direction = RIGHT;
    int quit = 0;

    for(int i=0; i < length; i++){
        x[i] = COLS / 2 - i;
        y[i] = ROWS / 2;
    }

    while(!quit){
        system("cls");

        for(int i=0; i <= COLS; i++){
            gotoxy(i, 0);
            printf("#");
            gotoxy(i, ROWS);
            printf("#");
        }
        
        for(int i=0; i < ROWS; i++){
            gotoxy(0, i);
            printf("#");
            gotoxy(COLS, i);
            printf("#");
        }

        gotoxy(food_x, food_y);
        printf("*");

        for(int i=0; i < length; i++){
            gotoxy(x[i], y[i]);
            printf("o");
        }

        if(kbhit()){
            char key = getch();
            switch(key){
                case UP:
                    direction = UP;
                    break;
                case DOWN:
                    direction = DOWN;
                    break;
                case LEFT:
                    direction = LEFT;
                    break;
                case RIGHT:
                    direction = RIGHT;
                    break;
                case 'q':
                    quit = 1;
                    break;
            }
        }

        for(int i=length - 1; i > 0; i--){
            x[i] = x[i - 1];
            y[i] = y[i - 1];
        }

        switch(direction){
            case UP:
                y[0]--;
                break;
            case DOWN:
                y[0]++;
                break;
            case LEFT:
                x[0]--;
                break;
            case RIGHT:
                x[0]++;
                break;
        }

        if(x[0] == food_x && y[0] == food_y){
            length++;
            score += 10;
            food_x = rand() % (COLS - 2) + 1;
            food_y = rand() % (ROWS - 2) + 1;
        }

        if(x[0] <= 0 || x[0] >= COLS || y[0] <= 0 || y[0] >= ROWS){
            quit = 1;
        }

        Sleep(100);
    }
    
    system("cls");
    printf("Game Over! Your score is: %d\n", score);

    return 0;
}