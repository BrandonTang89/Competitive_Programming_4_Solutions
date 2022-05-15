/**Kattis - centsavings
 * It's quite obvious that we need to use RSQ often, so we should use our static RSQ technique as a
 * pre-computation. Then its just a normal DP partitioning problem.. Gives me some Divide and
 * Conquer Optimisation PTSD but I'm not sure if it fits the optimality criteria for that (probably
 * does not). Anyway given the constraints, the following works.
 * 
 * Time: O(n^2 * d), Space: O(n*d)
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

int n, INF = 1e9, d;
vector<int> arr, ori;    // arr[i] contains the range sum from 0 to i inclusively
int rsq(int l, int r) {  // range sum from l to r inclusively
    if (l < 0 || r >= n) return -INF;
    if (l == 0) return arr[r];
    return (arr[r] - arr[l - 1]);
}

int round_to_nearest_10(int x) { return (x + 5) / 10 * 10; }
int memo[2002][21];
int dp(int idx, int k) {  // we have done idx items alr, k dividers left
    if (idx == n) return 0;
    if (memo[idx][k] != -1) return memo[idx][k];
    int &ans = memo[idx][k];
    if (k == 0) {
        return ans = round_to_nearest_10(rsq(idx, n - 1));  // buy the rest at whatever price
    }

    ans = INF;
    for (int i = idx + 1; i <= n; i++) {  // at least take 1 item
        int cur = dp(i, k - 1) + round_to_nearest_10(rsq(idx, i - 1));
        ans = min(ans, cur);
    }
    return ans;
}
int main() {
    cin >> n >> d;
    arr.resize(n);
    ori.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ori[i] = arr[i];  // only if preserving initial array
        if (i > 0) arr[i] += arr[i - 1];
    }
    memset(memo, -1, sizeof memo);
    cout << dp(0, d) << endl;

    return 0;
}