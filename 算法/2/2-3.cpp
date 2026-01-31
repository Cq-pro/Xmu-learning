

#include <iostream>
#include <vector>
using namespace std;

int changePoint(vector<int>&num, int n)
{
	for (int i = 0; i < n-1; i++)
	{
		if (num[i+1] < num[i])
		{
			return num[i];
		}
	}
}
int main()
{
	int num = 0;
	cin >> num;
	vector<int> number(num);
	for (int i = 0; i < num; i++)
	{
		cin >> number[i];
	}
	cout <<changePoint(number, num);
	return 0;
}
