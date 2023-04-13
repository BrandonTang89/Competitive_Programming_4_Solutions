/**Kattis - galactic
 * Relatively simple math. If we have a set of n distinct lines which are not all parallel then the
 * number of infinite regions is 2n. Adding extra (non parallel) lines will increase this by 2 each
 * time. We also need to deal wih the edge case of having all lines parallel, then we should add
 * some non-parallel lines to increase the number of regions as much as possible. Slightly tedious.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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
// Check for Parallel and Identical Lines
struct line {
    double a, b, c;  // ax + by + c = 0, b = 0 for all vertical lines and 1 otherwise
    line(ld _a, ld _b, ld _c) : a(_a), b(_b), c(_c) {}  // Direct Construction
    line(point p1, point p2)
    {                                   // Construct from two points
        if (fabs(p1.x - p2.x) < EPS) {  // Vertical Line
            a = 1.0;
            b = 0.0;
            c = -p1.x;  // Negative of x-intercept
        }
        else {
            a = -(p1.y - p2.y) / (p1.x - p2.x);  // Negative Gradient
            b = 1.0;                             // Non-vertical line
            c = -(a * p1.x) - p1.y;              // Negative of y-intercept
        }
    }
    line(point p, ld m)
    {                         // Construct from point and slope
        if (fabs(m) < EPS) {  // Vertical Line
            a = 1.0;
            b = 0.0;
            c = -p.x;  // Negative of x-intercept
        }
        else {
            a = -m;
            b = 1.0;
            c = -(a * p.x) - p.y;  // Negative of y-intercept
        }
    }
    line()
    {
        a = b = c = 0;  // No line
    };

    // Get line details
    ld getGradient()
    {
        assert(fabs(b) > EPS);  // Ensure line is not vertical
        return -a / b;
    }
    ld getYIntercept()
    {
        assert(fabs(b) > EPS);  // Ensure line is not vertical
        return -c / b;
    }
    ld getXIntercept()
    {
        assert(fabs(a) > EPS);  // Ensure line is not horizontal
        return -c / a;
    }

    // Get line evaluations
    ld getY(ld x)
    {
        assert(fabs(b) > EPS);  // Ensure line is not vertical
        return (-c - a * x) / b;
    }
    ld getX(ld y)
    {
        assert(fabs(a) > EPS);  // Ensure line is not horizontal
        return (-c - b * y) / a;
    }
};
bool areParallel(line l1, line l2) { return (fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS); }
bool areSame(line l1, line l2) { return areParallel(l1, l2) && (fabs(l1.c - l2.c) < EPS); }

vector<line> lines;
int w, n;
int main()
{
    cin >> w >> n;
    for (int i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back(line(point(x1, y1), point(x2, y2)));
    }

    // detect if all are parallel
    bool all_parallel = true;
    for (int i = 0; i < n - 1; i++) {
        if (!areParallel(lines[i], lines[i + 1])) all_parallel = false;
    }

    int num_distinct = 0;
    for (int i = 0; i < n; i++) {
        bool distinct = true;
        for (int j = i + 1; j < n; j++) {
            if (areSame(lines[i], lines[j])) distinct = false;
        }
        if (distinct) num_distinct++;
    }

    if (!all_parallel) {
        int num_required = (w + 1) / 2;  // ceil(w/2)
        cout << max(0, num_required - num_distinct) << endl;
        return 0;
    }

    if (num_distinct + 1 >= w) {
        cout << 0 << endl;
        return 0;
    }

    num_distinct++;
    int num_required = (w + 1) / 2;  // ceil(w/2)
    cout << max(1, 1 + num_required - num_distinct) << endl;

    return 0;
}