/**Kattis - convexhull
 * Simple convex hull, remove duplicate points. Use the libary code and it'll be manageable.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
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
    ld length() { return hypot(x, y); }

    // Length Square
    ld length_sq() { return x * x + y * y; }
};

// Vector Products
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

// Calculate angle ABC (in that order)
ld angle(const point &a, const point &b, const point &c) {
    vec v1 = vec(a, b);
    vec v2 = vec(a, c);
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

// Counter Clockwise Test and Variants
bool ccw(point p1, point p2, point p3) { return cross(vec(p1, p2), vec(p1, p3)) > EPS; }
bool collinear(point p1, point p2, point p3) { return fabs(cross(vec(p1, p2), vec(p1, p3))) < EPS; }

vector<point> CH_Andrew(vector<point> &Pts) {  // overall O(n log n)
    int n = Pts.size(), k = 0;
    vector<point> H(2 * n);
    sort(Pts.begin(), Pts.end());  // sort the points by x/y
    for (int i = 0; i < n; ++i) {  // build lower hull
        while ((k >= 2) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    for (int i = n - 2, t = k + 1; i >= 0; --i) {  // build upper hull
        while ((k >= t) && !ccw(H[k - 2], H[k - 1], Pts[i])) --k;
        H[k++] = Pts[i];
    }
    H.resize(k);
    return H;
}

int n;
ld x, y;
vector<point> polygon;
set<point> points;
int main() {
    while (true) {
        cin >> n;
        if (n == 0) break;
        polygon.clear();
        points.clear();
        for (int i = 0; i < n; i++) {
            cin >> x >> y;

            point P(x, y);
            if (points.find(P) == points.end()) {  // avoid duplicates
                polygon.push_back(P);
                points.insert(P);
            }
        }
        auto hull = CH_Andrew(polygon);
        if ((int) hull.size() > 1) hull.pop_back();
        
        cout << hull.size() << endl;
        for (int i = 0; i < (int) hull.size(); i++) {
            cout << hull[i].x << " " << hull[i].y << endl;
        }
    }

    return 0;
}