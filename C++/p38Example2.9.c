#include <stdio.h>
#include <stdlib.h>

int f1(unsigned n)
{
   int sum=1,power=1;
   for(unsigned i=0;i<=n-1;i++)
   {
       power*=2;
       sum+=power;
   }
   return sum;
}

int main()
{
    printf("%d",f1(31));
}
