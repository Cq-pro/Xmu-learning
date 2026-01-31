
#include <stdio.h>
#include <stdlib.h>

float f2(unsigned n)
{
   float sum=1,power=1;
   for(unsigned i=0;i<=n-1;i++)
   {
       power*=2;
       sum+=power;
   }
   return sum;
}

int main()
{
    printf("%f",f2(24));
}
