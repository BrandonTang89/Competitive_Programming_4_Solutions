/** Shopee Code League 2021 Question 1
 * A simple dynamic programming question. State: last day, ending position. Transition: try to come from same side,
 * going any number of steps or from the other side taking all the flowers. 
 * 
 * Time: O(nm), Space: O(nm)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int t, n, m;
ll fruits [1001][1001];
// let dp[i]][j] be the maximum points after day i, ending at j = 0 or 1
ll dp[1001][2];

ll dynamic(int day, int pos){ 
    //printf("day: %d, pos: %d\n", day, pos);
    if (day == -1 && pos == 0) return 0; // havent gotten any yet
    if (day == -1 && pos == 1) return (ll) INT_MIN; // INF because impossible to be at the opposite end
    
    ll &ans = dp[day][pos];
    if (ans != -1) return ans;

    ans = dynamic(day-1, pos); // worse outcome is don't move
    ll cur_add = 0;
    if (pos == 0){
        for (int i=0;i<m; i++){ 
            cur_add += fruits[day][i];
            ans = max(ans, cur_add + dynamic(day-1, 0));
        }
        ans = max(ans, cur_add + dynamic(day-1, 1));
    }
    else{ // go from the right side
        for (int i=m-1;i>=0; i--){ 
            cur_add += fruits[day][i];
            ans = max(ans, cur_add + dynamic(day-1, 1));
        }
        ans = max(ans, cur_add + dynamic(day-1, 0));
    }

    return ans;
}
int main(){
    cin >> t;
    for (int tc=0; tc<t;tc++){
        cin >> n >> m;
        memset (dp, -1, sizeof(dp));

        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++){
                cin >> fruits[i][j];
            }
        }
        cout << max(dynamic(n-1, 0), dynamic(n-1, 1)) << endl;

    }
    return 0;
}