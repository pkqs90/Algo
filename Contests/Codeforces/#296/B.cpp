// Easy problem, but I complicated it at the beginning.

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
#define  LL    long long

using namespace std;

const int N = 2e5 + 7;
const int Inf = 0x3fffffff;
const int Mod = 1e9 + 7;
const double eps = 1e-8;

int n, a[N], b[N], id[N];

bool cmp(int i, int j) {
    return a[i] + b[i] < a[j] + b[j];
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
        scanf("%d%d", &a[i], &b[i]);
        id[i] = i;
    }
    sort(id, id + n, cmp);
    int mn = -1e9, res = 0;
    for (int ii = 0; ii < n; ii ++) {
        int i = id[ii];
        if (a[i] - b[i] >= mn) {
            mn = a[i] + b[i];
            res ++;
        }
    }
    printf("%d\n", res);
}
