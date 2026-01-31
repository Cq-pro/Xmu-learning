
//先输入字符串个数 再输入由字母组成的字符串 输出它的序号 比如b=2 aa=27 zz=26*27
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

int findorder(char* code,int num)
{
    int order = 0;
    char codeflag = 'a';
    for (int i = 0; i < num; i++)
    {
        order = order * 26 + (code[i] - codeflag + 1);
        codeflag = code[i]+1;
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
    for (int i = 0; i < num; i++)//对每个字符串操作
    {
        char code[7] = { 0 };
     
             cin >> code;
        
        
        orders[i] = findorder(code, strlen(code));
    }
    for (int i = 0; i < num; i++)
    {
        cout << orders[i] << endl;
    }
    
     // 释放动态分配的内存
    delete[] orders;

}
