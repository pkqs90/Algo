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

const int N = 1e5 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct Seg{
    int l, r, mx, pos;
    int mid(){
        return l + r >> 1;
    }
} tree[N << 2];

void Init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r, tree[x].mx = 0;
    if(l == r){
        tree[x].pos = l;
        return;
    }
    int mid = l + r >> 1;
    Init_tree(l, mid, lc(x));
    Init_tree(mid + 1, r, rc(x));
}

void Insert(int pos, int num, int x){
    if(tree[x].l == tree[x].r){
        tree[x].mx += num;
        return;
    }
    int mid = tree[x].mid();
    if(pos <= mid) Insert(pos, num, lc(x));
    else Insert(pos, num, rc(x));
    if(tree[lc(x)].mx >= tree[rc(x)].mx) tree[x].mx = tree[lc(x)].mx, tree[x].pos = tree[lc(x)].pos;
    else tree[x].mx = tree[rc(x)].mx, tree[x].pos = tree[rc(x)].pos;
}

struct edge{
    int v, next;
} e[N << 1];

int first[N], ecnt, fa[N], seq[N], id[N], head[N], sz[N], son[N], dep[N], tot;

vector <PII> vec[N];

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

void Gao(int u, int v, int w){
    int fu = head[u], fv = head[v];
    while(fu != fv){
        if(dep[fu] < dep[fv])
            swap(fu, fv), swap(u, v);
        vec[fu].PB(MP(w, 1));
        if(id[u] < tot) vec[seq[id[u] + 1]].PB(MP(w, -1));
        u = fa[fu], fu = head[u];
    }
    if(dep[u] < dep[v])
        swap(u, v);
    vec[v].PB(MP(w, 1));
    if(id[u] < tot) vec[seq[id[u] + 1]].PB(MP(w, -1));
}

int T, u, v, w, n, m, ans[N];

int main(){
//    freopen("in.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) == 2){
        if(!n && !m) break;
        memset(first, -1, sizeof(first));
        ecnt = -1, tot = 0;
        for(int i = 1; i <= n; i ++)
            vec[i].clear();
        for(int i = 1; i < n; i ++){
            scanf("%d%d", &u, &v);
            Addedge(u, v), Addedge(v, u);
        }
        Dfs(1, 0);
        Build(1, 1);
//        for(int i = 1; i <= n; i ++)
//            printf("id[%d] = %d, son[%d] = %d, sz[%d] = %d, head[%d] = %d\n", i, id[i], i, son[i], i, sz[i], i, head[i]);
        Init_tree(1, N, 1);
        for(int i = 1; i <= m; i ++){
            scanf("%d%d%d", &u, &v, &w);
            Gao(u, v, w);
        }
        for(int i = 1; i <= n; i ++){
            u = seq[i];
            for(int j = 0; j < vec[u].size(); j ++)
                Insert(vec[u][j].first, vec[u][j].second, 1);
            ans[u] = (tree[1].mx == 0 ? 0 : tree[1].pos);
        }
        for(int i = 1; i <= n; i ++)
            printf("%d\n", ans[i]);
    }
}
