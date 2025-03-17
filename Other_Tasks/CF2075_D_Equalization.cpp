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

// vector<vector<vector<ll>>> memo;
ll memo[70][70][70][64];
ll dp(ll cur_lcp, ll a_left, ll b_left, ll next) {
    if (memo[cur_lcp][a_left][b_left][next] != -1) return memo[cur_lcp][a_left][b_left][next];
    if (a_left == b_left && a_left <= cur_lcp) return memo[cur_lcp][a_left][b_left][next] = 0;  // we can just skip the rest

    ll ans = 1e18;
    if (next + 1 <= 63) {
        ans = min(ans, dp(cur_lcp, a_left, b_left, next + 1));  // skip this one
        ans = min(ans, dp(cur_lcp, max(0LL, a_left - next), b_left, next + 1) + (1LL << next));
        ans = min(ans, dp(cur_lcp, a_left, max(0LL, b_left - next), next + 1) + (1LL << next));
    }
    return memo[cur_lcp][a_left][b_left][next] = ans;
}

int main() {
    int tc;
    cin >> tc;
    memset(memo, -1, sizeof(memo));
    while (tc--) {
        ll x, y;
        cin >> x >> y;

        // we find the longest common prefix of x and y in binary
        int xlen, ylen;
        if (x == 0)
            xlen = 0;
        else
            xlen = 64 - __builtin_clzll(x);

        if (y == 0)
            ylen = 0;
        else
            ylen = 64 - __builtin_clzll(y);

        ll lcp = 0;
        for (int i = 0; i < min(xlen, ylen); i++) {
            bool bitx = (x & (1LL << (xlen - 1 - i))) > 0;
            bool bity = (y & (1LL << (ylen - 1 - i))) > 0;
            if (bitx == bity)
                lcp++;
            else
                break;
        }

        // cerr << "lcp: " << lcp << endl;
        // cerr << "xlen: " << xlen << " ylen: " << ylen << endl;
        // memo.assign(xlen + 2, vector<vector<ll>>(ylen + 2, vector<ll>(max(xlen, ylen) + 5, -1)));
        cout << dp(lcp, xlen, ylen, 1) << endl;
    }

    return 0;
}