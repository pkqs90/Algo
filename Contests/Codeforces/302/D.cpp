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

const int N = 2e5 + 7;
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;

vector <int> e[N]; LL f[N], ans[N];
vector <LL> pre[N], suf[N];

void Gao(int u) {
    f[u] = 1;
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i];
        Gao(v);
        f[u] = f[u] * (1 + f[v]) % MOD;
    }
    pre[u].resize(e[u].size(), 1);
    suf[u].resize(e[u].size(), 1);
    for (int i = 0; i < e[u].size(); i ++) {
        if (i != e[u].size() - 1) pre[u][i + 1] = pre[u][i] * (1 + f[e[u][i]]) % MOD;
    }
    for (int i = e[u].size() - 1; i >= 0; i --) {
        if (i != 0) suf[u][i - 1] = suf[u][i] * (1 + f[e[u][i]]) % MOD;
    }
}

void Dfs(int u, int fa) {
    ans[u] = f[u];
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i];
        f[u] = pre[u][i] * suf[u][i] % MOD;
        if (fa != 0) f[u] = f[u] * (f[fa] + 1) % MOD;
        f[v] = f[v] * (f[u] + 1) % MOD;
        Dfs(v, u);
    }
}

int n, u;

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> n;
    for (int i = 2; i <= n; i ++) {
        scanf("%d", &u);
        e[u].PB(i);
    }
    Gao(1); Dfs(1, 0);
    for (int i = 1; i <= n; i ++)
        printf("%I64d ", ans[i]);
    puts("");
}
