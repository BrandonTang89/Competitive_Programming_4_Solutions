/**Kattis - goingdutch
 * First observe that the person to person transfers don't really matter, we just record whether
 * each person has a positive negative or zero balance. Then we can just try to group people into
 * small groups such that the sum of each group's balance is 0. For a group of size k, we will need
 * k-1 transactions (all just pay/get paid their balances to 1 person). So what we are really trying
 * to do is to maximise the number of groups we split the n people into.
 *
 * We can generate all such groups by checking 2^n subsets. This results in a DP state of O(2^n)
 * and a transition time of O(2^n). But a key observation is that groups A and B are valid and group
 * A is a subset of group B then group B is actually useless since this implies the existance of a
 * group B\A that is also valid (so choosing A and B\A is better than choosing B). And so we can
 * actually prune off supersets.
 *
 * Furthermore, for each state in the DP, instead of trying any random valid group, we look for
 * groups that contain the LSB of the state. This reduces the search space for possible transitions
 * to those groups that have the LSB of the state as the smallest element. The smallest element part
 * comes from the fact that we will not want groups that have elements smaller than the LSB since
 * the definition of LSB implies that it should be the smallest of any group we choose.
 * 
 * Time: O(? (a lot of pruning)), Mem: O(2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define LSOne(S) (S & (-S))
int n, m;
vector<int> arr;
vector<vector<int>> pruned_bms;

vector<int> memo;
int dp(int bm)
{
    if (memo[bm] != -1) return memo[bm];
    if (bm == 0) return 0;
    int ans = 1e8;

    for (auto new_group : pruned_bms[__builtin_ctz(bm)]) {
        if ((bm & new_group) != new_group) continue;  // not a subset
        ans = min(ans, dp(bm - new_group) + __builtin_popcount(new_group) - 1);
    }

    return memo[bm] = ans;
}
int main()
{
    cin >> n >> m;
    arr.assign(n, 0);
    memo.assign(1 << n, -1);
    pruned_bms.assign(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        arr[u] += w;
        arr[v] -= w;
    }
    vector<int> valid_bms;

    for (int i = 1; i < (1 << n); i++) {
        int bm = i;
        int cur = 0;
        while (bm) {
            int k = __builtin_ctz(bm);
            cur += arr[k];
            bm -= LSOne(bm);
        }
        if (cur == 0) {
            valid_bms.emplace_back(i);
        }
    }

    for (int i = 0; i < (int)valid_bms.size(); i++) {
        bool issuperset = false;
        // check if valid_bms[i] is a superset of any other valid bitmask
        for (int j = 0; j < (int)valid_bms.size(); j++) {
            if (i == j) continue;
            if ((valid_bms[i] & valid_bms[j]) == valid_bms[j]) {
                issuperset = true;
                break;
            }
        }
        if (!issuperset) {
            pruned_bms[__builtin_ctz(valid_bms[i])].emplace_back(valid_bms[i]);
        }
    }

    cout << dp((1 << n) - 1) << endl;

    return 0;
}