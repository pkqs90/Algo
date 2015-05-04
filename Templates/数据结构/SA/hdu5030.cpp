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
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  PLL   pair<LL, LL>
#define  PB    push_back
#define  MP    make_pair

using namespace std;

const int N = 1e5 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

int wa[N], wb[N], S[N];

int sa[N], rank[N], height[N];

void da(char *ch, int n, int m){
    // 不用初始化 ..
    int i, j, p = 0, *X = wa, *Y = wb;
    for(i = 0; i < m; i ++) S[i] = 0;
    for(i = 0; i < n; i ++) S[X[i] = ch[i]] ++;
    for(i = 1; i < m; i ++) S[i] += S[i - 1];
    for(i = n - 1; i >= 0; i --) sa[-- S[X[i]]] = i;
    for(j = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n - j; i < n; i ++) Y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) Y[p ++] = sa[i] - j;
        for(i = 0; i < m; i ++) S[i] = 0;
        for(i = 0; i < n; i ++) S[X[Y[i]]] ++;
        for(i = 1; i < m; i ++) S[i] += S[i - 1];
        for(i = n - 1; i >= 0; i --) sa[-- S[X[Y[i]]]] = Y[i];
        swap(X, Y);
        for(p = 1, X[sa[0]] = 0, i = 1; i < n; i ++)
            X[sa[i]] = (Y[sa[i-1]] == Y[sa[i]] && Y[sa[i - 1] + j] == Y[sa[i] + j]) ? p - 1 : p ++;
    }
}

void calcheight(char *ch, int n){
    int i, j, k = 0;
    for(i = 0; i <= n; i ++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i ++]] = k)
        for(k ? k -- : 0, j = sa[rank[i] - 1]; ch[i + k] == ch[j + k]; k ++);
}

int n, m, vis[N]; LL sum[N];

char ch[N];

PII calc(LL x){
    // 二分找到字串位置 ..
    int u = lower_bound(sum, sum + 1 + n, x) - sum;
    return MP(u, x - sum[u - 1] + height[u]);
}

bool check(LL x){
    PII u = calc(x);
    int pos = u.first, len = u.second;
    memset(vis, -1, sizeof(vis));
    vis[sa[pos] + len] = sa[pos];
    int minv = len;
    for(int i = pos + 1; i <= n; i ++){
        minv = std::min(minv, height[i]);
        vis[sa[i] + minv] = std::max(vis[sa[i] + minv], sa[i]);
        if(minv == 0) return 0;
    }
    int last = 0, cnt = 1;
    for(int i = 0; i < n; i ++){
        if(vis[i] >= last)
            cnt ++, last = i;
    }
    return cnt <= m;
}

int main(){
    while(scanf("%d", &m) == 1){
        if(m == 0) break;
        scanf(" %s", ch);
        if(m == 1){
            printf("%s\n", ch);
            continue;
        }
        n = strlen(ch);
        da(ch, n + 1, 200), calcheight(ch, n);
        sum[0] = 0;
        // 二分所有字串 .. 注意 LL
        for(int i = 1; i <= n; i ++){
            sum[i] = sum[i - 1] + n - sa[i] - height[i];
        }
        LL l = 1, r = sum[n];
        while(l < r){
            LL mid = l + r >> 1;
            if(check(mid)) r = mid;
            else l = mid + 1;
        }
        PII u = calc(l);
        int pos = u.first, len = u.second;
        for(int i = sa[pos]; i < sa[pos] + len; i ++)
            printf("%c", ch[i]);
        puts("");
    }
}
