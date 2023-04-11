/**Kattis - joggers
 * Minimum vertex cover on a tree. First we need to establish the boundaries of the tree, so we do a
 * DFS and record the distance from the source. Now if dist[u] >= 2*s then we will not need to use
 * the edges between u and its children so we treat u as a leaf, else we will need to cover the
 * edges between u and its children so u is an internal vertex. Then we just do the regular minimum
 * vertex cover DP with the extra modification that some nodes are already pre-lit.
 * 
 * Time: O(V), Mem: O(V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, s;
vector<vector<tuple<int, int>>> adjlist;

vector<int> dist;
void dfs(int u)
{
    for (auto [v, w] : adjlist[u]) {
        if (dist[v] > dist[u] + w) {
            dist[v] = dist[u] + w;
            dfs(v);
        }
    }
}

vector<int> pre_lit;
vector<vector<int>> memo;  // minimum lanterns to light the subtree rooted at u
int dp(int u, int prev_lit)
{
    if (memo[u][prev_lit] != -1) return memo[u][prev_lit];
    int &ans = memo[u][prev_lit];

    if (dist[u] * 2 >= s) return (ans = (prev_lit || pre_lit[u] ? 0 : 1));  // leaf

    // try lighting u
    ans = 0;
    for (auto [v, w] : adjlist[u]) {
        if (dist[v] == dist[u] + w) {  // child
            ans += dp(v, 1);
        }
    }
    ans += (pre_lit[u] ? 0 : 1);

    if ((!prev_lit) || pre_lit[u]) return ans;  // need to light u

    // try not lighting u
    int ans2 = 0;
    for (auto [v, w] : adjlist[u]) {
        if (dist[v] == dist[u] + w) {  // child
            ans2 += dp(v, 0);
        }
    }
    ans = min(ans, ans2);

    return ans;
}
int main()
{
    cin >> n >> s;
    adjlist.assign(n, vector<tuple<int, int>>());
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }
    dist.assign(n, 1e8);
    dist[0] = 0;
    dfs(0);

    memo.assign(n, vector<int>(2, -1));
    pre_lit.assign(n, 0);

    int l;
    cin >> l;
    while (l--) {
        int u;
        cin >> u;
        u--;
        pre_lit[u] = 1;
    }

    cout << dp(0, 1) << endl;

    return 0;
}