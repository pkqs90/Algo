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
const int MOD = 1e9 + 7;

void ext_gcd(LL a, LL b, LL &d, LL &x, LL &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}

LL inv(LL a, LL c) {
    LL d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

int x1, y1, x2, y2, M;

LL Gao(int a, int b, int c) {
    LL ret = 1, tot = 0, result = 0;
    if (b > a) return 0;
    for (int i = a; i > a - b; i --) {
        int t = i;
        while (t % M == 0) {
            t /= M, tot ++;
        }
//        cout << t <<endl;
        ret = ret * t % M;
    }
//    cout << ret <<endl;
    for (int i = b; i >= 1; i --) {
        int t = i;
        while (t % M == 0) {
            t /= M, tot --;
        }
        ret = ret * inv(t, M) % M;
    }
//    cout << ret << ' ' << tot << endl;
    if (tot == 0) result += ret;
    for (int i = b + 1; i <= c; i ++) {
        if (i > a) break;
        int t = a - i + 1;
        while (t % M == 0) {
            t /= M, tot ++;
        }
        ret = ret * t % M;
        t = i;
        while (t % M == 0) {
            t /= M, tot --;
        }
        ret = ret * inv(t, M) % M;
        if (tot == 0) {
            result += ret;
            result %= M;
        }
    }
    return result;
}

int main(){
//    freopen("in.txt", "r", stdin);
//    M = 3;
//    cout << Gao(3, 1, 3) << endl;
    while(cin >> x1 >> y1 >> x2 >> y2 >> M)  {
        LL res = 0;
        res += Gao(x2 + 1, y1 + 1, y2 + 1);
        res -= Gao(x1, y1 + 1, y2 + 1);
        res = (res % M + M) % M;
        cout << res << endl;
    }
}
