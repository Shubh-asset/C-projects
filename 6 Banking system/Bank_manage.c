#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void create_account();
void deposit_money();
void withdraw_money();
void check_balance();

const char * ACCOUNT_FILE = "account.dat";

typedef struct
{
    char name[20];
    int acc_no;
    int balance;
}Account;

int main(int argc, char const *argv[])
{
    while(1)
    {
        int choice;
        printf("\n\n**Bank management system**\n");
        printf("1. Create account\n2. Deposit money\n3. Withdraw money\n4. Check Balance\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

            switch (choice)
            {
                case 1:
                    create_account();
                    break;

                case 2:
                    deposit_money();
                    break;

                case 3:
                    withdraw_money();
                    break;

                case 4:
                    check_balance();
                    break;

                case 5:
                    printf("Exiting the Bank, Thanks for your visit\n");
                    return 0;
                    break;

                default:
                    printf("Invalid choice\n");
                    break;
            }
        
            
    }

    return 0;
}

void create_account()
{
    Account acc;

//**file handling**//
    FILE *file = fopen(ACCOUNT_FILE, "ab+");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
        return;
    }

    char c;
    do
    {
        c = getchar();
    }
    while(c != '\n' && c != EOF);

    //printf("\nCreating account");
    printf("\nEnter your name: ");
        fgets(acc.name, sizeof(acc.name), stdin);
        int ind = strcspn(acc.name, "\n");
        acc.name[ind] = '\0';
        //scanf("%s", &acc.name );
    printf("Enter your account number: ");
        //fgets(acc.acc_no, sizeof(acc.acc_no), stdin);
        scanf("%d", &acc.acc_no);

    acc.balance = 0;

    fwrite(&acc, sizeof(acc), 1, file);
    fclose(file);

    printf("\nAccount created successfully\n");
}

void deposit_money()
{
    //printf("\nDepositing money");
    FILE * file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL)
    {
        printf("Unable to open the file, better luck next time");
        return;
    }

    int acc_no;
    float money;
    Account acc_r;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);
    printf("Enter the amount you want to deposit: ");
    scanf("%f", &money);

    while(fread(&acc_r, sizeof(acc_r), 1, file))
    {
        if(acc_r.acc_no == acc_no)
        {
            acc_r.balance += money;
//**Overwriting the file by moving cursors in backward direction**//
            fseek(file, -sizeof(acc_r), SEEK_CUR);
            fwrite(&acc_r, sizeof(acc_r), 1, file);

            fclose(file);

            printf("Successfully Deposited %.2f and the current balance is %d",money, acc_r.balance);
        
            return;
        }
    }
    fclose(file);
    printf("Account number %d not found in records", acc_no);

}

void withdraw_money()
{
    FILE * file = fopen(ACCOUNT_FILE, "rb+");
    if(file == NULL)
    {
        printf("Unable to open the file, withdrawing is not possible at this time");
        return;
    }

    int acc_no;
    float money;

    Account acc_w;

   // printf("\nWithdrawing money");
   printf("\nEnter the Account number: ");
   scanf("%d", &acc_no);
   printf("Enter the amount you want to withdraw: ");
   scanf("%f", &money);

    while(fread(&acc_w, sizeof(acc_w), 1, file)!= EOF)
    {
        if(acc_w.acc_no == acc_no)
        {
            if(acc_w.balance < money)
            {
                printf("Insufficient balance");
            }
            else{
                acc_w.balance -= money;
                fseek(file, -sizeof(acc_w), SEEK_CUR); //seek_cur = seek_current
                fwrite(&acc_w, sizeof(acc_w), 1, file);
                printf("Successfully withdrawn %.2f and the current balance is %d", money, acc_w.balance);
            }
            fclose(file);
            return;
        }

    }
    fclose(file);
    printf("Account number %d not found. Hence system failed to withdraw given amount", acc_no);

}

void check_balance()
{
    //printf("\nChecking balance");

    FILE *file = fopen(ACCOUNT_FILE, "rb");
    if (file == NULL)
    {
        printf("\nUnable to open the file!!");
        return;
    }

    int acc_no;
    Account acc_read;
    printf("\nEnter your account number: ");
    scanf("%d", &acc_no);

    while(fread(&acc_read, sizeof(acc_read), 1, file))
    {
        if(acc_read.acc_no == acc_no)
        {
            printf("Your account balance is : %d", acc_read.balance);
            fclose(file);
            return;
        }
    }
    fclose(file);
    printf("Account number %d was not found!", acc_no);

}
