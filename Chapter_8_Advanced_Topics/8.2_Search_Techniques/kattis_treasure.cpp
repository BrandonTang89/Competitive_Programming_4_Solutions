/**Kattis - treasure
 * State-Space Dijkstra / 0-1 BFS. The state is (r, c, energy) and the dist is the number of days to
 * each a certain state. There are 2 kinds of edges, 0 cost edges that expend energy to move between
 * 2 tiles, as well as 1 cost edges within a tile that allow you to use.
 * 
 * The difficulty rating on kattis much higher than it should be.
 * 
 * Time: O(h*w*k log (h*w*k)), Space: O(h*w*k)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int h, w, k;
vector<vector<char>> grid;
priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>,
               greater<tuple<int, int, int, int>>>
    pq;
vector<vector<vector<int>>> dist;  // r, c, energy
int dr[] = {0, 0, 1, -1};
int dc[] = {1, -1, 0, 0};
unordered_map<char, int> tileCost = {{'S', 1000}, {'G', 1}, {'.', 1}, {'F', 2}, {'M', 3}};
int main()
{
    fast_cin();
    cin >> h >> w >> k;
    grid.assign(h, vector<char>(w, '.'));
    int sr, sc;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
            }
        }
    }
    dist.assign(h, vector<vector<int>>(w, vector<int>(k + 1, 1e9)));
    dist[sr][sc][k] = 1;
    pq.push(make_tuple(1, sr, sc, k));

    while (!pq.empty()) {
        auto [d, r, c, e] = pq.top();
        pq.pop();
        if (d > dist[r][c][e]) continue;

        if (grid[r][c] == 'G') {
            cout << d << endl;
            return 0;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (grid[nr][nc] == '#') continue;

            int energyCost = tileCost[grid[nr][nc]];
            if (energyCost > e) continue;
            if (dist[nr][nc][e - energyCost] > dist[r][c][e]) {
                dist[nr][nc][e - energyCost] = dist[r][c][e];
                pq.push(make_tuple(dist[nr][nc][e - energyCost], nr, nc, e - energyCost));
            }
        }

        // rest here
        if (dist[r][c][k] > dist[r][c][e] + 1) {
            dist[r][c][k] = dist[r][c][e] + 1;
            pq.push(make_tuple(dist[r][c][k], r, c, k));
        }
    }
    cout << -1 << endl;

    return 0;
}