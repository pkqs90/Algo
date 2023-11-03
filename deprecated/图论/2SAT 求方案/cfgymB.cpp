/* http://codeforces.com/gym/100268 */

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
const int INF = 1e9 + 7;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;
const ULL MAGIC = 79;

struct Edge{
    int v, next;
}e[2 * N * N];

int first[4 * N], ecnt;

void Addedge(int u, int v){
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].v = v;
}

int n, dfn[4 * N], low[4 * N], scc_id[4 * N], ins[4 * N], ts, scc_cnt;

stack  <int> stk;

void Dfs(int u){
    stk.push(u);
    dfn[u] = low[u] = ++ ts;
    ins[u] = 1;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(!dfn[v])
            Dfs(v), low[u] = min(low[u], low[v]);
        else if(ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        scc_cnt ++;
        while(1){
            int x = stk.top(); stk.pop();
            scc_id[x] = scc_cnt;
            ins[x] = false;
            if(x == u) break;
        }
    }
}

void Tarjan(){
     ts = 0;
     for(int i = 0; i < 2 * n; i ++)
        if(!dfn[i]) Dfs(i);
}

vector <int> block[2 * N]; int c[2 * N];

bool _2Sat(vector <bool> &res){
    Tarjan();
    for(int i = 0; i < n; i ++)
        if(scc_id[2 * i] == scc_id[2 * i + 1])
            return false;
    for(int i = 1; i <= scc_cnt; i ++)
        block[i].clear(), c[i] = -1;
    for(int i = 0; i < 2 * n; i ++) block[scc_id[i]].PB(i);
    for(int i = 1; i <= scc_cnt; i ++){
        c[i] = 1;
        for(int j = 0; j < block[i].size(); j ++){
            int u = block[i][j];
            for(int k = first[u]; k != -1; k = e[k].next){
                int v = e[k].v;
                if(c[scc_id[v]] == 0) c[i] = 0;
            }
            if(c[scc_id[u ^ 1]] == 1) c[i] = 0;
        }
    }
    res.resize(n);
    for(int i = 0; i < n; i ++)
        res[i] = c[scc_id[2 * i]];
//    for(int i = 0; i < n; i ++)
//        cout << res[i] << ' '; cout << endl;
    return true;
}

int m, sta[2 * N], d[N][N], u, v;

vector <bool> res;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> n >> m;
    memset(sta, -1, sizeof(sta));
    memset(first, -1, sizeof(first)), ecnt = -1;
    for(int i = 1; i <= m; i ++){
        scanf("%d%d", &u, &v);
        u --, v --;
        if(u == 0) sta[v] = 0;
        if(v == 0) sta[u] = 0;
        if(u == 1) sta[v] = 1;
        if(v == 1) sta[u] = 1;
        d[u][v] = d[v][u] = true;
    }
    sta[0] = 0, sta[1] = 1;
    Addedge(2 * 0 + 1, 2 * 0);
    Addedge(2 * 1 + 1, 2 * 1);
    for(int i = 2; i < n; i ++){
        if(sta[i] == -1) Addedge(2 * i, 2 * i + 1);
        for(int j = i + 1; j < n; j ++){
            if(d[i][j] == false){
                if((sta[i] == 0 && sta[j] == 0) || (sta[i] == 1 && sta[j] == 1)){
//                    cout << i << ' ' << j << endl;
                    Addedge(2 * i, 2 * j + 1);
                    Addedge(2 * i + 1, 2 * j);
                    Addedge(2 * j, 2 * i + 1);
                    Addedge(2 * j + 1, 2 * i);
                } else{
                    Addedge(2 * i + 1, 2 * j);
                    Addedge(2 * j + 1, 2 * i);
                }
            }
        }
    }
//    cout << "!";
    if(!_2Sat(res)) puts("impossible");
    else{
        vector <int> v[2];
        for(int i = 0; i < n; i ++){
            if(sta[i] == 0 && res[i]) v[0].PB(i);
            if(sta[i] == 1 && res[i]) v[1].PB(i);
        }
        sort(v[0].begin(), v[0].end());
        sort(v[1].begin(), v[1].end());
        for(int i = 0; i < v[0].size(); i ++) printf("%d%c", 1 + v[0][i], (i == v[0].size() - 1) ? '\n' : ' ');
        for(int i = 0; i < v[1].size(); i ++) printf("%d%c", 1 + v[1][i], (i == v[1].size() - 1) ? '\n' : ' ');
    }
}
