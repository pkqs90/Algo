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

const int N = 100055;
const int INF = 0x7fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct seg{
    int l, r; LL mk, mk2, mx, mx2;
    int mid(){
        return l + r >> 1;
    }
} tree[N << 4];

void init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r;
    tree[x].mk = tree[x].mk2 = tree[x].mx = tree[x].mx2 = 0;
    if(l == r) return;
    int mid = l + r >> 1;
    init_tree(l, mid, lc(x));
    init_tree(mid + 1, r, rc(x));
}

inline void update(int x){
    tree[x].mx = max(tree[lc(x)].mx, tree[rc(x)].mx) + tree[x].mk;
    tree[x].mx2 = max(max(tree[lc(x)].mx2, tree[lc(x)].mx + tree[x].mk2),
                      max(tree[rc(x)].mx2, tree[rc(x)].mx + tree[x].mk2));
}

inline void pushdown(int x){
    tree[lc(x)].mk2 = max(tree[lc(x)].mk2, tree[lc(x)].mk + tree[x].mk2);
    tree[rc(x)].mk2 = max(tree[rc(x)].mk2, tree[rc(x)].mk + tree[x].mk2);
    tree[lc(x)].mk += tree[x].mk, tree[rc(x)].mk += tree[x].mk;
    update(lc(x)), update(rc(x));
    tree[x].mk = tree[x].mk2 = 0;
}

inline void insert(int l, int r, int x, int num){
    if(l <= tree[x].l && tree[x].r <= r){
        tree[x].mk += num;
        tree[x].mk2 = max(tree[x].mk2, tree[x].mk);
        update(x);
        return;
    }
    pushdown(x);
    int mid = tree[x].mid();
    if(l <= mid) insert(l, r, lc(x), num);
    if(r > mid) insert(l, r, rc(x), num);
    update(x);
}

inline LL query(int l, int r, int x){
    if(l <= tree[x].l && tree[x].r <= r){
        return tree[x].mx2;
    }
    pushdown(x);
    int mid = tree[x].mid();
    LL mx;
    if(r <= mid) mx = query(l, r, lc(x));
    else if(l > mid) mx = query(l, r, rc(x));
    else mx = max(query(l, r, lc(x)), query(l, r, rc(x)));
    return mx;
}

int n, m, l, r, a[N], pre[N], pos[N * 2];
vector <PII> vec[N];
LL ans[N];

int main(){
    while(scanf("%d", &n) == 1){
        memset(pos, 0, sizeof(pos));
        for(int i = 1; i <= n; i ++){
            scanf("%d", &a[i]);
            pre[i] = pos[a[i] + N];
            pos[a[i] + N] = i;
            vec[i].clear();
        }
        scanf("%d", &m);
        for(int i = 1; i <= m; i ++){
            scanf("%d%d", &l, &r);
            vec[r].PB(MP(l, i));
        }
        init_tree(1, n, 1);
        for(int i = 1; i <= n; i ++){
            insert(pre[i] + 1, i, 1, a[i]);
            for(int j = 0; j < vec[i].size(); j ++){
                ans[vec[i][j].second] = query(vec[i][j].first, i, 1);
            }
        }
        for(int i = 1; i <= m; i ++)
            printf("%lld\n", ans[i]);
    }
}
