#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {
    cin >> a >> b;
    if (a < b) {
        puts("-1");
    } else {
        int l = a - b, r = a + b;
        int x = l / b, y = r / b;
        if (x & 1) x --;
        if (y & 1) y --;
        double res = 1e10;
        if (x) res = min(res, 1.0 * l / x);
        if (y) res = min(res, 1.0 * r / y);
        printf("%.10f\n", res);
    }
}
