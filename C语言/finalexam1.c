#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
    //设计一个数组来存中文句子
    int sentence[60];
   scanf("%s",sentence);
    //输入字符串
    int len=strlen(sentence);
    int top=0,end=len-3;//定义两个变量指向开头结尾
    while(top<end)
    {
        for(int p=0; p<3; p++)
            {char temp[3];
        temp[p]=sentence[top+1];
        sentence[top+p]=sentence[end+p];
        sentence[end+p]=temp[p];}
        top++;
        end--;
    }

    //逆序
    printf("%s\n,sentence");//输出
    return 0;
}
