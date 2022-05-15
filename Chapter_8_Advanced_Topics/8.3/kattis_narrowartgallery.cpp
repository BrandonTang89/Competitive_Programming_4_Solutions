/**Kattis - narrowartgallery
 * Relatively simple DP problem. The interesting part is representing the previous row as a "bitmask" number
 * in the range [0,2] such that it represents either both open, right closed or left closed respectively.
 * 
 * Time: O(n*k), Space: O(n*k)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


int INF = 1e9;
int n, k;
pair<int, int> values[201];

int memo[201][3][201];
int dp(int row, int prev_row, int k_left){ // 0 -> both open, 1 -> right close , 2 -> left closed
    if (row == n)return (k_left == 0 ? 0 : -INF);
    if (memo[row][prev_row][k_left] != -1)return memo[row][prev_row][k_left];
    if (k_left == 0){
        return memo[row][prev_row][k_left] = dp(row+1, 0, 0) + values[row].first + values[row].second;
    }

    int ans = dp(row+1, 0, k_left) + values[row].first + values[row].second; // dont close anything

    // Close left (not possible if prev_row == 1)
    if(prev_row == 0 || prev_row == 2){
        ans = max(ans, dp(row+1, 2, k_left-1) + values[row].second);
    }
    if(prev_row == 0 || prev_row == 1){
        ans = max(ans, dp(row+1, 1, k_left-1) + values[row].first);
    }

    return memo[row][prev_row][k_left] = ans;
}

int main(){
    cin >> n >> k; 
    int a, b;
    for (int i=0; i<n; i++){
        cin >> a >> b;
        values[i] = {a, b};
    }

    memset(memo, -1, sizeof memo);
    cout << dp(0, 0, k) << endl;
    return 0;
}