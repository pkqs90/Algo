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

const int N = 205;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct edge{
    int v, next;
} e[(N * N) << 1];

int first[N], ecnt;

void addedge(int u, int v){
    e[++ ecnt].v = v, e[ecnt].next = first[u], first[u] = ecnt;
}

int vote[N], matchx[N], matchy[N]; bool vis[N];

vector <int> obj[N], X, Y;

bool check(int x, int y){
    for(int i = 0; i < obj[x].size(); i ++)
        if(vote[y] == obj[x][i]) return false;
    for(int i = 0; i < obj[y].size(); i ++)
        if(vote[x] == obj[y][i]) return false;
    return true;
}

bool gao(int u, bool f1, bool f2){ // f1 means left or right, f2 means change match or not ..
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(!vis[v]){
            vis[v] = true;
            if(f1 == 0){
                if(matchy[v] == -1 || gao(matchy[v], f1, f2)){
                    if(!f2) matchy[v] = u, matchx[u] = v;
                    return true;
                }
            } else{
                if(matchx[v] == -1 || gao(matchx[v], f1, f2)){
                    if(!f2) matchx[v] = u, matchy[u] = v;
                    return true;
                }
            }
        }
    }
    return false;
}

int Hungary(){
    memset(matchx, -1, sizeof(matchx));
    memset(matchy, -1, sizeof(matchy));
    int ret = 0;
    for(int i = 0; i < X.size(); i ++){
        memset(vis, 0, sizeof(vis));
        if(gao(X[i], 0, 0)) ret ++;
    }
    return ret;
}

int t, a, b, n, x, y;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        scanf("%d%d%d", &a, &b, &n);
        X.clear(), Y.clear();
        for(int i = 1; i <= n; i ++){
            scanf("%d", &vote[i]);
            if(vote[i] <= a) X.PB(i);
            else Y.PB(i);
            scanf("%d", &x);
            obj[i].clear();
            for(int j = 1; j <= x; j ++){
                scanf("%d", &y);
                obj[i].PB(y);
            }
        }
        memset(first, -1, sizeof(first)); ecnt = -1;
        for(int i = 1; i <= n; i ++)
            for(int j = i + 1; j <= n; j ++)
                if(!check(i, j)){
                    addedge(i, j), addedge(j, i);
                }
        cout << n - Hungary() << endl;
        vector <int> vec;
        // checking whether a point is in the maximum matching using brute-force ..
        for(int i = 0; i < X.size(); i ++){
            int v = X[i];
            if(matchx[v] != -1){
                memset(vis, 0, sizeof(vis));
                vis[v] = true;
                if(gao(matchx[v], 1, 1)) vec.PB(vote[v]);
            } else vec.PB(vote[v]);
        }
        for(int i = 0; i < Y.size(); i ++){
            int v = Y[i];
            if(matchy[v] != -1){
                memset(vis, 0, sizeof(vis));
                vis[v] = true;
                if(gao(matchy[v], 0, 1)) vec.PB(vote[v]);
            } else vec.PB(vote[v]);
        }
        sort(vec.begin(), vec.end());
        vec.erase(unique(vec.begin(), vec.end()), vec.end());
        if(vec.size() == 0) puts("0");
        else{
            cout << vec.size() << ' ';
            for(int i = 0; i < vec.size(); i ++)
                printf("%d%c", vec[i], i == vec.size() - 1 ? '\n' : ' ');
        }
    }
}
