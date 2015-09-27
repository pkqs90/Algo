// Simple, but finished a bit slow.

#include <bits/stdc++.h>

using namespace std;

#define  lc(x)  (x << 1)
#define  rc(x)  (lc(x) + 1)
#define  LL     long long

const int N = 2e5 + 7;

int n, a[N], l[N], r[N], res[N];
pair<int, int> s[N]; int tail;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++)
        scanf("%d", &a[i]);
    s[tail ++] = {0, 0};
    for (int i = 1; i <= n; i ++) {
        while (tail && a[i] <= s[tail - 1].first) tail --;
        l[i] = s[tail - 1].second;
        s[tail ++] = {a[i], i};
    }
    s[0] = {0, n + 1};
    tail = 1;
    for (int i = n; i >= 1; i --) {
        while (tail && a[i] <= s[tail - 1].first) tail --;
        r[i] = s[tail - 1].second;
        s[tail ++] = {a[i], i};
    }
    for (int i = 1; i <= n; i ++) {
        int d = r[i] - l[i] - 1;
        res[d] = max(res[d], a[i]);
//        cout << l[i] << ' ' << r[i] <<endl;
    }
    for (int i = n; i >= 1; i --) {
        res[i] = max(res[i], res[i + 1]);
    }
    for (int i = 1; i <= n; i ++) {
        printf("%d ", res[i]);
    }
    puts("");
}
