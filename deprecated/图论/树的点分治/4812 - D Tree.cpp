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
#define  MAXN  111111
#define  MAXM  8888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  lowbit(x) (x&(-x))
#define  mod   1000003

using namespace std;

//////////////////////////////////////////////////////////

int inv[mod];

void init_inv(){
    inv[1] = 1;
    for(int i = 2; i < mod; i ++)
        inv[i] = (LL )(mod - mod / i) * inv[mod % i] % mod;
}

//////////////////////////////////////////////////////////

int first[MAXN], ecnt, size[MAXN];
int heavy, totsize, mx, num[MAXN];

bool del[MAXN];

struct edge{
    int next, v;
} e[MAXN << 1];

void addedge(int u, int v){
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].v = v;
}

void dfs_size(int u, int pre){
    size[u] = 1;
    for(int i = first[u]; i != -1; i = e[i].next)
        if(e[i].v != pre && !del[e[i].v])
            dfs_size(e[i].v, u), size[u] += size[e[i].v];
}

void dp(int u, int pre){
    int tmp = 0;
    for(int i = first[u]; i != -1; i = e[i].next)
        if(e[i].v != pre && !del[e[i].v])
            dp(e[i].v, u), tmp = max(tmp, size[e[i].v]);
    tmp = max(tmp, totsize - size[u]);
    if(tmp < mx) mx = tmp, heavy = u;
}

void dfs_get_heavy(int u){
    heavy = -1, mx = INF;
    dfs_size(u, 0), totsize = size[u];
    dp(u, 0);
}

pair<int, LL> flag[mod];

vector<pair<int, int> > vec;
LL ID;

pair<int, int> ANS;

void go(int x, int y){
    if(x > y) swap(x, y);
    ANS = min(ANS, mp(x, y));
}

int m;

void gao(int u, int pre, int tot, int k){
    tot = (LL) tot * num[u] % mod;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(del[e[i].v] || e[i].v == pre) continue;
        gao(v, u, tot, k);
    }
    k = (LL) m * inv[(LL) tot * k % mod] % mod;
    if(flag[k].second == ID)
        go(flag[k].first, u);
    vec.pb(mp(tot, u));
}

void dfs(int u){
    dfs_get_heavy(u);
    u = heavy;
    del[u] = true;
    if(totsize == 1) return;
    ID ++;
    flag[1] = mp(u, ID);
    for(int i = first[u]; i != -1; i = e[i].next)
        if(!del[e[i].v]){
            vec.clear();
            gao(e[i].v, 0, 1, num[u]);
            for(int j = 0; j < vec.size(); j ++){
                if(flag[vec[j].first].second == ID)
                    flag[vec[j].first].first = min(flag[vec[j].first].first, vec[j].second);
                else flag[vec[j].first].first = vec[j].second, flag[vec[j].first].second = ID;
            }
        }
    for(int i = first[u]; i != -1; i = e[i].next)
        if(!del[e[i].v])
            dfs(e[i].v);
}

int n, x, y;

void init(){
    for(int i = 1; i <= n; i ++)
        first[i] = -1, del[i] = 0;
    //memset(first, -1, sizeof(first));
    //memset(del, 0, sizeof(del));
    ecnt = -1;
    ANS = mp(INF, INF);
}

int main(){
    //freopen("read.in","r",stdin);
    init_inv();
    while(scanf("%d%d", &n, &m) == 2){
        init();
        for(int i = 1; i <= n; i ++)
            scanf("%d", &num[i]);
        for(int i = 1; i < n; i ++){
            scanf("%d%d", &x, &y);
            addedge(x, y), addedge(y, x);
        }
        if(m == 0){
            printf("No solution\n");
            continue;
        }
        dfs(1);
        if(ANS.first == INF)
            printf("No solution\n");
        else printf("%d %d\n", ANS.first, ANS.second);
    }
}
