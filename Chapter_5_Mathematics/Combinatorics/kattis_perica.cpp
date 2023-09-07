/**Kattis - perica
 * Quite a simple counting problem. The key observations that counting is much easier if we just
 * sort the values first. Then for value v[i] (0th index), the contribution is v[i] * comb(i, k-1)
 * which fixes v[i] as the largest value then selects k-1 other smaller or equal values from the
 * left. If you think for a bit, you'll realise that duplicate values are also still dealt with
 * correctly.
 * 
 * Time: O(n (k + log n)), Space: O(nk)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll MOD = 1e9 + 7;
ll memo_comb[100001][51];
ll comb(int n, int r)
{
    if (r == 0 || n == r) return 1;
    if (n < r) return 0;
    if (memo_comb[n][r] != -1) return memo_comb[n][r];
    return memo_comb[n][r] = (comb(n - 1, r - 1) + comb(n - 1, r)) % MOD;
}
vector<ll> v;
int main()
{
    fast_cin();
    int n, k;
    memset(memo_comb, -1, sizeof(memo_comb));
    cin >> n >> k;
    v.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    sort(v.begin(), v.end());

    ll ans = 0;
    for (int i = k - 1; i < n; i++) {
        ans += (v[i] * comb(i, k - 1)) % MOD;
        ans %= MOD;
    }
    cout << ans << endl;

    return 0;
}