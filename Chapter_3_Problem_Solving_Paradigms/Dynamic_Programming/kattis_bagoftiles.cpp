/**Kattis - bagoftiles
 * Relatively simple problem despite the high difficulty rating. Rather than coin change, it is more
 * similar to knapsack since each tile is only either used or not used, but we are finding the
 * number of ways instead of some max value. So we use DP to find the number of ways to get the
 * target. Then we use dp n choose r to find the total number of ways, we calculate the number of ways
 * to lose as the difference between these 2 values. 
 * 
 * Time: O(nmt), Space: O(nmt)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int num_tc, m, n, t;
vector<int> v;
ll memo[31][31][10009];
ll dp(int index, int n_left, int t_left){ // returns the number of ways 
    if (n_left == 0 && t_left == 0) return 1;
    if (n_left <= 0 || t_left <= 0) return 0; // Not enough tiles or overshoot
    if (index >= m) return 0; // Not enough tiles

    ll &ans = memo[index][n_left][t_left];
    if (ans != -1) return ans;

    ans = dp(index + 1, n_left, t_left) + dp(index + 1, n_left - 1, t_left - v[index]);
    return ans;
}

// DP n choose k
ll memo_comb[31][31];
ll comb(int n, int r){
    if (r == 0 || n == r) return 1;
    if (n < r) return 0;
    if (memo_comb[n][r] != -1) return memo_comb[n][r];
    return memo_comb[n][r] =  comb(n - 1, r - 1) + comb(n - 1, r);
}


int main(){
    fast_cin();
    memset(memo_comb, -1, sizeof memo_comb);
    cin >> num_tc;
    for (int tc=1; tc<=num_tc; tc++){
        cin >> m;
        v.resize(m);
        for (int i = 0; i < m; i++) cin >> v[i];
        memset(memo, -1, sizeof memo);
        cin >> n >> t;
        printf("Game %d -- %lld : %lld\n", tc, dp(0, n, t), comb(m, n) - dp(0, n, t));
    }
    return 0;
}