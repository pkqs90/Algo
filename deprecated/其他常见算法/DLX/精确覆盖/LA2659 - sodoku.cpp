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

const int MAXC = 20005, MAXR = 20005, MAXNODE = 4 * 20005;

struct DLX{
    int n, sz, S[MAXC]; // S[] 是每列的节点数
    int row[MAXNODE], col[MAXNODE];
    int L[MAXNODE], R[MAXNODE], U[MAXNODE], D[MAXNODE];
    int ans[MAXR], ansd; // ansd 是答案长度

    void init(int n){
        this -> n = n;
        for(int i = 0; i <= n; i ++)
            U[i] = D[i] = i, L[i] = i - 1, R[i] = i + 1;
        R[n] = 0, L[0] = n;
        sz = n + 1;
        memset(S, 0, sizeof(S));
    }

    void addRow(int r, vector <int> columns){
        int first = sz;
        for(int i = 0; i < columns.size(); i ++){
            int c = columns[i];
            L[sz] = sz - 1, R[sz] = sz + 1, D[sz] = c, U[sz] = U[c];
            D[U[c]] = sz, U[c] = sz;
            row[sz] = r, col[sz] = c;
            S[c] ++, sz ++;
        }
        R[sz - 1] = first, L[first] = sz - 1;
    }

    void rmv(int c){
        L[R[c]] = L[c], R[L[c]] = R[c];
        for(int i = D[c]; i != c; i = D[i])
            for(int j = R[i]; j != i; j = R[j])
                U[D[j]] = U[j], D[U[j]] = D[j], S[col[j]] --;
    }
    void rst(int c){
        for(int i = U[c]; i != c; i = U[i])
            for(int j = L[i]; j != i; j = L[j])
                S[col[j]] ++, U[D[j]] = j, D[U[j]] = j;
        L[R[c]] = c, R[L[c]] = c;
    }

    bool dfs(int d){
        if(R[0] == 0){
            ansd = d;
            return true;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(S[i] < S[c]) c = i;
        //cout << c << ' ' << S[c] << endl;

        rmv(c);

        for(int i = D[c]; i != c; i = D[i]){
            ans[d] = row[i];
            for(int j = R[i]; j != i; j = R[j]) rmv(col[j]);
            if(dfs(d + 1)) return true;
            for(int j = L[i]; j != i; j = L[j]) rst(col[j]);
        }
        rst(c);
        return false;
    }

    bool solve(vector <int> &v){
        v.clear();
        if(!dfs(0)) return false;
        for(int i = 0; i < ansd; i ++) v.PB(ans[i]);
        return true;
    }

};

DLX Solver;

int encode(int a, int b, int c){
    return 256 * a + 16 * b + c + 1;
}

void decode(int x, int &a, int &b, int &c){
    x --;
    c = x % 16; x /= 16;
    b = x % 16; x /= 16;
    a = x;
}

int cas;

char ch[17][17];

vector <int> vec;

int main(){
    //freopen("in.txt", "r", stdin);
    while(scanf(" %s", ch[0]) == 1){
        if(cas) puts(""); else cas ++;
        Solver.init(1024);
        for(int i = 1; i < 16; i ++)
            scanf(" %s", ch[i]);
        for(int r = 0; r < 16; r ++)
            for(int c = 0; c < 16; c ++){
                if(ch[r][c] == '-'){
                    for(int v = 0; v < 16; v ++){
                        vec.clear();
                        vec.PB(encode(0, r, c));
                        vec.PB(encode(1, r, v));
                        vec.PB(encode(2, c, v));
                        vec.PB(encode(3, r / 4 * 4 + c / 4, v));
                        Solver.addRow(encode(r, c, v), vec);
                    }
                }
                else{
                    int v = ch[r][c] - 'A';
                    vec.clear();
                    vec.PB(encode(0, r, c));
                    vec.PB(encode(1, r, v));
                    vec.PB(encode(2, c, v));
                    vec.PB(encode(3, r / 4 * 4 + c / 4, v));
                    Solver.addRow(encode(r, c, v), vec);
                }
            }
        vec.clear();
        Solver.solve(vec);
        for(int i = 0; i < vec.size(); i ++){
            int r, c, v;
            decode(vec[i], r, c, v);
            ch[r][c] = 'A' + v;
        }
        for(int i = 0; i < 16; i ++)
            printf("%s\n", ch[i]);
    }
}
