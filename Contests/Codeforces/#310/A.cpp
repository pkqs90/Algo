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

int n, m, x, y, cnt;

int main() {
    scanf("%d%d", &n, &m);
    int mx = 0, res = n - 1;
    for (int i = 1; i <= m; i ++) {
        scanf("%d", &x);
        res += x - 1;
        int op = 0, pre = -1;
        for (int j = 0; j < x; j ++) {
            scanf("%d", &y);
            if (y == 1) op = 1, cnt = 0;
            else {
                if (op && y == pre + 1) cnt ++;
                else op = 0;
            }
            pre = y;
        }
    }
    printf("%d\n", res - 2 * cnt);
}
