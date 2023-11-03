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

const int N = 1e5 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 9;
const DB  EPS = 1e-8;

LL pow_mod(LL x, LL y, LL z) {
    LL res = 1;
    while(y) {
       if(y & 1) res *= x, res %= z;
       x *= x, x %= z, y >>= 1;
    }
    return res % z;
}

struct Complex{
    LL x, y;
    Complex(){}
    Complex(LL _x, LL _y){
        x = _x, y = _y;
    }
};

LL w;

Complex Mul(Complex A, Complex B, LL p){
    Complex ret;
    ret.x = (A.x * B.x % p + A.y * B.y % p * w % p) % p;
    ret.y = (A.x * B.y % p + A.y * B.x % p) % p;
    return ret;
}

Complex Pow_mod(Complex x, LL y, LL p){
    Complex ret(1, 0);
    while(y){
        if(y & 1) ret = Mul(ret, x, p);
        x = Mul(x, x, p), y >>= 1;
    }
    return ret;
}

LL Legendre(LL x, LL y){ // 勒让德符号，仅在 d ^ ((p - 1) / 2) 之时 d 为 p 的二次剩余；
    return pow_mod(x, (y - 1) / 2, y);
}

LL gao(LL d, LL p){
    if(p == 2) return 1;
    if(Legendre(d, p) + 1 == p) return -1;
    LL a;
    while(1){
        a = rand() % p;
        w = ((a * a - d) % p + p) % p;
//        cout << a << ' ' << w << ' ' << Legendre(w, p) << endl;
        if(Legendre(w, p) + 1 == p) break;
    }
    Complex ret = Pow_mod(Complex(a, 1), (p + 1) / 2, p);
//    cout << ret.x <<endl;
    return ret.x;
}

int t; LL d, p;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        scanf("%lld%lld", &d, &p);
        d %= p;
        if(p == 2){
            if(d == 1) puts("1");
            else puts("No root");
        } else{
            LL k = gao(d, p);
            if(k == -1){
                puts("No root");
            } else{
                if(k > p - k) k = p - k;
                printf("%lld %lld\n", k, p - k);
            }
        }
    }
}
