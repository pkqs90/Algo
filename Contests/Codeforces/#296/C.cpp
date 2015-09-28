// Euler circuit.

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
#define  LL    long long

using namespace std;

const int N = 5e5 + 7;
const int Inf = 0x3fffffff;
const int Mod = 1e9 + 7;
const double eps = 1e-8;

vector<pair<int, int> > res;
vector<int> vec, euler;
multiset<int> e[N];

void Gao(int u) {
    while (!e[u].empty()) {
        int v = *e[u].begin();
        e[u].erase(e[u].begin());
        e[v].erase(e[v].find(u));
        Gao(v);
    }
    euler.push_back(u);
}

int n, m, u, v, num;
int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++) {
        scanf("%d%d", &u, &v);
        e[u].insert(v);
        e[v].insert(u);
        num ++;
    }
    for (int i = 1; i <= n; i ++) {
        if (e[i].size() & 1) {
            vec.push_back(i);
        }
    }
    for (int i = 0; i < vec.size(); i += 2) {
        e[vec[i]].insert(vec[i + 1]);
        e[vec[i + 1]].insert(vec[i]);
        num ++;
    }
    if (num & 1) {
        e[1].insert(1);
        e[1].insert(1);
    }
    Gao(1);
    //for (int i = 0; i < euler.size(); i ++) {
    //    cout << euler[i] << ' ';
    //} puts("");
    for (int i = 1; i < euler.size() - 1; i += 2) {
        res.push_back(make_pair(euler[i], euler[i - 1]));
        res.push_back(make_pair(euler[i], euler[i + 1]));
    }
    printf("%d\n", (int)res.size());
    for (int i = 0; i < res.size(); i ++) {
        printf("%d %d\n", res[i].first, res[i].second);
    }
}
