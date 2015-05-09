#include <bits/stdc++.h>

#define  lc(x) (x << 1)
#define  rc(x) (lc(x) + 1)
#define  lowbit(x) (x & (-x))
#define  PI    (acos(-1))
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  PLL   pair<LL, LL>
#define  PB    push_back
#define  MP    make_pair

using namespace std;

const int N = 3005;
const int INF = 1e9 + 7;

int n, m;

vector <int> e[N];
queue <int> Q;

void Bfs(int st, int a[]) {
    for (int i = 1; i <= n; i ++)
        a[i] = INF;
    a[st] = 0;
    Q.push(st);
    while (!Q.empty()) {
        int u = Q.front(); Q.pop();
        for (int i = 0; i < e[u].size(); i ++) {
            int v = e[u][i];
            if (a[v] > a[u] + 1) {
                Q.push(v), a[v] = a[u] + 1;
            }
        }
    }
}

int u, v, f[N][N], s1, t1, l1, s2, t2, l2;

int Gao() {
    if (f[s1][t1] > l1 || f[s2][t2] > l2) {
        return -1;
    }
    int ret = f[s1][t1] + f[s2][t2];
    for (int i = 1; i <= n; i ++)
    for (int j = 1; j <= n; j ++) {
        if (f[s1][i] + f[i][j] + f[j][t1] <= l1 && f[s2][i] + f[i][j] + f[j][t2] <= l2) {
            ret = min(ret, f[s1][i] + f[s2][i] + f[i][j] + f[j][t1] + f[j][t2]);
        }
        if (f[s1][i] + f[i][j] + f[j][t1] <= l1 && f[t2][i] + f[i][j] + f[j][s2] <= l2) {
            ret = min(ret, f[s1][i] + f[t2][i] + f[i][j] + f[j][t1] + f[j][s2]);
        }
    }
    return m - ret;
}

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < m; i ++) {
        scanf("%d%d", &u, &v);
        e[u].PB(v), e[v].PB(u);
    }
    cin >> s1 >> t1 >> l1;
    cin >> s2 >> t2 >> l2;
    for (int i = 1; i <= n; i ++) {
        Bfs(i, f[i]);
    }
    cout << Gao() << endl;
}

