#include <iostream>
#include <vector>
using namespace std;

int maxPathSum(vector<vector<int>>& triangle, int n) {
    vector<vector<int>> dp(n, vector<int>(n, 0));

    // 将三角形最后一行的值复制到 dp 数组中
    for (int i = 0; i < n; ++i) {
        dp[n - 1][i] = triangle[n - 1][i];
    }

    // 从倒数第二行开始自底向上计算最大路径和
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = triangle[i][j] + max(dp[i + 1][j], dp[i + 1][j + 1]);
        }
    }

    return dp[0][0]; // 返回顶部的最大路径和
}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> triangle(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            cin >> triangle[i][j];
        }
    }

    cout << maxPathSum(triangle, n) << endl;

    return 0;
}
