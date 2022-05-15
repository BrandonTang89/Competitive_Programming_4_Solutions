/**Kattis - nikola
 * Relatively basic DP problem, just ensure to get the basecases and transitions down right.
 * Note that the upperbound on last_jump should be n since for all jumps > n, there are no possible
 * pairs of start and end locations to jump accross.
 * Time: O(n^2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, INF = 1e9;
vector<int> costs;
vector<vector<int>> memo;
int dp(int i, int last_jump){ // Returns the minimum cost to reach square i with last jump
    // cout << "i: " << i << " last_jump: " << last_jump << endl;
    if (i == 0 && last_jump == 0) return 0;
    if (i < 0 || i >= n) return INF;
    if (last_jump == 0) return INF;

    if (memo[i][last_jump] != -1) return memo[i][last_jump];
    memo[i][last_jump] = min(dp(i - last_jump, last_jump-1), dp(i + last_jump, last_jump)) + costs[i];
    return memo[i][last_jump];
}

int main(){
    fast_cin();
    cin >> n;
    memo.assign(n, vector<int>(n, -1));
    costs.assign(n, 0);
    for (int i=0;i <n; i++){
        cin >> costs[i];
    }

    int ans = INT_MAX;
    for (int i=1; i<n; i++){
        ans = min(ans, dp(n-1, i));
    }
    cout << ans << endl;

    return 0;
}