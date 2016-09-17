// If we do this reversely, we can get a linear solution.

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

const int N = 100055;
const int Inf = 0x3fffffff;
const int Mod = 1e9 + 7;
const double eps = 1e-8;

int a, b, n, t; set<int> v, h;
multiset<int> H, V;
char ch;

int main() {
    scanf("%d%d%d", &a, &b, &n);
    v.insert(0), v.insert(a), V.insert(a);
    h.insert(0), h.insert(b), H.insert(b);
    int mxh = b, mxv = a;
    while (n --) {
        scanf(" %c%d", &ch, &t);
        if (ch == 'H') {
            auto i = h.upper_bound(t);
            int next = *i;
            int pre = *(--i);
            H.erase(H.find(next - pre));
            H.insert(next - t);
            H.insert(t - pre);
            h.insert(t);
        } else {
            auto i = v.upper_bound(t);
            int next = *i;
            int pre = *(--i);
            V.erase(V.find(next - pre));
            V.insert(next - t);
            V.insert(t - pre);
            v.insert(t);
        }
        auto i = H.rbegin();
        auto j = V.rbegin();
        printf("%I64d\n", 1LL * (*j) * (*i));
    }
}
