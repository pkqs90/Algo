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
#define  MAXN  333333
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffffffffffffll
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct splay{
    int l, r, f, sz, num[2], gcd[2];
    void init(){
        l = r = f = sz = num[0] = num[1] = gcd[0] = gcd[1] = 0;
    }
}tree[MAXN];

int root, sz;

void debug(){
    cout << "Root : " << root << endl;
    for(int i = 0; i <= sz; i ++){
        cout << i << ' ' << tree[i].l << ' ' << tree[i].r << ' ' << tree[i].sz << ' ' << tree[i].num[0] << ' ' << tree[i].num[1] << ' ' << tree[i].gcd[0] << ' ' << tree[i].gcd[1] << endl;
    }
}

int gcd(int x, int y){
    return !y ? x : gcd(y, x % y);
}

void update(int x){
    tree[x].gcd[0] = gcd(gcd(tree[x].num[0], tree[tree[x].l].gcd[0]), tree[tree[x].r].gcd[0]);
    tree[x].gcd[1] = gcd(gcd(tree[x].num[1], tree[tree[x].l].gcd[1]), tree[tree[x].r].gcd[1]);
    tree[x].sz = 1 + tree[tree[x].l].sz + tree[tree[x].r].sz;
}

void zig(int x){
     int y = tree[x].f, z = tree[y].f, A = tree[x].r;
     if(tree[z].l == y) tree[z].l=x;
     else tree[z].r = x;
     tree[x].f = z, tree[y].f = x;
     tree[y].l = A, tree[x].r = y;
     if(A) tree[A].f = y;
     update(y);
}
void zag(int x){
     int y = tree[x].f, z = tree[y].f, A = tree[x].l;
     if(tree[z].l == y) tree[z].l = x;
     else tree[z].r = x;
     tree[x].f = z, tree[y].f = x;
     tree[y].r = A, tree[x].l = y;
     if(A) tree[A].f = y;
     update(y);
}
void splay(int x){
     int y = tree[x].f, z = tree[y].f;
     while(y){
        if(!z){
           if(x == tree[y].l) zig(x);
           else zag(x);
           break;
        }
        if(x == tree[y].l && y == tree[z].l) zig(y), zig(x);
        else if(x == tree[y].l && y == tree[z].r) zig(x), zag(x);
        else if(x == tree[y].r && y == tree[z].r) zag(y), zag(x);
        else zag(x), zig(x);
        y = tree[x].f, z = tree[y].f;
     }
     update(x);
     root = x;
}

int find(int M){
    int x = root;
    while(1){
        if(tree[tree[x].l].sz == M - 1) break;
        if(tree[tree[x].l].sz < M){
            M -= (tree[tree[x].l].sz + 1), x = tree[x].r;
        }
        else x = tree[x].l;
     }
     return x;
}

void insert(int x, int num, int sta){
    x = find(x), splay(x);
    sz ++;
    tree[sz].init();
    tree[sz].sz = 1, tree[sz].gcd[sta] = tree[sz].num[sta] = num;
    if(tree[x].r == 0){
        tree[sz].f = x, tree[x].r = sz;
    }
    else{
        x = tree[x].r;
        while(tree[x].l) x = tree[x].l;
        tree[sz].f = x, tree[x].l = sz;
    }
    splay(sz);
}

void erase(int x){
    x = find(x), splay(x);
    if(!tree[x].l){
        tree[tree[x].r].f = 0;
        root = tree[x].r;
    }
    else{
        int y = tree[x].l;
        tree[y].f = 0;
        while(tree[y].r) y = tree[y].r;
        splay(y);
        tree[y].r = tree[x].r;
        if(tree[x].r) tree[tree[x].r].f = y;
        update(y);
    }
    tree[x].init();
}

void gao(int x, int num){
    x = find(x), splay(x);
    if(num == -1){
        tree[x].gcd[0] = gcd(gcd(tree[x].num[1], tree[tree[x].l].gcd[0]), tree[tree[x].r].gcd[0]);
        tree[x].gcd[1] = gcd(gcd(tree[x].num[0], tree[tree[x].l].gcd[1]), tree[tree[x].r].gcd[1]);
        swap(tree[x].num[1], tree[x].num[0]);
    }
    else{
        int sta;
        if(tree[x].num[0] != 0) sta = 0; else sta = 1;
        tree[x].num[sta] = num;
        tree[x].gcd[sta] = gcd(gcd(tree[x].num[sta], tree[tree[x].l].gcd[sta]), tree[tree[x].r].gcd[sta]);
    }
}

int query(int x0, int x1, int sta){
    x0 = find(x0), splay(x0);
    tree[tree[x0].r].f = 0;
    x1 = find(x1), splay(x1);
    root = x0;
    tree[x1].f = x0, tree[x0].r = x1;
    update(x0);
    return tree[tree[x1].l].gcd[sta];
}

int n, num[MAXN], sta[MAXN];

int build(int l, int r, int f){
    if(l > r) return 0;
    int x = l + r >> 1;
    tree[x].init();
    if(f == 0) root = x;
    tree[x].f = f;
    if(x >= 2 && x <= n + 1)
        tree[x].num[sta[x - 1]] = tree[x].gcd[sta[x - 1]] = num[x - 1];
    tree[x].l = build(l, x - 1, x);
    tree[x].r = build(x + 1, r, x);
    update(x);
    return x;
}

void init(){
    for(int i = 1; i <= n; i ++)
        scanf("%d%d", &num[i], &sta[i]);
    build(1, n + 2, 0);
    sz = n + 2;
    //debug();
}

char ch;

int x, l, r, q, pos, y;

int main(){
    while(scanf("%d%d", &n, &q) == 2){
        init();
        while(q --){
            scanf(" %c", &ch);
            if(ch == 'Q'){
                scanf("%d%d%d", &l, &r, &x);
                r += 2;
                int k = query(l, r, x);
                printf("%d\n", k == 0 ? -1 : k);
            }
            else if(ch == 'I'){
                scanf("%d%d%d", &pos, &x, &y);
                insert(pos + 1, x, y);
            }
            else if(ch == 'D'){
                scanf("%d", &x);
                erase(x + 1);
            }
            else if(ch == 'R'){
                scanf("%d", &x);
                gao(x + 1, -1);
            }
            else if(ch == 'M'){
                scanf("%d%d", &x, &y);
                gao(x + 1, y);
            }
        }
    }
}
