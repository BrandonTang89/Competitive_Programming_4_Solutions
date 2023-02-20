/**Kattis - arachnophobia
 * BSTA + Dijkstra. First we find the distance from each node to the nearest spider, we can do this
 * by a multi-source dijkstra from each of the spiders. Then we do a binary search for the maximum
 * minimum distance from the path to to the spiders such that we can still arrive in <= t time. In
 * each iteration, we do a dijkstra from the source to the destination, but we only consider going
 * to nodes that are at least m distance from the spiders.
 * 
 * Time: O(E (log V) (Log max_distance_in_graph)), Space: O(V + E)
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

int n, e, t;
int source, dest;
vector<vector<tuple<int, int>>> adjlist;
vector<int> dist_from_spiders, dist;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int main()
{
    cin >> n >> e >> t;
    adjlist.assign(n, vector<tuple<int, int>>());
    dist_from_spiders.assign(n, INT_MAX);

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adjlist[u].push_back(make_tuple(v, w));
        adjlist[v].push_back(make_tuple(u, w));
    }

    cin >> source >> dest;

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int c;
        cin >> c;
        pq.push(make_pair(0, c));
        dist_from_spiders[c] = 0;
    }

    // Dijkstra

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist_from_spiders[u]) continue;
        for (auto [v, w] : adjlist[u]) {
            if (dist_from_spiders[v] > dist_from_spiders[u] + w) {
                dist_from_spiders[v] = dist_from_spiders[u] + w;
                pq.push(make_pair(dist_from_spiders[v], v));
            }
        }
    }

    // we find the max distance we can be from spiders such that we still arrive in t time
    int r = min(dist_from_spiders[source], dist_from_spiders[dest]);
    int l = 0;
    while (l < r) {
        int m = ((l + r + 1) / 2);
        dist.assign(n, INT_MAX);
        dist[source] = 0;
        pq.push(make_pair(0, source));
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : adjlist[u]) {
                if (dist[v] > dist[u] + w && dist_from_spiders[v] >= m) {
                    dist[v] = dist[u] + w;
                    pq.push(make_pair(dist[v], v));
                }
            }
        }
        if (dist[dest] <= t)
            l = m;
        else
            r = m - 1;
    }

    cout << l << endl;

    return 0;
}