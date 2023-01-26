/**Kattis - george
 * Dijkstra but some lanes are blocked at some times. However, the dijkstra validity condition that
 * arriving to a node earlier is always beneficial in visiting subsequent nodes still holds. So we
 * just need to adjust the weight of the edge to account for waiting for the minister to pass.
 * Fortunately V is <= 10000 and each edge is only blocked once so we can store the pair of time the
 * edge is blocked for in a 2D array. The rest is more or less standard.
 *
 * Time: O(kV + E log V), Space: O(V + E) where the kV accounts for the time taken to check the edge
 * weights along the visited path
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

int n, e, u, v, w, source, dest, k, minister_length;
vector<vector<tuple<int, int>>> adjlist;  // w, v
vector<int> dist, minister_path;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

vector<vector<pair<int, int>>> blocked_times;  // start_end;
int main()
{
    cin >> n >> e;
    cin >> source >> dest >> k >> minister_length;
    source--;
    dest--;
    minister_path.assign(minister_length, 0);
    for (int i = 0; i < minister_length; i++) {
        cin >> minister_path[i];
        minister_path[i]--;
    }

    adjlist.assign(n, vector<tuple<int, int>>());
    dist.assign(n, INT_MAX);
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        if (u == v) continue;
        u--;
        v--;
        adjlist[u].push_back({w, v});
        adjlist[v].push_back({w, u});
    }

    blocked_times.assign(n, vector<pair<int, int>>(n, {-1, -1}));
    int t = 0;
    for (int i = 0; i < minister_length - 1; i++) {
        // determine the time taken to go from minister_path[i] to minister_path[i+1]
        int u = minister_path[i];
        int v = minister_path[i + 1];
        for (auto [w, v2] : adjlist[u]) {
            if (v2 == v) {
                blocked_times[u][v] = {t, t + w - 1};
                blocked_times[v][u] = {t, t + w - 1};
                t += w;
                break;
            }
        }
    }

    dist[source] = k;
    pq.push({k, source});

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        // cout << u << " " << d << endl;
        pq.pop();
        if (u == dest) break;
        if (d > dist[u]) continue;  // inferior pair
        for (auto &[w, v] : adjlist[u]) {
            int new_dist;
            if (blocked_times[u][v].first <= d && d <= blocked_times[u][v].second) {
                new_dist = 1 + blocked_times[u][v].second + w;
            }
            else {
                new_dist = d + w;
            }
            if (new_dist >= dist[v]) continue;  // relaxing through this node doesn't help
            dist[v] = new_dist;
            pq.emplace(dist[v], v);
        }
    }

    cout << dist[dest] - k << endl;

    return 0;
}