/**vjudge - UVA-348
 * Find the optimal way to perform matrix chain multiplication. Classic DP + print solution.
 * For each (i, j) we try to split at all possible splitting points and get the minimum
 * number of operations.
 * 
 * Time: O(n^3), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

int n;
vector<pair<int, int>> mats;

vector<vector<int>> memo;
int dp(int l, int r){
    if (l == r)return 0;
    if (memo[l][r] != -1)return memo[l][r];

    int ans = INT_MAX;
    for (int k=l; k<r; k++){ // we do until k
        ans = min(ans, dp(l, k) + dp(k+1, r) + mats[l].first * mats[k].second * mats[r].second);
    }
    return memo[l][r] = ans;
}

string get_solution(int l, int r){
    if (l == r)return "A" + to_string(l+1);
    for (int k=l; k<r; k++){ // we do until k
        if (dp(l, k) + dp(k+1, r) + mats[l].first * mats[k].second * mats[r].second == dp(l, r)){
            return "(" + get_solution(l, k) + " x " + get_solution(k+1, r) + ")";
        }
    }
    assert(false);
}
int main(){
    int x, y;
    for (int tc=1; ;tc++){
        cin >> n;
        if (n==0)break;
        mats.clear();
        memo.assign(n, vector<int>(n, -1));
        for (int i=0; i<n; i++){
            cin >> x >> y;
            mats.emplace_back(x,y);
        }

        cout << "Case " << tc << ": " <<  get_solution(0, n-1) << endl;
    }

    return 0;
}