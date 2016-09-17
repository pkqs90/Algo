// http://hihocoder.com/problemset/problem/1236
// 暴力Bitset，分块

#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include <set>
#include <bitset>
#include <algorithm>
using namespace std;

const int N = 50005;

bitset<N> p[250][5], res, temp;
vector<pair<int, int> > vec[5];

int T, n, m, a[N][5], q, x;

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d", &T);
    while (T --) {
        scanf("%d%d", &n, &m);
        int sz = sqrt(m + 0.5);
        for (int i = 0; i < 5; i ++) {
            vec[i].clear();
        }
        for (int i = 0; i < n; i ++) {
            for (int j = 0; j < 5; j ++) {
                scanf("%d", &a[i][j]);
                vec[j].push_back(make_pair(a[i][j], i));
            }
        }
        for (int i = 0; i < 250; i ++)
            for (int j = 0; j < 5; j ++)
                p[i][j].reset();
        for (int i = 0; i < 5; i ++) {
            sort(vec[i].begin(), vec[i].end());
            int cur = 0;
            for (int j = 0; j < n; j ++) {
                p[cur + 1][i].set(vec[i][j].second);
                if ((j + 1) % sz == 0) {
                    cur ++;
                    p[cur+1][i] = p[cur][i];
                }
            }
        }
        scanf("%d", &q);
        int pre = 0;
        while (q --) {
            res.set();
            for (int i = 0; i < 5; i ++) {
                scanf("%d", &x);
                x ^= pre;
                int pos = upper_bound(vec[i].begin(), vec[i].end(), make_pair(x, N+N)) - vec[i].begin() - 1;
                int t = pos / sz;
                temp = p[t][i];
                //cout << pos << ' ' << t << temp.count() << endl;
                for (int j = t * sz; j <= pos; j ++) {
                    temp.set(vec[i][j].second);
                }
                res &= temp;
            }
            printf("%d\n", (int)res.count());
            pre = res.count();
        }
    }
}
