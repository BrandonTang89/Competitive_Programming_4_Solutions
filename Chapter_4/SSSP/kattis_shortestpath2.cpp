/**Kattis - shortestpath2
 * The key insight is that we should always aim to arrive at any node in the shortest amount of time,
 * this is because if we arrive any later, at best we catch the same "train" or path opening, but at
 * worst we need to take a later path opening. As such, the dijkstra algorithm will still produce
 * optimal answers as we visit the nodes at their minimum distance away from the source and attempt
 * to propagate with those distances. We just modify it to have an adjusted weight that accounts
 * for waiting for the path to open up.
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

int n, e, u, v, w, source, dest, num_q;
int t0, p;
vector<vector<tuple<int, int, int, int>>> adjlist;  // w, v, t0, P
vector<int> dist, parent, path;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

int main() {
    fast_cin();
    while (true) {
        cin >> n >> e >> num_q >> source;
        if (n == 0 && e == 0 && num_q == 0 && source == 0) break;
        while (!pq.empty())pq.pop();
        adjlist.assign(n, vector<tuple<int, int, int, int>>());
        dist.assign(n, INT_MAX);
        for (int i = 0; i < e; i++) {
            cin >> u >> v >> t0 >> p >> w;
            adjlist[u].push_back(make_tuple(w, v, t0, p));
        }
        dist[source] = 0;
        pq.emplace(0, source);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;  // inferior pair
            //cout << "u: " << u << " d: " << d << endl;
            for (auto &[w, v, t0, p] : adjlist[u]) {
                int weight = w;
                if (p == 0) {
                    if (dist[u] <= t0)
                        weight = w + t0 - dist[u];
                    else
                        continue;
                } else {
                    if (dist[u] < t0)
                        weight = w + t0 - dist[u];
                    else
                        weight = w + (p - (dist[u] - t0) % p) % p;
                }
                if (dist[u] + weight >= dist[v])
                    continue;  // relaxing through this node doesn't help
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }

        for (int i = 0; i < num_q; i++) {
            cin >> dest;
            if (dist[dest] == INT_MAX)
                cout << "Impossible" << endl;
            else
                cout << dist[dest] << endl;
        }
        cout << endl;
    }

    return 0;
}