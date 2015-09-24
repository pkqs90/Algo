// 正难则反 .. =_=

#include <bits/stdc++.h>

using namespace std;

#define LL  long long

LL a[5], l, res;

void Gao() {
    for (int i = 0; i <= l; i ++) {
        LL t = a[0] + i;
        LL mx = min(l - i, t - a[1] - a[2]);
        if (mx < 0) continue;
        res -= (mx + 2) * (mx + 1) / 2;
    }
}

int main() {
    for (int i = 0; i < 3; i ++) {
        scanf("%I64d", &a[i]);
    }
    scanf("%I64d", &l);
    res = (l + 3) * (l + 2) * (l + 1) / 6;
    Gao();
    swap(a[0], a[1]);
    Gao();
    swap(a[0], a[2]);
    Gao();
    printf("%I64d\n", res);
}
