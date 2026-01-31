

#include <iostream>
using namespace std;

int halfnumber(int n)
{
    int number = 0;
    if (n / 2 >= 1)
    {
        number += n / 2;
    }
    for (int i = 1; i <=n / 2; i++)
    {
        number += halfnumber(i);
    }
    return number;
}

int main()
{
    int n;
        cin >> n;
    cout <<halfnumber(n)+1;
}
