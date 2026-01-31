#include <stdio.h>
#include <math.h>
int main()
{
    double a,b;
    char c;
    scanf("%lf %c %lf =",&a,&c,&b);
    if (c=='+')
        printf("%.4lf",a+b);
    if (c=='-')
        printf("%.4lf",a-b);
    if (c=='*')
        printf("%.4lf",a*b);
    if (c=='/')
    {
        if (fabs(b-0)<=1e-20)
            printf("Error!");
        else
            printf("%.4lf",a/b);
    }
}
