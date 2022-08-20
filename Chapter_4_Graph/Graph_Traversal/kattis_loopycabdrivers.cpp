/**Kattis - loopycabdrivers
 * A relatively straightforward problem. We do the string to index mapping to pre-process the graph,
 * do Tarjan's algorithm, then for each SCC, we determine if it is a single node or >= 2 nodes, then
 * add them to either the avoid or sccs vectors. Then we convert the indices back to strings, sort,
 * then output.
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 20009

typedef vector<int> vi;

int t, n, e, u, v, dfsNumberCounter, numSCC;
vi dfs_num, dfs_low, visited, scc_index;
stack<int> st;
vi adjlist[MAX_N];
vector<vector<int>> sccs;
vector<int> avoid;

vector<string> shops;
unordered_map<string, int> m;

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

        if (st.top() == u) {  // single things
            avoid.push_back(u);
            st.pop();
            visited[u] = 0;
            scc_index[u] = numSCC;
        } else {
            sccs.push_back(vector<int>());
            while (true) {
                v = st.top();
                st.pop();
                visited[v] = 0;
                scc_index[v] = numSCC;  // use numSCC as a counter
                sccs.back().push_back(v);
                if (v == u) break;
            }
        }
        numSCC++;
    }
}

int main() {
    cin >> e;
    int n = 0;  // num nodes
    for (int i = 0; i < e; i++) {
        string x, y;
        cin >> x >> y;
        if (m.find(x) == m.end()) {
            m[x] = n++;
            shops.push_back(x);
        }
        if (m.find(y) == m.end()) {
            m[y] = n++;
            shops.push_back(y);
        }
        adjlist[m[x]].push_back(m[y]);
    }

    // Reset Variables
    scc_index.assign(n, 0);
    dfs_num.assign(n, -1);
    dfs_low.assign(n, 0);
    visited.assign(n, 0);
    dfsNumberCounter = numSCC = 0;

    // Colour nodes according to the SCC they belong to
    for (int i = 0; i < n; i++) {
        if (dfs_num[i] == -1) tarjanSCC(i);
    }

    vector<vector<string>> sccsnames;
    for (int i = 0; i < (int)sccs.size(); i++) {
        sccsnames.push_back(vector<string>());
        for (int j = 0; j < (int)sccs[i].size(); j++) {
            sccsnames.back().push_back(shops[sccs[i][j]]);
        }
        sort(sccsnames.back().begin(), sccsnames.back().end());
    }
    sort(sccsnames.begin(), sccsnames.end());

    vector<string> avoidnames;
    for (int i = 0; i < (int)avoid.size(); i++) {
        avoidnames.push_back(shops[avoid[i]]);
    }
    sort(avoidnames.begin(), avoidnames.end());

    for (auto &scc : sccsnames) {
        cout << "okay ";
        for (auto v : scc) {
            cout << v << " ";
        }
        cout << endl;
    }
    if (avoidnames.size() > 0) {
        cout << "avoid ";
        for (auto v : avoidnames) {
            cout << v << " ";
        }
        cout << endl;
    }
}