#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);


ll n;
unordered_map<ll, vector<ll>> adjlist;
vector<ll> arr;

unordered_set<ll> visited;

ll dfs(ll u){
    if (visited.find(u) != visited.end()) return 0;
    visited.insert(u);
    ll ans = u;
    for (auto v : adjlist[u]){
        assert(v > u);
        ans = max(ans, dfs(v));
    }
    return ans;
}
int main(){
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--){
        cin >> n;
        arr.assign(n, 0);
        adjlist.clear();
        adjlist.reserve(n);
        visited.clear();

        cin >> arr[0];
        for (int i = 1; i < n; i++){
            cin >> arr[i];
            ll x = n - i;
            ll y = arr[i] - x;

            if (y >= 0){
                adjlist[y].push_back(y+i);
            }
        }

        ll ans = dfs(0) + n;
        cout << ans << endl;
        
    }

    return 0;
}