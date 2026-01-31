

#include <iostream>
using namespace std;

int findnum(int number)
{
    int num = 0;
    for (int i = 1; i * i <= number; i++)
    {
        if (number % i == 0)
        {
            num++;
            if (number / i != i)
            {
                    num++;
                   // cout << num<<":"<<number / i << "\n";

            }
                    
        }
    }
    return num;
}

int findlargest(int start, int end)
{
    int largest = 0;
    int i = 0;
    int largestone;
    for (i = start; i <= end; i++)
    {
        if (findnum(i) > largest)
        {
            largest = findnum(i);
            largestone = i;
        }
    }
    //cout << largestone<<" ";
    return largest;
}

int main()
{
    int start, end;
    cin >> start >> end;
    cout << findlargest(start,end);
}
