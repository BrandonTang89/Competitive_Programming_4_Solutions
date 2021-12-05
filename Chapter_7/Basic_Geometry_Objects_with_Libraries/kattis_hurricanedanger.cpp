/**Kattis - hurricanedanger
 * Relatively easy if we have the prepared libary code. Just repeatedly call the dist from point 
 * to line function.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-10;

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
    ld length() { return hypot(x, y); }

    // Length Square
    ld length_sq() { return x * x + y * y; }
};

// Vector Products
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
vec cross(vec v1, vec v2) { return vec(v1.x * v2.y, v1.y * v2.x); }

// Vectors with Points
point translate(point p, vec v) { return point(p.x + v.x, p.y + v.y); }
point scale(point p, ld r) { return point(p.x * r, p.y * r); }

// Calculate angle ABC (in that order)
ld angle(const point &a, const point &b, const point &c) {
    vec v1 = vec(a, b);
    vec v2 = vec(a, c);
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

// Counter Clockwise Test and Variants
bool ccw(point p1, point p2, point p3) {
    return cross(vec(p1, p2), vec(p1, p3)).length() > EPS;
}
bool collinear(point p1, point p2, point p3) {
    return fabs(cross(vec(p1, p2), vec(p1, p3)).length()) < EPS;
}

// Minimum Length from point to line, and point on line
ld distToLine(point p, point a, point b, point &closest_pt){
    vec v1 = vec(a, b);
    vec v2 = vec(a, p);
    ld t = dot(v1, v2) / v1.length_sq();
    closest_pt = point(a.x + v1.x * t, a.y + v1.y * t);
    return hypot(p.x - closest_pt.x, p.y - closest_pt.y);
}   

int num_tc, n;
ld x, y, x2, y2;
point s, e;
ld cur_min_dist = 1e9;
vector<string> cities;
point dummy;
int main() {
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cities.clear();
        cur_min_dist = 1e9;
        cin >> x >> y >> x2 >> y2;
        s = point(x, y);
        e = point(x2, y2);
        cin >> n;
        for (int i = 0; i < n; i++) {
            string city;
            cin >> city >> x >> y;

            ld min_dist = distToLine(point(x, y), s, e, dummy);
            // cout << s << e << point(x, y) << endl;
            // cout << "i: " << min_dist <<endl;
            if (fabs(min_dist - cur_min_dist) < EPS){
                cities.push_back(city);
            
            }
            else if (cur_min_dist - min_dist> EPS){
                cities.clear();
                cities.push_back(city);
                cur_min_dist = min_dist;
            }  

        }
        for (auto city : cities) {
            cout << city << " ";
        }
        cout << endl;
    }
    return 0;
}