/**Kattis - hopscotch50
 * Relatively simple Dijkstra. We need to use the "convert grid coordinates to graph node index"
 * trick and add a dummy starting node that goes to all 1s and a dummy ending node that all ks point
 * to.
 * 
 * Time: O(n^4), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, k;
int v;
inline int coord_to_idx(int r, int c) { return r * n + c; }
inline int manhattan(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
vector<vector<int>> grid;
vector<int> dist;
vector<vector<tuple<int, int>>> adjlist;  // (idx, weight)
priority_queue<tuple<int, int>, vector<tuple<int, int>>, greater<tuple<int, int>>>
    pq;  // (dist, idx)
int main()
{
    cin >> n >> k;
    v = n * n + 2;
    grid.assign(n, vector<int>(n));
    adjlist.assign(v, vector<tuple<int, int>>());

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 1) {
                adjlist[n * n].emplace_back(coord_to_idx(i, j), 0);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == k) {
                adjlist[coord_to_idx(i, j)].emplace_back(n * n + 1, 0);  // we are done
                continue;
            }
            for (int r = 0; r < n; r++) {
                for (int c = 0; c < n; c++) {
                    if (grid[r][c] == grid[i][j] + 1) {
                        adjlist[coord_to_idx(i, j)].emplace_back(coord_to_idx(r, c),
                                                                 manhattan(i, j, r, c));
                    }
                }
            }
        }
    }

    dist.assign(v, INT_MAX);
    dist[n * n] = 0;
    pq.emplace(0, n * n);
    while (!pq.empty()) {
        auto [d, idx] = pq.top();
        pq.pop();
        if (d > dist[idx]) continue;
        for (auto [nidx, w] : adjlist[idx]) {
            if (dist[nidx] > dist[idx] + w) {
                dist[nidx] = dist[idx] + w;
                pq.emplace(dist[nidx], nidx);
            }
        }
    }

    if (dist[n * n + 1] == INT_MAX) {
        cout << -1 << endl;
    }
    else {
        cout << dist[n * n + 1] << endl;
    }

    return 0;
}