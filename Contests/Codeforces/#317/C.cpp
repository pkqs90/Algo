// Take clauses as nodes and literals as edges and turn into graph problem.
// For every node, find an edge pointing to it.
// IMPORTANT: Start DFS at somewhere inside the cycle.
// Consider cases that variables can be assigned immediately, DFS from these nodes (clauses) first.

#include <bits/stdc++.h>

using namespace std;

#define LL  long long

const int N = 2e5 + 7;

int n, m, x, y, vis[N], res[N], use[N], cycle[N];
vector<int> vec[N];
vector<pair<int, int>> node[N], e[N];

void Dfs(int u) {
    if (vis[u]) {
        return;
    }
    vis[u] = true;
    bool cnt = 1;
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i].first;
        int id = e[u][i].second;
        if (use[id]) continue;
//        cout << u << ' ' << v << ' ' << id << endl;
        use[id] = true;
        if (node[id][0].first == v) res[id] = node[id][0].second > 0;
        else res[id] = node[id][1].second > 0;
        Dfs(v);
    }
}

int FindCycle(int u, int pre) {
    if (cycle[u]) return u;
    cycle[u] = true;
    bool cnt = true;
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i].first;
        if (cnt && v == pre) {
            cnt = 0; continue;
        }
        int st = FindCycle(v, u);
        if (st != -1) return st;
    }
    return -1;
}

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    for (int i = 0; i < n; i ++) {
        scanf("%d", &x);
        for (int j = 0; j < x; j ++) {
            scanf("%d", &y);
            vec[i].push_back(y);
            int t = abs(y);
            node[t].push_back({i, y});
        }
    }
    vector<int> v2;
    for (int i = 1; i <= m; i ++) {
        if (node[i].size() == 1) {
            int u;
            u = node[i][0].first;
            v2.push_back(u);
            if (node[i][0].second > 0) res[i] = 1;
            else res[i] = 0;
        } else if (node[i].size() == 2) {
            if (node[i][0].second == node[i][1].second) {
                int u;
                u = node[i][0].first; v2.push_back(u);
                u = node[i][1].first; v2.push_back(u);
                if (node[i][0].second > 0) res[i] = 1;
                else res[i] = 0;
            } else {
                int u = node[i][0].first;
                int v = node[i][1].first;
                e[u].push_back({v, i}), e[v].push_back({u, i});
//                cout << u << ' ' << v << ' ' << i << "~" << endl;
            }
        }
    }
    for (int i = 0; i < v2.size(); i ++) {
//        cout << v2[i] << "!!" << endl;
        Dfs(v2[i]);
    }
    for (int i = 0; i < n; i ++) {
        if (vis[i] == 0) {
            int st = FindCycle(i, -1);
//            cout << st << endl;
            if (st != -1) {
                Dfs(st);
            } else {
                puts("NO");
                return 0;
            }
        }
    }
    puts("YES");
    for (int i = 1; i <= m; i ++)
        printf("%d", res[i]);
    puts("");
}
