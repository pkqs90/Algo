// This solution is very nice.

#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

int n, m, x, y; char c;
map<int, pair<char, int> > mp;

int main() {
    scanf("%d%d", &n, &m);
    mp[0] = make_pair('U', n + 1);
    mp[n + 1] = make_pair('L', n + 1);
    for (int i = 0; i < m; i ++) {
        scanf("%d%d %c", &x, &y, &c);
        auto u = mp.lower_bound(x);
        if (u->first == x) {
            puts("0");
        } else {
            if (c == 'L')
                u --;
            int res = fabs(u->first - x);
            if (u->second.first == c)
                res += u->second.second;
            printf("%d\n", res);
            mp[x] = make_pair(c, res);
        }
    }
}
