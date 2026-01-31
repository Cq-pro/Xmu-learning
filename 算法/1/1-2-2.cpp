// 1-2-2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//先输入字符串个数 再输入由字母组成的字符串 输出它的序号 比如b=2 aa=27 zz=26*27
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int C(int n, int m)//计算组合数
{
    int fenzi = 1;
    int fenmu = 1;
    for (int i = 1; i <= m; i++)
    {
        fenzi *= n - i + 1;
        fenmu *= i;
    }
    return fenzi / fenmu;
}

int findorder(char code[], int num)
{
    int order = 0;
    int length = strlen(code);
    if (length < 1) return 0;
    char first = code[0];//首字母
    for (int i = 1; i <= first - 'a' - num; i++)//为什么要排除num:求从a到首字母那个数之前的组合数
    {
        order += C(26 - i - num, length - 1);// 这什么啊！
    }
    if (length > 1)
    {
        order += findorder(&code[1], first - 'a' + 1);
    }
    return order;
}


int main()
{
    int num = 0;
    //cout << "请输入字符串个数：";
    cin >> num;
    // 动态分配 10 个字符的数组
    int* orders = new int[num];
    for (int i = 0; i <num; i++)//对每个字符串操作
    {
        char code[7];
        cin >> code;
        orders[i] = 0;
        if (!code[0])
            continue;
        int n = strlen(code);
        for (int j = 1; j < n; j++)
        {
            orders[i]+=  C(26, j);
        }
        orders[i]+=findorder(code, 0) + 1;
    }
    for (int i = 0; i  < num; i++)
    {
        cout << orders[i] << endl;
    }

    // 释放动态分配的内存
    delete[] orders;
    return 0;
}
