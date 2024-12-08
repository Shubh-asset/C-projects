#include<stdio.h>
#include<string.h>

#define MAX_USER 10
#define CREDENTIALS_L 30

typedef struct
{
    char username[CREDENTIALS_L];
    char password[CREDENTIALS_L];
}User;

User user[MAX_USER];
int user_count = 0;

void user_reg();
int login_user();
void fgets_input();
void user_cred();

int main()
{
    printf("**User management**");
    printf("\n1.Register");
    printf("\n2.Login");
    printf("\n3.Exit");

    int option;
    printf("\nEnter your choice:\n");
    scanf("%d", &option);

    switch(option)
    {   case 1:
        printf("Kindly fill your credentials\n");
        registration();
        break;

        case 2:
        //printf("Welcome back %s", username);

        case 3:
        printf("Exiting the software, Thank you\n");
        break;

        default:
        printf("Incorrect Option, please exiting the program\n");
        break;
    }


    return 0;
}

void user_reg()
{

}