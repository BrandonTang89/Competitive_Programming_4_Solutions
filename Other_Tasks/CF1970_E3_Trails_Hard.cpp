/**CF1970 E3
 * We make the observation that we can break down the whole path into 3 sections
 * - cabin 1 to lake
 * - lake to some cabin then back to lake (n-1 times)
 * - lake to some cabin
 *
 * We can thus do DP on then number of ways to go from the lake to some cabin and back to the lake.
 * We have 4 different types of such journeys, coresponding to whether the first and last trail used
 * are short/long.
 * 
 * Time: O(m log n), Space: O(log n)
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

int m, n;
const ll MOD = 1e9 + 7;
vector<ll> s, l;

unordered_map<ll, ll> memo[4];
ll dp(int kind, ll k)
{
    assert(kind >= 0 && kind <= 3);
    // kind = 0: Short -> Short
    // kind = 1: Short -> Long
    // kind = 2: Long -> Short
    // kind = 3: Long -> Long

    if (memo[kind].find(k) != memo[kind].end()) return memo[kind][k];
    if (k == 0) return memo[kind][k] = 1;
    if (k == 1) {
        ll ans = 0;
        for (int w = 0; w < m; w++) {
            if (kind == 0)
                ans += (s[w] * s[w]) % MOD;
            else if (kind == 1)
                ans += (s[w] * l[w]) % MOD;
            else if (kind == 2)
                ans += (l[w] * s[w]) % MOD;
            else
                ans += (l[w] * l[w]) % MOD;
            ans %= MOD;
        }
        return memo[kind][k] = ans;
    }

    ll ans = 0;
    ll part, remaining;
    if (k % 2 == 0) {
        part = k >> 1;
        remaining = k - part;
    }
    else {
        part = 1;
        remaining = k - 1;
    }

    if (kind == 0) {
        ans = (dp(0, part) * dp(0, remaining)) % MOD;   // short -> short -> short -> short
        ans += (dp(1, part) * dp(0, remaining)) % MOD;  // short -> long -> short -> short
        ans += (dp(0, part) * dp(2, remaining)) % MOD;  // short -> short -> long -> short
        ans %= MOD;
    }
    else if (kind == 1) {
        ans = (dp(1, part) * dp(1, remaining)) % MOD;   // short -> long -> short -> long
        ans += (dp(0, part) * dp(3, remaining)) % MOD;  // short -> short -> long -> long
        ans += (dp(0, part) * dp(1, remaining)) % MOD;  // short -> short -> short -> long
        ans %= MOD;
    }
    else if (kind == 2) {                               // long -> short
        ans = (dp(2, part) * dp(0, remaining)) % MOD;   // long -> short -> short -> short
        ans += (dp(3, part) * dp(0, remaining)) % MOD;  // long -> long -> short -> short
        ans += (dp(2, part) * dp(2, remaining)) % MOD;  // long -> short -> long -> short
        ans %= MOD;
    }
    else {                                              // long -> long
        ans = (dp(2, part) * dp(3, remaining)) % MOD;   // long -> short -> long -> long
        ans += (dp(2, part) * dp(1, remaining)) % MOD;  // long -> short -> short -> long
        ans += (dp(3, part) * dp(1, remaining)) % MOD;  // long -> long -> short -> long
        ans %= MOD;
    }
    return memo[kind][k] = ans;
}

int main()
{
    cin >> m >> n;
    s.resize(m);
    l.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> l[i];
    }

    memo[0].clear();
    memo[1].clear();
    memo[2].clear();
    memo[3].clear();

    n -= 1;
    ll ans = 0;
    for (int last = 0; last < m; last++) {
        ans += ((s[0] * (dp(0, n) + dp(1, n) + dp(2, n) + dp(3, n))) % MOD) *
               s[last];  // short - (short || long)->(short || long) - short
        ans %= MOD;

        // long - (short)->(short || long) - short
        ans += ((l[0] * (dp(0, n) + dp(1, n))) % MOD) * s[last];
        ans %= MOD;

        // short - (short||long)->(short) - long
        ans += ((s[0] * (dp(0, n) + dp(2, n))) % MOD) * l[last];
        ans %= MOD;

        // long - (short)->(short) - long
        ans += ((l[0] * dp(0, n)) % MOD) * l[last];
        ans %= MOD;
    }

    cout << ans << endl;

    return 0;
}