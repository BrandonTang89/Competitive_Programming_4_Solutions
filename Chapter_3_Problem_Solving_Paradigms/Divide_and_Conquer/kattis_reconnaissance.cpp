/**Kattis - reconnaissance
 * Relatively easy ternary search problem. Essentially we ternary search for the best time. For each
 * time, we check the maximum value of the lines and the minimum value of the lines, then take the
 * difference. This works because the graph of min(all lines) is concave while that of max(all
 * lines) is convex. We could improve this with the same trick as that of the DP convex hull
 * optimisation. However, that is unnecessary for this problem.
 *
 * Time: O(100 n), Space: O(n)
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

int n;
vector<pair<int, int>> v;

double val(double x) {
    double maxi = -1e12;
    for (auto p : v) {
        double a = p.first, b = p.second;
        double y = a + b * x;
        maxi = max(maxi, y);
    }
    double mini = maxi;
    for (auto p : v) {
        double a = p.first, b = p.second;
        double y = a + b * x;
        mini = min(mini, y);
    }
    return maxi - mini;
}
int main() {
    fast_cin();
    cin >> n;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
    }

    double hi = 1e12, lo = 0;
    for (int i = 0; i < 100; i++) {
        // ternary search
        double mid_lo = lo + (hi - lo) / 3;
        double mid_hi = hi - (hi - lo) / 3;

        if (val(mid_lo) < val(mid_hi)) {
            hi = mid_hi;
        } else {
            lo = mid_lo;
        }
    }
    cout << fixed << setprecision(10) << val(hi) << endl;

    return 0;
}