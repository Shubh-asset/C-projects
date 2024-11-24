#include<stdio.h>;
include<unistd.io>;

const int bar_prog=60;
const int m_task=5;

typedef struct
{
    int id;
    int progress;
    int step;
}Task;
void progress_bar(Task all);

    int main(int argc, char const *argv[])
    {
            
        //int id=1, progress=20;
        Task task[m_task];
        //initialization
            for (int i = 0; i < m_task; i++)
            {
                task[i].id =  i+1;
                task[i].progress = 0;
                task[i].step = 4; 
            }
        int task_incomp = 1; //flag
        while(task_incomp)
        {
            sleep(1);
        }
            

        return 0;
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