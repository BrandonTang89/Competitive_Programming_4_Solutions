/* Kattis - stockbroker

Observation 1:
    When to buy/sell stocks:
        just sell everyday
        buy when the stocks the next day is higher than today
    How much to buy;
        as much as possible! (greedy)

Time: O(n), Mem: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
 
typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
 
ll n;
ll arr[370];
ll cash = 100;
int main(){
    fast_cin();
    cin >> n;
    for (int i=0;i<n;i++){
        cin >> arr[i];
    }
 
    ll own_shares = 0;
    for (int i=0;i<n-1;i++){
        cash += own_shares*arr[i];
        own_shares = 0;
        if (arr[i+1] > arr[i]){
            own_shares = min(cash/arr[i], (ll) 100000);
            cash -= (own_shares*arr[i]);
        }
    }
    cash += own_shares*arr[n-1];
    cout << cash << endl;
    
    return 0;
}