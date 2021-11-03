/* Kattis - catenyms
A somewhat standard Eulerian path problem. Just note to sort the adjacency list lexicograhically
before we start the algorithm.

Observation 1:
    We model each word u____v as an edge from u to v. There are thus 26 nodes with n edges in a
    non-simple graph. We are trying to find an eulerian path within the graph. Check for both
    cycles and non-cycles.

Time: O(V + E), Space: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
int num_tc, e, u, v, n = 26;
string s;
vector<pair<string, int>> adjlist[26];
vi in_deg, out_deg;

vector<pair<string, int>> hierholzer(int s) {
    vi idx(n, 0);
    vector<pair<string, int>> st;
    vector<pair<string, int>> ans;  // edge visiting, node
    st.emplace_back("-", s);
    while (!st.empty()) {
        auto &[edge, u] = st.back();
        if (idx[u] < (int)adjlist[u].size()) {  // still has neighbor
            st.push_back(adjlist[u][idx[u]]);
            ++idx[u];
        } else {
            ans.push_back(make_pair(edge, u));
            st.pop_back();
        }
    }

    reverse(ans.begin(), ans.end());
    if ((int)ans.size() != e + 1) {  // Eulerian path/cycle doesn't exist
        return vector<pair<string, int>>();
    }

    return ans;
}

int main() {
    cin >> num_tc;
    for (int t = 0; t < num_tc; t++) {
        cin >> e;
        for (int i = 0; i < n; i++) adjlist[i].clear();
        in_deg.assign(n, 0);
        out_deg.assign(n, 0);
        for (int i = 0; i < e; i++) {
            cin >> s;
            u = s[0] - 'a';
            v = s.back() - 'a';
            adjlist[u].push_back(make_pair(s, v));
            in_deg[v]++;
            out_deg[u]++;
        }
        for (int i = 0; i < 26; i++) {
            sort(adjlist[i].begin(), adjlist[i].end());
        }

        // Check if there is a Eulerian path
        int potential_start = 0, potential_end = 0, equal_in_out = 0;
        int start_node = 0, equal_node = -1;
        for (int i = 0; i < 26; i++) {
            if (in_deg[i] + 1 == out_deg[i]) {
                potential_start++;
                start_node = i;
            }
            if (in_deg[i] == out_deg[i] + 1) {
                potential_end++;
            }
            if (in_deg[i] == out_deg[i]) {
                equal_in_out++;
                // to know which node is part of the cycle
                if (in_deg[i] > 0 && equal_node == -1) {  // start from the earliest possible node
                    equal_node = i;
                }
            }
        }

        vector<pair<string, int>> ans;
        if (equal_in_out == n) {  // eulerian cycle present
            ans = hierholzer(equal_node);
        } else if (potential_start == 1 && potential_end == 1 &&
                   equal_in_out == n - 2) {  // eulerian path present
            ans = hierholzer(start_node);
        }

        if (ans.size() == 0) {
            cout << "***" << endl;
            continue;
        }

        for (int i = 1; i < (int)ans.size() - 1; i++) {
            cout << ans[i].first << ".";
        }
        cout << ans.back().first << endl;
    }

    return 0;
}