/** CF1970 E1
 * Use dp(daysleft, cabin) to compute the number of ways to do the trails assuming we are walking
 * for daysleft days and start from cabin cabin.
 *
 * Time: O(n m^2), Space: O(n m)
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
vector<ll> s, l;
vector<vector<ll>> memo;
const ll MOD = 1e9 + 7;
ll nshort = 0, nlong = 0;
ll dp(int daysLeft, int cabin)
{  // returns the number of ways to walk assuming needs to walk for daysleft from cabin
    if (memo[daysLeft][cabin] != -1) return memo[daysLeft][cabin];
    if (daysLeft == 0) return memo[daysLeft][cabin] = 1;

    ll ans = 0;
    for (int v = 0; v < m; v++) {
        ans += (s[cabin] * ((l[v] + s[v]) * dp(daysLeft - 1, v)) % MOD) % MOD;
        ans += (l[cabin] * (s[v] * dp(daysLeft - 1, v)) % MOD) % MOD;
    }
    ans %= MOD;
    return memo[daysLeft][cabin] = ans;
}
int main()
{
    fast_cin();
    cin >> m >> n;
    s.resize(m);
    l.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
        nshort += s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> l[i];
        nlong += l[i];
    }

    memo.assign(n + 1, vector<ll>(m, -1));
    cout << dp(n, 0) << endl;

    return 0;
}