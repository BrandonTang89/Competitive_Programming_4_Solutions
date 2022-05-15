/**Kattis - globalwarming
 * The key insight is that the graph given is a bunch of disjoint cliques. Due to the constraint on
 * the number of edges, the maximum clique size is 22. Within each clique, we should try doing
 * minimum weight perfect matching, this is done with O(n^2 * 2^n) dp. So how do we put these 2
 * ideas together? Essentially for each unvisited node, process the clique is it belongs to and flag
 * all the other nodes in that clique as visited. Note that the only case where it is impossible is
 * when there exists at least 1 odd sized clique.
 * 
 * Time: O(22^2 * 2^22)  in the worst case where all the nodes are in 1 clique
 * Space: O(22^2 * 2^22 + V + E);
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
#define LSOne(S) (S & (-S))

int n, e;
vector<vector<ll>> adjmat;
vector<vector<pair<int, ll>>> adjlist;  // index, weight
vector<ll> memo;
vector<bool> used;
ll dp(int mask) {
    ll &ans = memo[mask];
    if (ans != -1) return ans;
    if (mask == 0) return 0;
    ans = 1e9;
    int two_pow_p1 = LSOne(mask);
    int p1 = __builtin_ctz(two_pow_p1);
    int m = mask ^ two_pow_p1;
    while (m) {
        int two_pow_p2 = LSOne(m);
        int p2 = __builtin_ctz(two_pow_p2);
        m ^= two_pow_p2;
        ans = min(ans, dp(mask ^ two_pow_p2 ^ two_pow_p1) + adjmat[p1][p2]);
    }
    return ans;
}
ll minimum_weight_perfect_matching(int u) {  // process the clique containing u
    used[u] = true;
    vector<int> clique = {u};
    for (auto i : adjlist[u]) {
        clique.push_back(i.first);
        used[i.first] = true;
    }

    if (clique.size() % 2) {
        return -1;  // odd clique size
    }

    adjmat.assign(clique.size(), vector<ll>(clique.size(), 1e9));
    for (int i = 0; i < (int)clique.size(); i++) {
        for (int j = i + 1; j < (int)clique.size(); j++) {
            for (auto k : adjlist[clique[i]]) {
                if (k.first == clique[j]) {
                    adjmat[i][j] = adjmat[j][i] = k.second;
                    break;
                }
            }
        }
    }

    memo.assign(1 << clique.size(), -1);
    return dp((1 << clique.size()) - 1);
}
int main() {
    cin >> n >> e;
    adjlist.assign(n, vector<pair<int, ll>>());
    used.assign(n, false);
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    bool valid = true;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        if (used[i]) continue;
        ll cur = minimum_weight_perfect_matching(i);
        if (cur == -1) {
            valid = false;
            break;
        }
        ans += cur;
    }

    if (valid) {
        cout << ans << endl;
    } else {
        cout << "impossible" << endl;
    }

    return 0;
}