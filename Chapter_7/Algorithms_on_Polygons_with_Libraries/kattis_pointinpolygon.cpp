/**Kattis - pointinpolygon
 * What supposed to be easy turned out to be a mad hunt for a bug. Turns out, finding the
 * length of a vector using hypot(x, y) gave WA but using sqrt(x*x+y*y) is AC? Idk man, I
 * think the testcases were prepared wrongly
 * 
 * Time: O(nq), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long double ld;
const ld EPS = 1e-9;

struct point {
    ld x, y;
    point() { x = y = 0; }
    point(ld _x, ld _y) : x(_x), y(_y) {}

    // Compare x-coordinate, if equal compare y-coordinate
    bool operator<(const point &p) const {
        if (fabs(x - p.x) > EPS) return x < p.x;
        return y < p.y;
    }

    // Compare both x and y
    bool operator==(const point &p) const { return (fabs(x - p.x) < EPS && (fabs(y - p.y) < EPS)); }

    // Arithmetic Operations (Translation and Scaling)
    point operator+(const point &p) const { return point(x + p.x, y + p.y); }
    point operator-(const point &p) const { return point(x - p.x, y - p.y); }
    point operator*(const ld &r) const { return point(x * r, y * r); }
    point operator/(const ld &r) const { return point(x / r, y / r); }
};
// Output Representation of a point
ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }

// Euclidean Distance
ld dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y); }

// Vector Struct
struct vec {
    ld x, y;
    vec(ld _x, ld _y) : x(_x), y(_y) {}
    vec(point p1, point p2) : x(p2.x - p1.x), y(p2.y - p1.y) {}

    // Vector Operations
    vec operator+(const vec &v) const { return vec(x + v.x, y + v.y); }
    vec operator-(const vec &v) const { return vec(x - v.x, y - v.y); }
    vec operator*(const ld &r) const { return vec(x * r, y * r); }
    vec operator/(const ld &r) const { return vec(x / r, y / r); }

    // Length
    ld length() { return sqrt(x * x + y * y); }

    // Length Square
    ld length_sq() { return x * x + y * y; }
};

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double angle(point a, point o, point b) {  // returns angle aob in rad
    vec oa = vec(o, a), ob = vec(o, b);
    return acos((dot(oa, ob)) / (oa.length() * ob.length()));
    // return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) { return cross(vec(p, q), vec(p, r)) > 0; }

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point> &P) {
    int n = (int)P.size();
    // if (n <= 3) return -1;  // avoid point or line
    bool on_polygon = false;
    for (int i = 0; i < n - 1; ++i)  // on vertex/edge?
        if (fabs(dist(P[i], pt) + dist(pt, P[i + 1]) - dist(P[i], P[i + 1])) < EPS)
            on_polygon = true;
    if (on_polygon) return 0;  // pt is on polygon

    if (n <= 3) return -1;
    ld sum = 0.0;  // first = last point
    for (int i = 0; i < n - 1; ++i) {
        if (ccw(pt, P[i], P[i + 1]))
            sum += (angle(P[i], pt, P[i + 1]));  // left turn/ccw
        else
            sum -= (angle(P[i], pt, P[i + 1]));  // right turn/cw
    }
    // cout << "sum " << sum << endl;
    return fabs(sum) > M_PI ? 1 : -1;  // 360d->in, 0d->out
}

int main() {
    int n;
    vector<point> P;
    while (1) {
        cin >> n;
        if (n == 0) break;
        P.clear();
        for (int i = 0; i < n; ++i) {
            ld x, y;
            cin >> x >> y;
            P.push_back(point(x, y));
        }
        P.push_back(P[0]);
        int q;
        cin >> q;
        for (int i = 0; i < q; i++) {
            ld x, y;
            cin >> x >> y;
            int ans = insidePolygon(point(x, y), P);
            if (ans == 0) {
                cout << "on\n";
            } else if (ans == 1) {
                cout << "in\n";
            } else {
                cout << "out\n";
            }
        }
    }
    return 0;
}