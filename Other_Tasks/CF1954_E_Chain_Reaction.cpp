/**CF1954_E
 * Observe that the dead monsters divide the alive monsters into various segments. Observe that it
 * doesn't matter which of the segments we throw the next attack since we still be doing them
 * independently. Observe also that we can assume that we throw the next attack at each of the
 * intervals then repeat with the new set of intervals.
 *
 * Consider dp(i) = number of (l, r) segments that a[l:r] > i (pointwise)
 * Observe that for a fixed k, our answer is actually dp(0) + dp(k) + dp(2k) + dp(3k) + ...
 * until we reach the maximum value of a (maxi).
 *
 * This is because we need dp(0) attacks to raise the amount of damage of all (alive monsters) to k.
 * Then dp(k) attacks to raise the amount of damage of all (alive monsters) to 2k. And so on.
 *
 * We compute dp(i) in a bottom up manner, simulating which monsters are alive and dead with the
 * alive array.
 *
 * dp(0) = 1 since initally all
 * dp(i) = dp(i-1) + no. of monsters q with a[q] = i and q is surrounded by alive monsters
 *                 - no. of monsters q with a[q] = i and q is not surrounded by alive monsters
 *
 * Notice that eventually we will need to do n + n/2 + n/3 + ... + 1 operations, which is O(n log
 * n).
 *
 * Time complexity: O(n log n)
 * Space complexity: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<int> alive;
vector<ll> dp, a;
// dp(i) = number of (l, r) segments that a[l:r] > i (pointwise)

int main()
{
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    int maxi = *max_element(a.begin(), a.end());
    dp.assign(maxi + 1, 0);

    vector<pair<int, int>> b;
    for (int i = 0; i < n; i++) {
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());

    alive.assign(n + 2, 1);  // 1-indexed
    alive[0] = 0;
    alive[n + 1] = 0;
    dp[0] = 1;
    int j = 0;
    for (int i = 1; i <= maxi; i++) {
        dp[i] = dp[i - 1];
        while (j < n && b[j].first == i) {
            int idx = b[j].second;
            alive[idx + 1] = 0;
            if (alive[idx] && alive[idx + 2]) {
                dp[i]++;
            }
            if (!alive[idx] && !alive[idx + 2]) {
                dp[i]--;
            }
            j++;
        }
    }

    for (int i = 1; i <= maxi; i++) {
        int j = 0;
        ll ans = 0;
        while (j < maxi) {
            ans += dp[j];
            j += i;
        }
        cout << ans << " ";
    }
    cout << endl;

    return 0;
}