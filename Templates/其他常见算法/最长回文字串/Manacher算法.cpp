// https://cp-algorithms.com/string/manacher.html#manachers-algorithm

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

const int N = 2000005;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;


char ch[N], str[N]; int p[N];

void Manacher(int n){
    int mx = 0, id;
    for(int i = 1; i <= n; i ++){
        if(mx > i) p[i] = min(p[2 * id - i], mx - i);
        else p[i] = 1;
        for(; str[i + p[i]] == str[i - p[i]] && i + p[i] <= n && i + p[i] >= 0; p[i] ++);
        if(p[i] + i > mx)
           mx = p[i] + i, id = i;
    }
}

int cnt, ans, cas;

int main(){
    //freopen("in.txt", "r", stdin);
    while(scanf(" %s", ch + 1) == 1){
        if(ch[1] == 'E') break;
        str[0] = '#';
        cnt = 0;
        for(int i = 1, len = strlen(ch + 1); i <= len; i ++)
            str[++ cnt] = ch[i], str[++ cnt] = '#';
        Manacher(cnt);
        ans = 0;
        for(int i = 1; i <= cnt; i ++)
            ans = max(ans, p[i] - 1);
        printf("Case %d: %d\n", ++ cas, ans);
    }
}
