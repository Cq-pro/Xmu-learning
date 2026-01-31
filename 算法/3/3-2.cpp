#include<iostream>
#include<string.h>
using namespace std;
const int MAX_N = 201;
const int INF = 0x7fffff;
int n;
int f[MAX_N][MAX_N];

void dp() {

    for (int i = 1; i <= n; i++) {
        f[i][i] = 0;
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            int v = f[i][j];
            for (int k = i + 1; k <= j - 1; k++) {
                v = min(v, f[i][k] + f[k][j]);
                // cout << "update f = " << v << endl;
            }
            f[i][j] = v;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            cin >> f[i][j];
        }
    }
    dp();
    cout << f[1][n] << endl;
}
