/**Kattis - easyascab
 * Construct a graph of the letters such that there exist an edge u -> v if u comes before v in the
 * alphabet. We check if the graph has a unique topological order. If so, we print the topological
 * order. Else if there is no topological ordering, ie the graph is cyclic then we print impossible,
 * else we print ambiguous. Note that to check if the graph is cyclic, we can just use Kahn's
 * algorithm and see if the topological order is complete. To check if the topological ordering is
 * unique, check that it forms a hamiltonian path. Note the edge case where the prefix of a string
 * comes after the string, making it inconsistent.
 *
 * Time: O(n^2), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

char highest_char;
int n;
vector<string> words;
vector<vector<int>> adjmat;
bool inconsistent;

int main() {
    cin >> highest_char >> n;
    int num_char = highest_char - 'a' + 1;
    assert(num_char > 1);
    words.resize(n);
    adjmat.assign(num_char, vector<int>(num_char, 0));
    for (int i = 0; i < n; i++) {
        cin >> words[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            // find the first difference
            bool isprefix = true;
            for (int k = 0; k < (int)min(words[i].size(), words[j].size()); k++) {
                if (words[i][k] != words[j][k]) {
                    int u = words[i][k] - 'a';
                    int v = words[j][k] - 'a';

                    adjmat[u][v] = 1;
                    isprefix = false;
                    break;
                }
            }
            if (isprefix && words[i].size() > words[j].size()) {  // VERY SNEAKY EDGE CASE
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    // get topo sort
    vector<int> in_degree(num_char, 0);
    for (int i = 0; i < num_char; i++) {
        for (int j = 0; j < num_char; j++) {
            if (adjmat[i][j] == 1) {
                in_degree[j]++;
            }
        }
    }
    vector<int> ts;
    priority_queue<int, vector<int>, greater<int>> pq;

    for (int i = 0; i < num_char; i++) {
        if (in_degree[i] == 0) {
            pq.push(i);
        }
    }
    while (!pq.empty()) {
        int u = pq.top();
        pq.pop();

        ts.push_back(u);
        for (int v = 0; v < num_char; v++) {
            if (adjmat[u][v] == 1) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    pq.push(v);
                }
                assert(in_degree[v] >= 0);
            }
        }
    }

    if ((int)ts.size() != num_char) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    bool hamiltonian = true;
    for (int i = 0; i < num_char - 1; i++) {
        if (adjmat[ts[i]][ts[i + 1]] != 1) {
            hamiltonian = false;
            break;
        }
    }
    if (hamiltonian) {
        for (int i = 0; i < num_char; i++) {
            cout << (char)(ts[i] + 'a');
        }
        cout << endl;

    } else {
        cout << "AMBIGUOUS" << endl;
    }
    return 0;
}