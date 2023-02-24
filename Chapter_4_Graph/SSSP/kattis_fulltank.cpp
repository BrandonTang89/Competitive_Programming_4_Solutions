/**Kattis - fulltank
 * We do dijkstra on a state space graph.
 *
 * Each node represents (city, cur_fuel) where 0 <= cur_fuel <= 100.
 *
 * There are 2 types of edges, within cities and between cities. Within cities we have
 * (city, cur_fuel) --p[city]--> (city, cur_fuel + 1) for all 0 <= cur_fuel < c (capacity) since we
 * can fill up our tank until c, each additional unit costing p[city] money. Between cities we have
 * (city, cur_fuel) --0--> (next_city, cur_fuel - d[city][next_city]) for all 100 >= cur_fuel >=
 * d[city][next_city]. These represent travelling between cities which doesn't use any extra money
 * directly.
 *
 * We start from (src, 0) and check for the minimum cost to reach (dest, cur_fuel) for
 * all 0 <= cur_fuel <= c. If we can't reach (dest, cur_fuel) for any cur_fuel then it is
 * impossible.
 * 
 * Time: O(q * (100(E+V)) * log(101*V) ~ O(q(E+V)log(V)), Mem: O(V + E)
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

int n, e, c, src, dest, q;
vector<vector<tuple<int, int>>> adjlist;
vector<int> p, dist;
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>> pq;

int inline mapping(int city, int fuel) { return city * 101 + fuel; }

int main()
{
    fast_cin();
    cin >> n >> e;
    p.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }

    adjlist.assign(n * 101 + 1, vector<tuple<int, int>>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;

        for (int j = w; j <= 100; j++) {
            adjlist[mapping(u, j)].push_back({mapping(v, j - w), 0});
            adjlist[mapping(v, j)].push_back({mapping(u, j - w), 0});
        }
    }
    cin >> q;
    while (q--) {
        cin >> c >> src >> dest;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) {
                adjlist[mapping(i, j)].push_back({mapping(i, j + 1), p[i]});
            }
        }

        dist.assign(n * 101 + 1, 1e9);
        dist[mapping(src, 0)] = 0;
        pq.push({0, mapping(src, 0)});
        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d > dist[u]) continue;
            for (auto [v, w] : adjlist[u]) {
                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }

        int ans = 1e9;
        for (int i = 0; i <= c; i++) {
            ans = min(ans, dist[mapping(dest, i)]);
        }
        if (ans == 1e9)
            cout << "impossible" << endl;
        else
            cout << ans << endl;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < c; j++) {
                adjlist[mapping(i, j)].pop_back();
            }
        }
    }
    return 0;
}