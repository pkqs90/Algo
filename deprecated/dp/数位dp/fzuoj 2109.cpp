#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define  lc(x) (x << 1)
#define  rc(x) (lc(x) + 1)
#define  lowbit(x) (x & (-x))
#define  PI    (acos(-1))
#define  lowbit(x) (x & (-x))
#define  EPS   1e-10
#define  MAXN  100005
#define  MAXM  2005
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  INF   0x3fffffff
#define  PB    push_back
#define  MP    make_pair
#define  MOD   1000000007

using namespace std;

int f[20][11][2][2], dig[20];

int dp(int pos, int num, int sta, int flag, bool first){
    if(pos == 0) return 1;
    if(flag == 0 && f[pos][num][sta][first] != -1) return f[pos][num][sta][first];
    int res = 0;
    for(int i = 0, r = flag ? dig[pos] : 9; i <= r; i ++){
        if(i == 0 && first == true) res = res + dp(pos - 1, 9, 0, 0, 1);
        else if(sta == 0 && i <= num) res = res + dp(pos - 1, i, sta ^ 1, flag && (i == r), 0);
        else if(sta == 1 && i >= num) res = res + dp(pos - 1, i, sta ^ 1, flag && (i == r), 0);
    }
    return flag ? res : f[pos][num][sta][first] = res;
}

int calc(int x){
    int cnt = 0, res;
    while(x) dig[++ cnt] = x % 10, x /= 10;
    res = dp(cnt, 9, 0, 1, 1);
    return res;
}

int t, l, r;

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> t;
    memset(f, -1, sizeof(f));
    while(t --){
        scanf("%d%d", &l, &r);
        int k2 = calc(r), k1 = calc(l - 1);
        cout << f[3][9][0][0] << ' ' << f[3][9][0][1] << endl;
        printf("%d\n", k2 - k1);
    }
}
