#include <bits/stdc++.h>

using namespace std;

#define LL  long long

const int N = 3e5 + 7;

int n, m; LL a[N], s[N];

int main() {
    cin >> n >> m;
    for (int i = 1; i <= n; i ++) {
        scanf("%I64d", &a[i]);
    }
    sort(a + 1, a + n + 1);
    vector<vector<LL>> f(n % m + 1, vector<LL>(m - n % m + 1, 2e9));
    int big = f.size(), small = f[0].size();
    int bsz = n / m + 1, ssz = n / m;
//    cout << bsz << ' ' << ssz << endl;
    f[0][0] = 0;
    for (int i = 0; i < big; i ++)
        for (int j = 0; j < small; j ++) {
            int cur = i * (bsz) + j * (ssz);
            if (i) f[i][j] = min(f[i][j], f[i - 1][j] + a[cur] - a[cur - bsz + 1]);
            if (j) f[i][j] = min(f[i][j], f[i][j - 1] + a[cur] - a[cur - ssz + 1]);
        }
    printf("%I64d\n", f[big - 1][small - 1]);
}
