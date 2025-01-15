#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h> //helps in let the program sleep for a short duration.

void fill_time(char* buffer, int format)
{
    time_t r_time;
    struct tm *current_time;
    
    
    time(&r_time);
    current_time=localtime(&r_time);

    if (format==1)
    {
        strftime(buffer, 50, "%H:%M:%S ", current_time);
    }
    else if (format==2)
    {
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }
    else{
        strftime(buffer, 50, "%I:%M:%S %p", current_time);
    }

    //H is for 24 hour clock | I is for 12 hour clock
        //strftime(buffer, sizeof(buffer), "%H:%M:%S", current_time); 
        //strftime(buffer, 50, "%I:%M:%S %p", current_time);

}

void fill_date(char*buffer)
{
    time_t raw_time;
    struct tm *current_time;

    time(&raw_time);
    current_time=localtime(&raw_time);
    strftime(buffer, 100, "%A, %dth %B, %Y", current_time);   
}

int input_format()
{
    int format;

    printf("\nChoose the time format:");
    printf("\n1. 24 hour format\n2. 12 hour format\n");
    printf("Make the choice: ");
    scanf("%d", &format);
    return format;

}

void clear_screen()
{
    //not necessary to call, just create an illusion of cleared screen as only one line showing at a time.
    // another method is:

    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif

}


int main()
{
    char time[50], date[50];
    int format = input_format();

    // printf("\nChoose the time format: ");
    // printf("\n1. 24 hour format\n2. 12 hour format\n");
    // printf("Enter your choice(1/2): ");
    // scanf("%d", &format);
    while(3){
    fill_date(date);
    fill_time(time, format);

    printf("\n\n\n\n\n\n\n\n\n\n\n\nCurrent time: %s", time);
    printf("\nDate: %s", date);
    sleep(3);
    }
    
    return 0;

}
