/**Kattis - bigtruck
 * Dijkstra DAG + DP. We first construt the Dijkstra predecessor DAG via regular Dijkstra. Then we
 * DP from the dest back to the src where dp(u) is the max number of items collected along some
 * shortest path (along src to dest). Honestly, pretty standard. You can combine both steps together
 * by doing the DP bottom up as you do the Dijkstra, but this is less clear imo.
 *
 * Time: O(E log V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e;
vector<int> arr;
vector<vector<pair<int, int>>> adjlist;
vector<int> dist;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<vector<int>> predecessors;

vector<int> memo;
int dp(int u)
{
    if (memo[u] != -1) return memo[u];
    if (u == 0) return arr[u];

    int ans = 0;
    for (auto v : predecessors[u]) {
        ans = max(ans, dp(v) + arr[u]);
    }
    return memo[u] = ans;
}
int main()
{
    fast_cin();
    cin >> n;
    arr.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cin >> e;
    adjlist.assign(n, vector<pair<int, int>>());
    predecessors.assign(n, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    dist.assign(n, 1e9);
    dist[0] = 0;
    pq.push({0, 0});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[u]) continue;
        for (auto &[v, w] : adjlist[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                predecessors[v].clear();
                predecessors[v].push_back(u);
            }
            else if (dist[u] + w == dist[v]) {
                predecessors[v].push_back(u);
            }
        }
    }
    memo.assign(n, -1);

    if (dist[n - 1] == 1e9) {
        cout << "impossible" << endl;
        return 0;
    }
    cout << dist[n - 1] << " " << dp(n - 1) << endl;

    return 0;
}