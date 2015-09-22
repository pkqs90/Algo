// 1. Ternary search
// 2. Binary search
// 3. Convex hull (cool solution)
// http://codeforces.com/blog/entry/20368

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;

int n, a[N];

double Gao(double x) {
    double mn = 0, mx = 0, ret = 0;
    for (int i = 0; i < n; i ++) {
        if (mx < 0) mx = 0; mx += (a[i] - x);
        if (mn > 0) mn = 0; mn += (a[i] - x);
        ret = max(ret, fabs(mx));
        ret = max(ret, fabs(mn));
    }
    return ret;
}

int main() {
    cin >> n;
    for (int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
    }
    double l = -1e4, r = 1e4;
    for (int i = 1; i <= 100; i ++) {
        double mid1 = l + (r - l) / 3.0;
        double mid2 = r - (r - l) / 3.0;
        if (Gao(mid1) < Gao(mid2)) r = mid2;
        else l = mid1;
    }
    printf("%.10f\n", Gao(l));
}
