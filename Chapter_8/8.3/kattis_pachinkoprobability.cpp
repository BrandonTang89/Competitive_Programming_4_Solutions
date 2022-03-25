/**Kattis - pachinkoprobability
 * A counting paths of DAG problem that is relatively easy and not to be confused with the ICPC question from
 * 2014 with a similar name (which is much more difficult).
 * 
 * Time: amortised O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e, u, v;
int num_gates;
unordered_set<int> gates, non_start_nodes;
vector<int> adjlist[1001];

pair<ll, ll> memo[1001];  // num paths, num winning paths
pair<ll, ll> dp(int u) {
    if (memo[u].first != -1) return memo[u];
    if (adjlist[u].size() == 0) {
        return {1, (gates.find(u) != gates.end())};
    }

    ll num_paths = 0, num_winning_paths = 0;
    for (int v : adjlist[u]) {
        auto [num_paths_v, num_winning_paths_v] = dp(v);
        num_paths += num_paths_v;
        num_winning_paths += num_winning_paths_v;
    }

    return memo[u] = {num_paths, num_winning_paths};
}
int main() {
    cin >> n >> e;
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        non_start_nodes.insert(v);
    }
    cin >> num_gates;
    for (int i = 0; i < num_gates; i++) {
        cin >> u;
        gates.insert(u);
    }

    for (int i = 0; i <= n; i++) {
        memo[i] = {-1, -1};
    }

    ll num_paths = 0, num_winning = 0;
    for (int i = 0; i < n; i++) {
        if (non_start_nodes.find(i) == non_start_nodes.end()) {
            num_paths += dp(i).first;
            num_winning += dp(i).second;
        }
    }

    cout << "winning paths " << num_winning << endl;
    cout << "total paths " << num_paths << endl;
    return 0;
}