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

const int N = 105;
const int M = N * N * 2;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const DB  EPS = 1e-8;

void ext_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}

LL inv(LL a, LL c) {
    LL d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

int T, n, a[N]; LL fac[N], dp[N];

bool vis[N];

int main() {
//    freopen("in.txt", "r", stdin);
    LL inv2 = inv(2, MOD);
    fac[0] = 1;
    for (int i = 1; i < N; i ++)
        fac[i] = fac[i - 1] * i % MOD;
    dp[1] = 0;
    for (int i = 2; i < N; i ++) {
        dp[i] = dp[i - 1] * i % MOD + fac[i - 1] * i % MOD * (i - 1) % MOD * inv2 % MOD;
        dp[i] %= MOD;
    }
    while(scanf("%d", &n) == 1) {
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &a[i]);
        }
        LL res = 0, mx = 0;
        memset(vis, 0, sizeof(vis));
        for (int i = 1; i <= n; i ++) {
            LL small = 0;
            for (int j = 1; j < a[i]; j ++) {
                if (!vis[j]) {
                    LL t = 0;
                    res += mx * fac[n - i] % MOD;
                    res += small * fac[n - i] % MOD;
                    res += dp[n - i];
                    res %= MOD;
                    small ++;
                }
            }
            vis[a[i]] = true;
            mx += small;
        }
        printf("%I64d\n", res);
    }
}
