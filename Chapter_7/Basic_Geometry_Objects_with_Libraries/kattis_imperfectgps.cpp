/**Kattis - imperfectgps
 * Example of why computational geometry question are tedious. So much code just for this.
 * Just be careful and it should all be alright, its just direct simulation to determine
 * the points recorded by the GPS using linear interpolation.
 * 
 * Time: O(max_time / t + n), Space: O(max_time / t + n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const ld EPS = 1e-9;

ld DEG_to_RAD(ld d) { return d * M_PI / 180; }
ld RAD_to_DEG(ld r) { return r * 180 / M_PI; }
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

    // Arithmetic Operations
    point operator+(const point &p) const { return point(x + p.x, y + p.y); }
    point operator-(const point &p) const { return point(x - p.x, y - p.y); }
    point operator*(const ld &r) const { return point(x * r, y * r); }
    point operator/(const ld &r) const { return point(x / r, y / r); }
};

// Output Representation of a point
ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }

// Euclidean Distance
ld dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y); }

// Interpolate the position of an object at time t assuming object was at p1 at time t1 and p2 at
// time t2
point linear_interpolate(point p1, point p2, int t1, int t2, int t) {
    return p1 + (p2 - p1) * (t - t1) / (ld)(t2 - t1);
}

// Counter Clockwise Rotation about Pivot which defaults to origin
point rotate(ld rad, point p, point pivot = point()) {
    ld x = p.x - pivot.x;
    ld y = p.y - pivot.y;
    ld nx = x * cos(rad) - y * sin(rad) + pivot.x;
    ld ny = x * sin(rad) + y * cos(rad) + pivot.y;
    return point(nx, ny);
}

int n, period, t;
ld x, y;
vector<pair<point, int>> points;
vector<point> gps_points;
int main() {
    cin >> n >> period;
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> t;
        points.push_back({point(x, y), t});
    }

    int last_time = points[n - 1].second;

    point prev_pt = points[0].first;
    int prev_time = points[0].second;
    // int prev_i;

    point next_pt = points[1].first;
    int next_time = points[1].second;
    int next_i = 1;

    gps_points.push_back(points[0].first);
    for (int t = period; t < last_time; t += period) {
        while (t >= next_time) {
            prev_pt = next_pt;
            prev_time = next_time;
            // prev_i = next_i;
            next_i = (next_i + 1);
            next_pt = points[next_i].first;
            next_time = points[next_i].second;
        }
        gps_points.push_back(linear_interpolate(prev_pt, next_pt, prev_time, next_time, t));
    }
    gps_points.push_back(points[n - 1].first);

    ld real_dist = 0, gps_dist = 0;
    for (int i = 0; i < n - 1; i++) {
        real_dist += dist(points[i].first, points[(i + 1)].first);
    }
    for (int i = 0; i < (int)gps_points.size() - 1; i++) {
        gps_dist += dist(gps_points[i], gps_points[i + 1]);
        // cout << gps_points[i] << " " << gps_points[i+1] << endl;
    }

    cout.precision(std::numeric_limits<double>::digits10);
    // cout << real_dist << " " << gps_dist << endl;
    cout << fabs(real_dist - gps_dist) * 100 / real_dist << endl;

    return 0;
}