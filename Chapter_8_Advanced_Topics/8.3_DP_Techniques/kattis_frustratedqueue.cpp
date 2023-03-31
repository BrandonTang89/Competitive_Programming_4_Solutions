/**Kattis - frustratedqueue
 * Relatively simple DP problem with recovering some parameters. Let dp(i, k) be the number of ways
 * assuming that we are allocating the ith character and we have k ( left. We can recover the
 * parameter of how many ) left by doing n - i - k. We can also recover the number of unclosed open
 * brackets by doing num_close - k.
 *
 * From here, if we are fixed, just try putting a ( or a ) [according to the constraints]. Else, put
 * either a ( or a ) if it is possible to do so and recurse.
 *
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

string s;
int n;
const int MOD = 1e6;
vector<vector<int>> memo;
int dp(int i, int k)
{  // index, number of ( left
    if (i == n) {
        assert(k == 0);
        return 1;
    }
    if (memo[i][k] != -1) return memo[i][k];
    int num_close = n - i - k;
    int num_pending = num_close - k;
    assert(num_pending >= 0);
    if (s[i] == '(') {
        if (k == 0) return 0;  // not possible
        return dp(i + 1, k - 1);
    }
    if (s[i] == ')') {
        if (num_close == 0 || num_pending == 0) return 0;  // not possible
        return dp(i + 1, k);
    }

    // s[i] == '.'
    int ans = 0;
    if (k > 0) ans += dp(i + 1, k - 1);
    if (num_close > 0 && num_pending > 0) ans += dp(i + 1, k);
    ans %= MOD;
    return memo[i][k] = ans;
}
int main()
{
    while (cin >> s) {
        n = s.size();
        memo.assign(n, vector<int>(n, -1));
        cout << dp(0, n / 2) << endl;
    }

    return 0;
}