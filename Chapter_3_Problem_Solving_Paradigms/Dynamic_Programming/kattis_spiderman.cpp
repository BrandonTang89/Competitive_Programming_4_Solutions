#pragma GCC optimize("Ofast")
/**Kattis - spiderman
 * DP with printing optimal solution. We let the state be (index of climb to consider, height before
 * climb index). The transitions are to climb up or down v[i] height. Note that the maximum
 * height attainable will be <= 1000.
 * 
 * Time: O(n*1000), Space: O(n*1000)
 */
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

const int INF = (int)1e9;
int num_tc, n;
vector<int> v;
vector<vector<int>> memo;
int dp(int i, int h){ 
    // minimum building height to go from index i to index n, at height h when considering i
    // cout << "i: " << i << " h: " << h << endl;
    if (i == n){
        if (h == 0)return 0;
        else return INF;
    }
    if (h < 0)return INF;

    if (memo[i][h] != -1)return memo[i][h];
    memo[i][h] = min(dp(i+1, h+v[i]), dp(i+1, h-v[i]));
    memo[i][h] = max(h, memo[i][h]);

    return memo[i][h];
}

void getpath(int i, int h){
    if (i == n) return;
    if (h < 0)return;

    if (dp(i+1, h+v[i]) < dp(i+1, h-v[i])){
        cout << "U";
        getpath(i+1, h+v[i]);
    }
    else{
        cout << "D";
        getpath(i+1, h-v[i]);
    }
}

int main(){
    cin >> num_tc;
    for (int tc=0; tc<num_tc;tc++){
        cin >> n;
        memo.assign(n, vector<int>(1009, -1));
        v.assign(n, 0);
        for (int i=0; i<n; i++){
            cin >> v[i];
        }

        if (dp(0, 0) == INF){
            cout << "IMPOSSIBLE" << endl;
        }
        else{
            //cout << dp(0, 0) << endl;
            getpath(0, 0);
            cout << endl;
        }

    }

    return 0;
}