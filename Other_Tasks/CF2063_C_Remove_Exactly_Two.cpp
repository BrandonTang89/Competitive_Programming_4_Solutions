/**CF2063 C
 * 
 * There are only 2 different cases to consider: 
 * - If we remove two adjacent nodes
 * - If we remove two non-adjacent nodes
 * 
 * If we remove adjacent nodes, the answer is the sum of the degrees of the two nodes minus 2
 * If we remove non-adjacent nodes, the answer is the sum of their degees minus 1
 * 
 * We iterate over each such case separately and find the maximum answer
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int n;
multiset<ll> degs;
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        vector<pair<int, int>> edges;
        vector<vector<int>> adjlist(n, vector<int>());
        degs.clear();

        vector<ll> vDeg(n, 0);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--;
            v--;

            edges.push_back({u, v});
            vDeg[u]++;
            vDeg[v]++;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }

        for (int i = 0; i < n; i++) {
            degs.insert(vDeg[i]);
        }

        ll ans = 0;
        for (auto &[u, v] : edges) {
            ans = max(ans, vDeg[u] + vDeg[v] - 2);
        }

        for (int i = 0; i < n; i++) {
            degs.erase(degs.find(vDeg[i]));
            for (auto &v : adjlist[i]) {
                degs.erase(degs.find(vDeg[v]));
            }

            if (!degs.empty()) ans = max(ans, vDeg[i] + *degs.rbegin() - 1);

            degs.insert(vDeg[i]);
            for (auto &v : adjlist[i]) {
                degs.insert(vDeg[v]);
            }
        }

        cout << ans << endl;
    }

    return 0;
}