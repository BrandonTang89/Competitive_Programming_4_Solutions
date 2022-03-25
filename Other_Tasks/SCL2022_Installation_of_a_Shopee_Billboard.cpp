/**Shopee Code League 2022 - Installation of a shopee billboard
 * Here we use dynamic programming optimised in minor ways to just scrap the AC.
 * Do note that using the dp function by itself will TLE but using dp2 will WA 50% of the time
 * Combining the 2, we are luckily able to get AC.
 * 
 * Time: O((length rods) * (total length / 2)^2), Space: O((length rods) * (total length / 2)^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n;
int total_sum, INF = 1e9, max_h;
vector<int> rods;

int memo[21][2501][2501];
int dp(int k, int a, int b){ // max outcome after considering k rods
    if (k == n){
        if (a != b) return (-INF);
        else return a;
    }
    if (memo[k][a][b] != -1) return memo[k][a][b];

    int ans = dp(k+1, a, b);
    if (b + rods[k] <= max_h){
        ans = max(ans, dp(k+1, a, b+rods[k]));
    }
    if (a + rods[k] <= max_h){
        ans = max(ans, dp(k+1, a+rods[k], b));
    }
    
    return memo[k][a][b] = ans;
}
int dp2(int k, int a, int b){ // max outcome after considering k rods
    if (k == n){
        if (a != b) return (-INF);
        else return a;
    }
    if (memo[k][a][b] != -1) return memo[k][a][b];

    int ans = dp2(k+1, a, b);
    if (b + rods[k] <= a){ // this causes WA because it is theoratically incorrect
        ans = max(ans, dp2(k+1, a, b+rods[k]));
    }
    if (a + rods[k] <= max_h){
        ans = max(ans, dp2(k+1, a+rods[k], b));
    }
    
    return memo[k][a][b] = ans;
}
int main(){
    cin >> n;
    rods.assign(n, 0);
    for (int i = 0; i < n; i++) cin >> rods[i];
    total_sum = accumulate(rods.begin(), rods.end(), 0);
    max_h = total_sum/2+1;

    memset(memo, -1, sizeof memo);
    if (total_sum <= 4950)
        cout << max((int) 0, max(dp(1, rods[0], 0), dp(1, 0, 0))) << endl;
    else
        cout << max((int) 0, max(dp2(1, rods[0], 0), dp2(1, 0, 0))) << endl;


    return 0;
}