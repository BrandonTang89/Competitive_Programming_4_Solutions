/**Kattis - roberthood
 * Convex hull + rotating calipers + distance between points.
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
    ld length() { return hypot(x, y); }

    // Length Square
    ld length_sq() { return x * x + y * y; }
};

// Vector Products
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

// Calculate angle between BA and BC (centered at B)
ld angle(const point &a, const point &b, const point &c) {
    vec v1 = vec(b, a);
    vec v2 = vec(b, c);
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

// Counter Clockwise Test and Variants
bool ccw(point p1, point p2, point p3) { return cross(vec(p1, p2), vec(p1, p3)) > EPS; }
bool collinear(point p1, point p2, point p3) { return fabs(cross(vec(p1, p2), vec(p1, p3))) < EPS; }

// returns the area of polygon P
ld cal_area(const vector<point> &P) {
    ld ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)  // Shoelace formula
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return fabs(ans) / 2.0;  // only do / 2.0 here
}

vector<point> CH_Andrew(vector<point> &Pts) {  // overall O(n log n)
    int n = Pts.size(), k = 0;
    vector<point> H(2 * n);
    sort(Pts.begin(), Pts.end());  // sort the points by x then if tie y
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

ld cal_tri_area(point a, point b, point c) { return fabs(cross(vec(a, b), vec(a, c)) / 2.0); }

// Rotating Caliper Algorithm to Get All AntiPodal Points
// Here P has no repeated vertice at the back
vector<pair<int, int>> GetAllAntiPodalPairs(vector<point> P) {
    int n = P.size();

    if (n == 1) return {};
    if (n == 2) return {{0, 1}};

    vector<pair<int, int>> ans;
    int i0 = n - 1;
    int i = 0;
    int j = i + 1;
    int j0 = j;
    while (cal_tri_area(P[i], P[i + 1], P[j + 1]) > cal_tri_area(P[i], P[i + 1], P[j])) {
        j = j + 1;
        j0 = j;
    }
    ans.push_back({i, j});
    while (j != i0) {
        i = i + 1;
        ans.push_back({i, j});

        while (cal_tri_area(P[i], P[i + 1], P[j + 1]) > cal_tri_area(P[i], P[i + 1], P[j])) {
            j = j + 1;
            if ((i != j0 && j != i0))
                ans.push_back({i, j});
            else
                return ans;
        }
        if (cal_tri_area(P[j], P[i + 1], P[j + 1]) == cal_tri_area(P[i], P[i + 1], P[j])) {
            if (i != j0 && j != i0)
                ans.push_back({i, j + 1});
            else
                ans.push_back({i + 1, j});
        }
    }
    return ans;
}

int main() {
    int n;
    vector<point> polygon;
    set<point> points;  // to help test for duplicates
    cin >> n;
    for (int i = 0; i < n; i++) {
        ld x, y;
        cin >> x >> y;

        point P(x, y);
        polygon.push_back(P);
    }
    auto hull = CH_Andrew(polygon);
    if (hull.size() == 1) {
        cout << "0" << endl;
        return 0;
    }
    hull.pop_back();
    auto pairs = GetAllAntiPodalPairs(hull);
    ld max_dist = 0.0;
    for (auto p : pairs) {
        // cout << p.first << " " << p.second << endl;
        max_dist = max(max_dist, dist(hull[p.first], hull[p.second]));
    }
    cout << fixed << setprecision(10) << max_dist << endl;
    return 0;
}