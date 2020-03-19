#include<stdio.h>
#include<stdlib.h>

struct process
{
    char pdetail[10];
    int pid;
    int burst_time;
    int turnaround_time;
    int wating_time;
    int response_time;
};

typedef struct process process;

void input(FILE *fin,process *p,int n)
{
    for(int i=0;i<n;i++)
    {
        fscanf(fin,"%s %d",p[i].pdetail,&p[i].burst_time);
    }
}

void compute(process *p,int n)
{
    p[0].response_time=0;
    p[0].turnaround_time=p[0].burst_time;
    p[0].wating_time=p[0].turnaround_time - p[0].burst_time;
    for(int i=1;i<n;i++)
    {
        p[i].turnaround_time=p[i-1].turnaround_time+p[i].burst_time;
        p[i].wating_time=p[i].turnaround_time - p[i].burst_time;
        p[i].response_time=p[i-1].turnaround_time;
    }
}

void display(process *p,int n)
{
    printf("ProcessID\tBurstTime\tTurnaroundTime\tResponseTime\tWaitingTime\n");
    for(int i=0;i<n;i++)
    {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\n",p[i].pdetail,p[i].burst_time,p[i].turnaround_time,p[i].response_time,p[i].wating_time);
    }
}

int main()
{
    char info[100];
    FILE *fin;
    fin = fopen("fcfs.txt","r");
    fscanf(fin,"%[^\n]c",info);
    int n;
    fscanf(fin,"%d",&n);
    if(n==0)
    {
        printf("No Process in Ready Queue\n");
        exit(0);
    }
    process *p=(process *)malloc(n*sizeof(process));
    input(fin,p,n);
    compute(p,n);
    display(p,n);
    return 0;
}