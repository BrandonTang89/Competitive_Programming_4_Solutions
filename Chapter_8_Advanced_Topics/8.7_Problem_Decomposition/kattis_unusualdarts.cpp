/**Kattis - unusualdarts
 * Geometry + complete search. Do a n! complete search of all permutations of the points. Then for
 * each permutation, check if the polygon is simple and if the (area/2)^3 == probablity of b
 * winning.
 *
 * Time: O(n! * n) where n = 7. Space: O(n)
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

// Check for Parallel and Identical Lines
bool areParallel(line l1, line l2) { return (fabs(l1.a - l2.a) < EPS && fabs(l1.b - l2.b) < EPS); }

// Check if 2 lines intersect at a unique point, determine the point
bool areIntersect(line l1, line l2, point &intersection)
{
    if (areParallel(l1, l2)) return false;
    intersection.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    if (fabs(l1.b) > EPS)  // Line is not vertical
        intersection.y = -(l1.a * intersection.x + l1.c);
    else
        intersection.y = -(l2.a * intersection.x + l2.c);
    return true;
}

ld cal_area(const vector<point> &P)
{
    ld ans = 0.0;
    for (int i = 0; i < (int)P.size() - 1; ++i)  // Shoelace formula
        ans += (P[i].x * P[i + 1].y - P[i + 1].x * P[i].y);
    return fabs(ans) / 2.0;  // only do / 2.0 here
}

bool issimple(vector<point> &p)
{
    for (int i = 0; i < (int)p.size() - 1; i++) {
        for (int j = i + 2; j < (int)p.size() - 1; j++) {
            if (i == 0 && j == (int)p.size() - 2) continue;
            // check if p[i],p[i+1] intersects p[j],p[j+1]?
            line line1 = line(p[i], p[(i + 1)]);
            line line2 = line(p[j], p[(j + 1)]);

            point intersection;

            if (areIntersect(line1, line2, intersection)) {
                if (intersection.x > min(p[i].x, p[(i + 1)].x) &&
                    intersection.x < max(p[i].x, p[(i + 1)].x) &&
                    intersection.y > min(p[i].y, p[(i + 1)].y) &&
                    intersection.y < max(p[i].y, p[(i + 1)].y)) {
                    if (intersection.x > min(p[j].x, p[(j + 1)].x) &&
                        intersection.x < max(p[j].x, p[(j + 1)].x) &&
                        intersection.y > min(p[j].y, p[(j + 1)].y) &&
                        intersection.y < max(p[j].y, p[(j + 1)].y)) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}
ld prob;
bool done;
vector<int> order;
vector<point> arr;
void recursivesearch(int bm)
{
    if (bm == 0) {
        vector<point> poly;
        for (auto i : order) {
            poly.push_back(arr[i]);
        }
        poly.push_back(arr[order[0]]);
        if (!issimple(poly)) {
            return;
        }
        ld area = cal_area(poly);
        if (fabs(area * area * area / 64.0 - prob) <= 1e-5) {
            for (auto i : order) {
                cout << i + 1 << " ";
            }
            done = true;
            cout << endl;
        }
    }
    int nbm = bm;
    while (nbm > 0 && !done) {
        int cur = __builtin_ctz(nbm);
        order.push_back(cur);
        recursivesearch(bm ^ (1 << cur));
        order.pop_back();
        nbm -= (1 << cur);
    }
}
int main()
{
    int tc;
    int n;
    n = 7;
    cin >> tc;
    while (tc--) {
        arr.resize(n);
        for (int i = 0; i < n; i++) {
            ld x, y;
            cin >> x >> y;
            arr[i] = point(x, y);
        }

        cin >> prob;
        done = false;
        recursivesearch((1 << 7) - 1);
        assert(done);
    }

    return 0;
}