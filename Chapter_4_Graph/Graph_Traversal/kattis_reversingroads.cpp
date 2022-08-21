/**Kattis - reversingroads
 * We first define valid(adjlist) = true if adjlist has only 1 SCC and false otherwise. We check if
 * valid(initial graph) then exit early if this is the case, else we complete search by testing e
 * other graphs (flip each edge once). This is alright since e is small (e <= 50^2).
 * 
 * Time: O(E^2), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define MAX_N 60

int t, n, e, u, v, dfsNumberCounter, numSCC;
vi dfs_num, dfs_low, visited;
stack<int> st;
vector<vector<int>> adjlist;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;
    dfsNumberCounter++;
    st.push(u);
    visited[u] = 1;

    for (auto v : adjlist[u]) {
        if (dfs_num[v] == -1) {
            tarjanSCC(v);
        }
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }

    if (dfs_low[u] == dfs_num[u]) {  // u is the root of an SCC
        while (true) {
            v = st.top();
            st.pop();
            visited[v] = 0;
            if (v == u) break;
        }
        numSCC++;
    }
}

bool only_one_scc(vector<vector<int>> &adjlist) {
    dfs_num.assign(n, -1);
    dfs_low.assign(n, 0);
    visited.assign(n, 0);
    dfsNumberCounter = numSCC = 0;
    while (!st.empty()) st.pop();
    for (int i = 0; i < n; i++) {
        if (dfs_num[i] == -1) tarjanSCC(i);
    }
    return numSCC == 1;
}

int main() {
    int tc = 0;
    while (cin >> n >> e) {
        tc++;

        adjlist.assign(n, vi());
        vector<pair<int, int>> edges;
        for (int i = 0; i < e; i++) {
            cin >> u >> v;
            adjlist[u].push_back(v);
            edges.push_back(make_pair(u, v));
        }

        if (only_one_scc(adjlist)) {
            cout << "Case " << tc << ": valid" << endl;
            continue;
        }

        bool can_be_valid = false;
        for (int i = 0; i < e; i++) {
            adjlist.clear();
            adjlist.assign(n, vi());
            for (int j = 0; j < e; j++) {
                if (i == j) {
                    adjlist[edges[j].second].push_back(edges[j].first);
                } else {
                    adjlist[edges[j].first].push_back(edges[j].second);
                }
            }
            if (only_one_scc(adjlist)) {
                can_be_valid = true;
                cout << "Case " << tc << ": " << edges[i].first << " " << edges[i].second << endl;
                break;
            }
        }
        if (!can_be_valid) {
            cout << "Case " << tc << ": invalid" << endl;
        }
    }
    return 0;
}