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
#define  EPS   1e-10
#define  MAXN  200055
#define  MAXM  2005
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  INF   0x3fffffff
#define  PB    push_back
#define  MP    make_pair
#define  MOD   1000000007

using namespace std;

const int MAXC = 60, MAXR = 60, MAXNODE = 60 * 60;

struct DLX{
    int n, m, sz, H[MAXR], S[MAXC]; // S[] 是每列的节点数
    int row[MAXNODE], col[MAXNODE];
    int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE];
    int ans[MAXR], ansd; // ansd 是答案长度

    void init(int _n, int _m){
        n = _n, m = _m;
        for(int i = 0; i <= m; i ++)
            S[i] = 0, U[i] = D[i] = i, L[i] = i - 1, R[i] = i + 1;
        R[m] = 0, L[0] = m;
        sz = m;
        for(int i = 1; i <= n; i ++) H[i] = -1;
        ansd = INF; // Here is different from accurate cover ..
    }

    void Link(int r, int c){ // Must be added in ascending order ..
        ++ S[col[++ sz] = c];
        row[sz] = r;
        D[sz] = D[c], U[sz] = c;
        U[D[c]] = sz, D[c] = sz;
        if(H[r] < 0) H[r] = L[sz] = R[sz] = sz;
        else {
            R[sz] = R[H[r]];
            L[R[H[r]]] = sz;
            L[sz] = H[r];
            R[H[r]] = sz;
        }
    }

    void rmv(int c){
        for(int i = D[c]; i != c; i = D[i])
            L[R[i]] = L[i], R[L[i]] = R[i];
    }
    void rst(int c){
        for(int i = U[c]; i != c; i = U[i])
            L[R[i]] = i, R[L[i]] = i;
    }

    int h(){
        bool vis[MAXC];
        memset(vis, 0, sizeof(vis));
        int ret = 0;
        for(int i = R[0]; i != 0; i = R[i])
            if(!vis[i]){
                ret ++;
                vis[i] = true;
                for(int j = D[i]; j != i; j = D[j])
                    for(int k = R[j]; k != j; k = R[k])
                        vis[col[k]] = true;
            }
        return ret;
    }

    void dfs(int d){
        if(d + h() >= ansd) return;
        if(R[0] == 0){
            ansd = d;
            return;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(S[i] < S[c]) c = i;

        for(int i = D[c]; i != c; i = D[i]){
            rmv(i);
            ans[d] = row[i];
            for(int j = R[i]; j != i; j = R[j]) rmv(j);
            dfs(d + 1);
            for(int j = L[i]; j != i; j = L[j]) rst(j);
            rst(i);
        }
    }

    bool solve(vector <int> &v){
        v.clear();
        dfs(0);
        if(ansd == INF) return false;
        for(int i = 0; i < ansd; i ++) v.PB(ans[i]);
        return true;
    }

};

DLX Solver;

int n, m, u, v;

int main(){
//    freopen("in.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) == 2){
        Solver.init(n, n);
        for(int i = 1; i <= n; i ++)
            Solver.Link(i, i);
        for(int i = 1; i <= m; i ++){
            scanf("%d%d", &u, &v);
            Solver.Link(u, v);
            Solver.Link(v, u);
        }
        vector <int> vec;
        Solver.solve(vec);
        printf("%d\n", vec.size());
        //for(int i = 0; i < vec[0].size(); i ++) cout << vec[0][i] << ' '; cout << endl;
    }
}
