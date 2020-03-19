const int max=100;
int q1[100];
int q2[100];
int q3[100];
int f1=-1,r1=-1;
int f2=-1,r2=-1;
int f3=-1,r3=-1;

//something has to be done for the queue limit
void enqueue(int data,int queue)
{
    int *f,*r;
    int *pwqueue;
    if(queue==1)
    {
        f=&f1;
        r=&r1;
        pwqueue=q1;
    }
    else if(queue==2)
    {
        f=&f2;
        r=&r2;
        pwqueue=q2;
    }
    else
    {
        f=&f3;
        r=&r3;
        pwqueue=q3;
    }
    if(((*r)+1)==(*f) || ((*f)==0 && (*r)==max-1))
    {
        printf("Queue Full");
        return;
    }
    if((*f)==-1)
    {
        (*f)=(*r)=0;
    }
    else if((*r)==max-1)
    {
        (*r)=0;
    }
    else
    {
        (*r)++;
    }
    pwqueue[(*r)]=data;
}

int dequeue(int queue)
{
    int *f,*r;
    int *pwqueue;
    if(queue==1)
    {
        f=&f1;
        r=&r1;
        pwqueue=q1;
    }
    else if(queue==2)
    {
        f=&f2;
        r=&r2;
        pwqueue=q2;
    }
    else
    {
        f=&f3;
        r=&r3;
        pwqueue=q3;
    }
    if((*f)==-1)
    {
        printf("Queue Empty");
        return -99;
    }
    int data=pwqueue[(*f)];
    if((*f)==(*r))
    {
        (*f)=(*r)=-1;
    }
    else if((*f)==max-1)
    {
        (*f)=0;
    }
    else
    {
        (*f)++;
    }
    return data;
}

int isempty(int queue)
{
    int *f,*r;
    int *pwqueue;
    if(queue==1)
    {
        f=&f1;
        r=&r1;
        pwqueue=q1;
    }
    else if(queue==2)
    {
        f=&f2;
        r=&r2;
        pwqueue=q2;
    }
    else
    {
        f=&f3;
        r=&r3;
        pwqueue=q3;
    }
    if((*f)==-1)
        return 1;
    else 
        return 0;
}


//Move all process to the top after every fixed time
void shift()
{
    if(isempty(2)==1 && isempty(3)==1)
        return;
    if(isempty(2)==0)
    {
        while(isempty(2)==0)
        {
            enqueue(dequeue(2),1);
        }
    }
    if(isempty(3)==0)
    {
        while(isempty(3)==0)
        {
            enqueue(dequeue(3),1);
        }
    }
}