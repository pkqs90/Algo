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
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

int sum[2 * N];

void Add(int x, int v){
    x = 2 * N - x;
    for(; x < 2 * N; x += lowbit(x))
        sum[x] += v;
}
int Query(int x){
    int ret = 0;
    x = 2 * N - x;
    for(; x; x -= lowbit(x))
        ret += sum[x];
    return ret;
}

struct Node{
    int op, id, l, r;
    Node(){}
    Node(int _op, int _id, int _l, int _r){
        op = _op, id = _id, l = _l, r = _r;
    }
} Q[N];

bool cmp_l(const Node &A, const Node &B){
    if(A.l != B.l) return A.l < B.l;
    return A.r > B.r;
}
bool cmp_id(const Node &A, const Node &B){
    return A.id < B.id;
}

int ans[N], n;

void gao(int l, int r){
    if(l >= r) return;
    int mid = l + r >> 1;
    gao(l, mid);
    sort(Q + l, Q + 1 + r, cmp_l);
    for(int i = l; i <= r; i ++){
        if(Q[i].id <= mid){
            if(Q[i].op == 1) Add(Q[i].r, 1);
            else if(Q[i].op == -1) Add(Q[i].r, -1);
        } else{
            if(Q[i].op == 2) ans[Q[i].id] += Query(Q[i].r);
        }
    }
    for(int i = l; i <= r; i ++){
        if(Q[i].id <= mid){
            if(Q[i].op == 1) Add(Q[i].r, -1);
            else if(Q[i].op == -1) Add(Q[i].r, 1);
        }
    }
    sort(Q + l, Q + 1 + r, cmp_id);
    gao(mid + 1, r);
}

char op; int l, r, id, _l[N], _r[N], qcnt;

vector <int> lsh;

int main(){
    //freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) == 1){

        qcnt = 0;
        lsh.clear();
        memset(ans, 0, sizeof(ans));

        for(int i = 1; i <= n; i ++){
            scanf(" %c", &op);
            if(op == 'D'){
                scanf("%d%d", &l, &r);
                Q[i] = Node(1, i, l, r);
                _l[++ qcnt] = l, _r[qcnt] = r;
                lsh.PB(l), lsh.PB(r);
            } else if(op == 'Q'){
                scanf("%d%d", &l, &r);
                lsh.PB(l), lsh.PB(r);
                Q[i] = Node(2, i, l, r);
            } else{
                scanf("%d", &id);
                Q[i] = Node(-1, i, _l[id], _r[id]);
            }
        }

        sort(lsh.begin(), lsh.end());
        lsh.erase(unique(lsh.begin(), lsh.end()), lsh.end());
        for(int i = 1; i <= n; i ++){
            Q[i].l = lower_bound(lsh.begin(), lsh.end(), Q[i].l) - lsh.begin() + 1;
            Q[i].r = lower_bound(lsh.begin(), lsh.end(), Q[i].r) - lsh.begin() + 1;
            //cout << i << ' ' << Q[i].op << ' ' << Q[i].l << ' ' << Q[i].r << endl;
        }

        gao(1, n);
        for(int i = 1; i <= n; i ++)
            if(Q[i].op == 2)
                printf("%d\n", ans[i]);
    }
}
