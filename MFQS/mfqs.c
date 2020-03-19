#include<stdio.h>
#include<stdlib.h>
#include"queue.c"

struct process
{
    int pid,arrivaltime,bursttime;
    int responsetime,turnaroundtime,waitingtime;
    int lburst;
};

typedef struct process process;

void input(FILE *fin,process *p,int n,int qt[3],int *ft)
{
    char temp[30];
    for(int i=0;i<n;i++)
    {
        fscanf(fin,"%s %d %d",temp,&p[i].arrivaltime,&p[i].bursttime);
        p[i].pid=i;
        p[i].lburst=p[i].bursttime;
    }
    fscanf(fin,"%s %d",temp,&qt[0]);
    fscanf(fin,"%s %d",temp,&qt[1]);
    fscanf(fin,"%s %d",temp,&qt[2]);
    fscanf(fin,"%s %d",temp,ft);
}

void display(process *p,int n,int qt[3],int ft)
{
    printf("\nQuantum Time Queue 1: %d",qt[0]);
    printf("\nQuantum Time Queue 2: %d",qt[1]);
    printf("\nQuantum Time Queue 3: %d",qt[2]);
    printf("\nFixed Time: %d",ft);
    printf("\nPID\tARRIVAL_TIME\tBURST_TIME\tTURN_AROUND_TIME\tWAITING_TIME\tRESPONSE_TIME");
    for(int i=0;i<n;i++)
    {
        printf("\nP%d\t\t%d\t    %d\t\t\t%d\t\t    %d\t\t    %d",p[i].pid,p[i].arrivaltime,p[i].bursttime,p[i].turnaroundtime,p[i].waitingtime,p[i].responsetime);
    }
}

//First sorting on the basis of burst time and second on the basis of Arrival time
void sort(process *p,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].bursttime>p[j+1].bursttime)
            {
                process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(p[j].arrivaltime>p[j+1].arrivaltime)
            {
                process temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void checkprocess(process *p,int n,int i)
{
    //Inserting processes into the queue who have arrived
    //All process that will arive will first goto queue 1
        for(int j=0;j<n;j++)
        {
            if(p[j].arrivaltime>i)
                break;
            else if(p[j].arrivaltime==i)
                enqueue(j,1);
        }
}

void compute(process *p,int n,int qt[3],int ft)
{
    int left=n;
    int i=0;
    sort(p,n);
    checkprocess(p,n,i);
    while(left)
    {
        int currprocess=-99;
        int cpindex;
        int rt=0;
        int queue=1;

        //Checking if their any process in the queue to run
        if(isempty(1)==1)
        {
            queue=2;
            if(isempty(2)==1)
            {
                queue=3;
                if(isempty(3)==1)
                {
                    printf("\nNo Process Running between %d and %d",i,i+1);
                    i++;
                    checkprocess(p,n,i);
                    continue;
                }
            }
        }


        cpindex=dequeue(queue);
        currprocess=p[cpindex].pid;
        if(p[cpindex].bursttime==p[cpindex].lburst)
        {
            p[cpindex].responsetime=i-p[cpindex].arrivaltime;
        }

        while(1)
        {
            if(rt<qt[queue-1] && p[cpindex].lburst>0)
            {
                rt++;
                p[cpindex].lburst--;
                printf("\nRunning Process%d in %d and %d",currprocess,i,i+1);
                i++;
                checkprocess(p,n,i);

                //After Fixed time move all process to queue 1
                //A small problem here is if the running process is from queue1 then it will be 
                //moved to the end of queue1 and then all other process of other queues will come.
                if(i%ft==0)
                {
                    if(queue!=1)
                        enqueue(cpindex,queue-1);
                    else
                        enqueue(cpindex,1);
                    shift();
                    break;
                }
                continue;
            }
            if(p[cpindex].lburst==0)
            {
                p[cpindex].turnaroundtime=i-p[cpindex].arrivaltime;
                p[cpindex].waitingtime=p[cpindex].turnaroundtime-p[cpindex].bursttime;
                left--;
            }
            else if(rt==qt[queue-1])
            {
                if(queue<=2)
                    enqueue(cpindex,queue+1);
                else
                    enqueue(cpindex,queue);
            }
            break;
        }
    }

}

int main()
{
    char temp[200];
    char file[20];
    int n;
    int qt[3];
    int ft;

    FILE *fin;
    fin=fopen("mfqs.txt","r");
    fscanf(fin,"%s%d\n",temp,&n);
    process *p=(process *)malloc(sizeof(process)*n);
    fscanf(fin,"%[^\n]c",temp);

    input(fin,p,n,qt,&ft);
    compute(p,n,qt,ft);
    printf("\n");
    display(p,n,qt,ft);
    return 0;
}