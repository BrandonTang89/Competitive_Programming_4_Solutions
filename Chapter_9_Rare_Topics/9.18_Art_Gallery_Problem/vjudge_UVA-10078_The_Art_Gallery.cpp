/**vjudge - UVA-10078 - Art Gallery
 * Simply check the gallery can be defended by 1 guard from anywhere by checking if the polygon
 * is convex. 
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

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }
double angle(point a, point o, point b) {  // returns angle aob in rad
    vec oa = vec(o, a), ob = vec(o, b);
    return acos((dot(oa, ob)) / (oa.length() * ob.length()));
}
double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) { return cross(vec(p, q), vec(p, r)) > 0; }
// returns true if we always make the same turn
// while examining all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
    int n = (int)P.size();
    // a point/sz=2 or a line/sz=3 is not convex
    if (n <= 3) return false;
    bool firstTurn = ccw(P[0], P[1], P[2]);  // remember one result,
    for (int i = 1; i < n - 1; ++i)          // compare with the others
        if (ccw(P[i], P[i + 1], P[(i + 2) == n ? 1 : i + 2]) != firstTurn)
            return false;  // different -> concave
    return true;           // otherwise -> convex
}
int main() {
    vector<point> P;
    while (1) {
        int n;
        cin >> n;
        if (n == 0)break;
        P.clear();
        for (int i=0; i<n;i++){
            int x, y;
            cin >> x >> y;
            P.push_back(point(x, y));
        }
        P.push_back(P[0]);
        cout << (isConvex(P) ? "No" : "Yes") << endl;
    }
    return 0;
}