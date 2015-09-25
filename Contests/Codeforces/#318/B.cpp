// I consider this a fairly easy way of implementing this problem.

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

const int N = 1e5 + 7;

int n, a[N];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i ++) {
        a[i] = min(a[i], a[i - 1] + 1);
    }
    for (int i = n; i >= 1; i --) {
        a[i] = min(a[i], a[i + 1] + 1);
    }
    int mx = 0;
    for (int i = 1; i <= n; i ++) {
        mx = max(mx, a[i]);
    }
    cout << mx << endl;
}
