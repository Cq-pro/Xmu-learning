#include <stdio.h>
#include <stdlib.h>

int main()
{
    int a[5];
    int i;
    int t;
    int q;
    for(i=0; i<5; i++)
        scanf("%d",&a[i]);
    for(i=0; i<5; i++)//计算外循环次数
    {
        for(int j=0; j<5-i; j++)
        {
            t=a[j];
            a[j]=a[1+j];
            a[j+1]=t;
        }
    }
    for (q=1; q<=5; q++)
        printf("%d",a[q]);

}
