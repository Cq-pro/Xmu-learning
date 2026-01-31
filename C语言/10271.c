#include <stdio.h>
int main()
{
    int i,year,month,date,days;
    int m[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d/%d/%d",&year,&month,&date);
    i=1;
    date=31;
    for(; i=month+1; i++);
    {
        date=date+m[i];
    }

    printf("&d",date);

}
