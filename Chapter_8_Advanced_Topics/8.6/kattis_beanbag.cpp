/**Kattis - beanbag
 * This is kinda like a novel dp problem. The key observations is that we can assume the
 * farmers will agree on a set S of beans to be given freely. S must fufil the condition
 * that it has a non-empty intersection with the sets of beans each farmer has. We can thus
 * try all possible set S and check which results in the highest cost for jack. Doing
 * a 2^n filter search is possible but might TLE. Thus we use DP with recursive backtracking.
 * Essentially for each next farmer, we see if he has a bean in S. If so then just move to the
 * next farmer, else we try adding each of the beans he has. We use a bunch of bitwise operations
 * to improve speed.
 *
 * Time: O(n*m * 2^n). Note that the true value is much less since transitions are usually much less
 * than O(n) because after a bean is added, it never needs to be added in again.
 * Space: O(m * 2^n)
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

int n, m;  // num beans, num farmers
int INF = 1e8;
vector<int> required, farmer_mask;
int memo[101][(1 << 20)];
int hardest_set(int idx, int mask) {
    if (idx == m) {
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!(mask & (1 << i))) ans += required[i];
        }
        return ans;
    }
    if (memo[idx][mask] != -1) return memo[idx][mask];
    if (mask & farmer_mask[idx])
        return memo[idx][mask] = hardest_set(idx + 1, mask);  // dont need additional beans

    int ans = -INF;
    int bm = farmer_mask[idx];
    while (bm) {
        int i = __builtin_ctz(bm);
        bm -= (1 << i);
        ans = max(ans, hardest_set(idx + 1, mask | (1 << i)));
    }
    return memo[idx][mask] = ans;
}
int main() {
    cin >> n;
    required.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> required[i];
    }
    cin >> m;
    farmer_mask.assign(m, 0);
    for (int i = 0; i < m; i++) {
        int k, bean;
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> bean;
            farmer_mask[i] |= (1 << (bean - 1));
        }
    }
    memset(memo, -1, sizeof memo);
    cout << hardest_set(0, 0) << endl;
    return 0;
}