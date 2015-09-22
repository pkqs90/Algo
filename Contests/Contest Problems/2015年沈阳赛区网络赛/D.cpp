// https://projecteuler.net/problem=10
// http://www.shuizilong.com/house/archives/project-euler-521-smallest-prime-factor/
// http://www.zhihu.com/question/29580448/answer/45218281
// 用 O(n^0.75) 的方法改改就能做这题

#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
using namespace std;

inline int pow_mod(int x, int y, int z) {
    int ret = 1;
    while (y) {
        if (y & 1) ret *= x, ret %= z;
        x *= x, x %= z, y >>= 1;
    }
    return ret;
}

inline int inv(int x, int y) {
    return pow_mod(x, y - 2, y);
}

// n! % m (don't calculate m's multiples)
int fac[5005];
int Calc(int n, int m) {
    int a = n / m;
    int b = n % m;
    int res = pow_mod(fac[m - 1], a, m);
    res = res * fac[b] % m;
    return res;
}
int T, n, m, cas;

int Gao() {
    int r = sqrt(n);
    vector<int> V;
    for (int i = 1; i <= r; i ++) V.push_back(n / i);
    for (int i = (*V.rbegin()) - 1; i >= 2; i --) V.push_back(i);
    unordered_map<int, int> dp, dp2;
    // dp2[] is the number of primes (dont calculate m's multiples)
    // dp[] is the PI of primes (dont calculate m's multiples)
    for (int i = 0; i < V.size(); i ++) {
        dp[V[i]] = Calc(V[i], m);
        dp2[V[i]] = V[i] - 1 - V[i] / m;
    }
    for (int p = 2; p <= r; p ++) {
        if (dp2[p] != dp2[p - 1]) {
            int pp = p * p;
            if (dp[p - 1] == 0) dp[p - 1] = 1;
            for (auto v : V) {
                if (v < pp) break;
                int t = dp2[v / p] - dp2[p - 1];
                dp2[v] -= t;
                dp[v] *= inv(pow_mod(p, t, m) * (dp[v / p] * inv(dp[p - 1], m) % m) % m, m);
                dp[v] %= m;
            }
            //cout << p << ' ' << dp2[n] << ' ' << dp[n] << "~~" << endl;
        }
    }
    //cout << dp2[n] << ' ' << dp[n] << endl;
    //return dp2[n];
    return dp[n];
}

int main() {
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        fac[0] = 1;
        for (int i = 1; i < m; i ++) {
            fac[i] = fac[i - 1] * i % m;
        }
        printf("Case #%d: %d\n", ++ cas, Gao());
    }
}
