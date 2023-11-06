// cf edu round #157 F
// https://codeforces.com/contest/1895/problem/F

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int Mod = 1e9 + 7;

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

template<class T>
struct Matrix {
    int r, c;
    vector<vector<T>> v;

    Matrix(int r, int c): r(r), c(c) {
        v = vector<vector<T>>(r, vector<T>(c));
    }

    vector<T>& operator[](int i) { return v[i]; }
    const vector<T>& operator[](int i) const { return v[i]; }

    Matrix operator*(const Matrix& b) const {
        assert(c == b.r);
        Matrix res(r, b.c);
        for (int i = 0; i < r; i++)
            for (int j = 0; j < b.c; j++)
                for (int k = 0; k < c; k++) {
                    res[i][j] += v[i][k] * b[k][j];
                }
        return res;
    }

    Matrix pow(ll b) const {
        Matrix res(r, r), A = *this;
        for (int i = 0; i < r; i++) {
            res[i][i] = 1;
        }
        for (; b; A = A * A, b >>= 1) if (b & 1) res = res * A;
        return res;
    }

    void debug() const {
        cout << "row = " << r << ", col = " << c << endl;
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                cout << v[i][j] << ' ';
            }
            cout << endl;
        }
    }
};

int cases, n, x, k;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> cases;
    while (cases --) {
        cin >> n >> x >> k;
        Mint res = power(Mint(2*k+1), n-1);
        res *= (x+k);
        Matrix<Mint> f(x, x);
        for (int i = 0; i < x; ++i) {
            for (int j = 0; j < x; ++j) {
                if (abs(i-j) <= k) {
                    f[i][j] = 1;
                }
            }
        }
        Matrix<Mint> v(x, 1);
        for (int i = 0; i < x; ++i) {
            v[i][0] = 1;
        }
        f = f.pow(n - 1);
        f = f * v;
        for (int i = 0; i < x; ++i) {
            res -= f[i][0];
        }
        cout << res << endl;
    }
}