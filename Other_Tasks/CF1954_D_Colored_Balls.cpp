/**CF1954_D
 * Fix a subset of colours.
 * - Observe that if the largest colour is > sum of the rest of the colours then the number of
 *   groups needed is the size of the largest colour. Call these subsets Type 1.
 * - If this is not true then the number of groups required is simply ceil((totalsum)/2). Call these
 *   subsets Type 2.
 *
 * Using this idea, we first precompute for each b, the number of subsets with b balls. This is done
 * via the dp below.
 *
 * Then we assume that all subsets are Type 2 subsets. After which, we iterate over all colours, and
 * all b < a[i]. Observe that for each subset of size b, we can add a[i] to it to get a Type 1
 * subset. A key reason for this is that a[i] could not already be in the a subset with b < a[i].
 * We thus subtract from the initial counting, the effect of counting these subsets as Type 2 and
 * add to the count the effect of counting them as Type 1.
 * 
 * Time: O(n*(numballs))
 * Space: O(n*(numballs)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
ll MOD = 998244353;

vector<ll> a;
vector<vector<ll>> memo;
ll dp(int i, int b)
{  // returns the number of subsets with b balls using only colours >= i
    if (i == n && b == 0) return 1;
    if (i == n && b != 0) return 0;
    if (memo[i][b] != -1) return memo[i][b];

    if (a[i] > b) return memo[i][b] = dp(i + 1, b);
    return memo[i][b] = (dp(i + 1, b) + dp(i + 1, b - a[i])) % MOD;
}
ll dp(int b) { return dp(0, b); }

int main()
{
    cin >> n;
    const int numballs = 5001;
    memo.assign(n + 2, vector<ll>(numballs, -1));
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    ll ans = 0;

    for (int i = 0; i < numballs; i++) {
        ans = (ans + ((i + 1) / 2) * dp(0, i)) % MOD;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < a[i]; j++) {  // over all subsets that a[i] will dominate
            ans -=
                (((j + a[i] + 1) / 2) * dp(j)) % MOD;  // remove the subsets that a[i] will dominate
            ans += (a[i] * dp(j)) % MOD;               // add the subsets that a[i] will dominate
            ans = (ans + MOD) % MOD;
        }
    }

    cout << ans << endl;

    return 0;
}