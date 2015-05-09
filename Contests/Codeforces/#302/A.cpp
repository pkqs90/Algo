#include <bits/stdc++.h>

using namespace std;

const int N = 505;

int n, m, b, mod, f[2][N][N], a[N];

void inline Add(int &x, int y) {
    x += y;
    if (x >= mod) x -= mod;
}

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> n >> m >> b >> mod;
    for (int i = 0; i < n; i ++)
        cin >> a[i];
    f[0][0][0] = 1;
    for (int i = 0; i < n; i ++) {
        int cur = i & 1, nxt = 1 - cur;
        memset(f[nxt], 0, sizeof(f[nxt]));
        for (int j = 0; j <= m; j ++)
            for (int k = 0; k <= b; k ++) {
                Add(f[nxt][j][k], f[cur][j][k]);
                if (k + a[i] <= b && j + 1 <= m) {
                    Add(f[cur][j + 1][k + a[i]], f[cur][j][k]);
                }
            }
    }
    int res = 0;
    for (int i = 0; i <= b; i ++)
        Add(res, f[n & 1][m][i]);
    cout << res << endl;
}
