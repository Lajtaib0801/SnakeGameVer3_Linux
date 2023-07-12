#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>

#define ROWS 20
#define COLS 20


void move_snake(char* map, char dir, int* row, int* col);
void draw(char* map, int row, int col);
void fill(char* map);
char _getch(void);
void end_game(void);

int main(void)
{

    char* map = malloc((ROWS * COLS) * sizeof(char));

    fill(map);


    int curr_r = 10;
    int curr_c = 10;
    char direction = '\0';
    do 
    {
        draw(map, curr_r, curr_c);
        direction = _getch();
        move_snake(map, direction, &curr_r, &curr_c);


    } while (direction != 'q');


    free(map);
    return 0;
}


void fill(char* map)
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if (i == 0 || j == 0 || i == ROWS - 1 || j == COLS - 1)
                map[i * COLS + j] = '1';
            else
                map[i * COLS + j] = ' ';
        }
    }
}
void move_snake(char* map, char dir, int* row, int* col)
{
    if (dir == 'w')
    {
        if (*row == 1)
            end_game();
        map[(*row) * COLS + (*col)] = ' ';
        (*row)--;
    }
    else if (dir == 'a')
    {	
        if (*col == 1)
            end_game();
        map[(*row) * COLS + (*col)] = ' ';
        (*col)--;
    }
    else if (dir == 's')
    {	
        if (*row == ROWS-2)
            end_game();
        map[(*row) * COLS + (*col)] = ' ';
        (*row)++;
    }
    else if (dir == 'd')
    {	
        if (*col == COLS-2)
            end_game();
        map[(*row) * COLS + (*col)] = ' ';
        (*col)++;
    }
}
void draw(char* map, int row, int col)
{
    printf("\033[H\033[J");
    map[row * COLS + col] = '#';
    for (int i = 0; i < ROWS; i++)
    {
        printf("\t\t");
        for (int j = 0; j < COLS; j++)
        {
            printf("%c", map[i * COLS + j]);

        }
        printf("\n");
    }
}


char _getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    //printf("%c\n", buf);
    return buf;
}

void end_game(void)
{
    printf("\033[H\033[J");
    printf("GAME OVER\n");
    exit(0);
}







