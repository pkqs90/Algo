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

const int N = 5005;
const int M = 50005;
const int MOD = 1e9 + 7;
const int INF = 1e9 + 7;
const DB  EPS = 1e-8;

struct Seg{
    int l, r, x, op;
    Seg(){}
    Seg(int _l, int _r, int _x, int _op){
        l = _l, r = _r, x = _x, op = _op;
    }
    bool operator < (const Seg &A) const{
        if(x != A.x) return x < A.x;
        return op > A.op;
    }
};

vector <Seg> seg;
vector <int> lsh;

struct Segtree{
    // cnt means the number of times the segment was covered, len means the length of the covered segment
    // ct means number of lines, cl & cr means the points of the seg has been covered or not
    int l, r, cnt, len, ct;
    bool cl, cr;
    int mid(){
        return l + r >> 1;
    }
} tree[N << 2];

void Init_tree(int l, int r, int x){
    tree[x].l = l, tree[x].r = r;
    tree[x].cnt = tree[x].len = 0;
    tree[x].cl = tree[x].cr = tree[x].ct = 0;
    if(l == r) return;
    int mid = l + r >> 1;
    Init_tree(l, mid, lc(x));
    Init_tree(mid + 1, r, rc(x));
}

void Update(int x){
    if(tree[x].cnt != 0){
        tree[x].cl = tree[x].cr = 1, tree[x].ct = 2;
        tree[x].len = lsh[tree[x].r + 1] - lsh[tree[x].l];
    } else if(tree[x].l != tree[x].r){
        tree[x].len = tree[lc(x)].len + tree[rc(x)].len;
        tree[x].cl = tree[lc(x)].cl;
        tree[x].cr = tree[rc(x)].cr;
        tree[x].ct = tree[lc(x)].ct + tree[rc(x)].ct;
        if(tree[lc(x)].cr && tree[rc(x)].cl) tree[x].ct -= 2;
    } else{
        tree[x].cl = tree[x].cr = tree[x].ct = 0;
        tree[x].len = 0;
    }
}

void Gao(int l, int r, int op, int x){
    if(l <= tree[x].l && tree[x].r <= r){
        tree[x].cnt += op;
        Update(x);
        return;
    }
    int mid = tree[x].mid();
    if(l <= mid) Gao(l, r, op, lc(x));
    if(r > mid) Gao(l, r, op, rc(x));
    Update(x);
}

int n, cas; int a, b, c, d;

int main(){
//    freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) == 1){
        if(!n) break;
        lsh.clear();
        seg.clear();
        for(int i = 1; i <= n; i ++){
            scanf("%d%d%d%d", &a, &b, &c, &d);
            seg.PB(Seg(b, d, a, 1));
            seg.PB(Seg(b, d, c, -1));
            lsh.PB(b), lsh.PB(d);
        }
        sort(lsh.begin(), lsh.end());
        lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
        for(int i = 0; i < seg.size(); i ++){
            seg[i].l = lower_bound(lsh.begin(), lsh.end(), seg[i].l) - lsh.begin();
            seg[i].r = lower_bound(lsh.begin(), lsh.end(), seg[i].r) - lsh.begin() - 1;
        }
//        for(int i = 0; i < lsh.size(); i ++)
//            cout << lsh[i] << ' '; cout << endl;
        sort(seg.begin(), seg.end());
        Init_tree(0, lsh.size() - 1, 1);
        int tot = 0, pre = 0;
        for(int i = 0; i < seg.size(); i ++){
            Gao(seg[i].l, seg[i].r, seg[i].op, 1);
            if(i != seg.size() - 1) tot += tree[1].ct * (seg[i + 1].x - seg[i].x);
            tot += abs(tree[1].len - pre);
            pre = tree[1].len;
//            cout << seg[i].x << ' ' << seg[i + 1].x << ' ' << tree[1].len << ' ' << tree[1].ct << ' ' << seg[i].l << ' ' << seg[i].r << ' ' <<seg[i].op << endl;
        }
        printf("%d\n", tot);
    }
}
