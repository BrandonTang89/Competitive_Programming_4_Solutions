/**Kattis - intervalcover
 * classic interval covering problem. Sort by increasing left and decreasing right boundaries. Then
 * we take the one that covers the most right while still joining with the previously covered place.
 * This is a linear pass.
 *
 * Note that we need to ensure that we try to account for floating point errors and ensure that our
 * max_r is sufficiently low (see code).
 *
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

vector<tuple<int, ld, ld>> intervals;
bool cmp(tuple<int, ld, ld> a,
         tuple<int, ld, ld> b) {  // sort by increasing left border then by decreasing right border
    auto &[id1, l1, r1] = a;
    auto &[id2, l2, r2] = b;

    if (l1 < l2) return true;
    if (l1 > l2) return false;
    return r1 > r2;
}

int n;
ld l, r, EPS = 1e-9;
int main() {
    fast_cin();
    while (cin >> l >> r) {
        cin >> n;
        intervals.clear();
        for (int i = 0; i < n; i++) {
            ld x, y;
            cin >> x >> y;
            intervals.push_back({i, x, y});
        }

        sort(intervals.begin(), intervals.end(), cmp);
        bool possible = true;
        ld covered = l;
        int ans = 0;
        vector<int> selection;

        for (int i = 0; i < n; i++) {
            if (covered >= r && ans > 0) break;
            auto &[id, li, ri] = intervals[i];
            if (ri < covered - EPS) continue;  // already covered
            if (fabs(ri - covered) < EPS && ans != 0) continue;
            if (li > covered + EPS) {
                possible = false;
                break;
            }
            ld max_r = l - 1;  // important, max_r must be less than l!!
            int max_id = i;
            for (int j = i; j < n && (get<1>(intervals[j]) < covered + EPS); j++) {
                if (get<2>(intervals[j]) > max_r) {
                    max_r = get<2>(intervals[j]);
                    max_id = j;
                }
            }
            ans++;
            covered = max_r;
            i = max_id;
            selection.push_back(get<0>(intervals[max_id]));
        }
        if (!possible || covered < r)
            cout << "impossible" << endl;
        else {
            cout << ans << endl;
            for (auto &i : selection) cout << i << " ";
            cout << endl;
        }
    }

    return 0;
}