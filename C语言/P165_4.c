#include <stdio.h>
#include <stdlib.h>

int main()
{
    int number[9]= {9,8,7,6,5,4,3,2,1};
    int newnumber;
    scanf("%d",&newnumber);
    if (number[1]<number[2])
    {
        int new[10]= {newnumber,number[0],number[1],number[2],number[3],number[4],number[5],number[6],number[7],number[8],number[9]};
        int i,j,t;
        for (j=0; j<9; j++)
        {
            for(i=0; i<9-j; i++)
                if (new[i]>new[i+1])
                {
                    t=new[i];
                    new[i]=new[i+1];
                    new[i+1]=t;
                }
        }

        for(i=0; i<10; i++)
            printf("%d",new[i]);
    }
    if (number[1]>number[2])
    {
        int new[10]= {newnumber,number[0],number[1],number[2],number[3],number[4],number[5],number[6],number[7],number[8],number[9]};
        int i,j,t;
        for (j=0; j<9; j++)
            for(i=0; i<9-j; i++)
                if (new[i]<new[i+1])
                {
                    t=
                    new[i]=new[i+1];
                    new[i+1]=t;
                }
        for(i=0; i<10; i++)
            printf("%d",new[i]);
    }
    return 0;
}
