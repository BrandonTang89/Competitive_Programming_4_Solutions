/**Kattis - cartrouble
 * Simply DFS from node 0 to determine all the nodes reachable from node 0. DFS from node 0 in the
 * transposed graph to determine all the nodes which have no path from themselves to 0 (trapped).
 * Note that the ID's are not necessarily 0 to n-1, so just account for that.
 * 
 * Time: O(V + E), Space: O(1001 + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adjlist, adjlistT;
vector<int> visited, order_of_nodes;

void dfs(int u, vector<vector<int>> &AL) {
    visited[u] = 1;
    for (int v : AL[u]) {
        if (!visited[v]) {
            dfs(v, AL);
        }
    }
}
int main() {
    cin >> n;
    adjlist.assign(1001, vector<int>());
    adjlistT.assign(1001, vector<int>());
    for (int i = 0; i < n; i++) {
        int u, e;
        cin >> u >> e;
        order_of_nodes.push_back(u);
        for (int j = 0; j < e; j++) {
            int v;
            cin >> v;
            adjlist[u].push_back(v);
            adjlistT[v].push_back(u);
        }
    }

    bool problem = false;
    visited.assign(1001, 0);
    dfs(0, adjlistT);
    for (auto i : order_of_nodes) {
        if (!visited[i]) {
            cout << "TRAPPED " << i << endl;
            problem = true;
        }
    }
    visited.assign(1001, 0);
    dfs(0, adjlist);
    for (auto i : order_of_nodes) {
        if (!visited[i]) {
            cout << "UNREACHABLE " << i << endl;
            problem = true;
        }
    }

    if (!problem) {
        cout << "NO PROBLEMS" << endl;
    }

    return 0;
}