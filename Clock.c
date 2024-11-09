#include<stdio.h>
#include<time.h>

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


int main()
{
    char time[50];
    

    int format;
    printf("\nChoose the time format: ");
    printf("\n1. 24 hour format\n2. 12 hour format\n");
    printf("Enter your choice(1/2): ");
    scanf("%d", &format);

    fill_time(time, format);

    printf("current time: %s", time);

    return 0;

}
