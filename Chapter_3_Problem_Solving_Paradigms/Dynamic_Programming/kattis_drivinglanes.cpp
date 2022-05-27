/**Kattis - drivinglanes
 * A dp with somewhat complex transition and basecase functions. We let the state be (the index of
 * current straightway, current lane) with dp(sw, lane) = minimum cost assuming we are currently at
 * the beginning of sw and are at lane lane. The base case is reaching the end, in this case, we
 * need to move back to the first lane at all costs. If that's not possible, return INF. The
 * transition involves trying increasingly further lanes from the current lane.
 *
 * Time: O(n m^2), Space: O(nm)
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

int n, m, k, r;
const int INF = 1e9;
vector<int> straightways;
vector<pair<int, int>> curves;  // stretch, curvature
ll memo[251][251];
ll dp(int sw, int lane) {
    if (sw == n - 1) {
        // much change back to lane 1!
        int lane_change_amt = lane - 1;
        if (k * lane_change_amt > straightways[n - 1]) return INF;
        return r * lane_change_amt + straightways[n - 1];
    }
    if (memo[sw][lane] != -1) return memo[sw][lane];

    ll ans = INF;
    for (int i = 0; lane + i <= m || lane - i >= 1; i++) {
        if (k * i > straightways[sw]) break;  // not enough dist to change lanes
        if (lane + i <= m) {
            ans = min(ans, dp(sw + 1, lane + i) + r * i + straightways[sw] + curves[sw].first +
                               curves[sw].second * (lane + i));
        }
        if (lane - i >= 1 && i != 0) {
            ans = min(ans, dp(sw + 1, lane - i) + r * i + straightways[sw] + curves[sw].first +
                               curves[sw].second * (lane - i));
        }
    }
    return memo[sw][lane] = ans;
}
int main() {
    cin >> n >> m >> k >> r;
    memset(memo, -1, sizeof memo);
    straightways.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> straightways[i];
    }
    curves.resize(n);
    for (int i = 0; i < n - 1; i++) {
        cin >> curves[i].first >> curves[i].second;
    }

    cout << dp(0, 1) << endl;
    return 0;
}