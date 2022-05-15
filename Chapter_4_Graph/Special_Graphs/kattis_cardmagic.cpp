/* Kattis - Card Magic
 * https://open.kattis.com/problems/cardmagic

Easy DP problem that took me way to f**king long to solve due to bugs. It was some stupid shit
about the memo table being too small........ like bruh

Time: O(nkt), Mem: O(tn)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int MOD = 1000000009;
int n, k, t;
int memo[5009][101]; // target, num decks left

// returns the number of ways to construct num_left using aint decks from [pos, n-1]
int dp(int num_left, int pos){
    if (pos == n-1) return (num_left >0 && num_left <= k) ? 1 : 0;
    if (memo[num_left][pos] != -1) return memo[num_left][pos];

    int ans = 0;
    for (int i = 1; i <= min(k, num_left); i++){
        ans += (dp(num_left - i, pos + 1));
        ans = ans%MOD;
    }
    //printf("num_left: %d, pos: %d, ans: %intd\n", num_left, pos, ans);
    return memo[num_left][pos] = ans;
}
int main(){
    fast_cin();
    memset(memo, -1, sizeof(memo));
    cin >> n >> k >> t;

    cout << dp(t, 0) << endl;
    return 0;
}