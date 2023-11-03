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

const int N = 55;
const int M = 5555;
const int MOD = 1e9 + 7;
const int INF = 0x3fffffff;
const DB  EPS = 1e-8;

int mat[N][N], best;

int dp[55];
//int x[maxn];   // 取决于是否需要最优解.若需要，还要增加一个path[maxn]数组
bool dfs(int *v, int tot, int depth){
    int t[55];
    if(tot == 0){
        if(best < depth){
            //for (int i = 0; i < depth; i ++) path[i] = x[i]; //路径信息2
            best = depth;
            return true;
        }
        return false;
    }
    for(int i = 0; i < tot; i ++){
        if(depth + (tot - i) <= best) return false;
        if(depth + dp[v[i]] <= best) return false;
        //x[depth] = v[i]; //路径信息3
        int k = 0;
        for(int j = i + 1; j < tot; j ++)
            if(mat[v[i]][v[j]]) t[k ++] = v[j];
        if(dfs(t, k, depth + 1)) return true;
    }
    return false;
}

int MaximumClique(int n){
    int v[N];
    best = 0;
    for(int i = n - 1; i >= 0; i --){
        //x[0] = i; 路径信息1
        int k = 0;
        for(int j = i + 1; j < n; j ++)
            if(mat[i][j]) v[k ++] = j;
        dfs(v, k, 1);
        dp[i] = best;
    }
    return best;
}

int n, u, v;

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> n;
    while(scanf("%d%d", &u, &v) == 2){
        u --, v --;
        mat[u][v] = mat[v][u] = 1;
    }
    printf("%d\n", MaximumClique(n));
}
