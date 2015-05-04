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
#define  lowbit(x) (x & (-x))
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  PLL   pair<LL, LL>
#define  PB    push_back
#define  MP    make_pair

using namespace std;

const int N = 2005;
const int M = N * N * 2;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const DB  EPS = 1e-8;

struct Edge{
    int u, v, next;
    bool vis, cut;
} e[M], e2[M];

int first[N], first2[N], ecnt, ecnt2;

void Addedge(int u, int v){
    e[++ ecnt].v = v, e[ecnt].next = first[u], e[ecnt].u = u, first[u] = ecnt;
}
void Addedge2(int u, int v){
    e2[++ ecnt2].v = v, e2[ecnt2].next = first2[u], e2[ecnt2].u = u, first2[u] = ecnt2;
}

int low[N], dfn[N], tim;

void Dfs(int u){
    low[u] = dfn[u] = ++ tim;
    for(int i = first[u]; i != -1; i = e[i].next){
        if(e[i].vis) continue;
        int v = e[i].v;
        e[i].vis = e[i ^ 1].vis = true;
        if(!dfn[v]) Dfs(v), low[u] = min(low[u], low[v]);
        else low[u] = min(low[u], dfn[v]);
    }
}

int res, dp[N], f[N], sz[N], nsz[N], cnt[N], belong[N], scnt, ans;

int getf(int x){
    return f[x] == x ? x : f[x] = getf(f[x]);
}

void Dfs2(int u, int pre){
    cnt[u] = sz[u];
    for(int i = first2[u]; i != -1; i = e2[i].next){
        int v = e2[i].v;
        if(v == pre) continue;
        Dfs2(v, u);
        cnt[u] += cnt[v];
        res += sz[u] * cnt[v];
    }
    res += sz[u] * sz[u];
}

int n, m;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    memset(first, -1, sizeof(first)), ecnt = -1;
    memset(first2, -1, sizeof(first2)), ecnt2 = -1;
    for(int i = 1; i <= m; i ++){
        int u, v;
        scanf("%d%d", &u, &v);
        Addedge(u, v);
        Addedge(v, u);
    }
    for(int i = 1; i <= n; i ++)
        if(!dfn[i]) Dfs(i);
    for(int i = 0; i <= ecnt; i ++)
        if(low[e[i].v] > dfn[e[i].u])
            e[i].cut = e[i ^ 1].cut = true;
    for(int i = 1; i <= n; i ++)
        f[i] = i, nsz[i] = 1;
    for(int i = 0; i <= ecnt; i ++)
        if(e[i].cut == false){
            int fu = getf(e[i].u), fv = getf(e[i].v);
            if(fu != fv) f[fu] = fv, nsz[fv] += nsz[fu];
//            cout << e[i].u << ' ' << e[i].v << endl;
        }
//    return 0;
    for(int i = 1; i <= n; i ++)
        if(f[i] == i){
            belong[i] = ++ scnt;
            sz[scnt] = nsz[i];
//            cout << i << ' ' << scnt << ' ' << nsz[i] << endl;
        }
//    return 0;
    for(int i = 0; i <= ecnt; i ++){
        int fu = getf(e[i].u), fv = getf(e[i].v);
        if(fu == fv) continue;
        fu = belong[fu], fv = belong[fv];
//        cout << fu << ' ' << fv << endl;
        Addedge2(fu, fv);
    }
//    return 0;
    for(int i = 1; i <= scnt; i ++){
        res = 0;
        Dfs2(i, -1);
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        for(int j = first2[i]; j != -1; j = e2[j].next){
            int t = cnt[e2[j].v];
            for(int j = 2000; j >= 0; j --)
                if(dp[j]) dp[j + t] = true;
        }
        for(int j = 0; j <= 2000; j ++)
            if(dp[j]) ans = max(ans, res + j * (n - j - sz[i]));
    }
    printf("%d\n", ans);
}
