#include <bits/stdc++.h>

using namespace std;

#define ll long long
#define lc(x) (x<<1)
#define rc(x) (lc(x)+1)

const int N = 2e5 + 7;
const ll Mod = 998244353;

int cases, n, a[N], s[N];

struct seg {
    int l, r, mn, mk;
    int mid() {
        return l + r >> 1;
    }
} tree[N << 2];

void buildtree(int l, int r, int x) {
    tree[x].l = l, tree[x].r = r, tree[x].mk = 0;
    if (l == r) {
        tree[x].mn = l;
        return;
    }
    buildtree(l, tree[x].mid(), lc(x));
    buildtree(tree[x].mid() + 1, r, rc(x));
    tree[x].mn = min(tree[lc(x)].mn, tree[rc(x)].mn);
}

void pushdown(int x) {
    if (!tree[x].mk) return;
    int v = tree[x].mk;
    tree[lc(x)].mk += v;
    tree[lc(x)].mn += v;
    tree[rc(x)].mk += v;
    tree[rc(x)].mn += v;
    tree[x].mk = 0;
}

void insert(int l, int r, int v, int x) {
    if (l <= tree[x].l && tree[x].r <= r){
        tree[x].mn += v, tree[x].mk += v;
        return;
    }
    pushdown(x);
    int mid = tree[x].mid();
    if (l <= mid) insert(l, r, v, lc(x));
    if (r > mid) insert(l, r, v, rc(x));
    tree[x].mn = min(tree[lc(x)].mn, tree[rc(x)].mn);
}

// Find left-most value < 0
int query(int l, int r, int x) {
    if (tree[x].mn >= 0) return INT_MAX;
    if (tree[x].l == tree[x].r) {
        if (tree[x].mn < 0) return tree[x].l;
        return INT_MAX;
    }
    pushdown(x);
    int res = query(l, r, lc(x));
    if (res != INT_MAX) return res;
    return query(l, r, rc(x));
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> cases;
    while (cases --){
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        ll res = 0, s0 = 0;
        vector<ll> ans;
        buildtree(1, n, 1);
        for (int i = 1; i <= n; ++i) {
            insert(a[i], n, -1, 1);
            res += a[i];
            int pos = query(1, n, 1);
            if (pos != INT_MAX) {
                insert(pos, n, 1, 1);
                res -= pos;
            } else {
                s0++;
            }
            ans.push_back(res - (1 + s0) * s0 / 2);
        }

        for (int i = 0; i < n; ++i) {
            cout << ans[i] << ' ';
        }
        cout << endl;
    }
}
