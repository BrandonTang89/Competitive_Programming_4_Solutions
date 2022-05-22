/**vjudge - UVA-1571 - How I Mathematician Wonder What You Are! 
 * Observe that this problem is basically just art gallery defendable by 1 guard. Use the
 * cutpolygon method.
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

// compute the intersection point between line segment p-q and line A-B
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y-A.y, b = A.x-B.x, c = B.x*A.y - A.x*B.y;
  double u = fabs(a*p.x + b*p.y + c);
  double v = fabs(a*q.x + b*q.y + c);
  return point((p.x*v + q.x*u) / (u+v), (p.y*v + q.y*u) / (u+v));
}

// cuts polygon Q along the line formed by point A->point B (order matters)
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point A, point B, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); ++i) {
    double left1 = cross(vec(A, B), vec(A, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = cross(vec(A, B), vec(A, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);         // Q[i] is on the left
    if (left1*left2 < -EPS)                      // crosses line AB
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], A, B));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());                      // wrap around
  return P;
}

int main() {
    vector<point> P;
    for (int floor=1; ;floor++){
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
        
        vector<point> space = P;
        for (int i=1; i<(int)P.size(); i++){
            point B = P[i], A = P[i-1];
            space = cutPolygon(A, B, space);
        }
        cout << ((int) space.size() != 0 ? "1" : "0") << endl;
    }
    return 0;
}