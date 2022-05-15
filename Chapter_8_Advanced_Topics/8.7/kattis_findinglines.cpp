/**Kattis - findinglines
 * This is one of the few problems I'v done that has an interesting randomised solution. See, if the true answer is positive, then each selection of
 * 2 points has at least a 20% chance of having a line passing through them that has p% of points in it. So the probability of getting a false negative
 * is (1 - 0.8^k) where k is the number of times we do the randomised test. With k == 1000, this is virtually not a problem. The probability of a
 * false positive is 0 because we only declare positive when we have found a valid line.
 * 
 * Time: O(k * n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

typedef long double ld;
const ld EPS = 1e-9;

struct point {
    ld x, y;
    point() { x = y = 0; }
    point(ld _x, ld _y) : x(_x), y(_y) {}
    bool operator==(const point &p) const { return (fabs(x - p.x) < EPS && (fabs(y - p.y) < EPS)); }
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

// Vector Products
ld dot(vec v1, vec v2) { return v1.x * v2.x + v1.y * v2.y; }
ld cross(vec v1, vec v2) { return v1.x * v2.y - v1.y * v2.x; }


bool collinear(point p1, point p2, point p3) {
    return fabs(cross(vec(p1, p2), vec(p1, p3))) < EPS;
}


int main(){
    int n, percent;
    cin >> n >> percent;

    int num_required = ceil(n * (ld) percent / (ld) 100.0);
    if (n == 1){
        cout << "possible" << endl;
        return 0;
    }
    vector<point> points;
    for (int i = 0; i < n; i++){
        int x, y;
        cin >> x >> y;
        points.push_back(point(x, y));
    }

    for (int test=0; test<1000; test++){
        point a = points[rand() % n];
        point b = points[rand() % n];
        while (b == a) b = points[rand() % n];

        int num_collinear = 0;
        for (auto p: points){
            if (p == a || p == b) continue;
            if (collinear(a, b, p)) num_collinear++;
        }

        if (num_collinear + 2 >= num_required){
            cout << "possible" << endl;
            return 0;
        }
    }
    cout << "impossible" << endl;

    return 0;
}