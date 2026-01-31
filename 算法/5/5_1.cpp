#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

struct Point
{
    int x, y;
};

const int MAX = 10;
int n, m, k;
int board[MAX][MAX];
int best[MAX][MAX];
int curr_rotation = 0;
int min_rotation = 100000;
int min_count = 0;
bool flag = false;

int dx[8] = { 1, 0, -1, 0, 1, 1, -1, -1 };
int dy[8] = { 0, 1, 0, -1, 1, -1, 1, -1 };

bool Point_check(Point pos)
{
    return pos.x > 0 && pos.x <= n && pos.y > 0 && pos.y <= m && board[pos.x][pos.y] == 0;
}

void upgrade()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            best[i][j] = board[i][j];
    flag = true;
}

void traceBack(int depth, Point pos, int di)
{
    if (depth == m * n - k && pos.x == n && pos.y == m && curr_rotation <= min_rotation)
    {
        if (curr_rotation < min_rotation)
        {
            min_rotation = curr_rotation;
            min_count = 1;
            upgrade();
        }
        else
        {
            min_count++;
        }
        return;
    }
    else
    {
        for (int i = 0; i < 8; i++)
        {
            Point next_pos;
            next_pos.x = pos.x + dx[i];
            next_pos.y = pos.y + dy[i];
            if (Point_check(next_pos))
            {
                board[next_pos.x][next_pos.y] = depth + 1;
                if (depth > 1 && di != i)
                    curr_rotation++;
                if (curr_rotation <= min_rotation)
                    traceBack(depth + 1, next_pos, i);
                board[next_pos.x][next_pos.y] = 0;
                if (depth > 1 && di != i)
                    curr_rotation--;
            }
        }
    }
}

int main()
{
    memset(board, 0, sizeof(board));
    memset(best, 0, sizeof(board));

    cin >> n >> m >> k;
    for (int i = 0; i < k; i++)
    {
        int x, y;
        cin >> x >> y;
        board[x][y] = -1;
    }

    Point luo, ye;
    cin >> luo.x >> luo.y >> ye.x >> ye.y;

    traceBack(1, luo, 0);

    if (flag)
    {
        cout << min_rotation << endl;
        cout << min_count << endl;
        if (min_count == 1)
        {
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= m; j++)
                {
                    cout << best[i][j] << " ";
                }
                cout << endl;
            }
        }
        else
        {
            cout << "No Solution!" << endl;
        }
    }
    else
    {
        cout << "No Solution!" << endl;
    }

    return 0;
}
