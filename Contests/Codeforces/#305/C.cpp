#include <bits/stdc++.h>

using namespace std;

const int N = 5e5 + 7;

bool is_prime[N];
vector<int> vec[N], num[N], prime;

void Init() {
    for(int i = 0; i < N; i ++) {
        is_prime[i] = true;
    }
    // Linear sieve
    for(int i = 2 ; i < N; i ++) {
        if(is_prime[i]) prime.push_back(i), vec[i].push_back(i);
        for(int j = 0; j < prime.size() && i * prime[j] < N; j ++) {
            is_prime[i * prime[j]] = false;
            int v = i * prime[j];
            for (int k = 0; k < vec[i].size(); k ++)
                vec[v].push_back(vec[i][k]);
            if(i % prime[j] == 0) break;
            else vec[v].push_back(prime[j]);
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

int n, m, x, a[N], sum[N], vis[N];

int main() {
//    freopen("in.txt", "r", stdin);
    Init();
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i ++) {
        scanf("%d", &a[i]);
    }
    long long tot = 0;
    while (m --) {
        scanf("%d", &x);
        int op;
        if (vis[x]) vis[x] = 0, op = -1;
        else vis[x] = 1, op = 1;
        int val = a[x], res = 0;
        for (int i = 0; i < num[val].size(); i ++) {
            int v = num[val][i];
            if (op > 0) {
                res += sum[abs(v)];
                if (v > 0) sum[v] ++;
                else sum[-v] --;
            } else {
                if (v > 0) sum[v] --;
                else sum[-v] ++;
                res += sum[abs(v)];
            }
        }
        tot += op * res;
        printf("%I64d\n", tot);
    }
}
