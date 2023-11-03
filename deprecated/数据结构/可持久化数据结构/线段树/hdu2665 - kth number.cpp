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
#define  MAXN  100055
#define  MAXM  2005
#define  LL    long long
#define  DB    double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  INF   0x3fffffff
#define  PB    push_back
#define  MP    make_pair

using namespace std;

struct seg{
    int lson, rson, sum;
} tree[MAXN * 20]; // 既然不是线段树的写法, 就不用开 *4 的空间了 ..

int T[MAXN], tot;

int init_tree(int l, int r){
    int root = ++ tot;
    tree[root].sum = 0;
    if(l != r){
        int mid = l + r >> 1;
        tree[root].lson = init_tree(l, mid);
        tree[root].rson = init_tree(mid + 1, r);
    }
    return root;
}

int update(int root, int pos, int l, int r){
    int newroot = ++ tot;
    tree[newroot].sum = tree[root].sum + 1;
    if(l != r){
        int mid = l + r >> 1;
        if(pos <= mid){
            tree[newroot].lson = update(tree[root].lson, pos, l, mid);
            tree[newroot].rson = tree[root].rson;
        }
        else{
            tree[newroot].lson = tree[root].lson;
            tree[newroot].rson = update(tree[root].rson, pos, mid + 1, r);
        }
    }
    return newroot;
}

int query(int lroot, int rroot, int k, int l, int r){
    if(l == r){
        return l;
    }
    int mid = l + r >> 1;
    if(k <= tree[tree[rroot].lson].sum - tree[tree[lroot].lson].sum){
        return query(tree[lroot].lson, tree[rroot].lson, k, l, mid);
    }
    else{
        return query(tree[lroot].rson, tree[rroot].rson,
        k - (tree[tree[rroot].lson].sum - tree[tree[lroot].lson].sum), mid + 1, r);
    }
}

int a[MAXN], n, m, q, l, r, k, t;
vector <int> vec;

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        scanf("%d%d", &n, &q);
        vec.clear(); tot = 0;
        for(int i = 1; i <= n; i ++)
            scanf("%d", &a[i]), vec.PB(a[i]);
        sort(vec.begin(), vec.end());
        for(int i = 1; i <= n; i ++)
            a[i] = lower_bound(vec.begin(), vec.end(), a[i]) - vec.begin() + 1;
        int sz = vec.size();
        T[0] = init_tree(1, sz);
        for(int i = 1; i <= n; i ++)
            T[i] = update(T[i - 1], a[i], 1, sz);
        while(q --){
            scanf("%d%d%d", &l, &r, &k);
            int res = query(T[l - 1], T[r], k, 1, sz);
            printf("%d\n", vec[res - 1]);
        }
    }
}
