/**Kattis - keyboardconcert
 * let dp(i, k) be the number of switches needed assuming we need to play the ith note next, we are
 * currently on k. If we can play ith note on instrument k, we should just do so since there is no
 * disadvantage in doing so. Else, we try switching to all other instruments that can play note i
 * and take the minimum.
 * 
 * Time: O(n^2 * m), Space: O(nm)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, m, k;
set<int> s[1001];  // s[note] = {instumentst that play note}

int song[1001];
int memo[1001][1001];
int dp(int i, int k) {
    if (i == m) return 0;                     // if we have played all notes, we are done
    if (memo[i][k] != -1) return memo[i][k];  // if we have already computed this, return it
    if (s[song[i]].count(k)) {
        return memo[i][k] = dp(i + 1, k);  // if we can play the ith note on instrument k, we can
                                           // play the next note on instrument k
    }
    // we need to switch
    int ans = INT_MAX;
    for (int instrument : s[song[i]]) {
        ans = min(ans, dp(i + 1, instrument) + 1);
    }
    return memo[i][k] = ans;
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int l;
            cin >> l;
            s[l].insert(i);
        }
    }
    for (int i = 0; i < m; i++) {
        cin >> song[i];
    }
    memset(memo, -1, sizeof memo);
    int ans = INT_MAX;
    for (int instrument : s[song[0]]) {
        ans = min(ans, dp(1, instrument));
    }
    cout << ans << endl;

    return 0;
}