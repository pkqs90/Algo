// Hash + Segment tree. Fairly straightforward solution.
// If we only use natural overflow with long long as hash, we will get WA.
// Because there is a way to make this kind of hashing collide easily: http://codeforces.com/blog/entry/4898

#include <bits/stdc++.h>

using namespace std;

#define  lc(x)  (x << 1)
#define  rc(x)  (lc(x) + 1)
#define  LL     long long

const int N = 1e5 + 7;
const int Magic = 10007;
const LL Mod = 1e9 + 7;

struct Seg {
    int l, r, len, mk; pair<LL, LL> val;
} tree[N << 2];

char ch[N]; LL po[N], sumpo[N], po2[N], sumpo2[N];

inline void Update(int x) {
    tree[x].val = {tree[lc(x)].val.first * po[tree[rc(x)].len] + tree[rc(x)].val.first,
                   (tree[lc(x)].val.second * po2[tree[rc(x)].len] + tree[rc(x)].val.second) % Mod};
}

inline void Gao(int x, int val) {
    tree[x].mk = val;
    tree[x].val = {sumpo[tree[x].len - 1] * val, sumpo2[tree[x].len - 1] * val % Mod};
}

inline void PushDown(int x) {
    if (tree[x].mk != -1) {
        Gao(lc(x), tree[x].mk);
        Gao(rc(x), tree[x].mk);
        tree[x].mk = -1;
    }
}

void InitTree(int l, int r, int x) {
    tree[x].l = l, tree[x].r = r;
    tree[x].len = r - l + 1;
    tree[x].mk = -1;
    if (l == r) {
        tree[x].val = {ch[l] - '0', ch[l] - '0'};
        return;
    }
    int mid = l + r >> 1;
    InitTree(l, mid, lc(x));
    InitTree(mid + 1, r, rc(x));
    Update(x);
}

void Insert(int l, int r, int x, int val) {
    if (l <= tree[x].l && tree[x].r <= r) {
        Gao(x, val);
        return;
    }
    PushDown(x);
    int mid = tree[x].l + tree[x].r >> 1;
    if (l <= mid) Insert(l, r, lc(x), val);
    if (r > mid)  Insert(l, r, rc(x), val);
    Update(x);
}

pair<LL, LL> Query(int l, int r, int x) {
    if (l <= tree[x].l && tree[x].r <= r) {
        return tree[x].val;
    }
    PushDown(x);
    int mid = tree[x].l + tree[x].r >> 1;
    if (r <= mid) return Query(l, r, lc(x));
    if (l > mid) return Query(l, r, rc(x));
    pair<LL, LL> t1 = Query(l, r, lc(x));
    pair<LL, LL> t2 = Query(l, r, rc(x));
    return {t1.first * po[min(r, tree[x].r) - mid] + t2.first,
            (t1.second * po2[min(r, tree[x].r) - mid] + t2.second) % Mod};
}

int n, m, K, op, l, r;
int main() {
//    freopen("in.txt", "r", stdin);
    sumpo[0] = po[0] = 1;
    sumpo2[0] = po2[0] = 1;
    for (int i = 1; i < N; i ++) {
        po[i] = po[i - 1] * Magic;
        sumpo[i] = sumpo[i - 1] + po[i];
        po2[i] = po2[i - 1] * Magic % Mod;
        sumpo2[i] = (sumpo2[i - 1] + po2[i]) % Mod;
    }
    scanf("%d%d%d", &n, &m, &K);
    m += K;
    scanf(" %s", ch);
    InitTree(0, strlen(ch) - 1, 1);
    while (m --) {
        scanf("%d%d%d%d", &op, &l, &r, &K);
        l --, r --;
        if (op == 1) {
            Insert(l, r, 1, K);
        } else {
            if (K == r - l + 1) {
                puts("YES");
                continue;
            }
            pair<LL, LL> t1 = Query(l, r - K, 1);
            pair<LL, LL> t2 = Query(l + K, r, 1);
//            cout << t1 << ' ' << t2 << endl;
            if (t1 == t2) puts("YES");
            else puts("NO");
        }
    }
}
