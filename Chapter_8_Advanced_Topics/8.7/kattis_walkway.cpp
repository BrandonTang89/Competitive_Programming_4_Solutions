/**Kattis - walkway
 * Simple-ish Dijkstra problem, use map rather than vector, and we calculate the edge weights using geometry. 
 * 
 * Time: O(E log V), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;

int e;
map<int, vector<pair<int, ld>>> adjlist;
map<int, ld> dist;
priority_queue<tuple<ld, int>, vector<tuple<ld, int>>, greater<tuple<ld, int>>> pq;
int main() {
    cout << fixed << setprecision(2) << endl;
    while (true) {
        cin >> e;
        if (e == 0) break;

        adjlist.clear();
        dist.clear();
        int a, b, h;
        for (int i = 0; i < e; i++) {
            cin >> a >> b >> h;
            ld surface_area = (a + b) * h / 2;
            adjlist[a].push_back({b, surface_area * 0.02});
            adjlist[b].push_back({a, surface_area * 0.02});
        }

        int source, dest;
        cin >> source >> dest;

        while (!pq.empty()) pq.pop();

        dist[source] = 0;
        pq.emplace(0, source);
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (u == dest) break;
            if (d > dist[u]) continue;  // inferior pair
            for (auto &[v, w] : adjlist[u]) {
                if (dist.count(v) && dist[u] + w >= dist[v]) continue;  // relaxing through this node doesn't help
                dist[v] = dist[u] + w;
                pq.emplace(dist[v], v);
            }
        }

        cout << dist[dest] << endl;
    }

    return 0;
}