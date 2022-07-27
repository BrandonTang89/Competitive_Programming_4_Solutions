/**Kattis - tricktreat
 * Just ternary search to minimise the maximum distance any one child must run to the meeting point.
 * U can prove that ternary search works by considering the graphs of the distances between the
 * initial point and the meeting point as the meeting varies. U can prove by contradiction that
 * there is only 1 minimum point of the maximum of all the graphs.
 *
 * Time: O(n), Space: O(1)
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

vector<pair<double, double>> points;
double cost(double x) {
    double ans = 0;
    for (auto p : points) {
        ans = max(hypot(fabs(p.first - x), p.second), ans);
    }
    return ans;
}
int main() {
    fast_cin();
    cout << fixed << setprecision(10);

    while (1) {
        points.clear();
        int n;
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; i++) {
            double x, y;
            cin >> x >> y;
            points.push_back({x, y});
        }

        double hi = 1e12, lo = -1e12;
        for (int i = 0; i < 100; i++) {
            // ternary search

            double mid_lo = lo + (hi - lo) / 3;
            double mid_hi = hi - (hi - lo) / 3;

            double mid_lo_cost = cost(mid_lo);
            double mid_hi_cost = cost(mid_hi);

            if (mid_lo_cost < mid_hi_cost) {
                hi = mid_hi;
            } else {
                lo = mid_lo;
            }
        }
        cout << lo << " " << cost(lo) << endl;
    }

    return 0;
}