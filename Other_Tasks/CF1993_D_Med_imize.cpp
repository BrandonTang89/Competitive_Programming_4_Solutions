#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, k;
constexpr int inf = 1e9;
constexpr int maxn = 5e5 + 1;
vector<int> arr;
vector<vector<int>> memo;
vector<int> suffixAtLeastX;
int totalSegments, toRemain, x;

int dp(int a, int b) {  // dp(a, b) = maximum number of additional remaining elements > = x assuming that we already have a remaining numbers and used b k segments
    if (memo[a][b] != -1) return memo[a][b];
    if (a == toRemain) return memo[a][b] = 0;  // already collected everything
    int idx = a + b * k;
    if (idx == n) return memo[a][b] = 0;  // no more able to take
    int ans = dp(a + 1, b) + (arr[idx] >= x);
    if (idx + k < n) ans = max(ans, dp(a, b + 1));

    return memo[a][b] = ans;
}

inline bool medAtLeast(int target) {  // true iff the median achieved can be at least x
    x = target;
    memo.assign(toRemain + 1, vector<int>(totalSegments + 1, -1));
    return dp(0, 0) >= (toRemain + 2) / 2;
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    arr.resize(maxn);
    suffixAtLeastX.resize(maxn);
    while (tc--) {
        cin >> n >> k;
        totalSegments = (n - 1) / k;
        toRemain = n - k * totalSegments;

        int top = 0;
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
            top = max(top, arr[i]);
        }

        int hi = top;
        int lo = 1;

        while (hi > lo) {
            int mid = (hi + lo + 1) / 2;
            if (medAtLeast(mid)) {
                lo = mid;
            } else {
                hi = mid - 1;
            }
        }

        cout << lo << endl;
    }

    return 0;
}