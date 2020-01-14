#include <stdio.h>

typedef struct 
{
    int wait;
    int burst;
    int pri;
    int turn;
    int arrival;
    int rem;
    int proc;
}process;


void swap(process* p1,process* p2 )
{
    process temp;
    temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

void sort_proc(process p[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].proc>p[j].proc)
            {
                swap(&p[i],&p[j]);
            }
        }
    }
}

void sort_priority(process p[],int n)
{
    int i,j;
    for(i=0;i<n-1;i++)
    {
        for(j=i+1;j<n;j++)
        {
            if(p[i].pri>p[j].pri)
            {
                swap(&p[i],&p[j]);
            }
        }
    }
}




int main()
{
    int n,i,j,k;
    float total_turn =0, total_wait=0;
    printf("Enter the number of process ");
    scanf("%d",&n);
    process p[n];
    printf("Enter the arrival time,burst time and priority:\n");
    for(i=0;i<n;i++)
    {
        scanf("%d%d%d",&p[i].arrival,&p[i].burst,&p[i].pri);
        p[i].rem = p[i].burst;         //Initially remaining time = burst time
        p[i].proc = i;
    }

    sort_priority(p,n);

    for(i=0,k=0;k<n;i++)    // i keeps track of each second, k = number of process that have completed execution
    {
        for(j=0;j<n;j++)
        {
            if(p[j].arrival<=i && p[j].rem!=0)
            {
                printf("Found process %d\n",p[j].proc);
                p[j].rem--;
                if(!p[j].rem)
                {
                    k++;         //Increase k if remaining time of it becomes 0
                    printf("Value of k is %d\n\n",k);
                    p[j].turn = (i+1) - p[j].arrival;
                    p[j].wait = p[j].turn -p[j].burst;
                }
                break;          //We have to break here because we found a process and gave it 1 sec execution time, now for next second we do i++
            }
        }
    }

    sort_proc(p,n);
    printf("Process\tArrival time\tburst time\twaiting time\tTurnaround time\n");
    for(i=0;i<n;i++)
    {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[i].proc,p[i].arrival,p[i].burst,p[i].wait,p[i].turn);
        total_turn += p[i].turn;
        total_wait += p[i].wait;
    }
    printf("Average waiting time is: %f\n",total_wait/n);
    printf("Average turnaround time is: %f\n",total_turn/n);
    return 0;
}

