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
#define  MAXN  50005
#define  MAXM  888888
#define  DB    double
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  MOD   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct Circle{
    int x, y, r;
} c[MAXN];

struct vecNode{
    int x, mk, id;
    vecNode(){};
    vecNode(int a, int b, int c){
        x = a, mk = b, id = c;
    }
};

bool operator < (const vecNode &A, const vecNode &B){
    if(A.x != B.x) return A.x < B.x;
    return A.mk < B.mk;
}

struct SNode{
    int ud, id;
    SNode(){}
    SNode(int a, int b){
        ud = a, id = b;
    }
};

int now;

DB sqr(DB x){
    return x * x;
}

bool operator < (const SNode &A, const SNode &B){
    double Ay = (DB) c[A.id].y + A.ud * sqrt(sqr((DB) c[A.id].r) - sqr((DB) now - c[A.id].x) + EPS);
    double By = (DB) c[B.id].y + B.ud * sqrt(sqr((DB) c[B.id].r) - sqr((DB) now - c[B.id].x) + EPS);
    return Ay < By;
}

set <SNode> S;
set <SNode> :: iterator it, it2;
vector <vecNode> vec;

int f[MAXN], n;

int main(){
    //freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) == 1){

        vec.clear(), S.clear();
        for(int i = 1; i <= n; i ++) f[i] = 0;

        for(int i = 1; i <= n; i ++){
            scanf("%d%d%d", &c[i].x, &c[i].y, &c[i].r);
            vec.pb(vecNode(c[i].x + c[i].r, 0, i)), vec.pb(vecNode(c[i].x - c[i].r, 1, i));
            // 0 means right, 1 means left ..
        }
        sort(vec.begin(), vec.end());

        for(int i = 0; i < vec.size(); i ++){
            now = vec[i].x;
            if(vec[i].mk == 1){
                it = S.lower_bound(SNode(1, vec[i].id));
                if(it != S.end() && it != S.begin()){
                    it2 = -- it; it ++;
                    int u = (*it).id, v = (*it2).id;
                    if(u == v) f[vec[i].id] = f[u] + 1;
                    else f[vec[i].id] = max(f[u], f[v]);
                }
                S.insert(SNode(1, vec[i].id)); // 1 means up ..
                S.insert(SNode(-1, vec[i].id)); // -1 means down ..
            }
            else{
                S.erase(SNode(1, vec[i].id));
                S.erase(SNode(-1, vec[i].id));
            }
        }

        int ans = 0;
        for(int i = 1; i <= n; i ++) ans = max(ans, f[i]);
        printf("%d\n", ans + 1);
    }
}
