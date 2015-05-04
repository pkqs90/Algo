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

const int N = 1005;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

int r, c, K, cas, x_1[N], x_2[N], y_1[N], y_2[N]; LL ans;

bool A[N << 1][N << 1], f[N << 1][N << 1];

vector <int> X, Y;

int main(){
//    freopen("in.txt", "r", stdin);
    while(scanf("%d%d%d", &r, &c, &K) == 3){
        if(!r && !c && !K) break;
        X.clear(), Y.clear();
        for(int i = 1; i <= K; i ++){
            scanf("%d%d%d%d", &x_1[i], &y_1[i], &x_2[i], &y_2[i]);
            X.PB(x_1[i]), X.PB(x_2[i] + 1);
            Y.PB(y_1[i]), Y.PB(y_2[i] + 1);
        }
        X.PB(0), X.PB(c);
        Y.PB(0), Y.PB(r);
        sort(X.begin(), X.end()); X.erase(unique(X.begin(), X.end()), X.end());
        sort(Y.begin(), Y.end()); Y.erase(unique(Y.begin(), Y.end()), Y.end());

        memset(A, 0, sizeof(A));
        memset(f, 0, sizeof(f));

        for(int i = 1; i <= K; i ++){
            int k = lower_bound(Y.begin(), Y.end(), y_2[i] + 1) - Y.begin();
            for(int j = 0; j < X.size(); j ++)
                if(X[j] > x_1[i] && X[j] <= x_2[i] + 1)
                    A[j][k] = 1;
        }

        f[X.size() - 1][Y.size() - 1] = 1; ans = 0;

        for(int i = X.size() - 1; i; i --)
            for(int j = Y.size() - 1; j; j --){
                if(A[i][j]) continue;
                if(!f[i][j])
                    ans += (LL) (X[i] - X[i - 1]) * (Y[j] - Y[j - 1]);
                else
                    f[i - 1][j] |= f[i][j], f[i][j - 1] |= f[i][j];
            }
        printf("Case %d: %lld\n", ++ cas, ans);

    }
}
