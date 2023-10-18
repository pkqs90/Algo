// https://codeforces.com/contest/1849/submission/224844993

#pragma  comment(linker, "/STACK:36777216")

#include<bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 1e6 + 7;
const ll Mod = 1e9 + 7;

int cases, n, a[N], pos[N], rmq[2][N][20], lg[N];

ll res = 0;

int get_max(int l, int r) {
    int d = lg[r - l + 1];
    return max(rmq[0][r][d], rmq[0][l + (1 << d) - 1][d]);
}

int get_min(int l, int r) {
    int d = lg[r - l + 1];
    return min(rmq[1][r][d], rmq[1][l + (1 << d) - 1][d]);
}

void dfs(int l, int r) {
    // cout << l << ' ' << r << endl;
    if (l >= r) return;
    int x = get_max(l, r);
    int dx = pos[x];
    // cout << l << ' ' << r << ' ' << x << ' ' << dx << endl;
    if (l != dx) {
        if (r - dx < dx - l) {
            int mn = x;
            for (int i = dx; i <= r; ++i) {
                mn = min(mn, a[i]);
                int a = l, b = dx - 1;
                if (get_min(l, dx) > mn) break;
                while (a < b) {
                    int mid = (a + b + 1) >> 1;
                    if (get_min(mid, dx) > mn) b = mid - 1;
                    else a = mid;
                }
                res += (a - l + 1);
                // cout << i << ' ' << a << ' ' << l << ' ' << "#" << endl;
            }
        } else {
            int mn = x;
            for (int i = dx - 1; i >= l; --i) {
                mn = min(mn, a[i]);
                int a = dx, b = r;
                while (a < b) {
                    int mid = (a + b + 1) >> 1;
                    if (get_min(dx, mid) < mn) b = mid - 1;
                    else a = mid;
                }
                res += (a - dx + 1);
                // cout << i << ' ' << a << ' ' << l << ' ' << "#" << endl;
            }
        }
    }
    dfs(l, dx - 1);
    dfs(dx + 1, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    // cin >> cases;
    // while (cases --) {
    cin >> n;
    for (int i = 2; i < N; ++i) {
       lg[i] = lg[i / 2] + 1;
    }
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pos[a[i]] = i;
        rmq[0][i][0] = a[i];
        rmq[1][i][0] = a[i];
    }
    for (int i = 1; i < 20; ++i) {
        for (int j = 1; j <= n; ++j) {
            rmq[0][j][i] = rmq[0][j][i-1];
            rmq[1][j][i] = rmq[1][j][i-1];
            if (j >= (1 << (i-1) + 1)) {
                rmq[0][j][i] = max(rmq[0][j][i], rmq[0][j - (1 << (i-1))][i-1]);
                rmq[1][j][i] = min(rmq[1][j][i], rmq[1][j - (1 << (i-1))][i-1]);
            }
        }
    }
    // for (int i = 1; i <= n; ++i) {
    //     for (int j = i; j <= n; ++j) {
    //         cout << i << ' ' <<j << ' ' << get_min(i, j) << ' ' << get_max(i, j) << endl;
    //     }
    // }
    dfs(1, n);
    cout << res << endl;
    // }
}