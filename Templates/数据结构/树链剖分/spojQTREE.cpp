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

const int N = 1e4 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct Seg{
    int l, r, mx;
    int mid(){
        return l + r >> 1;
    }
} tree[N << 2];

void Init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r, tree[x].mx = 0;
    if(l == r) return;
    int mid = l + r >> 1;
    Init_tree(l, mid, lc(x));
    Init_tree(mid + 1, r, rc(x));
}

int Query(int l, int r, int x){
    if(l <= tree[x].l && tree[x].r <= r)
        return tree[x].mx;
    int mid = tree[x].mid(), ret = 0;
    if(l <= mid) ret = max(ret, Query(l, r, lc(x)));
    if(r > mid) ret = max(ret, Query(l, r, rc(x)));
    return ret;
}

void Insert(int pos, int num, int x){
    if(tree[x].l == tree[x].r){
        tree[x].mx = num;
        return;
    }
    int mid = tree[x].mid();
    if(pos <= mid) Insert(pos, num, lc(x));
    else Insert(pos, num, rc(x));
    tree[x].mx = max(tree[lc(x)].mx, tree[rc(x)].mx);
}

struct edge{
    int u, v, next, w;
} e[N << 1], e2[N];

int first[N], ecnt, fa[N], seq[N], id[N], head[N], sz[N], son[N], dep[N], tot;

void Addedge(int u, int v, int w){
    e[++ ecnt].v = v, e[ecnt].next = first[u], first[u] = ecnt, e[ecnt].w = w;
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

int Gao(int u, int v){
    int fu = head[u], fv = head[v];
    int ret = 0;
    while(fu != fv){
        if(dep[fu] < dep[fv])
            swap(fu, fv), swap(u, v);
        ret = max(ret, Query(id[fu], id[u], 1));
        u = fa[fu], fu = head[u];
    }
    if(u != v){
        if(dep[u] < dep[v])
            swap(u, v);
        ret = max(ret, Query(id[son[v]], id[u], 1));
    }
    return ret;
}

int T, u, v, w, n; char ch[10];

int main(){
//    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while(T --){
        scanf("%d", &n);
        memset(first, -1, sizeof(first));
        ecnt = -1, tot = 0;
        for(int i = 1; i < n; i ++){
            scanf("%d%d%d", &u, &v, &w);
            Addedge(u, v, w), Addedge(v, u, w);
            e2[i].u = u, e2[i].v = v, e2[i].w = w;
        }
        Dfs(1, 0);
        Build(1, 1);
//        for(int i = 1; i <= n; i ++)
//            printf("fa[%d] = %d, id[%d] = %d, son[%d] = %d, sz[%d] = %d\n", i, fa[i], i, id[i], i, son[i], i, sz[i]);
        Init_tree(1, n, 1);
        for(int i = 1; i < n; i ++){
            if(dep[e2[i].u] < dep[e2[i].v])
                swap(e2[i].u, e2[i].v);
            Insert(id[e2[i].u], e2[i].w, 1);
        }
        while(scanf(" %s", &ch) == 1){
            if(ch[0] == 'D') break;
            else if(ch[0] == 'Q'){
                scanf("%d%d", &u, &v);
                printf("%d\n", Gao(u, v));
            } else if(ch[0] == 'C'){
                scanf("%d%d", &u, &v);
                Insert(id[e2[u].u], v, 1);
            }
        }
    }
}
