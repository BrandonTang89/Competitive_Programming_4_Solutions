#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
vector<vector<int>> heights;
vector<vector<ll>> memo;
vector<ll> costs;
constexpr ll inf = 1e18;
ll dp(int idx, int prev_up) {
    if (idx == n) return 0;
    if (memo[idx][prev_up] != -1) return memo[idx][prev_up];
    if (idx == 0) return min(dp(idx + 1, 0), dp(idx + 1, 1) + costs[idx]);

    // we need to check if we can no upgrade this current row
    bool same_can = true;
    for (int c = 0; c < n; c++) {
        if (heights[idx][c] == heights[idx - 1][c] + prev_up) {
            same_can = false;
            break;
        }
    }

    bool up_can = true;
    for (int c = 0; c < n; c++) {
        if (heights[idx][c] + 1 == heights[idx - 1][c] + prev_up) {
            up_can = false;
            break;
        }
    }

    if (same_can && up_can) {
        return memo[idx][prev_up] = min(dp(idx + 1, 0), dp(idx + 1, 1) + costs[idx]);
    } else if (same_can) {
        return memo[idx][prev_up] = dp(idx + 1, 0);
    } else if (up_can) {
        return memo[idx][prev_up] = dp(idx + 1, 1) + costs[idx];
    } else {
        return memo[idx][prev_up] = inf;
    }
}

void solve() {
    cin >> n;
    heights.assign(n, vector<int>(n));
    memo.assign(n, vector<ll>(2, -1));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> heights[i][j];
        }
    }

    costs.assign(n, 0);
    for (auto &x : costs) {
        cin >> x;
    }

    ll ans = dp(0, 0);

    // transpose the matrix
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(heights[i][j], heights[j][i]);
        }
    }

    memo.assign(n, vector<ll>(2, -1));
    for (auto &x : costs) {
        cin >> x;
    }

    ans += dp(0, 0);
    cout << (ans >= inf ? -1 : ans) << '\n';
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) solve();
}