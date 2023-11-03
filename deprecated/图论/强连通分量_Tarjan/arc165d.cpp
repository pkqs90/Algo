#include <bits/stdc++.h>

using namespace std;

#define ll long long

const int N = 2005;
const ll Mod = 998244353;

int cases, n, m, a[N], b[N], c[N], d[N], fa[N];

int getf(int x) {
    return fa[x] == x ? x : fa[x] = getf(fa[x]);
}

// ------------------------
//       SCC Template

int dfn[N], low[N], ts; bool ins[N];

vector<int> e[N];
vector<vector<int>> scc;

stack<int> stk;

void dfs(int u) {
    stk.push(u);
    dfn[u] = low[u] = ++ts;
    ins[u] = 1;
    for (int v : e[u]) {
        if (!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if (ins[v]) {
            low[u] = min(low[u], low[v]);
        }
    }
    if (dfn[u] == low[u]) {
        scc.emplace_back();
        while (1) {
            int v = stk.top(); stk.pop();
            scc.back().push_back(v);
            ins[v] = 0;
            if (u == v) break;
        }
    }
}

void tarjan() {
     ts = 0;
     for (int i = 1; i <= n; ++i) {
        if (!dfn[i]) {
            dfs(i);
        }
    }
}
// ------------------------


bool gao() {
    while (1) {
        for (int i = 0; i <= n; ++i) {
            e[i].clear();
            dfn[i] = low[i] = 0;
        }
        for (int i = 1; i <= m; ++i) {
            while (a[i] <= b[i] && c[i] <= d[i]) {
                if (getf(a[i]) == getf(c[i])) {
                    ++a[i], ++c[i];
                } else {
                    break;
                }
            }
            if (c[i] == d[i] + 1) {
                return false;
            }
            if (a[i] == b[i] + 1) {
                continue;
            }
            e[getf(a[i])].push_back(getf(c[i]));
            // cout << a[i] << " => " << c[i] << endl;
        }
        scc.clear();
        tarjan();
        bool cycle = 0;
        for (int i = 0; i < scc.size(); ++i) {
            cycle |= (scc[i].size() > 1);
            for (int j = 1; j < scc[i].size(); ++j) {
                // cout << "Merge " << scc[i][j] << ' ' << scc[i][0] << endl;
                fa[getf(scc[i][j])] = fa[getf(scc[i][0])];
            }
        }
        if (!cycle) {
            return 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> a[i] >> b[i] >> c[i] >> d[i];
    }
    for (int i = 1; i <= n; ++i) {
        fa[i] = i;
    }
    cout << (gao() ? "Yes" : "No") << endl;
}
