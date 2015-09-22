// http://hihocoder.com/problemset/problem/1232
// dfs序，强制在线用主席树记录历史

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

struct Seg {
    int l, r, val;
} tree[N * 30];

int root[N], tot;

int Newnode(int q = 0) {
    ++ tot;
    tree[tot].l = tree[tot].r = 0;
    tree[tot].val = tree[q].val;
    return tot;
}

void Insert(int &p, int q, int l, int r, int top, int bot, int val) {
    if (!p) p = Newnode(q);
    if (top <= l && r <= bot) {
        tree[p].val = max(tree[p].val, val);
    } else {
        int mid = l + r >> 1;
        if (top <= mid)
            Insert(tree[p].l, tree[q].l, l, mid, top, bot, val);
        if (bot > mid)
            Insert(tree[p].r, tree[q].r, mid + 1, r, top, bot, val);
        if (!tree[p].l) tree[p].l = tree[q].l;
        if (!tree[p].r) tree[p].r = tree[q].r;
    }
}

int res;
void Calc(int p, int l, int r, int pos) {
    if (!p) return;
    res = max(res, tree[p].val);
    if (l == r) {
        return;
    }
    int mid = l + r >> 1;
    if (pos <= mid) Calc(tree[p].l, l, mid, pos);
    else Calc(tree[p].r, mid + 1, r, pos);
}

struct Edge {
    int v, next;
} e[2][N << 1];

int ecnt[2], first[2][N];

void Addedge(int op, int u, int v) {
    e[op][++ ecnt[op]].v = v, e[op][ecnt[op]].next = first[op][u], first[op][u] = ecnt[op];
}

int timestamp, ll[N], rr[N], depth[2][N];

void Dfs_B(int u, int pre) {
    ll[u] = timestamp ++;
    for (int i = first[1][u]; i != -1; i = e[1][i].next) {
        int v = e[1][i].v;
        if (v == pre) {
            continue;
        }
        depth[1][v] = depth[1][u] + 1;
        Dfs_B(v, u);
    }
    rr[u] = timestamp;
//    cout << u << ' ' << ll[u] << ' ' << rr[u] << endl;
}

int n;
void Dfs_A(int u, int pre) {
    Insert(root[u], root[pre], 0, n - 1, ll[u], rr[u] - 1, u);
//    cout << u << ' ' << ll[u] << ' ' << rr[u] - 1 << "!!!" << ' ' << root[u] << ' ' << root[pre] << ' ' << pre << endl;
    for (int i = first[0][u]; i != -1; i = e[0][i].next) {
        int v = e[0][i].v;
        if (v == pre) {
            continue;
        }
        depth[0][v] = depth[0][u] + 1;
        Dfs_A(v, u);
    }
}

int m, u, v;

int main() {
//    freopen("in.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2) {
        for (int i = 0; i < 2; i ++) {
            ecnt[i] = -1;
            memset(first[i], -1, sizeof(first[i]));
        }
        tot = 0;
        timestamp = 0;
        memset(root, 0, sizeof(root));
        for (int i = 2; i <= n; i ++) {
            scanf("%d", &u), Addedge(0, u, i);
        }
        for (int i = 2; i <= n; i ++) {
            scanf("%d", &u), Addedge(1, u, i);
        }
        Dfs_B(1, 0);
        Dfs_A(1, 0);
        res = 0;
        while (m --) {
            scanf("%d%d", &u, &v);
            u = (u + res) % n + 1;
            v = (v + res) % n + 1;
//            cout << u << '~' << v << ' ' << ll[v] << ' ' << ll[v] << endl;
            res = 0;
            Calc(root[u], 0, n - 1, ll[v]);
            printf("%d %d %d\n", res, depth[0][u] - depth[0][res] + 1, depth[1][v] - depth[1][res] + 1);
        }
    }
}
