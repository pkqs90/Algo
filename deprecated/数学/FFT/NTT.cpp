// HDU 1402 A * B Problem Plus

#include <bits/stdc++.h>

using namespace std;

#define  LL  long long

const int N = 1e5 + 7;
const int Mod = 998244353; // 119 * 2^23 + 1, 2^xx > 2*N
const int g = 3; // prime root of Mod

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

LL a[N << 2], b[N << 2];

int res[N << 2];

int main() {
    while (scanf(" %s %s", ch1, ch2) == 2) {
        int l1 = strlen(ch1), l2 = strlen(ch2), len = 1;
        while (len < 2 * max(l1, l2)) len <<= 1;
        for (int i = 0; i < l1; i ++) a[i] = ch1[l1 - 1 - i] - '0';
        for (int i = l1; i < len; i ++) a[i] = 0;
        for (int i = 0; i < l2; i ++) b[i] = ch2[l2 - 1 - i] - '0';
        for (int i = l2; i < len; i ++) b[i] = 0;
        FFT(len, 1, a);
        FFT(len, 1, b);
        for (int i = 0; i < len; i ++) a[i] = a[i] * b[i] % Mod;
        FFT(len, -1, a);
        for (int i = 0; i < len; i ++) res[i] = a[i] % Mod;
        int mx = 0, op = 0;
        for (int i = 0; i < len; i ++) {
            res[i + 1] += res[i] / 10, res[i] %= 10;
            if (res[i]) mx = i;
        }
        for (int i = mx; i >= 0; i --) printf("%d", res[i]);
        puts("");
    }
}
