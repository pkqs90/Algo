#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <cstdio>
#include <string>
#include <vector>
#include <iomanip>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define  lc(x) (x<<1)
#define  rc(x) (lc(x)+1)
#define  PI    (acos(-1))
#define  EPS   1e-8
#define  MAXN  1111111
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  MOD   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

LL tot, sum[33], sum2[33];

int a[MAXN], b[MAXN], c[MAXN];

void gao(int dd, int l, int r){
    if(dd == 0) return;
    int mid = l + r >> 1;
    gao(dd - 1, l, mid), gao(dd - 1, mid + 1, r);
    vector <int> vec;
    int lp = l, rp = mid + 1;
    while(lp <= mid && rp <= r){
        if(b[lp] <= b[rp]) vec.pb(b[lp]), lp ++, sum[dd] += (rp - mid - 1);
        else vec.pb(b[rp]), rp ++;
    }
    while(lp <= mid) vec.pb(b[lp]), lp ++, sum[dd] += (r - mid);
    while(rp <= r) vec.pb(b[rp]), rp ++;
    for(int i = 0; i < vec.size(); i ++){
        b[l + i] = vec[i];
        //cout << l << ' ' << vec[i] << endl;
    }
}

void gao2(int dd, int l, int r){
    if(dd == 0) return;
    int mid = l + r >> 1;
    gao2(dd - 1, l, mid), gao2(dd - 1, mid + 1, r);
    vector <int> vec;
    int lp = l, rp = mid + 1;
    while(lp <= mid && rp <= r){
        if(c[lp] <= c[rp]) vec.pb(c[lp]), lp ++, sum2[dd] += (rp - mid - 1);
        else vec.pb(c[rp]), rp ++;
    }
    while(lp <= mid) vec.pb(c[lp]), lp ++, sum2[dd] += (r - mid);
    while(rp <= r) vec.pb(c[rp]), rp ++;
    for(int i = 0; i < vec.size(); i ++){
        c[l + i] = vec[i];
        //cout << l << ' ' << vec[i] << endl;
    }
}


int n, m, q, x;

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> n;
    m = 1;
    for(int i = 1; i <= n; i ++) m *= 2;
    for(int i = 1; i <= m; i ++) scanf("%d", &a[i]), b[i] = a[i], c[m - i + 1] = a[i];
    gao(n, 1, m), gao2(n, 1, m);
    for(int i = 1; i <= n; i ++)
        tot += sum[i];
    //cout << sum[1] << ' ' << sum2[1] << endl;
    cin >> q;
    while(q --){
        scanf("%d", &x);
        for(int i = x; i >= 1; i --){
            tot = tot - sum[i] + sum2[i];
            swap(sum[i], sum2[i]);
        }
        printf("%I64d\n", tot);
    }
}
