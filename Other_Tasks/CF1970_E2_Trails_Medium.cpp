/**CF1970 E2
 * Let dp(u, v, daysLeft) = number of ways to walk from u to v with daysLeft days left.
 * We can compute this faster by using dp(u, v, k) = sum(dp(u, w, d/2) * dp(w, v, d-d/2) for all w),
 * i.e. we iterate over all middle cabins w.
 *
 * This could have been better implemented in a manner similar to that of
 * CF1970_C3_Game_on_Tree_Hard.cpp, i.e. similar to repeated squaring exponentiation, rather than
 * doing all the bit math and 2x DPs done here.
 *
 * Tim: O(m^3 log n), Space:O(m^2 log n)
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
vector<vector<vector<ll>>> memo;
#define LSOne(S) ((S) & -(S))

ll dp(int u, int v, int k)
{  // returns the number of ways to walk assuming needs to walk from u to v with 2^k days left
    if (memo[u][v][k] != -1) return memo[u][v][k];
    ll ans = 0;
    if (k == 0) {  // 1 day left
        ans += (s[u] * (l[v] + s[v])) % MOD;
        ans += (l[u] * s[v]) % MOD;
        return memo[u][v][k] = ans;
    }

    for (int w = 0; w < m; w++) {
        ans += dp(u, w, k - 1) * dp(w, v, k - 1);
        ans %= MOD;
    }

    return memo[u][v][k] = ans;
}

vector<vector<vector<ll>>>
    memo2;  // memo[u][v][q] = number of ways to walk from u to v with n truncated to have q bits on
ll dp2(int u, int v, int days)
{
    if (memo2[u][v][__builtin_popcount(days)] != -1) return memo2[u][v][__builtin_popcount(days)];
    if (days == 0) return memo2[u][v][0] = (u == v);

    ll partDays = LSOne(days);
    ll remainingDays = days - partDays;
    ll ans = 0;
    for (int w = 0; w < m; w++) {
        ans += dp(u, w, __builtin_ctz(partDays)) * dp2(w, v, remainingDays);
        ans %= MOD;
    }
    return memo2[u][v][__builtin_popcount(days)] = ans;
}

int main()
{
    fast_cin();
    cin >> m >> n;
    s.resize(m);
    l.resize(m);
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> l[i];
    }

    memo.assign(m, vector<vector<ll>>(m, vector<ll>(33, -1)));
    memo2.assign(m, vector<vector<ll>>(m, vector<ll>(33, -1)));

    ll ans = 0;
    int u = 0;
    for (int v = 0; v < m; v++) {
        ans += dp2(u, v, n);
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}