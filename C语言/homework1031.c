#include <stdio.h>


int main()
{
   double a=2;
   double n=1;
   double b=1;
   double sum=0;
   double t;
   for (n=1;n<=20;n++)
    {
        sum=sum+a/b;
        t=a;
        a=a+b;
        b=t;
    }
    printf("%f",sum);
}

