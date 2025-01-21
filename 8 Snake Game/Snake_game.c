#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define HEIGHT 30
#define WIDTH 60

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    STOP
};

enum Direction dir;

int fruit_x = 10, fruit_y = 5;
int score;
int head_x = 15, head_y = 10;
int tail_lenght;
int tail_x[100];
int tail_y[100];

void clear_screen();

struct termios old_props;
void set_terminal_attributes();
void reset_terminal_attributes();
void draw();
void setup();
void input();

void game_play();

int input_available();

int main()
{
    srand(time(NULL));
    set_terminal_attributes();
    setup();
    while (1)
    {
        draw();
        input();
        game_play();
        int sleep_time = 3000000 / (score != 0 ? score : 10);
        usleep(sleep_time);
        // sleep(1);
    }

    // exit(0);

    return 0;
}
void input()
{
    if (input_available())
    {
        char ch = getchar();
        switch (ch)
        {
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 'x':
            exit(0);
            break;

        default:
            break;
        }
    }
}

void game_play()
{
    int x = head_x, y = head_y;
    // tail will shift one places one by one
    for (int i = tail_lenght - 1; i > 0; i--)
    {
        tail_x[i] = tail_x[i - 1];
        tail_y[i] = tail_y[i - 1];
    }
    tail_x[0] = head_x;
    tail_y[0] = head_y;

    switch (dir)
    {
    case UP:
        head_y--;
        break;
    case DOWN:
        head_y++;
        break;
    case LEFT:
        head_x--;
        break;
    case RIGHT:
        head_x++;
        break;
    case STOP:
        // Do nothing
        break;
    }
    if (head_x < 0)
    {
        head_x = WIDTH - 1;
    }
    else if (head_x >= WIDTH)
    {
        head_x = 0;
    }
    if (head_y < 0)
    {
        head_y = HEIGHT - 1;
    }
    else if (head_y >= HEIGHT)
    {
        head_y = 0;
    }

    for (int i = 0; i < tail_lenght; i++)
    {
        if (tail_x[i] == head_x && tail_y[i] == head_y)
        {

            printf("\n\t GAME OVER! \n");
            exit(0);
        }
    }

    if (head_x == fruit_x && head_y == fruit_y)
    {
        score += 10;

        tail_lenght++;

        fruit_x = rand() % WIDTH;
        fruit_y = rand() % HEIGHT;
    }
}

// input available from the keyboard
int input_available()
{
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_SET(0, &fds);
    return select(1, &fds, NULL, NULL, &tv);
}

void setup()
{
    head_x = WIDTH / 2;
    head_y = HEIGHT / 2;

    fruit_x = rand() % WIDTH;
    fruit_y = rand() % HEIGHT;
    dir = STOP;

    score = 0;
    tail_lenght;
}

void draw()
{
    clear_screen();
    printf("\t Welcome to The Snake Game");

    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++)
    {
        printf("#");
    }

    for (int i = 0; i < HEIGHT; i++)
    {
        printf("\n#");
        for (int j = 0; j < WIDTH; j++)
        {
            // i = y-axis
            // j = x-axis
            if (i == head_y && j == head_x)
            {
                printf("O");
            }
            else if (i == fruit_y && j == fruit_x)
            {
                printf("F");
            }
            else
            {
                int tail_found = 0;

                for (int k = 0; k < tail_lenght; k++)
                {
                    if (tail_x[k] == j && tail_y[k] == i)
                    {
                        printf("o");
                        tail_found = 1;
                        break;
                    }
                }
                if (!tail_found)
                {
                    printf(" ");
                }
            }
        }
        printf("#");
    }

    printf("\n");
    for (int i = 0; i < WIDTH + 2; i++)
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
    new_props.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    // if (tcgetattr(STDIN_FILENO, &old_props) == -1)
    // {
    //     perror("tcgetattr");
    //     // Handle the error
    // }
}

void reset_terminal_attributes()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}