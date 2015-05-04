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
#define  MAXN  200055
#define  MAXM  2005
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  INF   50000
#define  pb    push_back
#define  mp    make_pair
#define  MOD   1000000007

using namespace std;

int ext[MAXN], len, next[MAXN];

void extend_kmp(char *ch){
    // ext 下标从 0 开始 。。 ext[0] 无意义强制为 0 。。
    memset(ext, 0, sizeof(ext));
    len = strlen(ch);
    int j = 0;
    while(1 + j < len && ch[j] == ch[1 + j]) j ++;
    ext[1] = j;
    int k = 1;
    for(int i = 2; i < len; i ++){
        int Len = k + ext[k] - 1, L = ext[i - k];
        if(L < Len - i + 1)
            ext[i] = L;
        else{
            j = max(0, Len - i + 1);
            while(i + j < len && ch[i + j] == ch[j]) j ++;
            ext[i] = j, k = i;
        }
    }
}

void kmp(char *ch){
    // next 下标从 1 开始 。。 next[1] 无意义强制为 0 。。
    memset(next, 0, sizeof(next));
    len = strlen(ch);
    for(int i = len; i >= 1; i --) ch[i] = ch[i - 1];
    int j = 0;
    for(int i = 2; i <= len; i ++){
        while(j && ch[i] != ch[j + 1]) j = next[j];
        if(ch[i] == ch[j + 1]) j ++;
        next[i] = j;
    }
    for(int i = 0; i < len; i ++) ch[i] = ch[i + 1]; ch[len] = '\0';
    // 事后还原 。。
}

char ch[MAXN];

int t, cas;

int main() {
    //freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        scanf(" %s", &ch);
        int n = strlen(ch);
        for(int i = n; i < n * 2 - 1; i ++) ch[i] = ch[i - n];
        extend_kmp(ch);
        kmp(ch);
        int eq = 1, lg = 0, sm = 0;
        for(int i = 1; i < n; i ++){
            if(ext[i] >= n) eq ++;
            else{
                if(ch[i + ext[i]] > ch[ext[i]]) lg ++;
                else sm ++;
            }
        }
        int d = 1;
        if(n % (n - next[n]) == 0) d = n / (n - next[n]);
        printf("Case %d: %d %d %d\n", ++ cas, sm / d, eq / d, lg / d);
    }
}
