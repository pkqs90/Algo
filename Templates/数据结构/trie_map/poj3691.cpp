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

const int N = 1e3 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct trie{
    int fail, son[4];
    bool flag;
} tree[N];

int totsz = 0;

int H(char c){
    if(c == 'A') return 0;
    if(c == 'C') return 1;
    if(c == 'G') return 2;
    if(c == 'T') return 3;
}

void insert(char *word){
    int p = 0;
    for(int i = 0, len = strlen(word); i < len; i ++){
        int t = H(word[i]);
        if(!tree[p].son[t])
            tree[p].son[t] = ++ totsz;
        p = tree[p].son[t];
    }
    tree[p].flag = true;
}

void build_trie_map(){
    queue <int> Q;
    for(int i = 0; i < 4; i ++)
        if(tree[0].son[i])
            Q.push(tree[0].son[i]);
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i = 0; i < 4; i ++){
            if(tree[u].son[i]){
                tree[tree[u].son[i]].fail = tree[tree[u].fail].son[i];
                if(tree[tree[tree[u].fail].son[i]].flag)
                    tree[tree[u].son[i]].flag = true;
                Q.push(tree[u].son[i]);
            }
            else
                tree[u].son[i] = tree[tree[u].fail].son[i];
        }
    }
}

int f[N][N];

int gao(char *word){
    for(int i = 0, len = strlen(word); i <= len; i ++)
        for(int j = 0; j <= totsz; j ++)
           f[i][j] = INF;
    f[0][0] = 0;
    for(int i = 0, len = strlen(word); i < len; i ++)
        for(int j = 0; j <= totsz; j ++)
            for(int k = 0; k < 4; k ++)
                if(!tree[tree[j].son[k]].flag)
                    f[i + 1][tree[j].son[k]] = min(f[i + 1][tree[j].son[k]], f[i][j] + (H(word[i]) != k));
    int ret = INF;
    for(int i = 0, len = strlen(word); i <= totsz; i ++)
        ret = min(ret, f[len][i]);
    return (ret == INF) ? -1 : ret;
}

void init_tree(){
    for(int i = 0; i <= totsz; i ++){
        tree[i].fail = tree[i].flag = 0;
        for(int j = 0; j < 4; j ++)
            tree[i].son[j] = 0;
    }
    totsz = 0;
}

int n, cas; char ch[N];

int main(){
//    freopen("in.txt", "r", stdin);
    while(scanf("%d", &n) == 1){
        if(!n) break;
        init_tree();
        while(n --){
            scanf(" %s", ch);
            insert(ch);
        }
        build_trie_map();
        scanf(" %s", ch);
        printf("Case %d: %d\n", ++ cas, gao(ch));
    }
}
