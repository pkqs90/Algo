#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
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
#define  DB    long double
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

int sum[N * 55], st[N * 55], delta[N * 55], totID, totLen;

void Allocate(int id, int len){
    st[id] = totLen;
    delta[id] = len;
    for(int i = st[id] + 1; i <= st[id] + len; i ++) sum[i] = 0;
    totLen += len;
}
void Add(int id, int x, int v){
    for(; x <= delta[id]; x += lowbit(x)){
        sum[st[id] + x] += v;
    }
}
int Query(int id, int x){
    int res = 0;
    x = min(x, delta[id]);
    for(; x; x -= lowbit(x)){
        res += sum[st[id] + x];
    }
    return res;
}

map <int, int> M[N];

struct Node{
    int fa, sub, dist;
    Node(){}
    Node(int _fa, int _sub, int _dist){
        fa = _fa, sub = _sub, dist = _dist;
    }
};

vector <Node> Entries[N];

//////////////////////////////////////////////////////////

int first[N], ecnt, size[N], w[N];
int heavy, totsize, MN;

bool del[N];

struct edge{
    int next, v;
} e[N << 1];

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
    if(tmp < MN) MN = tmp, heavy = u;
}

void dfs_get_heavy(int u){
    heavy = -1, MN = INF;
    dfs_size(u, 0), totsize = size[u];
    dp(u, 0);
}

vector <PII> vec;

void gao(int u, int pre, int dist){
    if(dist != 0) vec.PB(MP(dist, u));
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(del[v]) continue;
        if(v == pre) continue;
        gao(v, u, dist + 1);
    }
}

void dfs(int u){
    dfs_get_heavy(u);
    u = heavy;
    del[u] = true;
    if(totsize == 1) return;
    M[u][-1] = ++ totID;
    Allocate(totID, totsize - 1);
    Entries[u].PB(Node(u, -1, 0));
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(del[v]) continue;
        vec.clear();
        M[u][v] = ++ totID;
        gao(v, u, 1);
        Allocate(totID, vec.size());
        for(int j = 0; j < vec.size(); j ++){
            Entries[vec[j].second].PB(Node(u, v, vec[j].first));
            Entries[vec[j].second].PB(Node(u, -1, vec[j].first));
            Add(M[u][v], vec[j].first, w[vec[j].second]);
            Add(M[u][-1], vec[j].first, w[vec[j].second]);
        }
    }

    for(int i = first[u]; i != -1; i = e[i].next)
        if(!del[e[i].v])
            dfs(e[i].v);
}

//////////////////////////////////////////////////////////

int n, m, u, v, p[N]; char op;

int main(){
    int size = 256 << 20; // 256MB
    char *p = (char*)malloc(size) + size;
    __asm__("movl %0, %%esp\n" :: "r"(p));
//    freopen("in.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) == 2){
        for(int i = 1; i <= n; i ++){
            first[i] = -1, del[i] = 0;
            Entries[i].clear();
            M[i].clear();
        }
        totID = totLen = 0;
        ecnt = -1;
        for(int i = 1; i <= n; i ++)
            scanf("%d", &w[i]);
        for(int i = 1; i < n; i ++){
            scanf("%d%d", &u, &v);
            addedge(u, v), addedge(v, u);
        }

        dfs(1);

        while(m --){
            scanf(" %c%d%d", &op, &u, &v);
            if(op == '!'){
                int dd = v - w[u];
                for(int i = 0; i < Entries[u].size(); i ++){
                    int fa = Entries[u][i].fa, sub = Entries[u][i].sub, di = Entries[u][i].dist;
                    if(di == 0) continue;
                    Add(M[fa][sub], di, dd);
                }
                w[u] = v;
            } else{
                int res = w[u];
                for(int i = 0; i < Entries[u].size(); i ++){
                    int fa = Entries[u][i].fa, sub = Entries[u][i].sub, di = Entries[u][i].dist;
                    if(v < di) continue;
                    if(sub == -1 && u != fa) res += w[fa];
                    if(sub == -1) res += Query(M[fa][-1], v - di);
                    else res -= Query(M[fa][sub], v - di);
                }
                printf("%d\n", res);
            }
        }
    }
}
