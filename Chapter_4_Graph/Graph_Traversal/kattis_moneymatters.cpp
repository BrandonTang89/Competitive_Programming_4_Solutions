/**Kattis - moneymatters
 * Quite a nice and simple graph problem. We just check if the sum of money owned within each
 * connected component is 0.
 * 
 * Time: O(V + E), Space: O(V + E)
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

int n, e, num_cc = 0;
vector<vector<int>> adjlist;
vector<int> visited, amt;
void dfs(int u) {
    if (visited[u] != -1) return;
    visited[u] = num_cc;
    for (int v : adjlist[u]) dfs(v);
}
int main() {
    fast_cin();
    cin >> n >> e;
    adjlist.assign(n, vector<int>());
    visited.assign(n, -1);
    amt.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> amt[i];
    }
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    for (int i = 0; i < n; i++)
        if (visited[i] == -1) {
            num_cc++;
            dfs(i);
        }
    bool can = true;
    for (int i = 1; i <= num_cc && can; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            if (visited[j] == i) {
                sum += amt[j];
            }
        }
        if (sum != 0) can = false;
    }
    cout << (can ? "POSSIBLE" : "IMPOSSIBLE") << endl;

    return 0;
}