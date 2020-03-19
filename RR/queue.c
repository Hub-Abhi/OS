const int max=10;
int pwqueue[10];
int f=-1,r=-1;

//something has to be done for the queue limit
void enqueue(int data)
{
    if((r+1)==f || (f==0 && r==max-1))
    {
        printf("Queue Full");
        return;
    }
    if(f==-1)
    {
        f=r=0;
    }
    else if(r==max-1)
    {
        r=0;
    }
    else
    {
        r++;
    }
    pwqueue[r]=data;
}

int dequeue()
{
    if(f==-1)
    {
        printf("Queue Empty");
        return -99;
    }
    int data=pwqueue[f];
    if(f==r)
    {
        f=r=-1;
    }
    else if(f==max-1)
    {
        f=0;
    }
    else
    {
        f++;
    }
    return data;
}

void qdisplay()
{
    printf("\n");
    printf("Elements are: ");
    if(f<=r)
    {
        for(int i=f;i<=r;i++)
        {
            printf("%d ",pwqueue[i]);
        }
    }
    else
    {
        for(int i=f;i<max;i++)
        {
            printf("%d ",pwqueue[i]);
        }
        for(int i=0;i<=r;i++)
        {
            printf("%d ",pwqueue[i]);
        }
    }
    printf("\n");
}

int isempty()
{
    if(f==-1)
        return 1;
    else 
        return 0;
}