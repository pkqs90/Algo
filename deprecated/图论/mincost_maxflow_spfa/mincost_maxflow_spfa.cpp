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
#define  MAXN  8888
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct edge{
    int u, v, next, flow, cost;
}e[MAXM];

int ecnt, first[MAXN], dist[MAXN], pre[MAXN];

bool flag[MAXN];

void addedge(int u, int v, int flow, int cost){
    //cout << u << ' ' << v << ' ' << flow << ' ' << cost << endl;
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].u = u, e[ecnt].v = v, e[ecnt].flow = flow, e[ecnt].cost = cost;
    e[++ ecnt].next = first[v], first[v] = ecnt, e[ecnt].u = v, e[ecnt].v = u, e[ecnt].flow = 0, e[ecnt].cost = -cost;
}

bool make_map(int S, int T){
     for(int i = 0; i < MAXN ; i ++)
        dist[i] = INF, pre[i] = -1;
     memset(flag, 0, sizeof(flag));
     dist[S] = 0;
     queue <int> Q;
     Q.push(S);
     while(!Q.empty()){
        int f = Q.front(); Q.pop();
        flag[f] = false;
        for(int i = first[f]; i != -1; i = e[i].next)
           if(e[i].flow && dist[e[i].v] > dist[f] + e[i].cost){
              dist[e[i].v] = dist[f] + e[i].cost,
              pre[e[i].v] = i;
              if(!flag[e[i].v])
                Q.push(e[i].v), flag[e[i].v]=true;
           }
    }
     return dist[T] != INF;
}

int mincost_maxflow(int S, int T){
    int ans = 0;
    while(make_map(S, T)){
        int delta = INF, cost = 0;
        for(int i = pre[T]; i != -1; i = pre[e[i].u])
            delta = min(e[i].flow, delta), cost += e[i].cost;
        for(int i = pre[T]; i != -1; i = pre[e[i].u])
            e[i].flow -= delta, e[i ^ 1].flow += delta;
        ans += delta * cost;
    }
    return ans;
}

int n, m, a[88][88];

int gao(int x, int y){
    return 2 + x * m + y;
}

int main(){
    //freopen("read.in", "r", stdin);
    scanf("%d%d", &n, &m);
    ecnt = -1;
    memset(first, -1, sizeof(first));
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++)
            scanf("%d", &a[i][j]);
    for(int i = 0; i < n; i ++)
        for(int j = 0; j < m; j ++){
            if((i + j) % 2 != 0){
                addedge(gao(i, j), 1, 1, 0);
                continue;
            }
            addedge(0, gao(i, j), 1, 0);
            if(i != n - 1) addedge(gao(i, j), gao(i + 1, j), 1, a[i][j] != a[i + 1][j]);
            if(i != 0) addedge(gao(i, j), gao(i - 1, j), 1, a[i][j] != a[i - 1][j]);
            if(j != m - 1) addedge(gao(i, j), gao(i, j + 1), 1, a[i][j] != a[i][j + 1]);
            if(j != 0) addedge(gao(i, j), gao(i, j - 1), 1, a[i][j] != a[i][j - 1]);
        }
    printf("%d\n", mincost_maxflow(0, 1));
}
