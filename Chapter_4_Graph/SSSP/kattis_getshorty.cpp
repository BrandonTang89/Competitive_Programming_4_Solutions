/**Kattis - getshorty
 * Simple Dijkstra's variant where we are maximising the "distance" and the "distances" are
 * multiplied rather than added. Note that this still works because reaching an intermediate node
 * with a larger size is always better than reaching it with a smaller size to use it as a stepping
 * stone.
 *
 * Time: O(E log V), Mem: O(V + E)
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
priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>>
    pq;  // min heap
vector<vector<pair<int, double>>> adjlist;
vector<double> dist;

int main()
{
    while (1) {
        cin >> n >> e;
        if (n == 0 && e == 0) break;
        adjlist.assign(n, vector<pair<int, double>>());

        for (int i = 0; i < e; i++) {
            int u, v;
            double w;
            cin >> u >> v >> w;
            adjlist[u].push_back({v, w});
            adjlist[v].push_back({u, w});
        }

        dist.assign(n, 0);  // INF
        dist[0] = 1;
        pq.push({1, 0});

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d < dist[u]) continue;
            for (auto [v, w] : adjlist[u]) {
                if (dist[v] < dist[u] * w) {
                    dist[v] = dist[u] * w;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << fixed << setprecision(4) << dist[n - 1] << endl;
    }

    return 0;
}