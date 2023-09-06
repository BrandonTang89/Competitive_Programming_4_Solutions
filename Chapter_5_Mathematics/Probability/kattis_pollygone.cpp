/**Kattis - pollygone
 * Relatively straightforward knapsack like problem. Let dp(cur, p) = the minimum energy required to
 * get p probability using only boxes [cur..n-1]. The transition is to either check the box or not
 * check the box. We notice that all probabilities are only to 4 dp so we can multiply everything by
 * 10000 and round to the nearest integer. Note the reason for +0.1 is to achieve this rounding
 * effect.
 *
 * Time: O(n*10000), Mem: O(n*10000)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<int> ps;
vector<int> es;

vector<vector<int>> memo;
int dp(int cur, int p)
{
    if (p <= 0) return 0;      // no more energy required
    if (cur == n) return 1e8;  // no more boxes available

    if (memo[cur][p] != -1) return memo[cur][p];

    return memo[cur][p] = min(dp(cur + 1, p), dp(cur + 1, p - ps[cur]) + es[cur]);
}
int main()
{
    fast_cin();
    double initp;
    cin >> n >> initp;
    ps.resize(n);
    es.resize(n);
    memo.assign(n, vector<int>(10001, -1));
    for (int i = 0; i < n; i++) {
        double p;
        cin >> es[i] >> p;
        ps[i] = (p * 10000 + 0.1);
    }

    int ans = dp(0, (initp * 10000 + 0.1));
    cout << ans << endl;

    return 0;
}