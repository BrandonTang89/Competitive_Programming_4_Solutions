/**Kattis - kingpinescape
 * The problem is to add edges to a tree such that there exist >= 2 paths between any 2 vertices, ie
 * no bridges. Observe that this can be done by finding the minimum path edge cover where a path
 * edge cover is a set of paths that cover all edges. Then we can join the 2 ends of each path. The
 * lowerbound on the minimum path edge cover is ceil(L/2) where L is the number of leaves. This is
 * because each path only covers 2 leaves, so we need minimum of ceil(L/2) paths. But is it always
 * possible to get a path edge cover of size ceil(L/2)? The answer is yes, using the following
 * algorithm.
 *
 * First we flatten the tree with DFS pre-order. However, we are only interested in the leaves, so we
 * don't need to record the internal vertices. Then sort the leaves by the pre-order number. Then
 * we pair leaf with pre-order number i with leaf with pre-order number i+L/2. We do this until we
 * are done.
 * 
 * I'm not sure why this results in a valid path cover all the time, but its AC lah
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, hq;
vector<vector<int>> adjlist;
vector<pair<int, int>> leaves;
vector<int> visited;
int leaf_counter = 0;
void dfs(int u) {
    visited[u] = 1;
    if ((int)adjlist[u].size() == 1) {
        leaves.push_back(make_pair(leaf_counter++, u));
    }

    for (int v : adjlist[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    cin >> n >> hq;
    adjlist.assign(n, vi());
    visited.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    dfs(0);

    sort(leaves.begin(), leaves.end());
    cout << ceil(leaves.size() / 2.0 - 0.1) << endl;

    for (int i = 0; i < (int)leaves.size() / 2; i++) {
        cout << leaves[i].second << " " << leaves[i + leaves.size() / 2].second << endl;
    }
    if (leaves.size() % 2 == 1) {
        cout << leaves[leaves.size() - 1].second << " " << leaves[0].second << endl;
    }

    return 0;
}