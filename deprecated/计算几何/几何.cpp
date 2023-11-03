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

const DB  EPS = 1e-8;
const int INF = 0x3fffffff;

inline int sgn(DB x) {
    return x < -EPS ? -1 : x < EPS ? 0 : 1;
}

struct Point {
    DB x, y;
    Point() {}
    Point(DB _x, DB _y) {
        x = _x, y = _y;
    }
    inline bool operator == (const Point &A) const {
        return (sgn(x - A.x) == 0 && sgn(y - A.y) == 0);
    }
    inline bool operator < (const Point A) const {
        if(sgn(x - A.x) != 0) return sgn(x - A.x) < 0;
        return sgn(y - A.y) < 0;
    }
    inline Point operator + (const Point &A) const {
        return Point(x + A.x, y + A.y);
    }
    inline Point operator - (const Point &A) const {
        return Point(x - A.x, y - A.y);
    }
    inline Point operator * (const DB &A) const {
        return Point(x * A, y * A);
    }
    inline Point operator / (const DB &A) const {
        return Point(x / A, y / A);
    }
    inline DB operator * (const Point &A) const {
        return x * A.y - y * A.x;
    }
    inline DB operator & (const Point &A) const {
        return x * A.x + y * A.y;
    }
    inline void transXY(DB ceta) {
        DB tx = x, ty = y;
        x = tx * cos(ceta) - ty * sin(ceta);
        y = tx * sin(ceta) + ty * cos(ceta);
    }
};

inline DB Dist(Point A, Point B) {
    return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
}

inline DB Angle(Point A, Point B) {
    return atan2(B.y - A.y, B.x - A.x);
}

inline bool IsPointOnSegment(Point p, Point a1, Point a2){
    return sgn((a1 - p) * (a2 - p)) == 0 && sgn((a1 - p) & (a2 - p)) < 0;
}

inline int IsPointInPolygon(Point p, Point poly[], int n){
    int wn = 0;
    for(int i = 0; i < n; i ++){
        if(IsPointOnSegment(p, poly[i], poly[(i + 1) % n])) return -1; // on the segment
        int k = sgn((poly[(i + 1) % n] - poly[i]) * (p - poly[i]));
        int d1 = sgn(poly[i].y - p.y);
        int d2 = sgn(poly[(i + 1) % n].y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn ++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn --;
    }
    if(wn != 0) return 1; // inside ..
    return 0; // outside
}


int ConvexHull(vector <Point> p, Point *ch){
    sort(p.begin(), p.end());
    int m = 0;
    for(int i = 0; i < p.size(); i ++){
        while(m > 1 && (ch[m - 1] - ch[m - 2]) * (p[i] - ch[m - 2]) <= 0) m --; // Must be <= , so that there are no 3 points 1 line
        ch[m ++] = p[i];
    }
    int k = m;
    for(int i = p.size() - 2; i >= 0; i --){
        while(m > k && (ch[m - 1] - ch[m - 2]) * (p[i] - ch[m - 2]) <= 0) m --;
        ch[m ++] = p[i];
    }
    if(p.size() > 1) m --;
    return m;
}

struct Line {
    Point st, ed, ve;
    DB k;
    Line() {}
    Line(Point _st, Point _ed) {
        st = _st, ed = _ed;
        k = atan2(ed.y - st.y, ed.x - st.x);
        ve = st - ed;
        ve = ve / sqrt(ve.x * ve.x + ve.y * ve.y);
    }
    inline Point point(DB len) {
        return st + (ve * len);
    }
};

inline Point GetLineProjection(Point P, Line L) {
    return L.st + L.ve * (L.ve & (P - L.st) / (L.ve & L.ve));
}

struct Circle {
    Point c; DB r;
    Circle() {}
    Circle(Point _c, DB _r) {
        c = _c, r = _r;
    }
    inline Point point(DB ceta) {
        return Point(c.x + cos(ceta) * r, c.y + sin(ceta) * r);
    }
};

// Intersection between circles .. return the state of intersecting ..
inline int GetCircleCircleIntersection(Circle C1, Circle C2, vector <Point> &sol) {
    DB d = Dist(C1.c, C2.c);
    if(sgn(d) == 0) {
        if(sgn(C1.r - C2.r) == 0) return -1; // overlap ..
        return 0;
    }
    if(sgn(C1.r + C2.r - d) < 0) return 0;
    if(sgn(fabs(C1.r - C2.r) - d) > 0) return 0;
    DB a = Angle(C1.c, C2.c);
    DB da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));
    Point p1 = C1.point(a - da), p2 = C1.point(a + da);
    if(p1 == p2) {
        sol.PB(p1);
        return 1;
    } else {
        sol.PB(p1), sol.PB(p2);
        return 2;
    }
}

// Intersection between line ans circle .. return the state of intersecting .. using analytic geometry
inline int GetLineCircleIntersection(Line L, Circle C, vector <Point> &sol) {
    DB a = L.ve.x, b = L.st.x - C.c.x, c = L.ve.y, d = L.st.y - C.c.y;
    DB e = a * a + c * c, f = 2 * (a * b + c * d), g = b * b + d * d - C.r * C.r;
    DB delta = f * f - 4 * e * g;
    if(sgn(delta) < 0) return 0;
    else if(sgn(delta) == 0) {
        DB t1 = -f / (2 * e);
        sol.PB(L.point(t1));
        return 1;
    } else {
        DB t1 = (-f - sqrt(delta)) / (2 * e);
        DB t2 = (-f + sqrt(delta)) / (2 * e);
        sol.PB(L.point(t1)), sol.PB(L.point(t2));
        return 2;
    }
}
