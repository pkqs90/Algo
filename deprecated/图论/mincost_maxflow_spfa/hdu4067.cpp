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

const int N = 415;
const int M = 1e5;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct edge {
    int u, v, next, flow, cost;
}e[M];

int ecnt, first[N], dist[N], pre[N];

bool flag[N];

void addedge(int u, int v, int flow, int cost) {
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].u = u, e[ecnt].v = v, e[ecnt].flow = flow, e[ecnt].cost = cost;
    e[++ ecnt].next = first[v], first[v] = ecnt, e[ecnt].u = v, e[ecnt].v = u, e[ecnt].flow = 0, e[ecnt].cost = -cost;
}

bool make_map(int S, int T) {
     for(int i = 0; i < N ; i ++)
        dist[i] = INF, pre[i] = -1;
     memset(flag, 0, sizeof(flag));
     dist[S] = 0;
     queue <int> Q;
     Q.push(S);
     while(!Q.empty()) {
        int f = Q.front(); Q.pop();
        flag[f] = false;
        for(int i = first[f]; i != -1; i = e[i].next)
           if(e[i].flow && dist[e[i].v] > dist[f] + e[i].cost) {
              dist[e[i].v] = dist[f] + e[i].cost,
              pre[e[i].v] = i;
              if(!flag[e[i].v])
                Q.push(e[i].v), flag[e[i].v]=true;
           }
    }
     return dist[T] != INF;
}

pair<int, int> mincost_maxflow(int S, int T) {
    int ans = 0, flow = 0;
    while(make_map(S, T)) {
        int delta = INF, cost = 0;
        for(int i = pre[T]; i != -1; i = pre[e[i].u])
            delta = min(e[i].flow, delta), cost += e[i].cost;
        for(int i = pre[T]; i != -1; i = pre[e[i].u])
            e[i].flow -= delta, e[i ^ 1].flow += delta;
        ans += delta * cost;
        flow += delta;
    }
    return MP(ans, flow);
}

int n, m, st, ed, T, u, v, a, b, ind[N], outd[N], cas, tot, sum;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while(T --) {
        scanf("%d%d%d%d", &n, &m, &st, &ed);
        memset(first, -1, sizeof(first));
        ecnt = -1, tot = sum = 0;
        memset(ind, 0, sizeof(ind));
        memset(outd, 0, sizeof(outd));
        for(int i = 1; i <= m; i ++) {
            scanf("%d%d%d%d", &u, &v, &a, &b);
            if(a <= b) {
                addedge(v, u, 1, b - a);
                tot += a;
                ind[v] ++, outd[u] ++;
            } else {
                addedge(u, v, 1, a - b);
                tot += b;
            }
        }
        ind[st] ++, outd[ed] ++;
        for(int i = 1; i <= n; i ++) {
            if(ind[i] > outd[i])
                addedge(0, i, ind[i] - outd[i], 0), sum += (ind[i] - outd[i]);
            else if(ind[i] < outd[i])
                addedge(i, n + 1, outd[i] - ind[i], 0);
        }
        PII res = mincost_maxflow(0, n + 1);
        printf("Case %d: ", ++ cas);
        if(res.second != sum) puts("impossible");
        else printf("%d\n", tot + res.first);
    }
}
