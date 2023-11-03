#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define  lc(x) (x << 1)
#define  rc(x) (lc(x) + 1)
#define  lowbit(x) (x & (-x))
#define  PI    (acos(-1))
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  PLL   pair<LL, LL>
#define  PB    push_back
#define  MP    make_pair

using namespace std;

const int N = 5e4 + 7;
const int INF = 2e9 + 7;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

inline int max(int x, int y){
    return x > y ? x : y;
}

inline int min(int x, int y){
    return x < y ? x : y;
}

struct Seg{
    int l, r, mx, mn, mk, res[2];
    int mid(){
        return l + r >> 1;
    }
} tree[N << 2];

int seq[N], p[N];

inline void Pushup(int x){
    tree[x].mx = max(tree[lc(x)].mx, tree[rc(x)].mx);
    tree[x].mn = min(tree[lc(x)].mn, tree[rc(x)].mn);
    tree[x].res[0] = max(max(tree[lc(x)].res[0], tree[rc(x)].res[0]), tree[lc(x)].mx - tree[rc(x)].mn);
    tree[x].res[1] = max(max(tree[lc(x)].res[1], tree[rc(x)].res[1]), tree[rc(x)].mx - tree[lc(x)].mn);
}

inline void Init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r;
    tree[x].mk = 0;
    if(l == r){
        tree[x].mx = tree[x].mn = p[seq[l]];
        tree[x].res[0] = tree[x].res[1] = -1;
        return;
    }
    int mid = l + r >> 1;
    Init_tree(l, mid, lc(x));
    Init_tree(mid + 1, r, rc(x));
    Pushup(x);
}

inline void Pushdown(int x){
    if(tree[x].mk){
        int t = tree[x].mk;
        tree[lc(x)].mx += t, tree[rc(x)].mx += t;
        tree[lc(x)].mn += t, tree[rc(x)].mn += t;
        tree[lc(x)].mk += t, tree[rc(x)].mk += t;
        tree[x].mk = 0;
    }
}

int Query(int l, int r, int &mx, int &mn, int op, int x){
    if(l <= tree[x].l && tree[x].r <= r){
        mx = tree[x].mx;
        mn = tree[x].mn;
        return tree[x].res[op];
    }
    Pushdown(x);
    int mid = tree[x].mid(), ret = -1;
    if(r <= mid) ret = Query(l, r, mx, mn, op, lc(x));
    else if(l > mid) ret = Query(l, r, mx, mn, op, rc(x));
    else{
        int mxl, mxr, mnl, mnr;
        ret = max(ret, Query(l, r, mxl, mnl, op, lc(x)));
        ret = max(ret, Query(l, r, mxr, mnr, op, rc(x)));
        if(op == 0) ret = max(ret, mxl - mnr);
        else ret = max(ret, mxr - mnl);
        mx = max(mxl, mxr);
        mn = min(mnl, mnr);
    }
    return ret;
}

void Update(int l, int r, int w, int x){
    if(l <= tree[x].l && tree[x].r <= r){
        tree[x].mx += w, tree[x].mn += w;
        tree[x].mk += w;
        return;
    }
    Pushdown(x);
    int mid = tree[x].mid();
    if(l <= mid) Update(l, r, w, lc(x));
    if(r > mid) Update(l, r, w, rc(x));
    Pushup(x);
}

struct edge{
    int u, v, next;
} e[N << 1];

int first[N], ecnt, fa[N], id[N], head[N], sz[N], son[N], dep[N], tot;

void Addedge(int u, int v){
    e[++ ecnt].v = v, e[ecnt].next = first[u], first[u] = ecnt;
}

void Dfs(int u, int pre){
    fa[u] = pre; sz[u] = 1;
    dep[u] = dep[pre] + 1;
    son[u] = 0;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre) continue;
        Dfs(v, u);
        if(sz[v] > sz[son[u]])
            son[u] = v;
        sz[u] += sz[v];
    }
}

void Build(int u, int st){
    head[u] = st;
    seq[++ tot] = u;
    id[u] = tot;
    if(son[u] != 0) Build(son[u], st);
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == fa[u] || v == son[u]) continue;
        Build(v, v);
    }
}

int Calc(int u, int v){
    int fu = head[u], fv = head[v], ret = -1;
    int mxv = -1, mnu = INF, tmx, tmn;
    while(fu != fv){
        if(dep[fu] > dep[fv]){
            int res = Query(id[fu], id[u], tmx, tmn, 0, 1);
            ret = max(ret, tmx - mnu);
            ret = max(ret, res);
            mnu = min(mnu, tmn);
            u = fa[fu], fu = head[u];
        } else{
            int res = Query(id[fv], id[v], tmx, tmn, 1, 1);
            ret = max(ret, mxv - tmn);
            ret = max(ret, res);
            mxv = max(mxv, tmx);
            v = fa[fv], fv = head[v];
        }
    }
    if(dep[u] > dep[v]){
        int res = Query(id[v], id[u], tmx, tmn, 0, 1);
        ret = max(ret, res);
    } else{
        int res = Query(id[u], id[v], tmx, tmn, 1, 1);
        ret = max(ret, res);
    }
    ret = max(ret, tmx - mnu);
    ret = max(ret, mxv - tmn);
    ret = max(ret, mxv - mnu);
    return ret < 0 ? 0 : ret;
}

void Gao(int u, int v, int w){
    int fu = head[u], fv = head[v];
    while(fu != fv){
        if(dep[fu] < dep[fv])
            swap(fu, fv), swap(u, v);
        Update(id[fu], id[u], w, 1);
        u = fa[fu], fu = head[u];
    }
    if(dep[u] < dep[v])
        swap(u, v);
    Update(id[v], id[u], w, 1);
}

int T, u, v, w, n, m;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> T;
    while(T --){
        scanf("%d", &n);
        for(int i = 1; i <= n; i ++)
            scanf("%d", &p[i]);
        memset(first, -1, sizeof(first));
        ecnt = -1, tot = 0;
        for(int i = 1; i < n; i ++){
            scanf("%d%d", &u, &v);
            Addedge(u, v), Addedge(v, u);
        }
        Dfs(1, 0);
        Build(1, 1);
//        for(int i = 1; i <= n; i ++)
//            printf("fa[%d] = %d, id[%d] = %d, son[%d] = %d, sz[%d] = %d\n", i, fa[i], i, id[i], i, son[i], i, sz[i]);
        Init_tree(1, n, 1);
        scanf("%d", &m);
        for(int i = 1; i <= m; i ++){
            scanf("%d%d%d", &u, &v, &w);
            printf("%d\n", Calc(u, v));
//            return 0;
            Gao(u, v, w);
        }
    }
}
