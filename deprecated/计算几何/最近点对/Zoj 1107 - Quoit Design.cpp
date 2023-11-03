#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <queue>
#include <cmath>
#include <stack>
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
#define  MAXN  100005
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  MOD   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct Point{
    double x, y;
} p[MAXN];
bool cmpx(const Point &A, const Point &B){
    if(A.x != B.x) return A.x < B.x;
    return A.y < B.y;
}
bool cmpy(const Point &A, const Point &B){
    return A.y < B.y;
}
double sqr(double x){
    return x * x;
}
double dist(Point A, Point B){
    return sqrt(sqr(A.x - B.x) + sqr(A.y - B.y));
}
double ans;
vector <Point> vec;
void gao(int l, int r){
    if(r - l <= 4){
        for(int i = l; i < r; i ++) for(int j = i + 1; j <= r; j ++) ans = min(ans, dist(p[i], p[j]));
        sort(p + l, p + r + 1, cmpy);
        return;
    }
    int mid = l + r >> 1;
    double midx = p[mid].x;
    gao(l, mid), gao(mid + 1, r);
    inplace_merge(p + l, p + mid + 1, p + r, cmpy);
    vec.clear();
    for(int i = l; i <= r; i ++) if(fabs(midx - p[i].x) <= ans) vec.pb(p[i]);
    for(int i = 0; i < vec.size(); i ++)
        for(int j = i + 1; j < vec.size() && vec[j].y - vec[i].y <= ans; j ++)
            ans = min(ans, dist(vec[i], vec[j]));
}
int n;
int main(){
    //freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) == 1){
        if(!n) break;
        for(int i = 0; i < n; i ++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        sort(p, p + n, cmpx);
        ans = 1e100;
        gao(0, n - 1);
        printf("%.2lf\n", ans / 2.0);
    }
}
