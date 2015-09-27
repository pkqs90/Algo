// I got this problem wrong 7 times before passing it.
// WTF dude.

#include <bits/stdc++.h>

using namespace std;

#define  lc(x)  (x << 1)
#define  rc(x)  (lc(x) + 1)
#define  LL     long long

const int N = 1e6 + 7;

int m, h[2], a[2], x[2], y[2];

pair<int, int> Calc(int o) {
    LL cur = h[o];
    int A = -1, B = -1;
    for (int i = 0; i < 2 * N; i ++) {
        if (cur == a[o] && A != -1) {
            B = i - A;
            break;
        }
        if (cur == a[o] && A == -1) {
            A = i;
        }
        cur = (cur * x[o] % m + y[o]) % m;
    }
    return {A, B};
}

int main() {
    cin >> m;
    for (int i = 0; i < 2; i ++) {
        scanf("%d%d", &h[i], &a[i]);
        scanf("%d%d", &x[i], &y[i]);
    }
    pair<int, int> t0 = Calc(0), t1 = Calc(1);
    if (t0.first == -1 || t1.first == -1)
        puts("-1");
    else {
        if (t0.second == -1 && t1.second == -1) {
            if (t0.first == t1.first) printf("%d\n", t0.first);
            else puts("-1");
        } else if (t0.second == -1 || t1.second == -1) {
            if (t1.second == -1) swap(t0, t1);
            int t = (t0.first - t1.first) / t1.second;
            if (t0.first < t1.first || (t0.first - t1.first) % t1.second)
                puts("-1");
            else
                printf("%d\n", t0.first);
        } else {
            for (int i = 0; i < N; i ++) {
                if (((t0.first + 1LL * t0.second * i) - t1.first) % t1.second == 0 &&
                    ((t0.first + 1LL * t0.second * i) - t1.first) >= 0) {
                    printf("%I64d\n", t0.first + 1LL * t0.second * i);
                    return 0;
                }
            }
            puts("-1");
        }
    }
}
