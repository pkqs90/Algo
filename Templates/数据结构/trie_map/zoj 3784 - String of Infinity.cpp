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
#define  MAXN  111111
#define  MAXM  888888
#define  LL    long long
#define  ULL   unsigned long long
#define  INF   0x7fffffff
#define  pb    push_back
#define  mp    make_pair
#define  mod   1000000007
#define  lowbit(x) (x&(-x))

using namespace std;

struct tree{
    int son[27], fail;
    bool mk;
} tree[MAXN];

int n, m, sz;

void insert(char *word){
     int p = 0;
     for(int i = 0, l = strlen(word); i < l; i ++){
        int tmp = word[i] - 'a' + 1;
        if(!tree[p].son[tmp])
            tree[p].son[tmp] = ++ sz;
        p = tree[p].son[tmp];
     }
     tree[p].mk = true;
}

void Build_Trie_Map(){
     queue <int> Q;
     for(int i = 1; i <= m; i ++)
        if(tree[0].son[i])
           Q.push(tree[0].son[i]);
     while(!Q.empty()){
        int f = Q.front(); Q.pop();
        for(int i = 1; i <= m; i ++){
           if(tree[f].son[i]){
              tree[tree[f].son[i]].fail = tree[tree[f].fail].son[i];
              if(tree[tree[tree[f].fail].son[i]].mk)
                 tree[tree[f].son[i]].mk = true;
              Q.push(tree[f].son[i]);
           }
           else
              tree[f].son[i] = tree[tree[f].fail].son[i];
        }
    }
}


////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

int first[MAXN], ecnt, deg[MAXN];

struct edge{
    int v, next;
}e[MAXN * 26];

void addedge(int u, int v){
    //cout << u << ' ' << v << endl;
    deg[u] ++, deg[v] ++;
    e[++ ecnt].next = first[u], first[u] = ecnt, e[ecnt].v = v;
}

int stk[MAXN], dfn[MAXN], low[MAXN], id[MAXN], cnt, idx, num;

bool instk[MAXN];

vector <int> vec[MAXN];

void dfs(int u){
    stk[++ cnt] = u;
    dfn[u] = low[u] = ++ idx;
    instk[u] = true;
    for(int i = first[u]; i != -1; i = e[i].next){
        int v = e[i].v;
        if(!dfn[v])
            dfs(v), low[u] = min(low[u], low[v]);
        else if(instk[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]){
        num ++;
        while(1){
            vec[num].pb(stk[cnt]);
            id[stk[cnt]] = num;
            instk[stk[cnt]] = false;
            cnt --;
            if(stk[cnt + 1] == u) break;
        }
    }
}

void gao(){
    cnt = idx = 0;
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(id, 0, sizeof(id));
    for(int i = 0; i <= sz; i ++)
        if(!dfn[i]) dfs(i);
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

bool vis[MAXN];

bool check(){
    memset(vis, 0, sizeof(vis));
    queue <int> Q;
    Q.push(0), vis[0] = true;
    while(!Q.empty()){
        int u = Q.front(); Q.pop();
        for(int k = 0, i = first[u]; i != -1; i = e[i].next){
            int v = e[i].v;
            if(id[v] == id[u]) k ++;
            if(k == 2) return true;
            if(vis[v]) continue;
            Q.push(v), vis[v] = true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////

void init(){
    for(int i = 0; i <= sz; i ++){
        for(int j = 1; j <= m; j ++)
            tree[i].son[j] = 0;
        tree[i].fail = tree[i].mk = 0;
    }
    for(int i = 1; i <= num; i ++) vec[i].clear();
    num = 0;
    sz = 0;
    ecnt = -1;
    memset(first, -1, sizeof(first));
    memset(deg, 0, sizeof(deg));
}

int t;
char ch[1005];

int main(){
    //freopen("in.txt", "r", stdin);
    cin >> t;
    while(t --){
        scanf("%d%d", &n, &m);
        init();
        for(int i = 1; i <= n; i ++){
            scanf(" %s", &ch);
            insert(ch);
        }
        Build_Trie_Map();
        for(int i = 0; i <= sz; i ++){
            if(tree[i].mk == true) continue;
            for(int j = 1; j <= m; j ++)
                if(tree[tree[i].son[j]].mk == false)
                    addedge(i, tree[i].son[j]);
        }
        gao();
        /*for(int i = 1; i <= num; i ++){
            cout << i << " : ";
            for(int j = 0; j < vec[i].size(); j ++)
                cout << vec[i][j] << ' ';
            cout << endl;
        }*/
        if(check()) printf("Yes\n"); else printf("No\n");
    }
}
