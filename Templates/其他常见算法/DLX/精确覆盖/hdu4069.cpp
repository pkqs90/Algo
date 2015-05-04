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

char ch[99]; int num;

const int MAXC = 400, MAXR = 1000, MAXNODE = 4 * 1000;

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

    inline void rmv(int c){
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], S[col[j]] --;
    }
    inline void rst(int c){
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                S[col[j]] ++, U[D[j]] = j, D[U[j]] = j;
        L[R[c]] = c, R[L[c]] = c;
    }

    void dfs(int d){
        if(num > 1) return;
        if(R[0] == 0){
            num ++;
            for(int i = 0; i < d; i ++){
                ch[(ans[i] - 1) / 9] = (ans[i] - 1) % 9 + '1';
            }
            return;
//            ansd = d; return true;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(S[i] < S[c]) c = i;

        rmv(c);

        for(int i = D[c]; i != c; i = D[i]){
            ans[d] = row[i];
            for(int j = R[i]; j != i; j = R[j]) rmv(col[j]);
            dfs(d + 1);
            if(num > 1) return;
            for(int j = L[i]; j != i; j = L[j]) rst(col[j]);
        }
        rst(c);
    }

    void solve(vector <int> &v){
        dfs(0);
        return;
//        v.clear();
//        if(!dfs(0)) return false;
//        for(int i = 0; i < ansd; i ++) v.PB(ans[i]);
//        return true;
    }

};

DLX Solver;

int a[10][10], vis[10][10], d[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void bfs(int x, int y, int id) {
    vis[x][y] = id;
    queue <PII> Q;
    Q.push(MP(x, y));
    while(!Q.empty()) {
        PII u = Q.front(); Q.pop();
        for(int i = 0; i < 4; i ++){
            if(a[u.first][u.second] >> (i + 4) & 1) continue;
            int xx = u.first + d[i][0], yy = u.second + d[i][1];
            if(xx < 0 || yy < 0 || xx >= 9 || yy >= 9) continue;
            if(vis[xx][yy] == -1) Q.push(MP(xx, yy)), vis[xx][yy] = id;
        }
    }
}

inline int encode(int a, int b, int c){
    return a * 9 * 9 + b * 9 + c + 1;
}

inline void decode(int x, int &a, int &b, int &c){
    x --;
    a = x / 81; x -= a * 81;
    b = x / 9; x -= b * 9;
    c = x;
}

int cas, T;

int main() {
//    freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while(T --) {
        for(int i = 0; i < 9; i ++)
        for(int j = 0; j < 9; j ++)
            scanf("%d", &a[i][j]);
        Solver.init(729, 324);
        int cnt = 0;
        memset(vis, -1, sizeof(vis));
        for(int i = 0; i < 9; i ++)
        for(int j = 0; j < 9; j ++)
            if(vis[i][j] == -1)
                bfs(i, j, cnt ++);
        for(int r = 0; r < 9; r ++)
        for(int c = 0; c < 9; c ++) {
            int t = (a[r][c] & 15);
            if(t == 0) {
                for(int v = 0; v < 9; v ++) {
                    int R = encode(r, c, v);
                    Solver.Link(R, encode(0, r, c));
                    Solver.Link(R, encode(1, r, v));
                    Solver.Link(R, encode(2, c, v));
                    Solver.Link(R, encode(3, vis[r][c], v));
                }
            } else {
                t --;
                int R = encode(r, c, t);
                Solver.Link(R, encode(0, r, c));
                Solver.Link(R, encode(1, r, t));
                Solver.Link(R, encode(2, c, t));
                Solver.Link(R, encode(3, vis[r][c], t));
            }
        }
        printf("Case %d:\n", ++ cas);
        num = 0;
        vector <int> vec;
        Solver.solve(vec);
        if(num > 1) {
            puts("Multiple Solutions");
            continue;
        } else if(num == 0) {
            puts("No solution");
            continue;
        }
        for(int i = 0; i < 81; i ++){
            printf("%c", ch[i]);
            if(i % 9 == 8) puts("");
        }
    }
}
