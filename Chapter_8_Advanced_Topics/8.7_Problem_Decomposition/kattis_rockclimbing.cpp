/**Kattis - rockclimbing
 * BSTA + Dijkstra + Negative Cycles.
 * We just BSTA for the minimum energy required. For each check, we Dijkstra from the source but
 * don't go to nodes if the dist is > energy. There may be the situation where we can go around a
 * negative cycle somehow. If this is true, we definitely have enough energy to reach the end so we
 * just terminate. If we terminate dijkstra (no negative cycles), then we check if we can reach the
 * destination. Honestly the most annoying part of the problem is just converting grid coordinates
 * to indices.
 *
 * Time: O(??) not too clear because of negative edges, but the grid pattern makes it hard to craft
 * exponential test cases. At least O(HW log (HW*150)) assuming Dijkstra doesn't repeat nodes too
 * much. Mem: O(HW)
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

int h, w;
int n;
vector<vector<int>> grid;
inline int idx_from_coord(int r, int c) { return r * w + c; }
inline tuple<int, int> coord_from_idx(int idx) { return {idx / w, idx % w}; }

vector<vector<tuple<int, int>>> adjlist;  // {weight, dest}
vector<int> dist;

bool possible(int energy)
{
    // Dijkstra
    dist.assign(n, 1e6);
    dist[n - 2] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, n - 2});
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        if (d < 0) return true;

        for (auto [w, v] : adjlist[u]) {
            if (dist[u] + w < dist[v] && dist[u] + w <= energy) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[n - 1] < 1e6;
}

int main()
{
    fast_cin();
    cin >> h >> w;
    n = h * w + 2;
    adjlist.assign(n, vector<tuple<int, int>>());
    // source = h * w, dest = h * w + 1

    grid.resize(h, vector<int>(w));
    for (int i = 0; i < w; i++) {
        char c;
        cin >> c;
    }
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
        }
    }

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                adjlist[idx_from_coord(r, c)].push_back({grid[nr][nc], idx_from_coord(nr, nc)});
            }
        }
    }
    for (int c = 0; c < w; c++) {
        adjlist[h * w].push_back({grid[h - 1][c], idx_from_coord(h - 1, c)});
        adjlist[idx_from_coord(0, c)].push_back({0, h * w + 1});
    }

    int l = 0, r = 150;
    while (l < r) {
        int mid = (l + r) / 2;

        if (possible(mid)) {  // can do with this amount of energy
            r = mid;
        }
        else {
            l = mid + 1;
        }
    }

    cout << l << endl;

    return 0;
}