// Straightforward but more complicated implementation.
// See C_map.cpp for a better & more elegant solution.

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 4e5 + 7;

struct Seg {
    int l, r, mn;
} t[N * 8];

int tl, tu;

int tot = 0;
int NewNode() {
    return ++ tot;
}

int InitTree(int l, int r) {
    int u = NewNode();
    t[u].mn = 1e9;
    if (l == r) return u;
    int mid = (l + r) >> 1;
    t[u].l = InitTree(l, mid);
    t[u].r = InitTree(mid + 1, r);
    return u;
}

void Insert(int u, int pos, int lim, int top, int bot) {
    if (top == bot) {
        t[u].mn = lim;
        return;
    }
    int mid = (top + bot) >> 1;
    if (pos <= mid) Insert(t[u].l, pos, lim, top, mid);
    if (pos > mid) Insert(t[u].r, pos, lim, mid + 1, bot);
    t[u].mn = min(t[t[u].l].mn, t[t[u].r].mn);
}

int Query(int u, int l, int r, int lim, int top, int bot) {
    if (top > r || bot < l) {
        return 1e9;
    }
    if (t[u].mn > lim) {
        return 1e9;
    }
    if (top == bot) {
        return top;
    }
    int mid = (top + bot) >> 1;
    int tt = Query(t[u].l, l, r, lim, top, mid);
    if (tt != 1e9) return tt;
    return Query(t[u].r, l, r, lim, mid + 1, bot);
}

int n, m, i, j, a[N], b[N]; char ch[N];
bool vis[N];

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    vector<int> vec;
    for (int i = 0; i < m; i ++) {
        scanf("%d%d %c", &a[i], &b[i], &ch[i]);
        vec.push_back(a[i]), vec.push_back(b[i]);
    }
    vec.push_back(n + 1);
    vec.push_back(0);
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
    int sz = vec.size() - 1;
    tot = 0;
    tl = InitTree(0, sz);
    tu = InitTree(0, sz);
    Insert(tl, sz, 0, 0, sz);
    Insert(tu, sz, 0, 0, sz);
    for (int i = 0; i < m; i ++) {
        a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin();
        b[i] = lower_bound(vec.begin(), vec.end(), b[i]) - vec.begin();
    }
    for (int p = 0; p < m; p ++) {
        i = a[p], j = b[p];
        if (vis[i]) {
            printf("0\n");
            continue;
        }
        vis[i] = true;
        if (ch[p] == 'U') {
            int p = Query(tl, i + 1, sz, i, 0, sz);
            printf("%d\n", vec[p] - vec[i]);
            int id = upper_bound(vec.begin(), vec.end(), n + 1 - vec[p]) - vec.begin() - 1;
            Insert(tu, j, id, 0, sz);
        } else {
            int p = Query(tu, j + 1, sz, j, 0, sz);
            printf("%d\n", vec[p] - vec[j]);
            int id = upper_bound(vec.begin(), vec.end(), n + 1 - vec[p]) - vec.begin() - 1;
            Insert(tl, i, id, 0, sz);
        }
    }
}
