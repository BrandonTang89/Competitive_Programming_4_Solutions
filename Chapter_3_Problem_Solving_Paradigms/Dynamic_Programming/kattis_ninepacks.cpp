/**Kattis-  ninepacks
 * Somewhat interesting 0-1 knapsack variant. Let dp(i, j, diff) be the minimum number of packs we
 * need to buy to get diff to be 0 where diff is the difference between the total number of hot dogs
 * and buns already selected. Then we have that if diff < 0, we should take more buns (increase j)
 * and if diff > 0, we should take more hot dogs (increase i). But we don't need to take the
 * immediate next bun or hotdog, we can choose to either take it to change diff, or not take it and
 * just increase i or j respectively.
 *
 * Note that we actually offset diff by 1000 to account for negative values. Also we cannot just
 * call dp(0, 0, 1000) since that would just return 0. We assume that the first hotdog taken is i
 * and get the min of dp(i, 0, 1000-a[i])+1 for all possible first hotdogs i.
 *
 * Time: O(a_amt * b_amt * 2000), Space: O(a_amt * b_amt * 2000)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int INF = 1e9, b_amt, a_amt;
vector<int> a, b;
int memo[101][101][2002];
int dp(int i, int j, int diff) {
    if (diff == 1000) return 0;
    if (diff < 1000 && j >= b_amt) return INF;
    if (diff > 1000 && i >= a_amt) return INF;

    if (memo[i][j][diff] != -1) return memo[i][j][diff];
    if (diff < 1000) {  // we need take from b pile
        return memo[i][j][diff] = min(dp(i, j + 1, diff + b[j]) + 1, dp(i, j + 1, diff));
    } else {
        return memo[i][j][diff] = min(dp(i + 1, j, diff - a[i]) + 1, dp(i + 1, j, diff));
    }
}
int main() {
    cin >> a_amt;
    a.resize(a_amt);
    for (int i = 0; i < a_amt; i++) {
        cin >> a[i];
    }
    cin >> b_amt;
    b.resize(b_amt);
    for (int i = 0; i < b_amt; i++) {
        cin >> b[i];
    }
    memset(memo, -1, sizeof memo);

    int ans = INF;
    for (int i = 0; i < a_amt; i++) {
        // assume the first a item is i
        ans = min(ans, dp(i + 1, 0, 1000 - a[i]) + 1);
    }
    if (ans == INF) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}