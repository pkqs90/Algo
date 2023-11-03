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
#define  MAXN  100005
#define  MAXM  222222
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffffffffffffll
#define  pb    push_back
#define  mp    make_pair
#define  lowbit(x) (x&(-x))

using namespace std;

struct edge{
    int v, next;
}e[MAXM];

int ecnt, first[MAXN], deep[MAXN], father[MAXN][22];

void addedge(int u, int v){
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].v = v;
}

int seq[MAXN], id[MAXN], cnt;

void dfs(int u, int pre, int depth){
    seq[++ cnt] = u;
    id[u] = cnt;
    deep[u] = depth;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(v == pre)continue;
        dfs(v, u, depth + 1);
        father[v][0] = u;
    }
}

void init_lca(){
     for(int i = 1; (1 << i) < MAXN; i ++)
        for(int j = 1; j < MAXN; j ++)
           father[j][i] = father[ father[j][i - 1] ][i - 1];
}

int lca(int x, int y){
    if(deep[x] < deep[y])
        swap(x, y);
    int temp = deep[x] - deep[y];
    for(int i = 0; (1 << i) <= temp; i++)
        if(temp & (1 << i))
            x = father[x][i];
    if(x == y) return x;
    for(int i = 20; i >= 0; i --)
        if(father[x][i] != father[y][i])
            x = father[x][i], y = father[y][i];
    return father[x][0];
}

int size, n, m, u, v;

set <int> Set;
set <int> :: iterator it;

void modify(int x, bool flag){
    if(!flag) Set.erase(id[x]);
    it = Set.lower_bound(id[x]);
    int rx = seq[it == Set.end() ? *Set.begin() : *it];
    int lx = seq[it == Set.begin() ? *Set.rbegin() : *(--it)];
    int dis = deep[x] + deep[lca(lx, rx)] - deep[lca(lx, x)] - deep[lca(x, rx)];
    if(flag) size += dis, Set.insert(id[x]);
    else size -= dis;
}

int main(){
    //freopen("read.in", "r", stdin);
    scanf("%d%d", &n, &m);
    memset(first, -1, sizeof(first));
    ecnt = -1;
    for(int i = 1; i < n; i ++){
        scanf("%d%d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1, 0, 0);
    init_lca();
    //cout << lca(2, 3) << endl;
    int head = 1, tail = 1, ans = 0;
    size = 1;
    Set.insert(id[1]);

    for(; head <= n && tail <= n; head ++){
        for(; size <= m && tail <= n;){
            tail ++;
            modify(tail, 1);
            //cout << tail << ' ' << size << endl;
        }
        //cout << head << ' ' << tail << ' ' << size << endl;
        ans = max(ans, tail - 1 - head + 1);
        modify(head, 0);
    }
    printf("%d\n", ans);
}

