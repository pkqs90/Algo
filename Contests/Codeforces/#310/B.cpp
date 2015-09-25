#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <set>
#include <bitset>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 2e5 + 7;
#define  LL  long long

struct Node {
    LL l, r, id;
    Node() {}
    Node(LL l_, LL r_, LL id_) {
        l = l_, r = r_, id = id_;
    }
    bool operator < (const Node &A) const {
        if (r != A.r) return r > A.r;
        return l > A.l;
    }
} p[N];

int n, m; LL x[N], y[N]; int res[N];
set<pair<LL, int> > l;

bool Check() {
    for (int i = 0; i < n - 1; i ++) {
        LL v = p[i].l;
        auto t = l.upper_bound(make_pair(v, N));
        if (t == l.begin()) return false;
        t --;
        if (t->first >= p[i].r) {
            res[p[i].id] = t->second;
            l.erase(t);
        } else {
            return false;
        }
    }
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i ++) {
        scanf("%I64d%I64d", &x[i], &y[i]);
        if (i) {
            p[i - 1] = Node(y[i] - x[i - 1], x[i] - y[i - 1], i - 1);
        }
    }
    sort(p, p + n - 1);
    LL t;
    for (int i = 0; i < m; i ++) {
        scanf("%I64d", &t);
        l.insert(make_pair(t, i + 1));
    }
    if (Check()) {
        puts("Yes");
        for (int i = 0; i < n - 1; i ++) {
            printf("%d ", res[i]);
        }
    } else {
        puts("No");
    }
}
