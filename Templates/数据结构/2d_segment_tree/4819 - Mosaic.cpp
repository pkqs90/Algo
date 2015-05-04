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
#define  MAXN  810
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct _2dseg{
    int mn, mx;
} tree[MAXN << 2][MAXN << 2];

int n;

pair<int, int> calcy(int x, int y, int ll, int rr, int ly, int ry){
    if(ly <= ll && rr <= ry)
        return mp(tree[x][y].mn, tree[x][y].mx);
    int mid = ll + rr >> 1;
    int mx = -INF, mn = INF;
    if(ly <= mid){
        pair<int, int> tmp = calcy(x, lc(y), ll, mid, ly, ry);
        mn = min(mn, tmp.first);
        mx = max(mx, tmp.second);
    }
    if(mid < ry){
        pair<int, int> tmp = calcy(x, rc(y), mid + 1, rr, ly, ry);
        mn = min(mn, tmp.first);
        mx = max(mx, tmp.second);
    }
    return mp(mn, mx);
}

pair<int, int> calcx(int x, int ll, int rr, int lx, int rx, int ly, int ry){
    if(lx <= ll && rr <= rx)
        return calcy(x, 1, 1, n, ly, ry);
    int mid = ll + rr >> 1;
    int mx = -INF, mn = INF;
    if(lx <= mid){
        pair<int, int> tmp = calcx(lc(x), ll, mid, lx, rx, ly, ry);
        mn = min(mn, tmp.first);
        mx = max(mx, tmp.second);
    }
    if(mid < rx){
        pair<int, int> tmp = calcx(rc(x), mid + 1, rr, lx, rx, ly, ry);
        mn = min(mn, tmp.first);
        mx = max(mx, tmp.second);
    }
    return mp(mn, mx);
}

void gaoy(int x, int y, int ll, int rr, int posy, int num, bool leaf){
    if(ll == rr){
        if(leaf) tree[x][y].mn = tree[x][y].mx = num;
        else{
            tree[x][y].mn = min(tree[lc(x)][y].mn, tree[rc(x)][y].mn);
            tree[x][y].mx = max(tree[lc(x)][y].mx, tree[rc(x)][y].mx);
        }
        return;
    }
    int mid = ll + rr >> 1;
    if(posy <= mid) gaoy(x, lc(y), ll, mid, posy, num, leaf);
    else gaoy(x, rc(y), mid + 1, rr, posy, num, leaf);
    tree[x][y].mn = min(tree[x][lc(y)].mn, tree[x][rc(y)].mn);
    tree[x][y].mx = max(tree[x][lc(y)].mx, tree[x][rc(y)].mx);
}

void gaox(int x, int ll, int rr, int posx, int posy, int num){
    if(ll == rr){
        gaoy(x, 1, 1, n, posy, num, true);
        return;
    }
    int mid = ll + rr >> 1;
    if(posx <= mid) gaox(lc(x), ll, mid, posx, posy, num);
    else gaox(rc(x), mid + 1, rr, posx, posy, num);
    gaoy(x, 1, 1, n, posy, num, false);
}

int t, x, q, X, Y, l;

int main(){
    //freopen("read.in","r",stdin);
    scanf("%d", &t);
    for(int cas = 1; cas <= t; cas ++){
        printf("Case #%d:\n", cas);
        scanf("%d", &n);
        init();
        for(int i = 1; i <= n; i ++)
            for(int j = 1; j <= n; j ++){
                scanf("%d", &x);
                gaox(1, 1, n, i, j, x);
            }
        scanf("%d", &q);
        while(q --){
            scanf("%d%d%d", &X, &Y, &l);
            int x_0 = max(X - l / 2, 1), x_1 = min(X + l / 2, n);
            int y_0 = max(Y - l / 2, 1), y_1 = min(Y + l / 2, n);
            pair<int, int> tmp = calcx(1, 1, n, x_0, x_1, y_0, y_1);
            int num = tmp.second + tmp.first >> 1;
            printf("%d\n", num);
            gaox(1, 1, n, X, Y, num);
        }
    }
}
