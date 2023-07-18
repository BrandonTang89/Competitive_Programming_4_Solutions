/**Kattis - glyphrecognition
 * Relatively simple comp geom + binary search problem. We generate all the unit polygons
 * by rotating a (1, 0) point around the origin a bunch. Then for each polygon we do 2 binary
 * searches to fit the polygon to the points and select the best shape. Note that if you're using
 * the library code from CP4 then comment out the section of on-polygon else there will be accuracy
 * issues.
 *
 * Time: O(n), Space: O(n)
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
const ld EPS = 1e-12;

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

ld dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
ld angle(point a, point o, point b)
{  // returns angle aob in rad
    vec oa = vec(o, a), ob = vec(o, b);
    return acos((dot(oa, ob)) / (oa.length() * ob.length()));
}
ld cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) { return cross(vec(p, q), vec(p, r)) > 0; }

// Counter Clockwise Rotation about Pivot which defaults to origin
ld DEG_to_RAD(ld d) { return d * M_PI / 180; }
ld RAD_to_DEG(ld r) { return r * 180 / M_PI; }
point rotate(ld rad, point p, point pivot = point())
{
    ld x = p.x - pivot.x;
    ld y = p.y - pivot.y;
    ld nx = x * cos(rad) - y * sin(rad) + pivot.x;
    ld ny = x * sin(rad) + y * cos(rad) + pivot.y;
    return point(nx, ny);
}

// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const vector<point> &P)
{
    int n = (int)P.size();
    if (n <= 3) return -1;  // avoid point or line
    /*
    bool on_polygon = false;
    for (int i = 0; i < n - 1; ++i)  // on vertex/edge?
        if (fabs(dist(P[i], pt) + dist(pt, P[i + 1]) - dist(P[i], P[i + 1])) < EPS)
            on_polygon = true;
    if (on_polygon) return 0;  // pt is on polygon
    */
    ld sum = 0.0;  // first = last point
    for (int i = 0; i < n - 1; ++i) {
        if (ccw(pt, P[i], P[i + 1]))
            sum += angle(P[i], pt, P[i + 1]);  // left turn/ccw
        else
            sum -= angle(P[i], pt, P[i + 1]);  // right turn/cw
    }
    return fabs(sum) > M_PI ? 1 : -1;  // 360d->in, 0d->out
}

// returns the area of polygon P
ld area(const vector<point> &P)
{
    ld ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)  // Shoelace formula
        ans += (ld)(P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return fabs(ans) / (ld)2.0;  // only do / 2.0 here
}

vector<point> polygons[9];
int main()
{
    int n;
    cin >> n;
    vector<point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    for (int i = 3; i <= 8; i++) {
        polygons[i].push_back(point(1, 0));
        for (int j = 1; j < i; j++) {
            polygons[i].push_back(rotate(j * 2 * M_PI / (ld)i, polygons[i][0]));
        }
    }

    ld best_score = 0;
    int best_shape = 0;
    for (int i = 3; i <= 8; i++) {
        // find the inner shape
        ld flo = 1;
        ld fhi = 1e8;
        for (int j = 0; j < 100; j++) {
            ld fmid = (flo + fhi) / 2;
            vector<point> inner;
            for (int k = 0; k < i; k++) {
                inner.push_back(polygons[i][k] * fmid);
            }
            inner.push_back(inner[0]);

            bool alloutside = true;
            for (int k = 0; k < n; k++) {
                if (insidePolygon(points[k], inner) != -1) {  // if not outside
                    alloutside = false;
                    break;
                }
            }

            if (alloutside) {
                flo = fmid;
            }
            else {
                fhi = fmid;
            }
        }

        // find outer shape
        ld ghi = 1e8;
        ld glo = 1;

        for (int j = 0; j < 100; j++) {
            ld gmid = (glo + ghi) / 2;
            vector<point> outer;
            for (int k = 0; k < i; k++) {
                outer.push_back(polygons[i][k] * gmid);
            }
            outer.push_back(outer[0]);

            bool allinside = true;
            for (int k = 0; k < n; k++) {
                if (insidePolygon(points[k], outer) == -1) {  // if not inside or on
                    allinside = false;
                    break;
                }
            }

            if (allinside) {
                ghi = gmid;
            }
            else {
                glo = gmid;
            }
        }

        vector<point> inner;
        for (int k = 0; k < i; k++) {
            inner.push_back(polygons[i][k] * flo);
        }
        inner.push_back(inner[0]);
        vector<point> outer;
        for (int k = 0; k < i; k++) {
            outer.push_back(polygons[i][k] * ghi);
        }
        outer.push_back(outer[0]);
        ld score = area(inner) / area(outer);

        if (score > best_score) {
            best_score = score;
            best_shape = i;
        }
    }
    cout << best_shape << " ";
    cout << setprecision(10) << fixed << best_score << endl;
}