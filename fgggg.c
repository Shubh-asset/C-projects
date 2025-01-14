#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 3
#define X 'X'
#define O 'O'

typedef struct
{
    int player;
    int computer;
    int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL));
    int choice;
    input_difficulty();

    do
    {
        play_game();
        printf("\n\nDo you want to play again? 1 for yes and 0 for no: ");
        scanf("%d", &choice);
    } while (choice == 1);

    printf("\nBye Bye! Thanks for playing the game!\n");
    return 0;
}

void input_difficulty()
{
    while (1)
    {
        printf("\nSelect difficulty level!\n");
        printf("1. Human (standard)\n2. God level (impossible to win)\n");
        printf("Enter your choice: ");
        scanf("%d", &difficulty);

        if (difficulty != 1 && difficulty != 2)
        {
            printf("\nInvalid choice! Please enter 1 or 2.\n");
        }
        else
        {
            break;
        }
    }
}

void clear_screen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void print_board(char board[BOARD_SIZE][BOARD_SIZE])
{
    clear_screen();
    printf("Score:- Player X: %d, Computer: %d, Draw: %d\n", score.player, score.computer, score.draw);
    printf("\nTic Tac Toe\n");

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < BOARD_SIZE - 1)
                printf("|");
        }
        if (i < BOARD_SIZE - 1)
            printf("\n---+---+---\n");
    }
    printf("\n");
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return 1;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return 1;
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;
    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
                return 0;
        }
    }
    return 1;
}

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};

    char current_player = rand() % 2 == 0 ? X : O;

    while (1)
    {
        print_board(board);
        if (current_player == X)
        {
            player_move(board);
            if (check_win(board, X))
            {
                score.player++;
                print_board(board);
                printf("Congratulations! You won!\n");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board); // Display board after computer move
            if (check_win(board, O))
            {
                score.computer++;
                printf("I won! Better luck next time.\n");
                break;
            }
            current_player = X;
        }
        if (check_draw(board))
        {
            score.draw++;
            printf("It's a draw!\n");
            break;
        }
    }
}

int valid_move(char board[BOARD_SIZE][BOARD_SIZE], int row, int col)
{
    return !(row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE || board[row][col] != ' ');
}

void player_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    int row, col;
    do
    {
        printf("\nPlayer X's turn\n");
        printf("Enter row and column (1-3) for X: ");
        scanf("%d %d", &row, &col);
        row--;
        col--;
    } while (!valid_move(board, row, col));
    board[row][col] = X;
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    // 1. Immediate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                    return;
                board[i][j] = ' ';
            }
        }
    }

    // 2. Immediate block
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = X;
                if (check_win(board, X))
                {
                    board[i][j] = O;
                    return;
                }
                board[i][j] = ' ';
            }
        }
    }

    // 3. Center play
    if (difficulty == 2 && board[1][1] == ' ')
    {
        board[1][1] = O;
        return;
    }

    // 4. Corner play
    int corners[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++)
    {
        if (board[corners[i][0]][corners[i][1]] == ' ')
        {
            board[corners[i][0]][corners[i][1]] = O;
            return;
        }
    }

    // 5. First available move
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                return;
            }
        }
    }
}
