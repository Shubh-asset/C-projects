#include <stdio.h>
#include <string.h>
//editing password input
#include <unistd.h> // point to current terminal
#include <stdlib.h>
// terminal's function to be edited
#include <termios.h> 


#define MAX_USER 10
#define CREDENTIALS_L 30

typedef struct
{
    char username[CREDENTIALS_L];
    char password[CREDENTIALS_L];
} User;

User user[MAX_USER];
int user_count = 0;

void user_reg();
int login_user();
void fgets_input(char* string);
void user_cred(char* username, char* password);

int main()
{
    int option;
    int user_index;
while (1)
{
    printf("**User management**");
    printf("\n1.Register");
    printf("\n2.Login");
    printf("\n3.Exit");

    
    printf("\nEnter your choice: ");
    scanf("%d", &option);
    getchar(); //consume extra enter key

    switch(option)
    {   case 1:
        printf("Kindly fill your credentials\n");
        user_reg();
        break;

        case 2:
        //printf("Welcome back %s", username);
        user_index = login_user();
        if(user_index>=0)
        {
            printf("login successfull !, welcome %s", user[user_index].username);
        }
        else
        {
            printf("Incorrect username or password!");
        }
        break;

        case 3:
        printf("Exiting the software, Thank you\n");
        break;

        default:
        printf("Incorrect Option, please exiting the program\n");
        break;
    }
}

    return 0;
}

void user_reg()
{
    if (user_count == MAX_USER)
    {
        printf("Maximum limit has been reached for User registration | the registered users are: %d\n", MAX_USER);
        return;
    }
    else
    {
       int new_index = user_count;
       printf("Register a new user\n");

       user_cred(user[new_index].username, user[new_index].password);

       user_count++;
       printf("\nRegistration successful\n");
    }
}

int login_user()
{
    char username[CREDENTIALS_L], password[CREDENTIALS_L];
    fgets(username, CREDENTIALS_L, stdin);

    fgets_input(username);
    user_cred(username, password);
    printf("\n-%s-%s-\n", username, password);

    for(int i = 0; i<user_count; i++)
    {
        if(strcmp(username, user[i].username) == 0 && strcmp(password, user[i].password) == 0)
        {
            return i;
        }
    }
    return -1;
}


void fgets_input(char* string)
{//replacing the backslash n to backslash 0 toh make it null terminated string
    int index = strcspn(string, "/n");
    string[index] = '\0';
}

void user_cred(char* username, char* password)
{
    printf("\nEnter Username: ");
    fgets(username, CREDENTIALS_L, stdin);
    fgets_input(username);

    printf("enter password (masking enabled): \n");
    fflush(stdout);

    //Change terminal properties
    struct termios old_props, new_props;
    tcgetattr(STDIN_FILENO, &old_props);
    new_props = old_props;

    //disable echo and canonical mode
    new_props.c_lflag &= ~(ECHO | ICANON);

    //TCSNOW: flags we changed should get visible easily
    tcsetattr(STDIN_FILENO, TCSANOW, &new_props);

    char ch;
    int i = 0;
    //printf("enter password (masking enabled):");
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if(ch == '\b' || ch == 127)//handle backspace
        {
            if(i>0)
            {
                i--;
                printf("\b \b");
                fflush(stdout);
            }
                
            }
        
        else
        {
            if (i<CREDENTIALS_L - 1)
            {
                password[i++] = ch;
                printf("*");
                fflush(stdout);
            }
            
            
        }    
            
    }
    password[i] = '\0';
    tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
    printf("\n");
    //printf("Enter password: ");
    //fgets(password, CREDENTIALS_L, stdin);
    //fgets_input(password);
}