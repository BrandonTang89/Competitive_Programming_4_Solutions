/**Kattis - bridgeautomation
 * I found this quite hard. We let dp(i, k) be the minimum time wasted assuming the ith boat crosses
 * starting at time b[i] + k (boat i waits k seconds).
 *
 * We can observe that dp(i, k) = min(close_bridge, open_bridge)
 * where close_bridge is the minimum time wasted if we close to bridge to allow cars to cross and
 * open_bridge is the minimum time wasted if leave the bridge open to boats.
 *
 * close_bridge = min(140 + dp(i + 1, j)) for all j such that the time difference is >= 140
 * open_bridge = min(td + dp(i + 1, j)) for all j such that td (time_difference) >= 20
 *
 * Doing the DP naively results in O(N*1800^2) time complexity. We can do better by observing that
 * we can update dp(i, k) in decreasing k, and update close_bridge and open_bridge in O(1) time
 * apart from k = 1800.
 *
 * First we make the observation that to keep things simpler, we can set
 * close_bridge = min(140 + dp(i + 1, j)) for all j such that the time difference is >= 20 <---
 * open_bridge = min(td + dp(i + 1, j)) for all j such that td (time_difference) >= 20
 *
 * This in theory doesn't make sense since we can't close the bridge if we don't have enough time to
 * close then reopen it. However, we note that if the eventual min(close_bridge, open_bridge) value
 * is from a j such that 20 <= td < 140, we would be taking the value from open_bridge since td <
 * 140 so it doesn't really matter and makes life simpler by looking at the same values of j.
 *
 * Now to update open_bridge, we start by incrementing it by 1 since all values of td would increase
 * by 1 on a decrease of j by 1. The minimum j for open_bridge won't change since all dp(i + 1, j)
 * are constant. Then we check if there is a new j that is valid. Since the new j wouldn't have been
 * valid before, the time difference must be exactly 20 so we can calculate this value of j
 *
 * int j = 20 + k + b[i] - b[i + 1];
 *
 * And check if it is within the right range (i.e. just >= 0). If so then we update open_bridge
 * and close_bridge.
 *
 * open_bridge = min(open_bridge, 20 + dp(i + 1, j))
 * close_bridge = min(close_bridge, 140 + dp(i + 1, j))
 *
 * To deal with the k=1800 case, we simply check all j decreasing order and as long as the td >= 20,
 * we update open_bridge and close_bridge.
 *
 * The basecase is just dp(n-1, k) = 20 for all k since we just wait 20 seconds to cross. Also at
 * the end we should add 120 since we need to open the bridge to boats before the first one and
 * close it after the last one. So our answer is min(dp(0, k)) + 120.
 *
 * Time: O(N * 1800), Mem: O(1800)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<vector<int>> memo;
vector<int> b;
int main()
{
    cin >> n;
    memo.assign(2, vector<int>(1801, -1));  // max waiting time 1800, min is 0
    b.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    for (int i = 0; i < 1801; i++) {
        memo[(n - 1) & 1][i] = 20;
    }

    for (int i = n - 2; i >= 0; i--) {
        int k = 1800;
        int min_var = INT_MAX;
        int min_const = INT_MAX;
        for (int j = 1800; j >= 0; j--) {
            int td = b[i + 1] + j - b[i] - k;  // time difference
            if (td < 20) break;
            min_const = min(min_const, memo[(i + 1) & 1][j] + 140);  // 20 to cross and 120 to wait
            min_var = min(min_var, memo[(i + 1) & 1][j] + td);       // td to cross and wait
        }
        memo[i & 1][k] = min(min_const, min_var);
        for (int k = 1799; k >= 0; k--) {
            min_var++;
            int j = 20 + k + b[i] - b[i + 1];
            assert(j <= 1800);
            if (j >= 0) {  // time difference of exactly 20
                min_var = min(min_var, memo[(i + 1) & 1][j] + 20);
                min_const = min(min_const, memo[(i + 1) & 1][j] + 140);
            }
            memo[i & 1][k] = min(min_const, min_var);
        }
    }
    int ans = INT_MAX;
    for (int i = 0; i < 1801; i++) {
        ans = min(ans, memo[0][i]);
    }
    cout << ans + 120 << endl;

    return 0;
}