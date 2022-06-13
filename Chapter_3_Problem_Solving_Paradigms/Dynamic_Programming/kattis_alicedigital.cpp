/**Kattis - alicedigital
 * Modified version of Kadane's algorithm, for each index i, consider the best sum ending at index
 * i, this sum should contain 1x minimum element of m, look at the code for more details.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int num_tc, n, m;
int main() {
    cin >> num_tc;
    while (num_tc--) {
        cin >> n >> m;
        vector<ll> v;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            v.push_back(x);
        }
        ll untilm = 0;  // sum of elements until the m in the sum (inclusive)
        ll sum = 0, ans = m;
        for (int i = 0; i < n; ++i) {  // linear scan, O(n)
            if (v[i] < m) {
                sum = 0;
                untilm = 0;
                continue;
            }
            if (v[i] == m) {
                sum -= untilm;
                sum += v[i];
                untilm = sum;

                ans = max(ans, sum);
                continue;
            }
            if (v[i] > m) {
                sum += v[i];
                if (untilm != 0) ans = max(ans, sum);  // ensure at least 1 m is inside the sum
                continue;
            }
        }
        cout << ans << endl;
    }

    return 0;
}