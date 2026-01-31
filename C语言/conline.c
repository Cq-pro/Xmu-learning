#include <stdio.h>
#include <stdlib.h>

int main()
{
    int T,i;//第一行输入一个T，代表有T组测试数据，T<100
    int num[100]= {0};
    scanf("%d",&T);
    for (i=0; i<T; i++)
    {
        scanf("%d",&num[i]);//输入T个正整数

    }
    char english[10][6]= {"zero","one","two","three","four","five","six","seven","eight","nine"};
    for (i=0; i<T; i++)
    {
        int ge;
        ge=(num[i])%10;
        for(int p=0; english[ge][p]!='\0'; p++)
            printf("%c",english[ge][p]);
        printf(" ");//第一个数
        while(num[i]>10)
        {
            num[i]=num[i]/10;
            int wei;
            wei=num[i]%10;
            for(int p=0;english[wei][p]!='\0' ; p++)
                printf("%c",english[wei][p]);
            printf(" ");
        }
        printf("\n");
    }//只要大于十，就继续输出
    //然后从个位开始一次输出每一位数字对应的英文字母。例如：输入1532，输出two three five one。
    return 0;
}
