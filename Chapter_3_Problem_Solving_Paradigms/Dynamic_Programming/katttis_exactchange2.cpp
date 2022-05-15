/* Kattis - exactchange2
This question is more like a weird version of knapsack rather than coin change (since each item can only be
taken once and the total sum is not necessarily exact).

Return: Overshoot (amount above the cost that we are paying)
        Notes (number of notes used to pay)

State: id (we consider all coins with index >= id)
       value (the value we need to make)

Base cases:
        value <= 0: finished, overshoot = -val
        n == 0, val > 0: failed, return a large overshoot and notes

Transitions:
        Take coin id or leave it. Check which is better using a custom comparator function

Time: O(nc), Mem: O(nc)
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

ll n, note, c, tc;
vector<ll>notes;
pair<ll,ll> memo[109][10009]; 

bool cus_comp(pair<ll,ll> a, pair<ll,ll>b){ // outcome a better than outcome b?
    if (a.first < b.first)return true; 
    if (a.first > b.first)return false;
    
    return (a.second < b.second);
}
// memo[index][val] = min (overshoot, notes) to produce val with all note of index >= index

pair<ll,ll> dp(ll id, ll val){
    if (val <= 0)return make_pair(-val, 0);
    if (id == n)return make_pair((ll)1e9, (ll)1e9); // failed :( since val > 0 but we considered all the coins already
    
    auto &ans = memo[id][val];
    if (ans != make_pair((ll) -1, (ll) -1)) return ans;

    ans = dp(id+1, val); // dont take this
    auto alt_ans = dp(id+1, val-notes[id]);
    alt_ans = make_pair(alt_ans.first, 1 + alt_ans.second);
    if (cus_comp(alt_ans, ans)){ // check if taking it is better
        ans = alt_ans;
    }

    //printf("id: %lld, val: %lld, ans: %lld %lld\n", id, val, ans.first, ans.second);
    return ans;
}


int main(){
    fast_cin();
    cin >> tc;
    for (ll t=0;t<tc;t++){
        // reset stuff
        for (ll i=0;i<109;i++){
            for (ll j=0;j<10009;j++)
                memo[i][j] = make_pair((ll) -1, (ll) -1);
        }
        notes.clear();

        cin >> c >> n;
        for (ll i=0;i<n;i++){
            cin >> note;
            notes.emplace_back(note);
        }

        auto sol = dp(0, c);
        cout << c + sol.first << " " << sol.second << endl;
    }
    

   return 0;
}