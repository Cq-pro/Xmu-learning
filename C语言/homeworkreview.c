#include<stdio.h>
int main()
{
    int t=0;
    int num[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int sumday[100]={0};
    int year,month,day,sum;
    scanf("%d-%d-%d",&year,&month,&day);
    while(year>0&&month>0&&day>0)
    {
        sum=0;
        if((year%4==0&&year%100!=0)||year%400==0)
        {
            for(int i = 0; i < month-1; i++)
            {
                if(i==1)//闰年且二月，不需要加数组中的28，单独加一次29
                    sum = sum + 29;
                else
                    sum = sum + num[i];
            }
            sum = sum + day;
        }
        else
        {
            //平年的话正常相加
            for(int i = 0; i < month-1; i++)
                sum = sum + num[i];
            sum = sum + day;
        }
        sumday[t]=sum;
        t++;
    }
    for(int i=0;sumday[i]>0;i++)
        printf("%d",sumday[i]);
    return 0;
}
