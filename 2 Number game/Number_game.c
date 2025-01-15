#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main() 
{
    int random, guess, no_of_guess=0;
    srand(time(NULL));

    printf("Welcome to the Guessing game (:\n");
    random = rand() % 100 +1; //Generating number 1 to 100
    
    //printf("\nthe random number is %d\n", random);

    do{

        printf("Enter the number of your choice(1 to 100)\n");
        scanf("%d", &guess);
        no_of_guess++;

        if(guess>random)
        {
            printf("guess a smaller number\n");
        }
        else if(guess<random)
        {
            printf("Guess the larger number please\n");
        }
        else
        {
            printf("Congratulation!! you guessed the right number in %d attempts\n", no_of_guess);
        }

    }while(random != guess);

    printf("Hurray!! you finished the game");
    printf("\ncredit: Prashant sir");

    return 0;
}