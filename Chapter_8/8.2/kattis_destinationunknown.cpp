/**Kattis - destinationunknown
 * Should have been a simple problem but ran into some complications on the way. The main part
 * of the problem is basically that we do a dijkstra state space search with state (vertex, used
 * edge gh). At the end, we check if each of the destinations can be reached from the source,
 * passing through gh, and arriving at least as fast as without passing through gh (if such)
 * an alternative route is even possible.
 * 
 * I ran into this issue where using auto &[d, u, used_edge] = pq.top(); pq.pop(); resulted
 * in u randomly changing value.. I believe this is because we already defined u somewhere else
 * as a global variable or something. I think in general we should avoid using & if we are
 * going to delete the pq.top() after...
 * 
 * Time: O(E log V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int num_tc;
set<int> s;
int n, e, t, u, v, w, source, g, h;
vector<pair<int, int>> adjlist[2001];
map<pair<int, int>, int> dist;
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>>
    pq;
int main() {
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        dist.clear();
        s.clear();

        cin >> n >> e >> t;
        cin >> source >> g >> h;
        for (int i = 0; i <= n; i++) adjlist[i].clear();

        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            adjlist[u].emplace_back(v, w);
            adjlist[v].emplace_back(u, w);
        }

        for (int i = 0; i < t; i++) {
            cin >> u;
            s.insert(u);
        }

        dist.insert({{source, 0}, 0});
        pq.emplace(0, source, 0);

        while (!pq.empty()) {
            auto [d, u, used_edge] = pq.top();
            pq.pop();

            if (d > dist[{u, used_edge}]) continue;  // inferior pair

            // cout << u << " " << d << " " << used_edge << endl;

            for (auto [v, w] : adjlist[u]) {
                // cout << "u " << u << " v " << v << " " << w << endl;

                if (max(u, v) == max(g, h) && min(u, v) == min(g, h)) {
                    if (dist.count({v, 1}) && dist[{v, 1}] <= d + w) {
                        continue;
                    }
                    dist[{v, 1}] = d + w;
                    pq.emplace(d + w, v, 1);
                } else {
                    if (dist.count({v, used_edge}) && dist[{v, used_edge}] <= d + w) {
                        continue;
                    }
                    dist[{v, used_edge}] = d + w;
                    pq.emplace(d + w, v, used_edge);
                }
            }
        }

        for (auto i : s) {
            if (dist.count({i, 1}) && (dist.count({i, 0}) == 0 || dist[{i, 1}] <= dist[{i, 0}])) {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    return 0;
}