/**Kattis - shortsell
 * Modified version of Kadane's Algorithm. Here we need to know for ending on each specific day,
 * what the best gain is where the profit is best_gain_for_day_i - cost_to_buy_on_day_i.
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> A;
int main() {
    cin >> n >> k;
    A.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int ans = 0, best_gain = 0;
    for (int i = 0; i < n; ++i) {  // linear scan, O(n)
        best_gain = max(best_gain - k, A[i] * 100);
        ans = max(ans, best_gain - A[i] * 100 - k);
    }
    cout << ans << endl;
    return 0;
}