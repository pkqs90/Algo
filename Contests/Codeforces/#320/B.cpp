// Using or sums of prefix & suffix would be much easier.

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;

int n, m, x, cnt[60], a[N], t;

void Gao(long long p, int d) {
    int num = 0;
    while (p) {
        cnt[num ++] += (p & 1LL) * d;
        p >>= 1LL;
    }
}

int main() {
    cin >> n >> m >> x;
    t = 1;
    for (int i = 1; i <= m; i ++)
        t *= x;
    for (int i = 0; i < n; i ++) {
        scanf("%d", &a[i]);
        Gao(a[i], 1);
    }
    long long res = 0;
    for (int i = 0; i < n; i ++) {
        Gao(a[i], -1);
        Gao(1LL * a[i] * t, 1);
        long long temp = 0;
        for (int j = 0; j < 60; j ++) {
            temp += (1LL << j) * ((bool)cnt[j]);
        }
        res = max(res, temp);
        Gao(1LL * a[i] * t, -1);
        Gao(a[i], 1);
    }
    cout << res << endl;
}
