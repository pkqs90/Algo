// 这是一道傻逼题。然而我是活傻逼，并不能做出来。
// 最开始的想法是用主席树维护历史信息然后最后统计。
// 这么做空间会爆出屎。。。。。。。写之前不计算一下复杂度都是耍流氓。
// 一个更显然的做法是边 Dfs 边统计，进节点出节点的时候算两次，然后就完了。
// 开个毛的主席树啊。。。

#include <bits/stdc++.h>

using namespace std;

const int N = 1e5 + 7;

struct Edge{
    int v, next;
} e[N << 1];

int first[N], ecnt;

void AddEdge(int u, int v){
    e[++ ecnt].v = v, e[ecnt].next = first[u], first[u] = ecnt;
}

bool is_prime[N];
vector<int> vec[N], num[N];

void Init() {
    for(int i = 0; i < N; i ++) {
        is_prime[i] = true;
    }
    for(int i = 2; i < N; i ++) {
        if (!is_prime[i]) continue;
        for (int j = i; j < N; j += i) {
            vec[j].push_back(i);
            is_prime[j] = 0;
        }
    }
    for (int i = 1; i < N; i ++) {
        int sz = vec[i].size();
        for (int j = 0; j < (1 << sz); j ++) {
            int res = 1, cnt = 0;
            for (int k = 0; k < sz; k ++) {
                if (j >> k & 1)
                    res *= vec[i][k], cnt ++;
            }
            if (cnt & 1) res = -res;
            num[i].push_back(res);
        }
    }
}

int val[N], res[N], sum[N];
void Dfs(int u, int pre) {
    int value = val[u];
    for (int i = 0; i < num[value].size(); i ++) {
        int v = num[value][i];
        if (v > 0) sum[v] ++;
        else sum[-v] --;
    }
    int pr = 0, cur = 0;
    for (int i = 0; i < num[value].size(); i ++) {
        int v = num[value][i];
        pr += sum[abs(v)];
    }
    for (int i = first[u]; i != -1; i = e[i].next) {
        int v = e[i].v;
        if (v == pre) {
            continue;
        }
        Dfs(v, u);
    }
    for (int i = 0; i < num[value].size(); i ++) {
        int v = num[value][i];
        cur += sum[abs(v)];
    }
    res[u] = cur - pr;
}

int n, u, v, cas;
int main() {
//    freopen("in.txt", "r", stdin);
    Init();
    while (scanf("%d", &n) == 1) {
        memset(first, -1, sizeof(first));
        ecnt = -1;
        memset(res, 0, sizeof(res));
        memset(sum, 0, sizeof(sum));
        for (int i = 1; i < n; i ++) {
            scanf("%d%d", &u, &v);
            AddEdge(u, v);
            AddEdge(v, u);
        }
        for (int i = 1; i <= n; i ++) {
            scanf("%d", &val[i]);
        }
        Dfs(1, 0);
        printf("Case #%d:", ++ cas);
        for (int i = 1; i <= n; i ++) {
            if (val[i] == 1) res[i] ++;
            printf(" %d", res[i]);
        }
        puts("");
    }
}
