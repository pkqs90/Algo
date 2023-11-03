#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  PI    (acos(-1))
#define  EPS   1e-8
#define  MAXN  222222
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000000
#define  lowbit(x) (x&(-x))

using namespace std;

LL fib[MAXN], sum[MAXN], a[MAXN];

void add(LL &x, LL y){
    if(y >= mod) y -= mod;
    x += y;
    if(x >= mod) x -= mod;
    if(x <= - mod) x += mod;
}

struct seg{
    int l, r;
    LL s0, s1;
    LL mk, A;
    int mid(){
        return l + r >> 1;
    }
}tree[MAXN << 2];

void init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r;
    tree[x].s0 = tree[x].s1 = tree[x].mk = 0;
    for(int i = l; i <= r; i ++){
        add(tree[x].s0, a[i] * fib[i - l] % mod);
        add(tree[x].s1, a[i] * fib[i - l + 1] % mod);
    }
    if(l == r){
        tree[x].A = a[l];
        return;
    }
    int mid = tree[x].mid();
    init_tree(l, mid, lc(x));
    init_tree(mid + 1, r, rc(x));
}

void pushdown(int x){
    if(tree[x].mk){
        int val = tree[x].mk;
        add(tree[lc(x)].A, val), add(tree[rc(x)].A, val);
        add(tree[lc(x)].mk, val), add(tree[rc(x)].mk, val);
        int L, R;
        L = 0, R = tree[lc(x)].r - tree[lc(x)].l;
        add(tree[lc(x)].s0, (sum[R] - (L == 0 ? 0 : sum[L - 1])) * val % mod);
        add(tree[lc(x)].s1, (sum[R + 1] - sum[L]) * val % mod);
        L = 0, R = tree[rc(x)].r - tree[rc(x)].l;
        add(tree[rc(x)].s0, (sum[R] - (L == 0 ? 0 : sum[L - 1])) * val % mod);
        add(tree[rc(x)].s1, (sum[R + 1] - sum[L]) * val % mod);
        tree[x].mk = 0;
    }
}

int calcA(int pos, int x){
    if(tree[x].l == tree[x].r)
        return tree[x].A;
    pushdown(x);
    int mid = tree[x].mid();
    if(pos <= mid) return calcA(pos, lc(x));
    else return calcA(pos, rc(x));
}

void gao(int l, int r, int val, int x){
    int L = max(l, tree[x].l) - tree[x].l;
    int R = min(r, tree[x].r) - tree[x].l;
    add(tree[x].s0, (sum[R] - (L == 0 ? 0 : sum[L - 1])) * val % mod);
    add(tree[x].s1, (sum[R + 1] - sum[L]) * val % mod);
    if(l <= tree[x].l && tree[x].r <= r){
        add(tree[x].A, val);
        add(tree[x].mk, val);
        return;
    }
    int mid = tree[x].mid();
    if(l <= mid) gao(l, r, val, lc(x));
    if(r > mid) gao(l, r, val, rc(x));
}

LL query(int l, int r, int x){
    if(l <= tree[x].l && tree[x].r <= r){
        int k = tree[x].l - l;
        //cout << tree[x].l << ' ' << tree[x].r << ' ' << tree[x].s0 << ' ' << tree[x].s1 << endl;
        if(k == 0) return tree[x].s0;
        else if(k == 1) return tree[x].s1;
        else return ((tree[x].s0 * fib[k - 2]) % mod + (tree[x].s1 * fib[k - 1]) % mod) % mod;
    }
    pushdown(x);
    int mid = tree[x].mid();
    LL res = 0;
    if(l <= mid) add(res, query(l, r, lc(x)));
    if(r > mid) add(res, query(l, r, rc(x)));
    return res;
}

int n, m, id, pos, val, l, r;

int main(){
    //freopen("read.in", "r", stdin);

    scanf("%d%d", &n, &m);

    fib[0] = fib[1] = 1;
    sum[0] = 1, sum[1] = 2;
    for(int i = 2; i <= n; i ++){
        add(fib[i], fib[i - 1] + fib[i - 2]);
        add(sum[i], sum[i - 1] + fib[i]);
    }
    sum[n + 1] = sum[n];

    for(int i = 1; i <= n; i ++)
        scanf("%I64d", &a[i]);
    init_tree(1, n, 1);

    while(m --){
        scanf("%d", &id);
        if(id == 1){
            scanf("%d%d", &pos, &val);
            gao(pos, pos, val - calcA(pos, 1), 1);
            //cout << calcA(pos, 1) << endl;
        }
        else if(id == 2){
            scanf("%d%d", &l, &r);
            LL ans = query(l, r, 1);
            if(ans < 0) ans += mod;
            printf("%I64d\n", ans);
        }
        else{
            scanf("%d%d%d", &l, &r, &val);
            gao(l, r, val, 1);
        }
    }
}
