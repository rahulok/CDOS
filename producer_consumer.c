#include <stdio.h>

int mutex = 1;

void wait(int* mutex)
{
    while(*mutex==0){
        printf("Infinite loop");
    }
    (*mutex)--;
}

void signal(int* mutex)
{
    (*mutex)++;
}

void producer(int *empty,int* full,int* mutex)
{
    wait(mutex);
    /*if( *empty == 0 )
    {
        printf("Buffer is full, cant produce\n");
        return;
    }*/
    wait(empty);
    signal(full);
    printf("empty is %d\n",(*empty)) ;
    printf("full is %d\n",(*full));
    printf("Item produced\n");
    signal(mutex);
}

void consumer(int* empty,int* full,int *mutex)
{
    wait(mutex);
    /*if(*full == 0)
    {
        printf("Buffer is empty nothing to consume\n");
        return;
    }*/
    wait(full);
    signal(empty);
    printf("empty is %d\n",(*empty)) ;
    printf("full is %d\n",(*full));
    printf("Item consumed\n");
    signal(mutex);
}

int main()
{
    int choice;
    int empty=5,full=0;
    while(1)
    {
        printf("Enter the choice\n1.Producer\n2.Consumer\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1: producer(&empty,&full,&mutex);
                    break;
            case 2: consumer(&empty,&full,&mutex);
                     break;
            default: exit(0);
        }
    }
    return 0;
}
