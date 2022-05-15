/**Kattis - walkforest
 * We need to first dijkstra from the house to determine the shortest distance between the house and
 * each junction. Then we construct our DAG where each node is connected to all adjacent nodes that
 * have a shorter distance to the house. Then we do topo sort and then count the number of paths
 * from the office to the house that go along the DAG. Might be a long problem, but we have plenty
 * of library code for most of the parts!
 * 
 * Time: O(E log V) for the Dijkstra, Space: O(E + V)
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

int n, e;
vector<vector<pair<int, int>>> adjlist;
vector<vector<int>> adjlist2;
vector<int> dist, ts;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

void toposort(int u) {
    dist[u] = 1;
    for (auto v : adjlist2[u]) {
        if (dist[v] == 0) {
            toposort(v);
        }
    }
    ts.push_back(u);
}

int main() {
    while (1) {
        cin >> n;
        if (n == 0) break;
        cin >> e;

        adjlist.assign(n, vector<pair<int, int>>());
        adjlist2.assign(n, vector<int>());
        dist.assign(n, 1e9);

        int u, v, w;
        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            u--;
            v--;
            adjlist[u].push_back({w, v});
            adjlist[v].push_back({w, u});
        }

        int source = 1;
        dist[source] = 0;
        pq.push({0, source});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();

            if (d > dist[u]) continue;
            for (auto &[w, v] : adjlist[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push(make_tuple(dist[v], v));
                }
            }
        }

        // Construct the DAG
        for (int i = 0; i < n; i++) {
            for (auto &[w, v] : adjlist[i]) {
                if (dist[v] < dist[i]) {
                    adjlist2[i].push_back(v);
                }
            }
        }

        // Topological Sort
        dist.assign(n, 0);
        ts.clear();
        for (int i = 0; i < n; i++) {
            if (dist[i] == 0) {
                toposort(i);
            }
        }
        reverse(ts.begin(), ts.end());

        // Count paths
        dist.assign(n, 0);
        dist[0] = 1;
        for (int i = 0; i < (int)ts.size(); i++) {
            for (auto v : adjlist2[ts[i]]) {
                dist[v] += dist[ts[i]];
            }
        }

        cout << dist[source] << endl;
    }

    return 0;
}