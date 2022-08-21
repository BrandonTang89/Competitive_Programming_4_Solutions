/**Kattis - test2
 * Relatively simple SCC question, we just need to print out all the SCCs, in sorted order. The only
 * issue is that some of the letters within [A, Z] are not actual nodes. As such, we need to avoid
 * printing those in the output.
 * 
 * Time: O(E + V log V), Spac : O(E + V) 
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int t, n, e, u, v, dfsNumberCounter, numSCC;
vi dfs_num, dfs_low, visited, scc_index;
stack<int> st;
vector<vector<int>> adjlist;
vector<unordered_set<int>> adjlist_dag;

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter;
    dfsNumberCounter++;
    st.push(u);
    visited[u] = 1;

    for (int v : adjlist[u]) {
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
            scc_index[v] = numSCC;  // use numSCC as a counter
            if (v == u) break;
        }
        numSCC++;
    }
}

int main() {
    while (true) {
        cin >> e;
        if (e == 0) {
            break;
        }

        n = 26;
        // Reset Variables
        unordered_set<char> activities;
        scc_index.assign(n, 0);
        dfs_num.assign(n, -1);
        dfs_low.assign(n, 0);
        visited.assign(n, 0);
        adjlist.assign(n, vector<int>());
        dfsNumberCounter = numSCC = 0;
        while (!st.empty()) st.pop();

        // Parse input graph
        for (int i = 0; i < e; i++) {
            vector<int> cur_activities(5);
            for (int j = 0; j < 5; j++) {
                char c;
                cin >> c;
                cur_activities[j] = c - 'A';
                activities.insert(c);
            }
            char u;
            cin >> u;
            for (int j = 0; j < 5; j++) {
                if (cur_activities[j] != u - 'A') {
                    adjlist[u - 'A'].push_back(cur_activities[j]);
                }
            }
        }

        // Colour nodes according to the SCC they belong to
        for (int i = 0; i < n; i++) {
            if (dfs_num[i] == -1) tarjanSCC(i);
        }

        vector<vector<char>> sccs(numSCC);
        for (int i = 0; i < n; i++) {
            sccs[scc_index[i]].push_back(i + 'A');
        }
        for (int i = 0; i < numSCC; i++) {
            sort(sccs[i].begin(), sccs[i].end());
        }
        sort(sccs.begin(), sccs.end());

        // Print output
        for (int i = 0; i < numSCC; i++) {
            if ((int)sccs[i].size() == 1 && activities.find(sccs[i][0]) == activities.end()) {
                continue;
            }
            for (int j = 0; j < (int)sccs[i].size(); j++) {
                cout << sccs[i][j] << " ";
            }
            cout << endl;
        }

        cout << endl;
    }
}