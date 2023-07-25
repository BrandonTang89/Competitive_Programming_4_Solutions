/**Kattis - rainbowroadrace
 * Quite an easy state-space Dijkstra question. It is obvious that we should use a tuple<bit_mask,
 * cur_node> to represent the state, where the bit_mask contains the colours that we have collected,
 * and we are trying to get from (0, 0) to (2^7-1, 0) in the shortest distance.
 *
 * Time: O(2^7 * e log (2^7 * n)), Space: O(2^7 * n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, e;
vector<vector<tuple<int, int, int>>> adjlist;
unordered_map<char, int> colours = {{'R', 0}, {'O', 1}, {'Y', 2}, {'G', 3},
                                    {'B', 4}, {'I', 5}, {'V', 6}};
vector<vector<int>> dist;
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<tuple<int, int, int>>>
    pq;  // dist, node, mask
int main()
{
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<int, int, int>>());
    for (int i = 0; i < e; i++) {
        int u, v, w;
        char c;
        cin >> u >> v >> w >> c;
        u--;
        v--;
        adjlist[u].push_back(make_tuple(v, w, colours[c]));
        adjlist[v].push_back(make_tuple(u, w, colours[c]));
    }

    dist.assign(1 << 7, vector<int>(n, INT_MAX));
    dist[0][0] = 0;
    pq.push(make_tuple(0, 0, 0));

    while (!pq.empty()) {
        auto [d, u, bm] = pq.top();
        pq.pop();
        if (d > dist[bm][u]) continue;

        if (u == 0 && bm == (1 << 7) - 1) {
            cout << d << endl;
            return 0;
        }

        for (auto [v, w, c] : adjlist[u]) {
            int newMask = bm | (1 << c);
            if (dist[newMask][v] > dist[bm][u] + w) {
                dist[newMask][v] = dist[bm][u] + w;
                pq.push(make_tuple(dist[newMask][v], v, newMask));
            }
        }
    }
    assert(false);

    return 0;
}