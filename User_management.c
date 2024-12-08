#include<stdio.h>
#include<string.h>
#include<stdlib.h>


#define MAX_USER  10
#define CREDENTIAL_LENGTH  30

typedef struct
{
    char username[CREDENTIAL_LENGTH];
    char password[CREDENTIAL_LENGTH];
}User;

User them[MAX_USER];
int user_count=0;

void register_user();
int login_user();
//helps in matching the register and login credentials of user
void fix_fgets_input(char*);//backslash n ko backslash 0 krne ka input
void input_credential(char* username, char* password);

int main()
{
    while(1)
    {
        int option;
        int user_index;
        printf("\n\n*Welcome toh user management*\n");
        printf("\n1. Register");
        printf("\n2. Login");
        printf("\n3. Exit");
        printf("\nEnter the option of your choice:\n");
        scanf("%d", &option);

        //To consume extra ENTER key which registers in input buffer of scanf function: thus consumes extra enter key
        getchar();


        switch (option)
        {
        case 1:
            register_user();
            break;

            case 2:  
                user_index = login_user();
                if (user_index >= 0)
                {
                    printf("Login successfull !, Welcome %s", them[user_index].username);
                }
                else
                {
                    printf("Incorrect username and password\n");
                }
            
        case 3:
            printf("\nExiting the program.\n");
            return 0;

                    default:
                        printf("Invalid option, please try again!");
                        break;
        }
    }
    return 0;
}

void register_user()
{
    if(user_count == MAX_USER)
    {
        printf("\nMaximum user allowed are %d, Limit reached. Hence please try again later\n", MAX_USER);
        return;
    }

    int new_index = user_count;
    printf("\nRegister a new user.");
    
        //scanf("%[^\n]s", alpha);  this bracket ensure that string will inserted till the new line is not entered 
    
    input_credential(them[new_index].username, them[new_index].password);

    user_count++;
    printf("\nRegistration successful\n");

    //printf("%s-%s", them[new_index].username, them[new_index].password);
 
}

int login_user()
{
    char username[CREDENTIAL_LENGTH], password[CREDENTIAL_LENGTH];
    // printf("Enter Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    
    fix_fgets_input(username);
    input_credential(username, password);

    

    for (int i = 0; i < user_count; i++)
    {
        if(strcmp(username, them[i].username)==0 && strcmp(password, them[i].password)==0)
        {
            return i;
        }
    }
    //printf("%s-%s", username, password);

    return -1;
}

void fix_fgets_input(char* string)
{
    int index = strcspn(string, "\n");
    string[index] == "\0";
}

void input_credential(char* username, char* password)
{
    printf("\nEnter Username: ");
    fgets(username, CREDENTIAL_LENGTH, stdin);
    
    fix_fgets_input(username);
    printf("\nEnter password: ");
    fgets(password, CREDENTIAL_LENGTH, stdin);
    fix_fgets_input(password);
}