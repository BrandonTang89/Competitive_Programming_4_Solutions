/**Kattis - cuttingcorners
 * We go around the polygon and find the smallest angle! Just do that a bunch of times
 * with some simple checks.
 * 
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
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


ostream &operator<<(ostream &os, const point &p) { return os << "(" << p.x << "," << p.y << ")"; }
// Vector Products
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }

// Calculate angle ABC (in that order)
ld angle(const point &a, const point &b, const point &c) {
    vec v1 = vec(b, a);
    vec v2 = vec(b, c);
    return acos(dot(v1, v2) / (v1.length() * v2.length()));
}

pair<ld, int> cal_smallest_angle(const vector<point> &P){
    ld ans = angle(P[P.size() - 2], P[0], P[1]); // angle centered at the first point
    int smallest_angle_idx = 0;
    for (int i=1; i< (int)P.size()-1; i++){
        ld cur = angle(P[i-1], P[i], P[i+1]);
        if (cur < ans){
            ans = cur;
            smallest_angle_idx = i;
        }
    }
    return {ans, smallest_angle_idx};
}

int n;
vector<point> poly, poly2;
int main(){
    while(1){
        cin >> n;
        if(n == 0) break;
        poly.clear();
        for (int i=0; i<n; i++){
            ld x, y;
            cin >> x >> y;
            poly.push_back(point(x, y));
        }
        poly.push_back(poly[0]);

        
        for (int i=0;; i++){
            vector<point> &cur_poly = (i % 2 == 0) ? poly : poly2;
            vector<point> &next_poly = (i % 2 == 0) ? poly2 : poly;

            if (cur_poly.size() <= 4){
                next_poly = cur_poly;
                break;
            }; // triangle or smaller
            auto [smallest_angle, smallest_angle_idx] = cal_smallest_angle(cur_poly);

            // cout << "smallest angle " << smallest_angle << " at " << smallest_angle_idx << endl;
            next_poly.clear(); 
            for (int j=0; j< (int)cur_poly.size(); j++){
                if (j != smallest_angle_idx){
                    next_poly.push_back(cur_poly[j]);
                }
            }

            auto [smallest_angle2, smallest_angle_idx2] = cal_smallest_angle(next_poly);
            if (smallest_angle2 <= smallest_angle){ // no improvement
                next_poly = cur_poly;
                break;
            }
        }
        poly.pop_back();
        cout << poly.size();
        for (auto p : poly){
            cout << " " << p.x << " " << p.y;
        }
        cout << endl;

    }
}