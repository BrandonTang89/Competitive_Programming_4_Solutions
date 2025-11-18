#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n;
ll maxi;

constexpr ll MOD = 998244353;
vector<ll> arr;
vector<vector<ll>> memo;
ll dp(int idx, ll taken) {
    if (idx >= n) {
        if (taken < maxi)
            return 0;
        else
            return 1;
    }

    if (memo[idx][taken] != -1) return memo[idx][taken];
    ll ans = 0;
    ans += dp(idx + 1, taken);
    ans %= MOD;
    ans += (arr[idx] * dp(idx + 1, taken + arr[idx])) % MOD;
    ans %= MOD;

    return memo[idx][taken] = ans;
}
void solve() {
    cin >> n;
    arr.assign(n, 0);
    maxi = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        arr[x-1]++;
        maxi = max(maxi, arr[x-1]);
    }
    memo.assign(n + 1, vector<ll>(n + 1, -1));
    cout << dp(0, 0) % MOD << '\n';
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) solve();

    return 0;
}