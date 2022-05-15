/**Kattis- flowerytrail
 * We modify dijkstra to keep track of a predessor adjacency list that goes in the reverse
 * direction from the dest to source. We later DFS using the predessor adjacency list to compute
 * the required answer
 * 
 * Time: O(E log V), Space: O(E + V)
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

int n, e, u, v, w, source, dest;
vector<vector<tuple<int, int>>> adjlist;       // w, v
vector<vector<tuple<int, int>>> predecessors;  // w, v
vector<int> dist;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

ll ans = 0;
vector<bool> visited;

void dfs(int u) {
    visited[u] = true;
    for (auto &[w, v] : predecessors[u]) {
        ans += w;
        if (!visited[v]) {
            dfs(v);
        }
    }
}

int main() {
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<int, int>>());
    predecessors.assign(n, vector<tuple<int, int>>());
    dist.assign(n, INT_MAX);
    visited.assign(n, false);
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        adjlist[u].push_back(make_tuple(w, v));
        adjlist[v].push_back(make_tuple(w, u));
    }
    source = 0, dest = n - 1;
    dist[source] = 0;
    pq.push(make_tuple(0, source));

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (d > dist[dest]) break;
        if (d > dist[u]) continue;

        for (auto &[w, v] : adjlist[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                predecessors[v].clear();
                predecessors[v].push_back(make_tuple(w, u));
                pq.push(make_tuple(dist[v], v));
            } else if (dist[v] == dist[u] + w) {
                predecessors[v].push_back(make_tuple(w, u));
            }
        }
    }

    dfs(dest);
    cout << ans * 2 << endl;
    return 0;
}