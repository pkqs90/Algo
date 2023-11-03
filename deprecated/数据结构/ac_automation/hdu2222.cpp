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

const int N = 1e6 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

struct trie{
    int sum, fail, son[26];
    bool flag;
} tree[N];

int totsz = 0, ans = 0;

void insert(char *word){
    int p = 0;
    for(int i = 0, len = strlen(word); i < len; i ++){
        int t = word[i] - 'a';
        if(!tree[p].son[t])
            tree[p].son[t] = ++ totsz;
        p = tree[p].son[t];
    }
    tree[p].sum ++;
}

void build_auto(){
    queue <int> Q;
    for(int i = 0; i < 26; i ++)
        if(tree[0].son[i])
            Q.push(tree[0].son[i]);
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int i = 0; i < 26; i ++){
            int t = tree[u].son[i];
            if(!t) continue;
            int f = tree[u].fail;
            while(f && !tree[f].son[i])
                f = tree[f].fail;
            tree[t].fail = tree[f].son[i];
            Q.push(t);
        }
    }
}

int query_auto(char *word){
    int p = 0, ret = 0;
    for(int i = 0, len = strlen(word); i < len; i ++){
        int t = word[i] - 'a';
        while(p && !tree[p].son[t])
            p = tree[p].fail;
        p = tree[p].son[t];
        int temp = p;
        while(temp && tree[temp].flag == false){
            ret += tree[temp].sum;
            tree[temp].flag = true;
            temp = tree[temp].fail;
        }
    }
    return ret;
}


void init_tree(){
    for(int i = 0; i <= totsz; i ++){
        tree[i].sum = tree[i].fail = tree[i].flag = 0;
        for(int j = 0; j < 26; j ++)
            tree[i].son[j] = 0;
    }
    ans = totsz = 0;
}

int t, n; char ch[N];

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        init_tree();
        scanf("%d", &n);
        while(n --){
            scanf(" %s", ch);
            insert(ch);
        }
        build_auto();
        scanf(" %s", ch);
        printf("%d\n", query_auto(ch));
    }
}
