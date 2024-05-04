/**CF1970 G2
 * Observe that we will need to build (number of CC - 1) new edges between the CCs but we have the
 * freedom the choose how to connect them.
 *
 * We find all the bridges of each connected component (CC), then we try using each bridge as the
 * bridge between the 2 complexes We assign the other CCs to either side of the bridge via a
 * knapsack style DP.
 *
 * Also consider edge case where the edge between complexes is an edge between CCs rather than a
 * bridge within a CC.
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

typedef vector<int> vi;

int n, e, u, v, dfs_num_counter, dfs_root, root_children;
vi adjlist[301], dfs_parent, dfs_num, dfs_low;

ll newedgecost, ccIndex;
vector<int> ccSize;
vector<vector<pair<int, int>>> ccBridges;

void articulation_point_and_bridge(int u)
{
    dfs_num[u] = dfs_num_counter++;
    dfs_low[u] = dfs_num[u];

    ccSize[ccIndex]++;
    for (int v : adjlist[u]) {
        if (dfs_num[v] == -1) {  // tree edge
            dfs_parent[v] = u;
            if (u == dfs_root) {  // special case, root
                root_children++;
            }

            articulation_point_and_bridge(v);
            if (dfs_low[v] > dfs_num[u]) {
                ccBridges[ccIndex].emplace_back(u, v);
            }

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u]) {  // back edge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

vector<int> visited;
int dfs(int u)
{  // returns the size of the connected component
    visited[u] = 1;
    int ans = 1;
    for (int v : adjlist[u]) {
        if (visited[v]) continue;
        ans += dfs(v);
    }
    return ans;
}

int bridgeCC;
vector<vector<ll>> memo;
ll dp(int complexSize, int curcc)
{
    if (memo[complexSize][curcc] != -1) return memo[complexSize][curcc];
    if (curcc == ccIndex) {
        ll c2 = n - complexSize;
        if (c2 == 0 || complexSize == 0) return memo[complexSize][curcc] = 1e18;
        return memo[complexSize][curcc] =
                   complexSize * complexSize + c2 * c2 + newedgecost * (ccIndex - 1LL);
    }

    if (curcc == bridgeCC)
        return memo[complexSize][curcc] =
                   dp(complexSize, curcc + 1);  // cannot repeat the CC the bridge is in

    ll ans = min(dp(complexSize + ccSize[curcc], curcc + 1), dp(complexSize, curcc + 1));
    return memo[complexSize][curcc] = ans;
}

int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> e >> newedgecost;
        for (int i = 0; i < n; i++) adjlist[i].clear();
        dfs_parent.assign(n, -1);
        dfs_num.assign(n, -1);  // -1 for unvisited
        dfs_low.assign(n, 0);
        dfs_num_counter = 0;
        ccSize.clear();
        ccBridges.clear();
        ccIndex = 0;

        // Load undirected graph
        for (int i = 0; i < e; i++) {
            cin >> u >> v;
            u--;
            v--;
            adjlist[u].emplace_back(v);
            adjlist[v].emplace_back(u);
        }

        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == -1) {
                // new cc
                ccSize.emplace_back(0);
                ccBridges.push_back({});
                dfs_root = i;
                root_children = 0;
                articulation_point_and_bridge(i);
                ccIndex++;
            }
        }

        if (ccIndex == 1 && (int)ccBridges[0].size() == 0) {  // only 1 CC with no bridges
            cout << -1 << endl;
            continue;
        }

        // ccIndex = number of connected components
        vector<vector<pair<int, int>>> bridgeDivSizes =
            vector<vector<pair<int, int>>>(ccIndex, vector<pair<int, int>>());
        for (int c = 0; c < ccIndex; c++) {
            for (auto &[u, v] : ccBridges[c]) {
                visited.assign(n, 0);
                visited[u] = visited[v] = 1;
                int size1 = dfs(u);
                int size2 = dfs(v);
                bridgeDivSizes[c].emplace_back(size1, size2);
            }
        }

        ll ans = 1e18;
        for (int c = 0; c < ccIndex; c++) {
            bridgeCC = c;
            for (auto &[size1, size2] : bridgeDivSizes[c]) {
                memo.assign(n + 1, vector<ll>(ccIndex + 1, -1));
                ans = min(ans, dp(size1, 0));
            }
        }

        memo.assign(n + 1, vector<ll>(ccIndex + 1, -1));
        bridgeCC = -1;  // don't use an existing bridge
        ans = min(ans, dp(0, 0));

        cout << ans << endl;
    }
}
