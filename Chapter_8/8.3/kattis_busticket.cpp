/**Kattis - busticket
 * A relatively simple DP + binary search problem. state is just the number of trips finished,
 * then transition is either buy a single pass ticket or a period ticket. Use binary search
 * to determine the first subsequent trip not covered by the period ticket.
 *
 * Time: O(n log n), Space: O(n)
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

ll s, p, m, n;
vector<ll> t;

ll memo[1000009];
ll dp(int k) {  // price assuming we have done k trips
    if (k >= n) return 0;
    if (memo[k] != -1) return memo[k];

    ll ans = dp(k + 1) + s;  // buy a single bus ticket
    // buy a period ticket

    ll last_day = t[k] + m - 1;
    int new_k = upper_bound(t.begin() + k + 1, t.end(), last_day) - t.begin();
    ans = min(ans, dp(new_k) + p);

    return memo[k] = ans;
}
int main() {
    fast_cin();
    cin >> s >> p >> m >> n;
    t.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    memset(memo, -1, sizeof memo);

    cout << dp(0) << endl;

    return 0;
}