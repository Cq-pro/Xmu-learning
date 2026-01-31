#include <stdio.h>
#include <stdlib.h>

int main()
{

    float a,b;
    char c;
    scanf("%f %c %f,=/n",&a, &c, &b);
    if (c=='+')
        printf("%.4f",a+b);
    if (c=='-')
        printf("%.4f",a-b);
    if (c=='*')
        printf("%.4f",a*b);
    if (b==0)
        printf("Error!");
    if (b!=0&&c=='/')
        printf("%.4f",a/b);


}
