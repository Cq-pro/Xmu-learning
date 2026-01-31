#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i=-1;unsigned j=2;
    printf("%d\n",i);
    i=i<<7;
    printf("%d\n",i);
    i=i>>8;
    printf("%d\n",i);
    j=j>>15;
    printf("%d\n",i);
    i=i>>j;
    printf("%d\n",i);
}
