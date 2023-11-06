// Atcoder ABC 327 G
// https://atcoder.jp/contests/abc327/tasks/abc327_g
// i nodes, j edges:
//   g[i][j] = 0/1 coloring nodes then count bipartite graph
//   h[i][j] = 0/1 coloring nodes then count bipartite graph that is connected
//   f[i][j] = count bipartite graph

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int Mod = 998244353;

template<class T>
T power(T a, ll b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
struct Mint {
    int x;
    Mint(int x = 0) : x(norm(x)) {}
    Mint(ll x) : x(norm(x % Mod)) {}
    int norm(int x) const {
        if (x < 0) {
            x += Mod;
        }
        if (x >= Mod) {
            x -= Mod;
        }
        return x;
    }
    int val() const {
        return x;
    }
    Mint operator-() const {
        return Mint(norm(Mod - x));
    }
    Mint inv() const {
        assert(x != 0);
        return power(*this, Mod - 2);
    }
    Mint &operator*=(const Mint &rhs) {
        x = ll(x) * rhs.x % Mod;
        return *this;
    }
    Mint &operator+=(const Mint &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Mint &operator-=(const Mint &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Mint &operator/=(const Mint &rhs) {
        return *this *= rhs.inv();
    }
    friend Mint operator*(const Mint &lhs, const Mint &rhs) {
        Mint res = lhs;
        res *= rhs;
        return res;
    }
    friend Mint operator+(const Mint &lhs, const Mint &rhs) {
        Mint res = lhs;
        res += rhs;
        return res;
    }
    friend Mint operator-(const Mint &lhs, const Mint &rhs) {
        Mint res = lhs;
        res -= rhs;
        return res;
    }
    friend Mint operator/(const Mint &lhs, const Mint &rhs) {
        Mint res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Mint &a) {
        ll v;
        is >> v;
        a = Mint(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Mint &a) {
        return os << a.val();
    }
};

struct Comb {
    int n;
    std::vector<Mint> _fac;
    std::vector<Mint> _invfac;
    std::vector<Mint> _inv;
    
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(int n) : Comb() {
        init(n);
    }
    
    void init(int m) {
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    
    Mint fac(int m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Mint invfac(int m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Mint inv(int m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Mint binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
} comb;

const int N = 31;
const int NN = N * N;

Mint f[N][NN], g[N][NN], h[N][NN];

int n, m;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> m;

    for (int i = 0; i <= n; ++i) {
        int y = i / 2 * (i + 1) / 2;
        for (int j = 0; j <= y; ++j) {
            for (int x = 0; x <= i; x ++) {
                g[i][j] += comb.binom(i, x) * comb.binom(x * (i-x), j);
            }
        }
    }

    // cerr << "#" << endl;

    for (int i = 0; i <= n; ++i) {
        int y = i / 2 * (i + 1) / 2;
        for (int j = 0; j <= y; ++j) {
            h[i][j] = g[i][j];
            for (int x = 1; x < i; ++x) {
                for (int j2 = 0; j2 <= y; ++j2) {
                    if (i) {
                        h[i][j] -= comb.binom(i-1, x-1) * h[x][j2] * g[i-x][j-j2];
                    }
                }
            }
        }
    }

    for (int i = 0; i <= n; ++i) {
        int y = i / 2 * (i + 1) / 2;
        for (int j = 0; j <= y; ++j) {
            f[i][j] = h[i][j] / 2;
            for (int x = 1; x < i; ++x) {
                for (int j2 = 0; j2 <= y; ++j2) {
                    if (i) {
                        f[i][j] += comb.binom(i-1, x-1) * h[x][j2] / 2 * f[i-x][j-j2];
                    }
                }
            }
        }
    }

    int tot = (n / 2) * ((n + 1) / 2);
    Mint res = 0;
    for (int i = 1; i <= tot; ++i) {
        // 2nd Stirling Number.
        auto calc = [&](int m, int x) -> Mint {
            Mint ret = 0, cc = 1;
            for (int i = 0; i <= x; ++i) {
                ret += cc * comb.binom(x, i) * power(Mint(x-i), m);
                cc *= -1;
            }
            return ret;
        };
        // cout << i << ' ' << f[n][i] << ' ' << calc(m, i) << ' ' << tot << ' ' << res << endl;
        res += f[n][i] * calc(m, i);
    }
    // cout << power(Mint(2), m) << endl;
    res *= power(Mint(2), m);

    // for (int i = 1; i <= 5; ++i) {
    //     for (int j = 0; j <= 10; ++j) {
    //         cout << i << ' '<< j << ' ' << g[i][j] << ' ' << h[i][j] << ' ' << f[i][j] << endl;
    //     }
    // }

    cout << res << endl;
}