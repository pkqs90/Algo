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
#define  LC(x) (x<<1)
#define  RC(x) (lc(x)+1)
#define  PI    (acos(-1))
#define  EPS   1e-8
#define  MAXN  111111
#define  MAXM  222222
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  PB    push_back
#define  MP    make_pair
#define  lowbit(x) (x&(-x))

using namespace std;

struct edge{
    int next, v;
}e[MAXM];

int first[MAXN], ecnt = -1, ll[MAXN], rr[MAXN], index, limit, col2[MAXN], col[MAXN], sz[MAXN];

void addedge(int u, int v){
    e[++ecnt].next = first[u], first[u] = ecnt, e[ecnt].v = v;
}

void dfs_sz(int u, int pre){
    sz[u] = 1;
    ll[u] = ++ index;
    col2[index] = col[u];
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre)continue;
        dfs_sz(v, u);
        sz[u] += sz[v];
    }
    rr[u] = index;
}

vector<pair<int,int> >Q[MAXN];

int n, m, u, v, num, cnt[MAXN], sum[MAXN], ans[MAXN];

void add_all(int u){
    int L = ll[u], R = rr[u];
    //cout << u << ' ' << L << ' ' << R << ' ' << sz[u] << endl;
    for(int i = L; i <= R; i ++){
        cnt[col2[i]]++;
        sum[cnt[col2[i]]]++;
    }
}

void clear_all(int u){
    int L = ll[u], R = rr[u];
    for(int i = L; i <= R; i ++){
        sum[cnt[col2[i]]]--;
        cnt[col2[i]]--;
    }
}

void dfs(int u, int pre){
    //cout << u << endl;
    int mx = 0, pos = 0;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre)continue;
        if(mx < sz[v])
            mx = sz[v], pos = v;
    }
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre || v == pos)continue;
        dfs(v, u);
        clear_all(v);
    }
    if(pos)
        dfs(pos, u);
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre || v == pos)continue;
        add_all(v);
    }
    cnt[col[u]]++, sum[cnt[col[u]]]++;
    for(int i = 0; i < Q[u].size(); i ++){
        /*cout << u << ' ' << Q[u][i].first << endl;
        for(int i = 1; i <= n; i ++){
            cout << i << ' ' << sum[i] <<endl;
        }*/
        ans[Q[u][i].second] = sum[Q[u][i].first];
    }
}

int main(){
    //freopen("read.in", "r", stdin);

    scanf("%d%d", &n, &m);

    memset(first, -1, sizeof(first));

    for(int i = 1; i <= n; i ++)
        scanf("%d", &col[i]);
    for(int i = 1; i <= n - 1; i ++){
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }

    dfs_sz(1, 0);

    for(int i = 1 ; i <= m ; i ++){
        scanf("%d%d", &v, &num);
        Q[v].PB(MP(num,i));
    }

    dfs(1, 0);

    for(int i = 1; i <= m; i ++)
        printf("%d\n", ans[i]);

}

