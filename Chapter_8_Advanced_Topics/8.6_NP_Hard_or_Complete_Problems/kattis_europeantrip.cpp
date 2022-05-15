/**Kattis - europeantrip
 * This is the Euclidean Steiner Tree problem with 3 terminal and 1 internal vertex. We can try to find the fermat point
 * with a lot of mathematics. But we can also use some very very very sketchy iterative optimization to find this...
 * 
 * At first I did what CP4 hint suggested: 2 ternary searches, but I was having problems passing certain testcases. I
 * implemented to alternate between cutting the search space of x and y. When one was being searched, i let the other
 * coordinate be the average of the high and low bounds.
 * 
 * Since it didn't work, I opted to use gradient descent. I found that the best starting point was the average of the
 * high and low bounds for each of the coordinates... I also just played around with the alpha (initial learning rate)
 * to see how it would fair... It's honestly mega mega sketchy but it works.
 * 
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

pair<ld, ld> a, b, c;
ld dist(pair<ld, ld> p) {
    return (hypot(p.first - a.first, p.second - a.second) +
            hypot(p.first - b.first, p.second - b.second) +
            hypot(p.first - c.first, p.second - c.second));
}

int main() {
    ld x, y;
    cin >> x >> y;
    a = make_pair(x, y);
    cin >> x >> y;
    b = make_pair(x, y);
    cin >> x >> y;
    c = make_pair(x, y);

    ld x_l = min(min(a.first, b.first), c.first);
    ld x_h = max(max(a.first, b.first), c.first);
    ld y_l = min(min(a.second, b.second), c.second);
    ld y_h = max(max(a.second, b.second), c.second);

    cout << fixed << setprecision(10);

    ld cx = (x_h + x_l)/2, cy = (y_h + y_l)/2;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    for (ld d=x_h; d > 1e-12; d *=0.999){
        for (int dir=0; dir < 4; dir++){
            ld nx = cx + dx[dir]*d;
            ld ny = cy + dy[dir]*d;
            if (dist(make_pair(nx, ny)) < dist(make_pair(cx, cy))){
                cx = nx;
                cy = ny;
            }
        }
    }

    cout << cx << " " << cy << endl;
    return 0;
}