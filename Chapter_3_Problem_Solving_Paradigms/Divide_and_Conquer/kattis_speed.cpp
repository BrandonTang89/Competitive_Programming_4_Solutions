/**Kattis - speed
 * Observe that the total time taken is sum((di)/(si + c)) for all segments. Now, observe that if
 * the time taken for a specific c is lower than the real time, it means our speeds are too fast, so
 * c needs to be lower. Similarly, if the time taken is a higher, then c needs to be higher. As
 * such, we can binary search for c.
 *
 * Note that the lowerbound for the speed should be such that the minimum real speed for the slowest
 * segment is 0.
 *
 * Time: O(n log(1e7)), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
double t;
vector<pair<int, int>> segments;  // di, si;
double time_taken(double c) {
    double ans = 0;
    for (auto &[di, si] : segments) {
        ans += (double)(di) / (double)(si + c);
    }
    return ans;
}
int main() {
    cin >> n >> t;
    segments.resize(n);
    int min_s = 2000;
    for (int i = 0; i < n; i++) {
        cin >> segments[i].first >> segments[i].second;
        min_s = min(min_s, segments[i].second);
    }

    double l = -min_s, r = 1e7;
    for (int i = 0; i < 1000; i++) {
        double mid = (l + r) / 2;
        if (time_taken(mid) <= t) {
            r = mid;
        } else {
            l = mid;
        }
    }
    cout << fixed << setprecision(10) << l << endl;
    return 0;
}