#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <vector>
#include <string>
#include <cstdio>
#include <iomanip>
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  PI    (acos(-1))
#define  EPS   1e-8
#define  MAXN  10005
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  MOD   1000000007
#define  pb    push_back
#define  mp    make_pair
#define  lowbit(x) (x&(-x))

using namespace std;

int wa[MAXN], wb[MAXN], S[MAXN];

int sa[MAXN], rank[MAXN], height[MAXN];

void da(char *ch, int n, int m){
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

int len1, lensum;

char ch[MAXN];

int main(){
    //freopen("in.txt", "r", stdin);
    scanf(" %s", ch);
    len1 = strlen(ch);
    ch[len1] = '$';
    scanf(" %s", ch + len1 + 1);
    lensum = strlen(ch);
    ch[lensum] = '\0';
    da(ch, lensum + 1, 200), calcheight(ch, lensum);
    /*cout << ch << endl;
    for(int i = 0; i <= lensum; i ++)
        cout << sa[i] << ' ' << rank[i] << ' ' << height[i] << endl;*/
    int ans = 100000;
    for(int i = 1; i <= lensum; i ++){
        if(height[i] > 0){
            if((sa[i] > len1 && sa[i - 1] < len1) || (sa[i] < len1 && sa[i - 1] > len1)){
                if(height[i - 1] >= height[i] || height[i + 1] >= height[i]) continue;
                int k = max(height[i - 1], height[i + 1]);
                ans = min(ans, k + 1);
            }
        }
    }
    if(ans == 100000) cout << -1 << endl;
    else cout << ans << endl;
    return 0;
}
