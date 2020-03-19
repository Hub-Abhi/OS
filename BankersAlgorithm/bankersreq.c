#include<stdio.h>

void input(FILE *fin,int n,int m,int max[][m],int allo[][m],int avl[m])
{
    char temp[100];
    for(int i=0;i<n;i++)
    {
        fscanf(fin,"%s",temp);
        //MAX INPUT
        for(int j=0;j<m;j++)
        {
            fscanf(fin,"%d",&max[i][j]);
        }
        //ALLOC INPUT
        for(int j=0;j<m;j++)
        {
            fscanf(fin,"%d",&allo[i][j]);
        }
    }
    fscanf(fin,"%s",temp);
    for(int i=0;i<m;i++)
    {
        fscanf(fin,"%d",&avl[i]);
    }
}

void display(int n,int m,int max[][m],int allo[][m],int need[][m],int avl[m])
{

    printf("\n");
    printf("Available Resourse: ");
    for(int i=0;i<m;i++)
    {
        printf("%d ",avl[i]);
    }
    printf("\n");
    printf("MAX  \tALLO \tNEED\n");
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            printf("%d ",max[i][j]);
        }
        printf("\t");
        for(int j=0;j<m;j++)
        {
            printf("%d ",allo[i][j]);
        }
        printf("\t");
        for(int j=0;j<m;j++)
        {
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }
}

int safesequence(int n,int m,int max[][m],int allo[][m],int need[][m],int avl[m])
{
    int temp[m];
    for(int i=0;i<m;i++)
    {
        temp[i]=avl[i];
    }

    int flag[n];
    for(int i=0;i<n;i++)
    {
        flag[i]=0;
    }

    int flag1=0;

    int ss[n],k=0;

    for(int l=0;l<n;l++)
    {
        int kprev=k;
        for(int i=0;i<n;i++)
        {
            if(flag[i]==1)
                continue;
            flag1=1;
            for(int j=0;j<m;j++)
            {
                if(need[i][j]>temp[j])
                {
                    flag1=0;
                    break;
                }
            }
            if(flag1==1)
            {
                ss[k++]=i;
                flag[i]=1;
                for(int j=0;j<m;j++)
                {
                    temp[j]+=allo[i][j];
                }
                break;
            }
        }
        if(kprev==k)
        {
            printf("\nNo Safe Sequence is Possible");
            return 0;
        }
    }

    printf("\nSafe Sequence: ");
    for(int i=0;i<k;i++)
    {
        printf("%d ",ss[i]);
    }
    return 1;
}

int main()
{
    //Variables Needed
    char temp[150];
    int n; //no of process
    int m; //no of resources
    FILE *fin;
    char file[20];
    printf("Enter the File name: ");
    scanf("%s",file);

    fin=fopen(file,"r");
    fscanf(fin,"%s %d",temp,&n);
    fscanf(fin,"%s %d \n",temp,&m);
    fscanf(fin,"%[^\n]c",temp);

    //Arrays Needed
    int max[n][m],allo[n][m],need[n][m],avl[m];

    //take input max and allo
    input(fin,n,m,max,allo,avl);

    //calculate the need
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            need[i][j]=max[i][j]-allo[i][j];
        }
    }

    //display all the details
    display(n,m,max,allo,need,avl);

    //calculate Safe Sequence
    safesequence(n,m,max,allo,need,avl);

    //Checking the Request
    printf("\nEnter the Details of Request\n");
    printf("Enter the process number: ");
    int pno;
    scanf("%d",&pno);
    int req[m];
    printf("Enter the Resourse requests: ");
    for(int i=0;i<m;i++)
        scanf("%d",&req[i]);
    //Checking if request is < need and avl or not
    int flag=1;
    for(int i=0;i<m;i++)
    {
        if(need[pno][i]<req[i]||avl[i]<req[i])
        {
            flag=0;
            break;
        }
    }
    if(flag==1)
    {
        for(int i=0;i<m;i++)
        {
            avl[i]=avl[i]-req[i];
            allo[pno][i]=allo[pno][i]+req[i];
            need[pno][i]=need[pno][i]-req[i];
        }
        flag=safesequence(n,m,max,allo,need,avl);
        if(flag==1)
        {
            printf("\nThe resources can be allocated to the process");
        }
    }
    if(flag==0)
    {
        printf("\nThe resourses cannot be given to the process");
    }
    return 0;
}