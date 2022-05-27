/**Kattis - debugging
 * Let the state be the number of lines left. Then the transition is to divide the lines into
 * d partitions with almost equal number of lines. This leads to ceil(n/d) lines being left in
 * the worst case scenario. The base case is when there are no or 1 line(s) left.
 * This dp looks like it would TLE since theres a for loop of n iterations. But its
 * actually not that bad, this is because we only call about sqrt(n) smaller instances of dp.
 *
 * Time: O(n sqrt n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int N, R, P;
ll INF = 1e18;
ll memo[(int)1e6 + 1];
ll dp(int n) {
    if (n <= 1) return 0;
    if (memo[n] != -1) return memo[n];

    ll ans = INF;
    int prev = 0;
    for (int d = 2; d <= n; d++) {  // actually O(sqrt(n))
        int cur = ceil(n / (double)d);
        if (cur == prev) continue;
        prev = cur;

        ans = min(ans, (ll)(d - 1) * P + dp(cur));
    }
    assert(ans != INF);
    return memo[n] = ans + R;
}
int main() {
    cin >> N >> R >> P;
    memset(memo, -1, sizeof memo);
    cout << dp(N) << endl;
    return 0;
}