#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#if defined(_WIN32) || defined(_WIN64)
    #include <conio.h>
    #include <windows.h>
    #define CLEAR_SCREEN "cls"
    #define SLEEP(ms) Sleep(ms)
    void gotoxy(int x, int y){
        COORD pos = {x, y};
        SetConsoleCursorPosition(GetStHandle(STD_OUTPUT_HANDLE), pos);
    }
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <stdbool.h>
    #define CLEAR_SCREEN "clear"
    #define SLEEP(ms) usleep((ms) * 900)
    void gotoxy(int x, int y){
        printf("\033[%d;%dH", (y)+1, (x)+1);
    }

    int kbhit(){
        struct termios oldt, newt;
        int ch;
        int oldf;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, F_GETFL, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);
        if(ch != EOF){
            ungetc(ch, stdin);
            return 1;
        }
        return 0;
    }

    int getch(void){
        struct termios oldattr, newattr;
        int ch;
        tcgetattr(STDIN_FILENO, &oldattr);
        newattr = oldattr;
        tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
        return ch;
    }

#endif


#define COLS 60
#define ROWS 30

//for Windows
#define UPW 72
#define DOWNW 80
#define LEFTW 75
#define RIGHTW 77

//for linux and MacOS
#define UP 65
#define DOWN 66
#define LEFT 68
#define RIGHT 67

int main(){
    
    int x[1000], y[1000];
    int food_x = rand() % (COLS - 2) + 1;
    int food_y = rand() % (ROWS - 2) + 1;
    int length = 5;
    int score = 0;
    int direction = RIGHT;
    int quit = 0;
    srand(time(NULL));


    for(int i=0; i < length; i++){
        x[i] = COLS / 2 - i;
        y[i] = ROWS / 2;
    }

    while(!quit){
        system(CLEAR_SCREEN);

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

        //Delay
        SLEEP(100);
    }
    
    //Game over message
    system(CLEAR_SCREEN);
    printf("Game Over! Your score is: %d\n", score);

    return 0;
}