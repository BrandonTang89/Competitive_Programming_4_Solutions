/** Hackrank - IOI 2014 Practise Contest 
 * This is a simple application of a difficult concept: Divide and Conquer optimisation of DP.
 * This technique is often seen when we need to split an array into K contiguous subarrays each with
 * a cost. See https://drive.google.com/drive/folders/1hTvkuQTgpJRWgQkdqB_WRtPMGezI2lRW for more
 * information.
 * 
 * Time: O(n*k log n), Space: O(n*k)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll INF = LONG_LONG_MAX / 10;
int L, G;
ll prefix_sum[8001], C[8001];

ll range_sum(int l, int r) {
    if (l == 0) return prefix_sum[r];
    return prefix_sum[r] - prefix_sum[l - 1];
}

ll cost(int l, int r) {  // O(1) to compute the cost of a single grouping
    return (range_sum(l, r) * (r - l + 1));
}

ll memo[8001][801], opt[8001][801];
/*
ll dp(int n, int k){ // cost with n inmates left and k guards, O(n^2*k) Naive DP
    if (k == 1) return cost(0, n-1);
    if (n == 0) return 0;
    if (memo[n][k] != -1) return memo[n][k];

    ll ans = INF;
    for (int i=0; i<n; i++){ // i is how many left, minimum one per group
        ans = min(ans, dp(i, k-1) + cost(i, n-1));
    }
    // cout << n << " " << k << " " << ans << endl;

    return memo[n][k] = ans;
}*/

// Works because opt(m-1, k) <= opt(m, k) for all m, k ie monotonicity condition is met
// s, e: dnc(s, e, ...) fills up dp[s..e][k], ie they are the range that we supposed to fill up
// x, y are the start and end of the search space for the optimal dividing point, ie x <= opt[s..e][k] <= y
void dnc(int s, int e, int x, int y, int k) { // O(n*k log n) Divide and Conquer DP
    int m = (s + e) / 2;
    memo[m][k] = INF;
    for (int i = x; i <= y; i++) {  // compute dp[m][k], opt[m][k]
        if (memo[m][k] > memo[i][k - 1] + cost(i, m - 1)) {
            memo[m][k] = memo[i][k - 1] + cost(i, m - 1);
            opt[m][k] = i;
        }
    }
    if (s < m) dnc(s, m - 1, x, opt[m][k], k);
    if (m < e) dnc(m + 1, e, opt[m][k], y, k);
}

int main() {
    memset(memo, -1, sizeof memo); 
    cin >> L >> G;
    for (int i = 0; i < L; i++) cin >> C[i];

    prefix_sum[0] = C[0];
    for (int i = 1; i < L; i++) prefix_sum[i] = prefix_sum[i - 1] + C[i];

    for (int i=0; i<=L;i++){
        memo[i][1] = cost(0,i-1); 
    }
    for (int i = 2; i <= G; i++) { // bottom up calculation through G layers
        dnc(0, L, 0, L, i);
    }

    cout << memo[L][G]<< endl;
    return 0;
}