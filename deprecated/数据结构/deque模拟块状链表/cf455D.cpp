#pragma  comment(linker, "/STACK:36777216")
#include <map>
#include <set>
#include <cmath>
#include <ctime>
#include <deque>
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
#define  DB    long double
#define  ULL   unsigned long long
#define  PII   pair<int, int>
#define  PLL   pair<LL, LL>
#define  PB    push_back
#define  MP    make_pair

using namespace std;

const int N = 1e5 + 7;
const int INF = 0x3fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

deque <int> Q[355];
int s[355][N];

int n, q, x, l, r, op, ans;

void gao(int &y){
    y = (y + ans - 1) % n + 1;
}

int main(){
//    freopen("in.txt", "r", stdin);
    cin >> n;
    int Limit = sqrt(n + 0.5);
    for(int i = 0; i < n; i ++){
        scanf("%d", &x);
        Q[i / Limit].push_back(x);
        s[i / Limit][x] ++;
    }
    cin >> q;
    while(q --){
        scanf("%d", &op);
        if(op == 1){
            scanf("%d%d", &l, &r);
            gao(l), gao(r);
            l --, r --;
            if(l > r) swap(l, r);
            int ll = l / Limit, rr = r / Limit;
            if(ll == rr){
                int t = Q[rr][r % Limit];
                Q[rr].erase(Q[rr].begin() + (r % Limit));
                Q[ll].insert(Q[ll].begin() + (l % Limit), t);
            } else{
                for(int i = ll; i < rr; i ++){
                    int t = Q[i].back(); Q[i].pop_back();
                    Q[i + 1].push_front(t);
                    s[i][t] --, s[i + 1][t] ++;
                }
                int t = Q[rr][1 + r % Limit];
                Q[rr].erase(Q[rr].begin() + (1 + r % Limit)); s[rr][t] --;
                Q[ll].insert(Q[ll].begin() + (l % Limit), t); s[ll][t] ++;
            }
        } else{
            scanf("%d%d%d", &l, &r, &x);
            gao(l), gao(r), gao(x); ans = 0;
            l --, r --;
            if(l > r) swap(l, r);
            int ll = l / Limit, rr = r / Limit;
            if(ll == rr){
                for(int i = l % Limit, len = r % Limit; i <= len; i ++){
                    ans += (Q[ll][i] == x);
                }
            } else{
                for(int i = ll + 1; i < rr; i ++) ans += s[i][x];
                for(int i = l % Limit; i < Limit; i ++) ans += (Q[ll][i] == x);
                for(int i = 0, len = r % Limit; i <= len; i ++) ans += (Q[rr][i] == x);
            }
            printf("%d\n", ans);
        }
    }
}
