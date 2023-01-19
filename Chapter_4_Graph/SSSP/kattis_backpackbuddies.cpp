/**Kattis - backpockbuddies
 * Dijkstra + Modified Dijkstra. We first do a classic dijkstra to get the time taken for the
 * knight. Then we add all the time needed for the knight to sleep Doing this is non-trivial and we
 * have to be careful with edge cases. We then do a modified dijkstra to get the time taken for the
 * mr day. This works still works because the property that "for all nodes U on the shortest path to
 * V, the shortest path to U follows this same path" or "there is no penalty for arriving to a node
 * as early as possible", so visiting nodes in increasing order from the source, finding the
 * shortest path to those nodes and then going from those nodes to other nodes is still a valid
 * strategy. The difference is the new_dist calculation will be more than just dist[u] + w. The
 * exact specifics can be seen in the code. Then we just compare the 2 times taken.
 * 
 * Time: O(E log V), Space: O(V + E)
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

int n, e, u, v, w;
vector<vector<tuple<int, int>>> adjlist;
vector<int> dist;

priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

int main()
{
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<int, int>>());
    dist.assign(n, INT_MAX);
    for (int i = 0; i < e; i++) {
        cin >> u >> v >> w;
        if (u == v) continue;
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    dist[0] = 0;
    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (u == n - 1) break;
        if (d > dist[u]) continue;
        for (auto [v, w] : adjlist[u]) {
            if (dist[u] + w >= dist[v]) continue;
            dist[v] = dist[u] + w;
            pq.push({dist[v], v});
        }
    }

    int knight_days = dist[n - 1] / 12 - (dist[n - 1] % 12 == 0) + (dist[n - 1] == 0);
    // 2 edge cases: if it is exactly a multiple of 12, don't need to sleep the night, if it is 0
    // then need to add back the subtracted 1
    int knight_hours = 12 * knight_days + dist[n - 1];

    dist.assign(n, INT_MAX);
    dist[0] = 0;
    while (!pq.empty()) pq.pop();

    pq.push({0, 0});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        if (u == n - 1) break;
        for (auto [v, w] : adjlist[u]) {
            int new_dist = dist[u] + w;
            if (new_dist % 24 >= 13 || new_dist % 24 == 0) {
                new_dist = dist[u] + (24 - dist[u] % 24) % 24 +
                           w;  // craft this line very carefully or split the 2 cases up
            }
            if (new_dist >= dist[v]) continue;
            dist[v] = new_dist;
            pq.push({dist[v], v});
        }
    }

    cout << dist[n - 1] - knight_hours << endl;

    return 0;
}