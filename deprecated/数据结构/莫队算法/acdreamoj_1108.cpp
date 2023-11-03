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
#define  DB    long double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  INF   0x3fffffff
#define  PB    push_back
#define  MP    make_pair

using namespace std;

int limit, l[MAXN], r[MAXN];

bool cmp(const int &i, const int &j){
    int k1 = l[i] / limit, k2 = l[j] / limit;
    if(k1 != k2) return k1 < k2;
    return r[i] < r[j];
}

int t, n, m, a[MAXN], c[MAXN], id[MAXN], fre[MAXN], cnt[MAXN], ans[MAXN];

int calc(int x){
    int ll = 1, rr = MAXN;
    while(ll < rr){
        int mid = ll + rr + 1 >> 1;
        if(fre[mid] < x) rr = mid - 1;
        else ll = mid;
    }
    return ll;
}

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        memset(fre, 0, sizeof(fre));
        memset(cnt, 0, sizeof(cnt));
        scanf("%d%d", &n, &m);
        limit = sqrt(n + 0.5);
        for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
        for(int i = 1; i <= m; i ++) scanf("%d%d%d", &l[i], &r[i], &c[i]), id[i] = i;
        sort(id + 1, id + 1 + m, cmp);
        int ll = 1, rr = 0;
        for(int i = 1; i <= m; i ++){
            int k = id[i];
            while(rr < r[k]) fre[++ cnt[a[++ rr]]] ++;
            while(rr > r[k]) fre[cnt[a[rr --]] --] --;
            while(ll < l[k]) fre[cnt[a[ll ++]] --] --;
            while(ll > l[k]) fre[++ cnt[a[-- ll]]] ++;
            ans[k] = calc(c[k]);
        }
        for(int i = 1; i <= m; i ++)
            printf("%d\n", ans[i]);
    }
}
