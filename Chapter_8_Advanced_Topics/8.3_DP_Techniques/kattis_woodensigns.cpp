/**Kattis - woodensigns
 * Mostly reading comprehension. Let dp(i, prev_flat) be the number of ways assuming that the next
 * sign to place has the basis of the arrowhead at v[i] and the prev sign has the flat part at
 * prev_flat. We can recover the position of the previous arrowhead basis as v[i-1] and then split
 * into the cases where the new arrowhead falls within the range of the previous sign, left of the
 * previous sign, or right of the previous sign.
 * 
 * Also remember to do the modulo stuff. 
 * 
 * Time: O(n^2), Mem: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<ll> v;
vector<vector<ll>> memo;
const ll MOD = 2147483647LL;
ll dp(ll i, ll prev_flat)
{
    if (i == n) return 1;
    if (memo[i][prev_flat] != -1) return memo[i][prev_flat];

    ll prev_head = v[i - 1];

    ll l = min(prev_head, prev_flat);
    ll r = max(prev_head, prev_flat);

    if (l <= v[i] && v[i] <= r)
        return memo[i][prev_flat] = (dp(i + 1, l) + dp(i + 1, r)) % MOD;
    else if (v[i] < l)
        return memo[i][prev_flat] = dp(i + 1, r) % MOD;
    else
        return memo[i][prev_flat] = dp(i + 1, l) % MOD;
}
int main()
{
    cin >> n;
    v.assign(n, 0);
    memo.assign(n + 2, vector<ll>(n + 2, -1));
    int prev_flat;
    cin >> prev_flat;
    for (int i = 0; i < n; i++) cin >> v[i];
    cout << dp(1, prev_flat) << endl;

    return 0;
}