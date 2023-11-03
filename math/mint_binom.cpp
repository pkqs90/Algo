// cf #850 Div1 D
// https://codeforces.com/contest/1785/submission/231134123

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

const int N = 20;
const int M = (1 << N) + 1;

int cases, n;

Mint f[21][M], g[21][M];

int two[21];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    two[0] = 1;
    for (int i = 1; i <= N; ++i) {
        two[i] = two[i - 1] * 2;
    }
    f[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        Mint s = f[i - 1][0];
        for (int j = 1; j <= (1 << n); ++j) {
            f[i][j] = s * comb.binom(two[n] - j - two[n - i], two[n - i] - 1) * comb.fac(two[n - i]);
            s += f[i - 1][j];
        }
    }
    Mint s = 0;
    for (int i = 1; i <= (1 << n); ++i) {
        printf("%d\n", (s * two[n]).val());
        s += f[n][i];
    }
}
