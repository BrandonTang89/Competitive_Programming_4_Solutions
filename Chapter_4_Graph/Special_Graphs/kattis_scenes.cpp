/* kattis - scenes
This is a count path of DAG question that is also solvable using DP, we'll just use DP cos its 
easier for me. Also its my first time using Githubcopilot, its interesting lah. Idk how useful it'll be
but nice to try

Time: O(nwh), Memory: O(nw) (nw state space, O(h) transition)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, w, h;
const int MOD = (int)1e9 + 7;
int memo[10005][105];
// returns the number of ways to fill the frame with length_left ribbon, next at mountain at pos
int dp(int length_left, int pos){ 
    if (length_left < 0) return 0;
    if (pos == w){
        //printf("pos is w-1, length_left: %d\n", length_left);
        return 1;
    }
    int &ans = memo[length_left][pos];
    if (ans != -1) return ans;

    ans = 0;
    for (int i = 0; i <= h; i++){
        // next mountain of height i
        ans += dp(length_left - i, pos + 1);
        ans %= MOD;
    }
    
    //printf("length_left: %d, pos:%d, ans: %d\n", length_left, pos, ans);
    return ans;
}
int main(){
    fast_cin();
    cin >> n >> w >> h;
    memset(memo, -1, sizeof memo);
    int ans = dp(n, 0);
    for (int i=0;i<=h;i++){
        if (i*w <= n){
            ans -= 1;
        }
    }
    ans %= MOD;
    cout << ans << endl;

    return 0;
}