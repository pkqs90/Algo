// There is no need for using disjoint set union for this problem (though I used it).
// We can just DFS once and get the answer. Not as straightforward, but also not hard to see.

#include <bits/stdc++.h>

using namespace std;

const int Mod = 1e9 + 7;
const int N = 1e5 + 7;

int u[N], v[N], f[N], col[N], op[N], n, m;
vector<int> e[N];
map<pair<int, int>, bool> M;

int getf(int u) {
    return f[u] == u ? u : f[u] = getf(f[u]);
}

bool Dfs(int u) {
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i];
        if (!col[v]) {
            col[v] = 3 - col[u];
            if (!Dfs(v)) return false;
        } else if (col[u] + col[v] != 3) {
            return false;
        }
    }
    return true;
}

int Gao() {
    for (int i = 1; i <= n; i ++) {
        f[i] = i;
    }
    for (int i = 0; i < m; i ++) {
        int fu = getf(u[i]);
        int fv = getf(v[i]);
        if (op[i] == 1) {
            f[fu] = fv;
        }
    }
    for (int i = 0; i < m; i ++) {
        int fu = getf(u[i]);
        int fv = getf(v[i]);
        if (fu > fv) swap(fu, fv);
        if (op[i] == 0) {
            if (fu == fv) return 0;
            if (M.find({fu, fv}) != M.end())
                continue;
            M[{fu, fv}] = true;
            e[fu].push_back(fv);
            e[fv].push_back(fu);
        }
    }
    int cnt = 0;
    for (int i = 1; i <= n; i ++) {
        if (getf(i) == i && !col[i]) {
            col[i] = 1;
            cnt ++;
            if (!Dfs(i)) {
                return 0;
            }
        }
    }
    int res = 1;
    for (int i = 1; i < cnt; i ++)
        res = res * 2 % Mod;
    return res;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++) {
        scanf("%d%d%d", &u[i], &v[i], &op[i]);
    }
    printf("%d\n", Gao());
}
