#include <stdio.h>
#include <stdlib.h>

int main()
{
    int year,month,day;//定义年月日数据
    scanf("%d,/,&d,/,&d",&year,&month,&day);//输入
//判断是否闰年
//如果不是闰年
    int allmonth[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int i=0;
    int sum=0;
    for (i=0; i=month-2; i++)
    {
        sum=sum+allmonth[i];
    }
     printf("%d",allmonth[month]);
    return 0;
}
