/**CF1960 G1
 * Here we just root the tree at any vertex and count the size of each subtree.
 * For each edge of the tree, we can use this information to determine the size of the 2 connected
 * components that the edge bridges
 * 
 * Time: O(V), Space: O(V)
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

ll n, m, c;
vector<vector<int>> adjlist;
vector<ll> subtreeSize, visited, parent;
int dfs(int u)
{
    visited[u] = 1;
    subtreeSize[u] = 1;
    for (int v : adjlist[u]) {
        if (visited[v]) continue;
        parent[v] = u;
        subtreeSize[u] += dfs(v);
    }
    return subtreeSize[u];
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> m >> c;
        assert(m == n - 1);

        adjlist.assign(n, vector<int>());
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        subtreeSize.assign(n, 0);
        visited.assign(n, 0);
        parent.assign(n, -1);
        dfs(0);

        ll ans = 1e18;
        for (int i = 0; i < n; i++) {
            if (parent[i] != -1) {
                ans = min(ans, subtreeSize[i] * subtreeSize[i] +
                                   (n - subtreeSize[i]) * (n - subtreeSize[i]));
            }
        }
        cout << ans << endl;
    }

    return 0;
}