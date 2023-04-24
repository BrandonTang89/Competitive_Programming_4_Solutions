/**Kattis - subwayplanning
 * Geometry + Binary Search. Relatively difficult problem with quite bad test data (doesn't test
 * much edge cases).
 *
 * The first obvious step is removing points within d from the origin. Then we can
 * sort the points based on their angle with the positive x axis.
 *
 * The next step is finding what kind of lines cover a point. What we can do is binary search for
 * the range of angles of the line that covers each point. Observer that we only need to test for
 * angle differences up to 90 degrees more than the angle of the point. Past that stage, the
 * distance to the ray is just the distance to the origin. This allows for us to check if any 2
 * points can be covered with 1 line.
 *
 * The next part is a greedy line sweep. Assume are planning on starting with p and covering some
 * points to the clockwise direction of p. Clearly we should cover as many points as possible with
 * that 1 line, this can be done by going in a clockwise direction and adding covered points until
 * the next point cannot be covered together with p. Then when we move to the next point that can't
 * be covered, repeat the process. However, there is an issue in that we don't know where to start
 * covering (i.e. the optimal solution might cover point n-1 and 0 with 1 line so we can't just
 * start with point 0).  Fortunuatelly, we can just try all points as the starting point and take
 * the best answer.
 *
 * Time: O(n^2), Space: O(n)
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

// Euclidean Distance
ld dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y); }

// Output Representation of a point
ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }

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
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

// Calculate angle between BA and BC (centered at B)
ld angle(const point &a, const point &b, const point &c)
{
    vec v1 = vec(b, a);
    vec v2 = vec(b, c);
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

// Counter Clockwise Test and Variants
bool ccw(point p1, point p2, point p3) { return cross(vec(p1, p2), vec(p1, p3)) > EPS; }

// Minimum Length from point to line, and point on line
ld distToLine(point p, line l, point &closest_pt)
{
    ld t = (l.a * p.x + l.b * p.y + l.c) / (l.a * l.a + l.b * l.b);
    closest_pt = point(p.x - l.a * t, p.y - l.b * t);
    return hypot(p.x - closest_pt.x, p.y - closest_pt.y);
}

// The angle going from A to B to C in a clockwise direction [0, 2pi)
ld corrected_angle(point a, point b, point c)
{
    ld anglex = angle(a, b, c);
    if (ccw(a, b, c)) anglex = 2 * M_PI - anglex;
    return anglex;
}
int n, d;
point origin(0, 0);
point onezero(1, 0);
vector<point> points;
vector<ld> max_angle_diff;
vector<int> tophalf;
bool comp(point a, point b)
{
    ld anglea = corrected_angle(onezero, origin, a);
    ld angleb = corrected_angle(onezero, origin, b);
    return anglea < angleb;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> d;
        points.clear();
        tophalf.clear();
        for (int i = 0; i < n; i++) {
            point p;
            cin >> p.x >> p.y;
            if (dist(origin, p) <= d) {  // ignore
                continue;
            }
            points.push_back(p);
        }
        n = points.size();
        sort(points.begin(), points.end(), comp);

        max_angle_diff.resize(n);
        for (int i = 0; i < n; i++) {
            ld l = corrected_angle(onezero, origin, points[i]);
            ld r = l + M_PI / 2.0;  // 90 degrees

            for (int j = 0; j < 50; j++) {
                ld m = (l + r) / 2.0;

                point p(cos(m), sin(m));
                line li(origin, p);

                if (distToLine(points[i], li, p) <= d) {
                    l = r;  // can have a bigger angle
                }
                else {
                    r = m;
                }
            }
            max_angle_diff[i] = l - corrected_angle(onezero, origin, points[i]);
        }
        ld ans = n;
        for (int i = 0; i < n; i++) {
            int cur_p = i;
            ld cur_ans = 1;
            for (int j = 1; j < n; j++) {
                int np = (i + j) % n;
                if (max_angle_diff[np] + max_angle_diff[cur_p] >=
                    angle(points[cur_p], origin, points[np])) {
                    continue;
                }
                else {
                    cur_ans++;
                    cur_p = np;
                }
            }
            ans = min(ans, cur_ans);
        }
        cout << ans << endl;
    }

    return 0;
}