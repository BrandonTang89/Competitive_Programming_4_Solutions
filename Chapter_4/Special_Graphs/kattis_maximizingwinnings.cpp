/* Kattis - Maximizing Winnings
This is supposed to be a relatively easy DP problem. But it is easy to TLE. Note the use of a
last_used array to avoid re-initialising memo between calls of DP. This is actually (very)
important in preventing TLE. Note that we also don't need to check for if memo == -1 since
we know that the last_used array is initialised to 0 but run_counter starts from 1.

Time: O(n^2 * m), Mem: O(nm)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, turns_left, run_counter = 1;
int adjmat[51][51];
int memo[51][5001], last_used[51][5001];
int dp(int room, int turns_left, bool maxi) {
    if (turns_left == 0) {
        return 0;
    }
    if (last_used[room][turns_left] == run_counter){
        return memo[room][turns_left];
    }

    int ans;
    if (maxi){
        ans = (int) -1e9;
        for (int v = 0; v < n; v++) {
            ans = max(ans, dp(v, turns_left - 1, maxi) + adjmat[room][v]);
        }
    }
    else{ // minimise
        ans = (int) 1e9;
        for (int v = 0; v < n; v++) {
            ans = min(ans, dp(v, turns_left - 1, maxi) + adjmat[room][v]);
        }
    }
    last_used[room][turns_left] = run_counter;
    return memo[room][turns_left] = ans;
}

int main() {
    while (true) {
        scanf("%d", &n);
        if (n == 0) {
            break;
        }

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                scanf("%d", &adjmat[u][v]);
            }
        }
        scanf("%d", &turns_left);
        printf("%d ", dp(0, turns_left, 1));
        run_counter++;
        printf("%d\n", dp(0, turns_left, 0));
        run_counter++;
    }

    return 0;
}