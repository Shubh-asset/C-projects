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
}Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw =  0};

void input_difficulty();
void clear_screen();
void print_board(char board[BOARD_SIZE][BOARD_SIZE]);
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player);
int check_draw(char board[BOARD_SIZE][BOARD_SIZE]);
void play_game();
void player_move(char board[BOARD_SIZE][BOARD_SIZE]);
void computer_move(char board[BOARD_SIZE][BOARD_SIZE]);
int valid_move( char board[BOARD_SIZE][BOARD_SIZE], int row, int col);

int main()
{
    srand(time(NULL));
    int choice;
    input_difficulty();
    
    do
    {
        play_game(); 
        printf("\n\nDo you want to play again? 1 for yes and 0 for no : ");
        scanf("%d", &choice);

    }while(choice == 1);

    printf("Bye Bye! Thanks for playing the game");

    return 0;
}

//**FUNCTION DEFINITION**//

void input_difficulty()
{
    while(1){
        printf("\nSelect difficulty level!\n");
        printf("1. Human(standard)\n2. God level(impossible to win)");
        printf("\nEnter your choice: ");
        scanf("%d", &difficulty);

            if(difficulty != 1 && difficulty != 2)
            {
                printf("\nInvalid choice! please enter (1/2)");
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
    printf("Tic Tac Toe\n"); 

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        printf("\n");
        for( int j = 0; j < BOARD_SIZE; j++)
        {
            printf(" %c ", board[i][j]);
            if(j < BOARD_SIZE - 1)
            {
                printf("|");
            }
        }
        if(i < BOARD_SIZE - 1)
        {
            printf("\n---+---+---");
        }
    }
    printf("\n");
}

int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player)
{
    for( int i =0; i < BOARD_SIZE; i++)
    {
        //row fixed , checking column
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player)
        {
            return 1; 
        }
        //column fixed checking row
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player)
        {
            return 1;
        }
    }

    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[2][0] == player && board[1][1] == player && board [0][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    {
        return 1;
    }

    return 0;
}

int check_draw(char board[BOARD_SIZE][BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }            
        }       
    }
    return 1;   
}

void play_game()
{
    char board[BOARD_SIZE][BOARD_SIZE] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // random output for chance
    char current_player = rand() % 2 == 0 ? X : O ;

    while(1)
    {
        print_board(board);
        if(current_player == X)
        {
            player_move(board);
            if(check_win(board, X))
            {
                score.player++;
                print_board(board);
                printf("Congratulation! You won!");
                break;
            }
            current_player = O;
        }
        else
        {
            computer_move(board);
            print_board(board);
            if(check_win(board, O))
            {
                score.computer++;
                printf("I won! Better luck next time");
                break;
            }
            current_player = X;
        }
        if(check_draw(board))
        {
            score.draw++;
            printf("Its a draw");
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
        printf("\nplayer X's turn\n");
        printf("\nEnter row and column (1-3) for X: ");
        scanf("%d", &row);
        scanf("%d", &col); 

        row--;
        col--; 

    } while (!valid_move(board, row, col));

    board[row][col] = X;   // converting to zero based indexing
}

void computer_move(char board[BOARD_SIZE][BOARD_SIZE])
{
    /* 
    //int row, col;
    //  do
    //  {
    //      row = rand() % BOARD_SIZE;
    //      col = rand() % BOARD_SIZE;
    //  } while (!valid_move(board, row, col));
    //  board[row][col] = player;   // converting to zero based indexing
    */

//**Algorithm**//
/*
1. immediate win
2. immediate block
3. center if possible
4. corner play
5. play as you wish
*/

    // 1. Immediate win
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            if (board[i][j] == ' ')
            {
                board[i][j] = O;
                if (check_win(board, O))
                {
                    return;
                }
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

//**God Mode**/
    // 3. Center if possible
    if(difficulty == 2)
    {
        if(board[1][1] == ' ')
        {
            board[1][1] = O;
            return;
        }
    
    //4. Corner play
        // if(board[0][0] || board[0][3] || board[3][0] || board[3][3] == ' ')
        // {
            
        // }
    int corner[4][2] = {
        {0,0},
        {0,2},
        {2,0},
        {2,2}
    };

    for( int i = 0; i < 4; i++)
    {
        if(board[corner[i][0]][corner[i][1]] == ' ')
        {
            board[corner[i][0]][corner[i][1]] = O;
            return;
        }
    }
    }

    // 5. Play first available move
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

