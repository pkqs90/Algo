// https://codeforces.com/contest/1830/submission/207632203

#include <bits/stdc++.h>
using int64 = long long;
const int N = 200005;
const int Q = 998244353;

class Combination {
 public:
  int n;
  std::vector<int> inv, P, I;
  Combination(int n = 1) : n(n), inv{0, 1}, P{1, 1}, I{1, 1} {};
  int binom(int a, int b) {
    if (a < 0 || b < 0 || b > a) {
      return 0;
    }
    process(a);
    return 1LL * P[a] * I[b] % Q * I[a - b] % Q;
  }

 private:
  void process(int m) {
    if (m <= n) {
      return;
    }
    inv.resize(m + 1);
    I.resize(m + 1);
    P.resize(m + 1);
    for (int i = n + 1; i <= m; ++i) {
      inv[i] = 1LL * (Q - Q / i) * inv[Q % i] % Q;
    }
    for (int i = n + 1; i <= m; ++i) {
      P[i] = 1LL * P[i - 1] * i % Q;
      I[i] = 1LL * I[i - 1] * inv[i] % Q;
    }
    n = m;
  }
} comb;

int inverse(int x) {
  return x == 1 ? 1 : 1LL * (Q - Q / x) * inverse(Q % x) % Q;
}

void work() {
  int n, m;
  std::cin >> n >> m;
  std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
  std::vector<int64> a(n + 1);
  for (int i = 0 ; i < m ; ++ i) {
    int l, r;
    std::cin >> l >> r;
    int64 x = rng();
    a[l - 1] ^= x;
    a[r] ^= x;
  }
  for (int i = 0 ; i < n ; ++ i) {
    a[i + 1] ^= a[i];
  }
  std::unordered_map<int64, int> ok;
  for (int i = 0 ; i < n ; ++ i) {
    ++ ok[a[i]];
  }
  int res = 1;
  for (auto &[v, k] : ok) {
    if (k % 2 == 1) {
      res = 0;
    } else {
      // Catalan
      res = 1LL * res * comb.binom(k, k / 2) % Q * inverse(k / 2 + 1) % Q;
    }
  }
  printf("%d\n", res);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int T = 1;
  std::cin >> T;
  while (T--) {
    work();
  }
  return 0;
}