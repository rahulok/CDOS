#include <stdio.h>
#include <stdlib.h>

int findmin(int arrT[], int exe[], int n)         //To find the Index of the process that is going to run next and make its exe as 1
{
    int minIndex, min;
    min = 9999;
    int i;
    for(i=0;i<n;i++)
    {
        if( exe[i]!= 1  &&  arrT[i]<min)
        {
            min = arrT[i];
            minIndex = i;
        }
    }
    exe[minIndex] = 1;
    return minIndex;
}


int main()
{
    int n,i,j,minIndex;
    printf("Enter the number of processes\n");
    scanf("%d",&n);
    int p[n],exe[n],arrivalT[n],burstT[n],workingOrder[n+1];
    //Working order will store the time order of process executing
    float totalTAT=0, totalWT=0;
    workingOrder[0] = 0;       //First time will be ofcourse 0
    printf("Enter the arrival time and burst time of %d processes\n",n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&arrivalT[i]);
        scanf("%d",&burstT[i]);
        exe[i]=0;              //First all exe will be 0 because no process has run yet
        p[i] = i;
    }
    i=1;       //Because workingOrder[0] = 0
    printf("Process\tStarting\tEnd\tTAT\tWT\n");
    for(j=0;j<n;j++)
    {
        minIndex = findmin(arrivalT,exe,n);
        workingOrder[i] = burstT[minIndex] + workingOrder[i-1];
        int tat = workingOrder[i]-arrivalT[minIndex];
        if(j==0)      //For first process WT will be 0
            printf("P%d\t%d\t\t%d\t%d\t%d\n",minIndex,workingOrder[i-1],workingOrder[i],tat,0);
        else
            printf("P%d\t%d\t\t%d\t%d\t%d\n",minIndex,workingOrder[i-1],workingOrder[i],tat,tat-burstT[minIndex]);
        totalTAT += tat;
        totalWT += (tat-burstT[minIndex]);
        i++;
    }
    printf("Average TAT = %f\n",totalTAT/n);
    printf("Average WT = %f",totalWT/n);
    return 0;
}
