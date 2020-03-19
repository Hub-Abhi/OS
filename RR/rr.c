#include<stdio.h>
#include<stdlib.h>
#include"queue.c"

struct process
{
    int pid,arrivaltime,bursttime;
    int lburst;
};

typedef struct process process;

void input(FILE *fin,process *p,int n,int *qt)
{
    char temp[30];
    for(int i=0;i<n;i++)
    {
        fscanf(fin,"%s %d %d",temp,&p[i].arrivaltime,&p[i].bursttime);
        p[i].pid=i;
        p[i].lburst=p[i].bursttime;
    }
    fscanf(fin,"%s %d",temp,qt);
}

void display(process *p,int n,int qt)
{
    printf("\nQuantum Time: %d",qt);
    printf("\nPID\tARRIVAL_TIME\tBURST_TIME\tLEFT_BURST");
    for(int i=0;i<n;i++)
    {
        printf("\nP%d\t\t%d\t\t%d\t\t%d",p[i].pid,p[i].arrivaltime,p[i].bursttime,p[i].lburst);
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
        for(int j=0;j<n;j++)
        {
            if(p[j].arrivaltime>i)
                break;
            else if(p[j].arrivaltime==i)
                enqueue(j);
        }
}

void compute(process *p,int n,int qt)
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

        //Checking if their any process in the queue to run
        if(isempty()==1)
        {
            printf("\nNo Process Running between %d and %d",i,i+1);
            i++;
            checkprocess(p,n,i);
            continue;
        }

        cpindex=dequeue();
        currprocess=p[cpindex].pid;

        while(1)
        {
            if(rt<qt && p[cpindex].lburst>0)
            {
                rt++;
                p[cpindex].lburst--;
                printf("\nRunning Process%d in %d and %d",currprocess,i,i+1);
                i++;
                checkprocess(p,n,i);
                continue;
            }
            if(p[cpindex].lburst==0)
            {
                left--;
            }
            else if(rt==qt)
            {
                enqueue(cpindex);
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
    int qt;

    printf("Enter the File Name to take data from: ");
    scanf("%s",file);

    FILE *fin;
    fin=fopen(file,"r");
    fscanf(fin,"%s%d\n",temp,&n);
    process *p=(process *)malloc(sizeof(process)*n);
    fscanf(fin,"%[^\n]c",temp);

    input(fin,p,n,&qt);
    compute(p,n,qt);
    display(p,n,qt);
    return 0;
}