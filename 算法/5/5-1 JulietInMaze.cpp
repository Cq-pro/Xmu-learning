
#include <iostream>
#include <vector>
using namespace std;

void printMaze(vector<vector<int>> maze, int n, int m)
{
	for (unsigned i = 0; i < maze.size(); i++)
	{
		vector<int> maze_temp = maze[i];
		for (unsigned j = 0; j < maze_temp.size(); j++)
		{
			cout << maze_temp[j] << "\t";
		}
		cout<<"\n";
	}
}
int main()
{
  //接收n、m、k（行、列、封闭房间数）
	int n,m, k;
	cin >>n>>m>>k;

	//创建一个n行m列的二维向量存储迷宫（初始化为1，即全部开放）
	vector<vector<int>> maze(n, vector<int>(m,1));
	printMaze(maze, n, m);

	//接下来接收k个封闭房间的坐标 改变二维向量maze里对应坐标的值为-1
	for (int i = 0; i < k; i++)
	{
		int line, col;
		cin >>line>>col;
		maze[line-1][col-1] = -1;
	}
	printMaze(maze, n, m);

	//接下来接收Romeo和Juliet的坐标
	vector<int> Romeo(2);
	vector<int> Juliet(2);
	cin >> Romeo[0] >> Romeo[1];
	cin >> Juliet[0] >> Juliet[1];
	cout << "Romeo:" << Romeo[0] <<"\t" << Romeo[1]<<"\n";
	cout << "Juliet:" << Juliet[0] << "\t" << Juliet[1] << "\n";

	//向四个方向移动
	const int dx[] = { 0, 0, 1, -1 }; // 分别表示向右、向左、向下、向上移动
	const int dy[] = { 1, -1, 0, 0 };

}

