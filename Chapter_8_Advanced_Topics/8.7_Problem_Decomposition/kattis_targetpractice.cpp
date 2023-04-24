/**Kattis - targetpractice
 * Geometry. Assume that the points do indeed fall along 2 lines. Consider the first 3 points, it
 * must be that 2 of the points fall along one of those 2 lines (at least). So we can try all 3
 * choose 2 ways for the 2 out of the 3 points to fall along the same line. Then we check if all the
 * other points not on this line are collinear.
 *
 * Time: O(n), Mem: O(n)
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

// Output Representation of a point
ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }

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

bool collinear(point p1, point p2, point p3) { return fabs(cross(vec(p1, p2), vec(p1, p3))) < EPS; }

bool restcollinear(vector<point> &missed)
{
    bool iscollinear = true;
    for (int i = 2; i < (int)missed.size(); i++) {
        if (!collinear(missed[0], missed[1], missed[i])) {
            iscollinear = false;
            break;
        }
    }
    return iscollinear;
}
int main()
{
    int n;
    cin >> n;
    vector<point> points;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    // Try points[0] and [1] form a line
    vector<point> missed;
    for (int i = 2; i < n; i++) {
        if (!collinear(points[0], points[1], points[i])) {
            missed.push_back(points[i]);
        }
    }
    // check if all missed are collinear
    if (restcollinear(missed)) {
        cout << "success" << endl;
        return 0;
    }

    // Try points[0] and [2] form a line
    missed.clear();
    for (int i = 1; i < n; i++) {
        if (!collinear(points[0], points[2], points[i])) {
            missed.push_back(points[i]);
        }
    }
    // check if all missed are collinear
    if (restcollinear(missed)) {
        cout << "success" << endl;
        return 0;
    }

    // Try points[1] and [2] form a line
    missed.clear();
    for (int i = 0; i < n; i++) {
        if (!collinear(points[1], points[2], points[i])) {
            missed.push_back(points[i]);
        }
    }
    if (restcollinear(missed)) {
        cout << "success" << endl;
        return 0;
    }
    cout << "failure" << endl;

    return 0;
}