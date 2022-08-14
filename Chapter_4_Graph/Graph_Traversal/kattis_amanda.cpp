/**Kattis - amanda
 * Lowkey a long problem. For all the edges with 0 or 2, we can directly apply the edge and check if
 * this causes any issues. Else, for all edges with only 1 on each side, we add it to an adjacency
 * list. Then for each node with either mandatory a lounge or mandatory no lounge, we do a DFS from
 * it, colouring the graph as we go, checking if it is bipartite. There might still be some
 * uncoloured connected components at this point, so we DFS those from any point, 2 colouring them
 * as we go. If at any point, our graph is not 2 colourable, it is impossible. Else, we take the
 * number of nodes with the colour that the node mandatory has a lounge + for all the randomly 2
 * coloured connected components, we take the size of the smaller bipartition.
 * 
 * Time: O(v + e), Space: O(v + e)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, e;
vector<int> state;  // 0 is undecided, -1 is have, -2 is don't have, 2i+1 and 2i+2 form a bipartite
                    // component

bool possible = true;
vector<tuple<int, int, int>> edges;
vector<vector<int>> adjlist;
void propagate(int u) {
    int new_state;
    if (state[u] > 0) {
        new_state = state[u] % 2 ? state[u] + 1 : state[u] - 1;
    } else {
        new_state = state[u] == -1 ? -2 : -1;
    }
    for (int v : adjlist[u]) {
        if (state[v] == 0) {
            state[v] = new_state;
            propagate(v);
        } else if (state[v] != new_state) {
            possible = false;
        }
    }
}

vector<int> num_of_state;  // 0 unused, 1, ... , num_cc*2 are for their respective states,
                           // num_cc*2+1 and num_cc*2+2 refer to -1 and -2

int main() {
    cin >> n >> e;
    state.assign(n, 0);
    adjlist.assign(n, vector<int>());
    for (int i = 0; i < e; i++) {
        int a, b, num_have;
        cin >> a >> b >> num_have;
        a--, b--;

        if (num_have == 0) {
            if (state[a] == -1 || state[b] == -1) {
                possible = false;
                break;
            }
            state[a] = -2;
            state[b] = -2;
        } else if (num_have == 2) {
            if (state[a] == -2 || state[b] == -2) {
                possible = false;
                break;
            }
            state[a] = -1;
            state[b] = -1;
        } else if (num_have == 1) {
            adjlist[a].push_back(b);
            adjlist[b].push_back(a);
        }
    }
    for (int i = 0; i < n; i++) {
        if (state[i] != 0) {
            propagate(i);
        }
    }

    int num_cc = 0;
    for (int i = 0; i < n; i++) {
        if (state[i] == 0) {
            num_cc++;
            state[i] = num_cc * 2 - 1;
            propagate(i);
        }
    }

    // assert(possible);
    if (!possible) {
        cout << "impossible" << endl;
        return 0;
    }

    num_of_state.assign(num_cc * 2 + 3, 0);
    for (int i = 0; i < n; i++) {
        assert(state[i] != 0);
        assert(state[i] < num_cc * 2 + 1);
        if (state[i] == -1) {
            num_of_state[num_cc * 2 + 1]++;
        } else if (state[i] == -2) {
            num_of_state[num_cc * 2 + 2]++;
        } else {
            num_of_state[state[i]]++;
        }
    }

    // cout << num_cc << endl;
    int ans = num_of_state[num_cc * 2 + 1];
    // cout << ans << endl;
    for (int i = 1; i <= num_cc; i++) {
        ans += min(num_of_state[i * 2 - 1], num_of_state[i * 2]);
    }

    cout << ans << endl;

    return 0;
}