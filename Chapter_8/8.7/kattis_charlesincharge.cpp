/**Kattis - charlesincharge
 * Dijkstra + BSTA Question. We BSTA for the maximum weight that can be traversed. Use
 * long long and long double at the proper places to avoid overflow / floating point errors.
 * 
 * Time: O(log(max_edge_weight) * E log V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

ll n, e, u, v, w, x, INF = 1e17;
vector<vector<tuple<ll, ll>>> adjlist;  // w, v
vector<ll> dist;
priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, greater<tuple<ll, ll>>> pq;
ll SSSP(int max_weight) {
    dist.assign(n, INF);
    while (!pq.empty()) pq.pop();

    dist[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (u == n - 1) break;
        if (d > dist[u]) continue;  // inferior pair
        for (auto &[w, v] : adjlist[u]) {
            if (w > max_weight) continue;          // too heavy
            if (dist[u] + w >= dist[v]) continue;  // relaxing through this node doesn't help
            dist[v] = dist[u] + w;
            pq.emplace(dist[v], v);
        }
    }

    return dist[n - 1];
}
int main() {
    cin >> n >> e >> x;
    adjlist.assign(n, vector<tuple<ll, ll>>());
    ll max_edge_weight = 0;
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        u--;
        v--;
        adjlist[u].push_back({w, v});
        adjlist[v].push_back({w, u});
        max_edge_weight = max(max_edge_weight, w);
    }

    ll shortest_dist = SSSP(INF);
    ll max_dist = (ld) shortest_dist * ((ld) 1 + (ld) x / (ld)100);
    ll lo = 0, hi = max_edge_weight, mid;
    while (lo + 1 < hi) {
        mid = (lo + hi) / 2;
        if (SSSP(mid) <= max_dist) {
            hi = mid;
        } else {
            lo = mid+1;
        }
    }
    if (SSSP(lo) <= max_dist) {
        hi = lo;
    }

    cout << hi << endl;

    return 0;
}