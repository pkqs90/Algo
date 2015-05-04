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

const int N = 1e5 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct edge{
    int v, next, w;
} e[N << 1];

int first[N], ecnt, n, m, dist[2][N], vis[N]; DB cnt[2][N];

void Addedge(int u, int v, int w){
    e[++ ecnt].v = v, e[ecnt].next = first[u], first[u] = ecnt, e[ecnt].w = w;
}

void Dijkstra(int s, int t, bool op){
    for(int i = 1; i <= n; i ++)
        dist[op][i] = INF, vis[i] = 0;
    dist[op][s] = 0;
    cnt[op][s] = 1;
    priority_queue <PII, vector <PII>, greater <PII> > Q;
    Q.push(MP(0, s));
    while(!Q.empty()){
        PII fr = Q.top(); Q.pop();
        int u = fr.second;
        if(vis[u]) continue;
        vis[u] = true;
        for(int i = first[u]; i != -1; i = e[i].next){
            int v = e[i].v, w = e[i].w;
            if(dist[op][v] > dist[op][u] + w){
//                cout << u << " -> " << v << endl;
                dist[op][v] = dist[op][u] + w;
                cnt[op][v] = cnt[op][u];
                Q.push(MP(dist[op][v], v));
            } else if(dist[op][v] == dist[op][u] + w){
//                cout << u << " ~> " << v << endl;
                cnt[op][v] += cnt[op][u];
            }
        }
    }
}

int u, v, c;

int main(){
//    freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first)), ecnt = -1;
    for(int i = 1; i <= m; i ++){
        scanf("%d%d%d", &u, &v, &c);
        Addedge(u, v, c), Addedge(v, u, c);
    }
    Dijkstra(1, n, 0), Dijkstra(n, 1, 1);
//    for(int i = 1; i <= n; i ++)
//        cout << i << ' ' << cnt[0][i] << ' ' << cnt[1][i] << endl;
    DB tot = cnt[0][1] * cnt[1][1];
    int mx = dist[0][n];
    for(int i = 1; i <= n; i ++){
        DB res;
        if(dist[0][i] + dist[1][i] > mx) res = 0;
        else res = cnt[0][i] * cnt[1][i];
        printf("%.10f ", 2 * res / tot);
    }
    puts("");
}
