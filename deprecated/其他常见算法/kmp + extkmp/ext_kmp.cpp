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
#define  MAXN  500055
#define  MAXM  2005
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  MOD   1000000007

using namespace std;

int ext[MAXN], pos[MAXN];

void extend_kmp(char *ch1, char *ch2){
    // ext 下标从 0 开始 。。 ext[0] 无意义强制为 0 。。
    memset(ext, 0, sizeof(ext));
    int len1 = strlen(ch1);
    int j = 0;
    while(1 + j < len1 && ch1[j] == ch1[1 + j]) j ++;
    ext[1] = j;
    int k = 1;
    for(int i = 2; i < len1; i ++){
        int Len = k + ext[k] - 1, L = ext[i - k];
        if(L < Len - i + 1)
            ext[i] = L;
        else{
            j = max(0, Len - i +1);
            while(i + j < len1 && ch1[i + j] == ch1[j]) j ++;
            ext[i] = j, k = i;
        }
    }
    int len2 = strlen(ch2); j = 0;
    while(j < len2 && j < len1 && ch1[j] == ch2[j]) j ++;
    pos[0] = j, k = 0;
    for(int i = 1; i < len2; i ++){
        int Len = k + pos[k] - 1, L = ext[i - k];
        if(L < Len - i + 1)
            pos[i] = L;
        else{
            j = max(0, Len - i + 1);
            while(i + j < len2 && j < len1 && ch2[i + j] == ch1[j]) j ++;
            pos[i] = j, k = i;
        }
    }
}

char ch1[MAXN], ch2[MAXN];

int t, cas, a[30], s[MAXN], ll[MAXN], rr[MAXN];

int main() {
    //freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        for(int i = 1; i <= 26; i ++) scanf("%d", &a[i]);
        scanf(" %s", &ch1);
        int n = strlen(ch1);
        for(int i = 0; i < n; i ++){
            s[i] = (i == 0 ? 0 : s[i - 1]) + a[ch1[i] - 'a' + 1];
            ch2[i] = ch1[n - i - 1];
        }

        extend_kmp(ch2, ch1);
        //for(int i = 0; i < n; i ++) cout << i << ' ' << ext[i] << ' ' << pos[i] << endl;
        for(int i = 1; i < n; i ++){
            if(pos[i] == n - i) rr[i] = s[n - 1] - s[i - 1];
            else rr[i] = 0;
            //cout << i << ' ' << rr[i] << endl;
        }

        extend_kmp(ch1, ch2);
        //for(int i = 0; i < n; i ++) cout << i << ' ' << ext[i] << ' ' << pos[i] << endl;
        for(int i = 1; i < n; i ++){
            if(pos[i] == n - i) ll[n - 1 - i] = s[n - 1 - i];
            else ll[i] = 0;
        }


        int ans = -INF;
        for(int i = 0; i < n; i ++){
            if(i != n - 1) ans = max(ans, ll[i] + rr[i + 1]);
            if(i != 0) ans = max(ans, ll[i - 1] + rr[i]);
        }
        printf("%d\n", ans);
    }
}
