/**Kattis - city
 * Slightly tricky DP. Let dp(i, ld) be the minimum number of movies to destory buildings [i..n)
 * assuming that building i-1 is already destoryed iff ld == 1. Then we can either destory building
 * i completely now, or leave it just weak enough to be destroyed when building i+1 is destoryed.
 * Just work out the math of the divisions properly. Beware of edge cases where the building is just
 * completely destoryed when both the left and right buildings are destroyed..
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
ll d;
vector<vector<ll>> memo;
vector<ll> h, e;

ll dp(int i, int last_destroyed)
{
    if (i == n) return 0;
    ll &ans = memo[i][last_destroyed];
    if (ans != -1) return ans;

    ll cur_health = h[i];
    if (i > 0 && last_destroyed == 1) {
        cur_health -= e[i - 1];
    }
    if (cur_health <= 0) {
        ans = dp(i + 1, 1);
    }
    else {
        ll num_destory_completely = (cur_health - 1) / d + 1;
        assert(num_destory_completely > 0);
        ll num_destoryed_after_next_building =
            (cur_health - e[i + 1] <= 0) ? 0 : (cur_health - e[i + 1] - 1) / d + 1;
        ans = min(dp(i + 1, 1) + num_destory_completely,
                  dp(i + 1, 0) + num_destoryed_after_next_building);
    }
    return ans;
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> d;
        e.assign(n + 1, 0);
        h.assign(n + 1, 0);
        memo.assign(n, vector<ll>(2, -1));
        for (int i = 0; i < n; i++) {
            cin >> h[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> e[i];
        }
        cout << dp(0, 0) << endl;
    }

    return 0;
}