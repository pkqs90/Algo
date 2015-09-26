// I thought this was harder than problem B.

#include <bits/stdc++.h>

using namespace std;

#define LL  long long

const int N = 2005;
const int Mod = 1e9 + 7;

void ext_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}
LL inv(LL a, LL c) {
    LL d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

LL fac[N];
LL C(int x, int y) {
    return fac[x] * inv(fac[y], Mod) % Mod * inv(fac[x - y], Mod) % Mod;
}

int n;

int main() {
    fac[0] = 1;
    for (int i = 1; i < N; i ++)
        fac[i] = fac[i - 1] * i % Mod;
    scanf("%d", &n);
    LL res = 1;
    int tot = 0, x;
    for (int i = 0; i < n; i ++) {
        scanf("%d", &x);
        tot += x;
        res = res * C(tot - 1, x - 1) % Mod;
    }
    printf("%I64d\n", res);
}
