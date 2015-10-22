// ZOJ 3631 Birthday Gift

#include <bits/stdc++.h>

using namespace std;

#define  LL  long long

const int N = 1e4 + 5;
const int Mod = 786433; // 3 * 2^18 + 1, 2^18 > 2*N
const int g = 10; // prime root of Mod

void ext_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}

LL inv(LL a, LL c) {
    LL d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

LL pow_mod(LL x, LL y, LL z) {
    LL res = 1;
    while(y) {
       if(y & 1) res *= x, res %= z;
       x *= x, x %= z, y >>= 1;
    }
    return res % z;
}

void Change(LL y[], int len) {
    for(int i = 1 ,j = len / 2; i < len - 1; i ++){
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k)
            j -= k, k /= 2;
        if(j < k) j += k;
    }
}

void FFT(int len, int on, LL y[]){
    Change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        LL wn = pow_mod(g, (Mod - 1) / h, Mod);
        if (on == -1) wn = inv(wn, Mod);
        for (int j = 0; j < len; j += h){
            LL w = 1;
            for (int k = j; k < j + h / 2; k ++){
                LL u = y[k];
                LL t = w * y[k + h / 2] % Mod;
                y[k] = (u + t) % Mod;
                y[k + h / 2] = (u - t + Mod) % Mod;
                w = w * wn % Mod;
            }
        }
    }
    if(on == -1) {
        LL lenInv = inv(len, Mod);
        for(int i = 0; i < len; i ++)
            y[i] = (y[i] * lenInv) % Mod;
    }
}

char ch1[N], ch2[N];

LL fac[N], invfac[N];
LL a[N << 2], b[N << 2], st2[N << 2];

int n1;
void InitStirling() {
    int len = 1;
    while (len < 2 * n1) len <<= 1;
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    // F[i] = (1/i!) * sigma((-1 ^ k) * C(i, k) * (i - k) ^ n1);
    for (int i = 0, op = 1; i <= n1; i ++, op = -op)
        a[i] = (op * invfac[i] + Mod) % Mod;
    for (int i = 0; i <= n1; i ++)
        b[i] = pow_mod(i, n1, Mod) * invfac[i] % Mod;
    FFT(len, 1, a);
    FFT(len, 1, b);
    for (int i = 0; i < len; i ++) a[i] = a[i] * b[i] % Mod;
    FFT(len, -1, a);
    for (int i = 1; i <= n1; i ++) st2[i] = a[i];
}

bool isPrime[N];
void InitPrimeTable() {
    for (int i = 2; i < N; i ++) isPrime[i] = true;
    for (int i = 2; i < N; i ++) {
        if (!isPrime[i]) continue;
        for (int j = i + i; j < N; j += i)
            isPrime[j] = 0;
    }
}

LL C(int x, int y) {
    if (y < 0 || x < 0 || x < y) return 0;
    return fac[x] * invfac[x - y] % Mod * invfac[y] % Mod;
}

int T, M, Q, n2, q;
int main() {
    InitPrimeTable();
    fac[0] = invfac[0] = 1;
    for (int i = 1; i < N; i ++) {
        fac[i] = fac[i - 1] * i % Mod;
        invfac[i] = inv(fac[i], Mod);
    }
    cin >> T;
    while (T --) {
        scanf("%d%d%d%d", &n1, &n2, &M, &Q);
        InitStirling();
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for (int i = 1; i <= n1; i ++) {
            if (isPrime[i]) a[i] = st2[i];
            else if (i == n1) a[i] = 1;
            else a[i] = C(n1, i - 1);
        }
        for (int i = 1; i <= n2; i ++) {
            b[i] = C(M, i) * C(n2 - 1, i - 1) % Mod;
        }
        int len = 1;
        while (len < 2 * max(n1, n2)) len <<= 1;
        FFT(len, 1, a);
        FFT(len, 1, b);
        for (int i = 0; i < len; i ++) a[i] = a[i] * b[i] % Mod;
        FFT(len, -1, a);
        while (Q --) {
            scanf("%d", &q);
            printf("%lld\n", a[q]);
        }
    }
}
