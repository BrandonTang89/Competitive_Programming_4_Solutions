/**Kattis - urbandesign
 * Relatively simple geom problem. For each candiate pair of points, we test if the number of lines
 * between the pair is even or odd. This can be done using the counter clockwise test for 2 fixed
 * points on the line and the 2 points we are testing.
 *
 * Time: O(nq), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-9;

struct point {
    ld x, y;
    point() { x = y = 0; }
    point(ld _x, ld _y) : x(_x), y(_y) {}

    // Compare x-coordinate, if equal compare y-coordinate
    bool operator<(const point &p) const
    {
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

// Vector Products
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

// Counter Clockwise Test and Variants
bool ccw(point p1, point p2, point p3) { return cross(vec(p1, p2), vec(p1, p3)) > EPS; }

vector<pair<point, point>> lines;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        point p1, p2;
        cin >> p1.x >> p1.y >> p2.x >> p2.y;
        lines.push_back({p1, p2});
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        point p, q;
        cin >> p.x >> p.y >> q.x >> q.y;

        int different = 0;
        for (auto l : lines) {
            if (ccw(l.first, l.second, p) != ccw(l.first, l.second, q)) {
                different++;
            }
        }
        cout << (different & 1 ? "different" : "same") << endl;
    }

    return 0;
}