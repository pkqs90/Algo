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

const int N = 2e5 + 7;
const int INF = 0x7fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct Complex{
    DB a, b;
    Complex(){}
    Complex(DB _a, DB _b){
        a = _a, b = _b;
    }
    Complex operator + (const Complex &c) const {return Complex(a + c.a , b + c.b);}
    Complex operator - (const Complex &c) const {return Complex(a - c.a , b - c.b);}
    Complex operator * (const Complex &c) const {return Complex(a * c.a - b * c.b , a * c.b + b * c.a);}
};

void Change(Complex y[], int len) {
    for(int i = 1 ,j = len / 2; i < len - 1; i ++){
        if(i < j) swap(y[i], y[j]);
        int k = len / 2;
        while(j >= k)
            j -= k, k /= 2;
        if(j < k) j += k;
    }
}

void FFT(int len, int on, Complex y[]){
    Change(y, len);
    for (int h = 2; h <= len; h <<= 1){
        Complex wn(cos(-on * 2 * PI / h), sin(-on  *2 * PI / h));
        for (int j = 0; j < len; j += h){
            Complex w(1, 0);
            for (int k = j; k < j + h / 2; k ++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t, y[k + h / 2] = u - t, w = w * wn;
            }
        }
    }
    if(on == -1)
        for(int i = 0; i < len; i ++)
            y[i].a = (y[i].a / len);
}

Complex A[N << 2], B[N << 2];

char ch1[N], ch2[N]; int a[N], b[N], Q[205][N];

int main(){
//    freopen("in.txt", "r", stdin);
    scanf(" %s", ch1); int n1 = strlen(ch1);
    scanf(" %s", ch2); int n2 = strlen(ch2);

    for(int i = 0; i < n1; i ++) a[i] = ch1[i] - '0' == 1 ? 1 : -1;
    for(int i = 0; i < n2; i ++) b[i] = ch2[i] - '0' == 1 ? 1 : -1;
    reverse(b, b + n2);
    int sz = sqrt(n1 * 16), tot = (n1 - 1) / sz;
    int len = 1; while(len < n2 + sz) len <<= 1;
    for(int i = 0; i < n2; i ++) B[i] = Complex(b[i], 0);
    for(int i = n2; i < len; i ++) B[i] = Complex(0, 0);
    reverse(b, b + n2);
    FFT(len, 1, B);

    for(int i = 0; i <= tot; i ++){
        int st = sz * i, cur = min(sz, n1 - st), ed = st + cur, t = 0;
        for(int j = st; j < ed; j ++) A[t ++] = Complex(a[j], 0);
        for(; t < len; t ++) A[t] = Complex(0, 0);
        FFT(len, 1, A);
        for(int j = 0; j < len; j ++) A[j] = A[j] * B[j];
        FFT(len, -1, A);
        for(int j = 0; j <= n2 - cur; j ++) Q[i][j] = (cur - (floor)(A[n2 - 1 - j].a + 0.5)) / 2;
    }
    int l1, l2, r1, m;
    cin >> m;
    while(m --){
        scanf("%d%d%d", &l1, &l2, &len);
        r1 = l1 + len - 1;
        int ll = l1 / sz, rr = r1 / sz;
        int res = 0, t = 0;
        if(ll == rr){
            for(int i = l1; i <= r1; i ++) res += (a[i] != b[l2 + t]), t ++;
        } else{
            for(int i = l1; i < sz * (ll + 1); i ++) res += (a[i] != b[l2 + t]), t ++;
            for(int i = ll + 1; i < rr; i ++) res += Q[i][l2 + t], t += sz;
            for(int i = sz * rr; i <= r1; i ++) res += (a[i] != b[l2 + t]), t ++;
        }
        printf("%d\n", res);
    }
}
