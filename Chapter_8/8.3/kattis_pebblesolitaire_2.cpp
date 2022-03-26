/**Kattis - pebblesolitaire
 * This is an interesting DP problem because there's no "basecase". But infinite recursion is prevented
 * since we will not conitnue with dp when theres no more possible moves for a given mask. 
 * 
 * Time: O(23 * 2^23), Space: O(2^23)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int memo[(1 << 23) + 9];
int dp(int mask) {  // minimum possible number of pebbles after an arbitary number of moves
    if (memo[mask] != -1) return memo[mask];

    int ans = __builtin_popcount(mask);
    for (int i = 0; i < 23; i++) {
        if (mask & (1 << i)) {
            // try to move left and move right
            if (i >= 2 && (mask & (1 << (i - 1))) && (!(mask & (1 << (i - 2))))) {
                ans = min(ans, dp(mask ^ (1 << i) ^ (1 << (i - 1)) ^ (1 << (i - 2))));
            }
            if (i <= 20 && (mask & (1 << (i + 1))) && (!(mask & (1 << (i + 2))))) {
                ans = min(ans, dp(mask ^ (1 << i) ^ (1 << (i + 1)) ^ (1 << (i + 2))));
            }
        }
    }
    return memo[mask] = ans;
}
int main() {
    int n;
    string s;
    cin >> n;
    memset(memo, -1, sizeof memo);
    for (int i = 0; i < n; i++) {
        cin >> s;
        int bm = 0;
        for (auto c : s) {
            bm *= 2;
            bm += (c == 'o');
        }

        cout << dp(bm) << endl;
    }

    return 0;
}