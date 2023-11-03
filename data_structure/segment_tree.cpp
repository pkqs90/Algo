// CF #905 Div1 C
// https://codeforces.com/contest/1887/submission/231129375

#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll inf = 1e18;

struct Tag {
    ll add = 0;
    void apply(const Tag &t) {
        add += t.add;
    }
};
struct Info {
    ll min = inf;
    ll max = -inf;
    void apply(const Tag &t) {
        min += t.add;
        max += t.add;
    }
    Info operator+(const Info& v) const {
        return {std::min(this->min, v.min), std::max(this->max, v.max)};
    }
};

template<class Info, class Tag>
struct LazySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    LazySegmentTree() : n(0) {}
    LazySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    void init(const std::vector<Info>& init_) {
        n = init_.size();
        info.assign((n << 2) + 1, Info());
        tag.assign((n << 2) + 1, Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (l == r) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m + 1, r);
            pull(p);
        };
        build(1, 0, n - 1);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        apply(2 * p, tag[p]);
        apply(2 * p + 1, tag[p]);
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (l == r) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x <= m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m + 1, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n - 1, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l > y || r < x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m + 1, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n - 1, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        // cout << p << ' ' << l << ' ' << r << ' ' << x << ' ' << y << endl;
        if (l > y || r < x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m + 1, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n - 1, l, r, v);
    }
    template<class F>
    int findFirst(int p, int l, int r, int x, int y, F pred) {
        if (l > y || r < x || !pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m + 1, r, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findFirst(int l, int r, F pred) {
        return findFirst(1, 0, n - 1, l, r, pred);
    }
    template<class F>
    int findLast(int p, int l, int r, int x, int y, F pred) {
        if (l > y || r < x || !pred(info[p])) {
            return -1;
        }
        if (l == r) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findLast(2 * p + 1, m + 1, r, x, y, pred);
        if (res == -1) {
            res = findLast(2 * p, l, m, x, y, pred);
        }
        return res;
    }
    template<class F>
    int findLast(int l, int r, F pred) {
        return findLast(1, 0, n - 1, l, r, pred);
    }
};

const int N = 5e5 + 7;
const ll Mod = 998244353;
 
int cases, n, m, a[N];

vector<pair<int, int>> vec[N];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> cases;
    while (cases --) {
        cin >> n;
        for (int i = 1; i <= n; ++i) {
            cin >> a[i];
        }
        cin >> m;
        int x, y, v;
        for (int i = 1; i <= n; ++i) {
            vec[i].clear();
        }
        for (int i = 1; i <= m; ++i) {
            cin >> x >> y >> v;
            vec[x].push_back({i, v});
            vec[y+1].push_back({i, -v});
        }
        auto tree = LazySegmentTree<Info, Tag>(m+1, Info{.min=0, .max=0});
        for (int i = 1; i <= n; ++i) {
            for (auto& [tt, v] : vec[i]) {
                tree.rangeApply(tt, m, Tag{.add=v});
            }
            ll mn = tree.rangeQuery(0, m).min;
            cout << a[i] + mn << ' ';
            while (1) {
                int x = tree.findFirst(0, m, [&](const Info& info) -> bool {
                    return info.max > mn;
                });
                if (x == -1) break;
                tree.modify(x, Info{.min = inf, .max = -inf});
            }
        }
        cout << endl;
    }
}
