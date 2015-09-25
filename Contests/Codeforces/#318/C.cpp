// I think this ad-hoc problem is pretty hard ..
// Solution: Consider streching the tree, and finding a path with branches attached to it.

#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <set>
#include <bitset>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 1e5 + 7;

int vis[N], legs[N];
vector<int> e[N];

void Dfs(int u, int pre) {
    if (e[u].size() > 2) {
        legs[u] ++;
        return;
    }
    vis[u] = true;
    for (int i = 0; i < e[u].size(); i ++) {
        int v = e[u][i];
        if (v == pre) continue;
        Dfs(v, u);
    }
}

int n, u, v;

int main() {
    while(scanf("%d", &n) == 1) {
        for (int i = 1; i < n; i ++) {
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        for (int i = 1; i <= n; i ++) {
            if (e[i].size() == 1) {
                Dfs(i, -1);
            }
        }
        for (int i = 1; i <= n; i ++) {
            if (legs[i] == 2) {
                int cnt = 0;
                for (int j = 0; j < e[i].size(); j ++) {
                    cnt += !vis[e[i][j]];
                }
                if (cnt == 1) vis[i] = true;
            }
        }
        for (int i = 1; i <= n; i ++) {
            if (!vis[i]) {
                int cnt = 0;
                for (int j = 0; j < e[i].size(); j ++) {
                    cnt += !vis[e[i][j]];
                }
                if (cnt > 2) {
                    puts("No");
                    return 0;
                }
            }
        }
        puts("Yes");
        for (int i = 1; i <= n; i ++)
            e[i].clear();
        memset(vis, 0, sizeof(vis));
        memset(legs, 0, sizeof(legs));
    }
}
