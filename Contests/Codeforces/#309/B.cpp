#include <bits/stdc++.h>

using namespace std;

#define LL  long long

LL f[55], m;
int n, res[55];

void Gao(int pos) {
    if (pos >= n + 1) {
        return;
    }
    if (f[n - pos] >= m) {
        res[pos] = pos;
        Gao(pos + 1);
    } else {
        res[pos] = pos + 1;
        res[pos + 1] = pos;
        m -= f[n - pos];
        Gao(pos + 2);
    }
}

int main() {
    f[0] = f[1] = 1;
    for (int i = 2; i <= 50; i ++) {
        f[i] = f[i - 1] + f[i - 2];
    }
    scanf("%d%I64d", &n, &m);
    Gao(1);
    for (int i = 1; i <= n; i ++) {
        printf("%d ", res[i]);
    }
}
