/**Kattis - cursethedarkness
 * Simple problem involving checking the eucleadian distance between a main point and n
 * other points.
 * 
 * Time: O(n), Space: O(1)
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

    // Counter Clockwise Rotation about Origin
    point rotate(ld rad) {
        ld nx = x * cos(rad) - y * sin(rad);
        ld ny = x * sin(rad) + y * cos(rad);
        return point(nx, ny);
    }
};
// Output Representation of a point
ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }

// Euclidean Distance
ld dist(point p1, point p2) { return hypot(p1.x - p2.x, p1.y - p2.y); }

ld x, y;
point book;
int main() {
    int num_tc;
    cin >> num_tc;

    for (int tc = 1; tc <= num_tc; tc++) {
        int n;
        cin >> x >> y;
        book = point(x, y);

        bool can = false;
        cin >> n;
        for (int i=0; i<n; i++){
            cin >> x >> y;
            point p = point(x, y);
            if (dist(p, book) <= (ld) 8){
                can = true;
            }
        }

        cout << (can ? "light a candle\n" : "curse the darkness\n");
    }

}