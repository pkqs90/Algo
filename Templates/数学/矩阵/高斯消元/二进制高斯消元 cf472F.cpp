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

const int N = 1e4 + 7;
const int INF = 0x7fffffff;
const int MOD = 1e9 + 7;
const DB  EPS = 1e-8;

void Debug(int a[], int n){
    for(int i = 1; i <= n; i ++){
        for(int j = 30; j >= 0; j --)
            printf("%d", a[i] >> j & 1);
        puts("");
    }
    puts("");
}

void Gao(int a[], int n, vector <PII> &vec){
    int r = 1;
    for(int i = 30; i >= 0; i --){
        if((a[r] >> i & 1) == 0){
            int pos = -1;
            for(int j = r; j <= n; j ++)
                if(a[j] >> i & 1){
                    pos = j; break;
                }
            if(pos == -1) continue;
            swap(a[r], a[pos]);
            vec.PB(MP(r, pos));
            vec.PB(MP(pos, r));
            vec.PB(MP(r, pos));
        }
        for(int j = 1; j <= n; j ++)
            if((a[j] >> i & 1) && j != r){
                a[j] ^= a[r];
                vec.PB(MP(j, r));
            }
        pos[r] = i;
        r ++;
    }
}

int Lcp(int a, int b){
    int tot = 0;
    for(int i = 30; i >= 0; i --){
        if((a >> i & 1) != (b >> i & 1))
            break;
        tot ++;
    }
    return tot;
}

bool Check(int a[], int b[], int n, vector <PII> &vec){
    int r = 1;
    for(int i = 1; i <= 30; i ++){
        if(a[i] == b[i]) continue;
        for(int j = i; j <= 30; j ++){
            if(Lcp(a[i] ^ a[j], b[i]) > Lcp(a[i], b[i]))
                a[i] ^= a[j], vec.PB(MP(i, j));
        }
        if(a[i] != b[i]) return false;
    }
    return true;
}

int n, a[N], b[N];

vector <PII> vec1, vec2;

int main(){
//    freopen("in.txt", "r", stdin);

    cin >> n;
    for(int i = 1; i <= n; i ++) scanf("%d", &a[i]);
    for(int i = 1; i <= n; i ++) scanf("%d", &b[i]);

    vector <PII> vec1, vec2;

    Gao(a, n, vec1);
    Gao(b, n, vec2);

//    Debug(a, n), Debug(b, n);

    if(!Check(a, b, n, vec1)){
        puts("-1");
    } else{
//        cout << "~";
        for(int i = vec2.size() - 1; i >= 0; i --)
            vec1.PB(vec2[i]);
        printf("%d\n", vec1.size());
        for(int i = 0; i < vec1.size(); i ++)
            printf("%d %d\n", vec1[i].first, vec1[i].second);
    }
//    Debug(a, n), Debug(b, n);
}
