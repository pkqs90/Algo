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

const int N = 2005;
const int M = N * N * 2;
const int MOD = 2e9 + 7;
const int INF = 2e9 + 7;
const DB  EPS = 1e-8;

int T, n;

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> T;
    while (T --) {
        scanf("%d", &n);
        int res = INF;
        for (int i = 1; i * i <= n; i ++) {
            if (n % i == 0) res = min(res, i + n / i);
        }
        cout << 2 * res << endl;
    }
}
