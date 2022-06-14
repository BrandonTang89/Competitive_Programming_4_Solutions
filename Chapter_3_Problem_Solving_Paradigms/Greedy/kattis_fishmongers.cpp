/**Kattis - fishmongers
 * Quite easy to see greedy: just sell the highest weight fish to the highest paying fishmonger then repeat.
 * 
 * Time: O(n log n + m log n), Space: O(n + m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, m;
vector<ll> fish; // weight of each fish
vector<pair<ll, ll>> mongers; // {price, weight}
int main(){
    fast_cin();
    cin >> n >> m;
    fish.resize(n);
    for(int i = 0; i < n; i++) cin >> fish[i];
    mongers.resize(m);
    for(int i = 0; i < m; i++) cin >> mongers[i].second >> mongers[i].first;

    sort(fish.begin(), fish.end(), greater<int>());
    sort(mongers.begin(), mongers.end(), greater<pair<int, int>>());

    ll ans = 0;
    int monger_id = 0;
    for (auto i: fish) {
        ans += i * mongers[monger_id].first;
        mongers[monger_id].second--;
        if (mongers[monger_id].second == 0) monger_id++;
        if (monger_id == m) break;
    }
    cout << ans << endl;


    return 0;
}