#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

int a[N], vis[N], n;
vector<int> u, v;
vector<vector<int>> vec;

bool Gao() {
    for (int i = 1; i <= n; i ++) {
        if (a[i] == i) {
            for (int j = 1; j <= n; j ++) {
                if (i != j) u.push_back(i), v.push_back(j);
            }
            return true;
        }
    }
    if (n & 1) return false;
    for (int i = 1; i <= n; i ++) {
        if (vis[i]) continue;
        vector<int> temp;
        int j = i;
        while (!vis[j]) {
            temp.push_back(j);
            vis[j] = true;
            j = a[i];
        }
        vec.push_back(temp);
        if (temp.size() & 1) return false;
    }
    for (int i = 0; i < vec.size(); i ++) {
        if (vec[i].size() == 2) {
            u.push_back(vec[i][0]), v.push_back(vec[i][1]);
            for (int j = 0; j < vec.size(); j ++) {
                if (i != j) {
                    for (int k = 0; k < vec[j].size(); k ++) {
                        u.push_back(vec[i][k & 1]);
                        v.push_back(vec[j][k]);
                    }
                }
            }
            return true;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }
    if (Gao()) {
        puts("YES");
        for (int i = 0; i < n - 1; i ++) {
            printf("%d %d\n", u[i], v[i]);
        }
    } else {
        puts("NO");
    }
}
