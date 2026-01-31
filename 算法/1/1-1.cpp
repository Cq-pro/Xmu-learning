#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

using namespace std;
//输入页码
//输出0-9每个数字出现的次数

void nums(int n ,int num[9])
{
    for(int i = 1; i <= n; i++)
    {
        char page[10];
        //sprintf(page,"%d",i)
        sprintf_s(page,"%d",i);
        for (int j = 0; j <10; j++)
        {
            switch (*(page + j))
            {
            case'0':
                num[0]++;
                break;
            case'1':
                num[1]++;
                break;
            case'2':
                num[2]++;
                break;
            case'3':
                num[3]++;
                break;
            case'4':
                num[4]++;
                break;
            case'5':
                num[5]++;
                break;
            case'6':
                num[6]++;
                break;
            case'7':
                num[7]++;
                break;
            case'8':
                num[8]++;
                break;
            case'9':
                num[9]++;
                break;
         
            } 
        }
    }
    
}

int main()
{
    int n;
    cin >> n;//总页数
    int num[10] = { 0 };
    nums(n,num);
    for (int i = 0; i <= 9; i++)
    {
        cout << num[i] << endl;
    }
    return 0;
}


