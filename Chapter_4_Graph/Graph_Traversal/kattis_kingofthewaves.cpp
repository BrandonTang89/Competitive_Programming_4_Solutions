/**Kattis - kingofthewaves
 * Very similar to kattis-pearwise, just that this time we need to print the actual solution. Use the
 * same idea, construct the DFS spanning tree from node 0 and then traverse the tree from the furtherest
 * depth node back up the tree, once we exhaust all the nodes at a depth, we call on the parent of the
 * current king, causing us to move one depth upwards.
 * 
 * Time: O(V + E), Space: O(V^2)
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

int n, max_depth = 0;
vector<vector<int>> adjmat, nodes_at_depth;
vector<int> parent, depth;
int total_visited = 0;

void dfs(int u) {
    total_visited++;
    for (int v = 0; v < n; v++) {
        if (adjmat[u][v] == 0) continue;
        if (parent[v] == -1) {
            parent[v] = u;
            depth[v] = depth[u] + 1;
            if (depth[v] > max_depth) max_depth = depth[v];
            nodes_at_depth[depth[v]].push_back(v);
            dfs(v);
        }
    }
}
int main() {
    cin >> n;
    parent.assign(n, -1);
    depth.assign(n, 0);
    nodes_at_depth.assign(n, vector<int>());
    adjmat.assign(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c;
            cin >> c;
            if (i == j) {
                adjmat[i][j] = 0;
            } else {
                adjmat[i][j] = c - '0';
            }
        }
    }

    parent[0] = 0;
    depth[0] = 0;
    nodes_at_depth[0].push_back(0);
    dfs(0);

    if (total_visited != n) {
        cout << "impossible" << endl;
        return 0;
    }

    vector<int> visited(n, 0);
    int king = nodes_at_depth[max_depth].back();
    visited[king] = 1;
    cout << king << " ";

    for (int d = max_depth; d >= 0; d--) {
        for (int i = 0; i < (int)nodes_at_depth[d].size(); i++) {
            if (visited[nodes_at_depth[d][i]]) continue;
            int u = nodes_at_depth[d][i];
            cout << u << " ";
            if (adjmat[u][king]) {
                king = u;
            }
        }

        if (d == 0) break;
        king = parent[king];
        visited[king] = 1;
        cout << king << " ";
    }

    return 0;
}