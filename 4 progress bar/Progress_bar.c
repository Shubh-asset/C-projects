#include<stdio.h>
#include<unistd.h> //For sleep
#include<stdlib.h> //used system function for clearing
#include<time.h>   //Random seeding

const int bar_prog=30;
const int m_task= 5;

typedef struct
{
    int id;
    int progress;
    int step;
}Task;
void progress_bar(Task all);
void clear_screen();

    int main(int argc, char const *argv[])
    {
            
        //int id=1, progress=20;
        Task task[m_task];

        //random time seeding
        srand(time(NULL));

        //initialization
            for (int i = 0; i < m_task; i++)
            {
                task[i].id =  i+1;
                task[i].progress = 0;
                task[i].step = rand() % 5 +1 ; 
            }

        int task_incomp = 1; //flag

        while(task_incomp)
        {
            task_incomp = 0; //False, Task is completed

            clear_screen(); //To clear a screen

            for (int i = 0; i < m_task; i++)
            {
                task[i].progress += task[i].step;

                if(task[i].progress >100)
                {
                    task[i].progress = 100;
                }
                if(task[i].progress < 100)
                {
                    task_incomp = 1; //True, as task is not completed yet
                }
                progress_bar(task[i]);
            }
            
            sleep(1);
        }
            
            printf("All tasks are completed");

        return 0;
    }

void clear_screen()
{
    #ifdef _Win32
        system("clear");
    #else
        system("cls");
    #endif
}

void progress_bar(Task all)
{
    int bar_to_show = (all.progress * bar_prog)/100;
    printf("Task %d: [", all.id);

        for(int i=0; i < bar_prog; i++)
        {
            if (i<bar_to_show)
            {
                printf("=");
            }
            else 
            {
                printf(" ");
            }
            
        }

    printf("] %d%%\n", all.progress);
}