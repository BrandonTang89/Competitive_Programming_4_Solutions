#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, m;
ll k;
vector<int> arr;
vector<int> brr;
vector<array<int, 2>> memo;

int dp(int i, int avail) {
    if (memo[i][avail] != -1) return memo[i][avail];
    if (i == n) {
        if (avail == 0 || brr[m - 1] > k)
            return memo[i][avail] = m;
        else
            return memo[i][avail] = m - 1;
    }

    int ans = 1e9;
    if (avail == 1) {
        // we try to use the magic flower now
        int j = dp(i, 0);
        if (j == 0) return memo[i][avail] = 0;
        if (brr[j - 1] <= k) {
            // we can use the flower
            ans = min(ans, j - 1);
        }
    }
    // don't worry about the flower
    int j = dp(i + 1, avail);
    if (j == 0) return memo[i][avail] = 0;
    if (brr[j - 1] <= arr[i]) {
        ans = min(ans, j - 1);
    } else {
        ans = min(ans, j);
    }
    return memo[i][avail] = ans;
}

bool canDo(ll mid) {
    k = mid;
    memo.assign(n + 1, {-1, -1});
    return dp(0, 1) == 0;
}

void solve() {
    cin >> n >> m;
    arr.resize(n);
    for (auto &x : arr) cin >> x;
    brr.resize(m);
    for (auto &x : brr) cin >> x;

    constexpr ll inf = 1e18;
    ll lo = 0, hi = inf;

    while (lo < hi) {
        ll mid = (lo + hi) / 2;
        if (canDo(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    if (lo == inf) {
        cout << -1 << endl;
    } else {
        cout << lo << endl;
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        solve();
    }

    return 0;
}