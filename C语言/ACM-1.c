#include <stdio.h>240 80 480
#include <stdlib.h>

int paixu(int a,int b,int c)
{
    int t;
    if(a>b)
    {
        t=a;
        a=b;
        b=t;
    }
    if(b>c)
    {
        t=b;
        b=c;
        c=t;
    }

int main()
{
    int N;
    scanf("%d",&N);
    for(int i=0; i<N; i++)
    {
        char a[N][3];
        scanf("\n%c%c%c",&a[i][0],&b[i][1],&c[i][2]);
        paixu(a[i][0],b[i][1],c[i][2]);
    }//ÅÅÐò
     for(int i=0; i<N; i++)
    printf("%c %c %c",a[i][0],b[i][1],c[i][2]);
    return 0;
}

