/* Kattis - canonical
This is a pretty fun question that calls for you to implement both the dp and greedy solutions for coin change.
While memorising previously computed solutions is something associated with dp solutions, we also need to do
the same for the greedy algorithm since we are going to be calling our greedy algorithm many times. 

Time: O(n * (sum of max 2 denominations))
Mem: O(n * (sum of max 2 denominations))
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, v;
vector<int>coins;
int memo[(int) 2e6 + 9];
int greedy_memo[(int) 2e6 + 9][101];

int dp(int val){ // minimum number of coins to constuct val
    if (val == 0)return 0;
    if (val < 0)return (int) 1e9;

    int &ans = memo[val];
    if (ans != -1)return ans; //calculated before
    
    ans = val; // since smallest possible denonation is 1, max ans = val
    for (int i=0;i<n;i++){
        ans = min(ans, 1+dp(val - coins[i]));
    }
    return ans; 
}

int greedy(int val, int index){
    if (val == 0)return 0;
    int &ans = greedy_memo[val][index];
    if (ans != -1)return ans;
    if (coins[index] > val){
        return ans = greedy(val, index-1);
    }
    return ans = 1 + greedy(val-coins[index], index);
}

int main(){
    fast_cin();
    memset(memo, -1, sizeof(memo));
    memset(greedy_memo, -1, sizeof(greedy_memo));
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> v;
        coins.emplace_back(v);
    }

    int max_val = coins[coins.size()-1] + coins[coins.size()-2];
    bool canonical = true;
    for (int i=2;i<max_val;i++){
        if (dp(i) != greedy(i, n-1)){
            //printf("i: %d, dp(i):%d, greedy(i): %d\n", i, dp(i), greedy(i, n-1));
            canonical = false;
            break;
        }
    }

    cout << (canonical ? "canonical" : "non-canonical") << endl;
    return 0;
}