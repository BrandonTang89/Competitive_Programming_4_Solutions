/**Kattis - xentopia
 * Obvious state-space Dijkstra. Clearly the state is (location, red_left, blue_left) and we are
 * aiming to get from (src, k1, k2) to (dest, 0, 0). Note that we need long longs for the distances.
 *
 * Time: O(n*k1*k2 * log (e*k1*k2)), Space: O(n*k1*k2)
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

int n, e, k1, k2;
vector<vector<tuple<int, ll, int>>> adjlist;  // v, w, colour
vector<vector<vector<ll>>> dist;              // v, r, b
priority_queue<tuple<ll, int, int, int>, vector<tuple<ll, int, int, int>>,
               greater<tuple<ll, int, int, int>>>
    pq;  // dist, v, r, b
int main()
{
    fast_cin();
    cin >> n >> e >> k1 >> k2;
    adjlist.assign(n, vector<tuple<int, ll, int>>());
    for (int i = 0; i < e; i++) {
        int u, v, w, colour;
        cin >> u >> v >> w >> colour;
        u--;
        v--;
        adjlist[u].push_back(make_tuple(v, w, colour));
        adjlist[v].push_back(make_tuple(u, w, colour));
    }
    int src, dest;
    cin >> src >> dest;
    src--;
    dest--;

    dist.assign(n, vector<vector<ll>>(k1 + 1, vector<ll>(k2 + 1, 1e18)));
    dist[src][k1][k2] = 0;
    pq.push(make_tuple(0, src, k1, k2));

    while (!pq.empty()) {
        auto [d, u, r, b] = pq.top();
        pq.pop();
        if (d > dist[u][r][b]) continue;
        if (u == dest && r == 0 && b == 0) {
            cout << d << endl;
            return 0;
        }

        for (auto &[v, w, c] : adjlist[u]) {
            if (c == 1 && r == 0) continue;
            if (c == 2 && b == 0) continue;

            int newR = c == 1 ? r - 1 : r;
            int newB = c == 2 ? b - 1 : b;
            if (newR < 0) continue;
            if (newB < 0) continue;

            if (dist[v][newR][newB] > dist[u][r][b] + w) {
                dist[v][newR][newB] = dist[u][r][b] + w;
                pq.push(make_tuple(dist[v][newR][newB], v, newR, newB));
            }
        }
    }
    cout << -1 << endl;

    return 0;
}