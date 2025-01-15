#include<stdio.h>
#include<stdlib.h>
#include <termios.h>
#include<unistd.h>

#define HEIGHT 20
#define WIDTH 60

int fruit_x, fruit_y;
int score;
int head_x, head_y;

void clear_screen();

struct termios old_props;
void set_terminal_attributes();
void reset_terminal_attributes();
void draw();

int main()
{
    set_terminal_attributes();
    draw();

    return 0;
}

void draw()
{
    clear_screen();
    printf("\t Welcome to The Snake Game");

    printf("\n");
    for(int i = 0; i <HEIGHT + 2; i++)
    {
        printf("#");
    }

    for(int i = 0; i<HEIGHT; i++)
    {
        printf("\n#");
        for(int j = 0; j < WIDTH; j++)
        {
    //i = y-axis
    //j = x-axis
            if(i == head_y && j == head_x)
            {
                printf("O");
            }
            else if( i == fruit_y && j == fruit_x)
            {
                printf("F");
            }
            else{
                printf(" ");
            }
        }
        printf("#");    
    }

    printf("\n");
    for(int i = 0; i <WIDTH + 2; i++)
    {
        printf("#");
    }
    printf("\n");

    printf("Score: %d", score);
}

void clear_screen()
{
    #ifdef _WIN32
        system("cls");
    #else   
        system("clear");
    #endif
}

void set_terminal_attributes()
{
    tcgetattr(STDIN_FILENO, &old_props);

    atexit(reset_terminal_attributes);

    struct termios new_props = old_props;
    new_props.c_lflag &= ~(ECHO|ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    if (tcgetattr(STDIN_FILENO, &old_props) == -1) 
    {
        perror("tcgetattr");
        // Handle the error
    }
}

void reset_terminal_attributes()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}