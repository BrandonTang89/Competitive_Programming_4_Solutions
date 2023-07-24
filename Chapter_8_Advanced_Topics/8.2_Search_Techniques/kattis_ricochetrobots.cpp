/**Kattis - ricochetrobots
 * Obvious state-space BFS. Tedious implemention, I probably could have made better code design
 * choices.
 *
 * Time: O(10^8), Space: O(10^8)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, w, h, l;
int dist[11][11][11][11][11][11][11][11];
queue<tuple<int, int, int, int, int, int, int, int>> q;
vector<vector<char>> grid;
int dr[4] = {0, 1, 0, -1};  // E, S, W, N
int dc[4] = {1, 0, -1, 0};
int main()
{
    cin >> n >> w >> h >> l;
    pair<int, int> init[4] = {{10, 10}, {10, 10}, {10, 10}, {10, 10}};
    memset(dist, -1, sizeof(dist));
    grid.assign(h, vector<char>(w));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            if (grid[r][c] <= '4' && grid[r][c] >= '1') {
                init[grid[r][c] - '1'] = {r, c};
                grid[r][c] = '.';
            }
        }
    }
    assert(init[0] != make_pair(10, 10));
    q.push({init[0].first, init[0].second, init[1].first, init[1].second, init[2].first,
            init[2].second, init[3].first, init[3].second});
    dist[init[0].first][init[0].second][init[1].first][init[1].second][init[2].first]
        [init[2].second][init[3].first][init[3].second] = 0;

    while (!q.empty()) {
        auto [r1, c1, r2, c2, r3, c3, r4, c4] = q.front();
        q.pop();
        if (grid[r1][c1] == 'X') {
            cout << dist[r1][c1][r2][c2][r3][c3][r4][c4] << endl;
            return 0;
        }
        if (dist[r1][c1][r2][c2][r3][c3][r4][c4] == l) continue;
        vector<pair<int, int>> robots;
        robots.push_back({r1, c1});
        if (r2 != 10) robots.push_back({r2, c2});
        if (r3 != 10) robots.push_back({r3, c3});
        if (r4 != 10) robots.push_back({r4, c4});

        vector<char> curGrid;
        for (int j = 0; j < (int)robots.size(); j++) {
            curGrid.push_back(grid[robots[j].first][robots[j].second]);
            grid[robots[j].first][robots[j].second] = 'W';
        }
        for (int j = 0; j < (int)robots.size(); j++) {
            for (int i = 0; i < 4; i++) {
                int r = robots[j].first;
                int c = robots[j].second;
                while (true) {
                    int nr = r + dr[i];
                    int nc = c + dc[i];
                    if (nr < 0 || nr >= h || nc < 0 || nc >= w || grid[nr][nc] == 'W') break;
                    r = nr;
                    c = nc;
                }
                if (r == robots[j].first && c == robots[j].second) continue;
                // {r, c} is the robot's new position
                if (j == 0) {
                    if (dist[r][c][r2][c2][r3][c3][r4][c4] == -1) {
                        dist[r][c][r2][c2][r3][c3][r4][c4] =
                            dist[r1][c1][r2][c2][r3][c3][r4][c4] + 1;
                        q.push({r, c, r2, c2, r3, c3, r4, c4});
                    }
                }
                else if (j == 1) {
                    if (dist[r1][c1][r][c][r3][c3][r4][c4] == -1) {
                        dist[r1][c1][r][c][r3][c3][r4][c4] =
                            dist[r1][c1][r2][c2][r3][c3][r4][c4] + 1;
                        q.push({r1, c1, r, c, r3, c3, r4, c4});
                    }
                }
                else if (j == 2) {
                    if (dist[r1][c1][r2][c2][r][c][r4][c4] == -1) {
                        dist[r1][c1][r2][c2][r][c][r4][c4] =
                            dist[r1][c1][r2][c2][r3][c3][r4][c4] + 1;
                        q.push({r1, c1, r2, c2, r, c, r4, c4});
                    }
                }
                else if (j == 3) {
                    if (dist[r1][c1][r2][c2][r3][c3][r][c] == -1) {
                        dist[r1][c1][r2][c2][r3][c3][r][c] =
                            dist[r1][c1][r2][c2][r3][c3][r4][c4] + 1;
                        q.push({r1, c1, r2, c2, r3, c3, r, c});
                    }
                }
            }
        }

        for (int j = 0; j < (int)robots.size(); j++) {
            grid[robots[j].first][robots[j].second] = curGrid[j];
        }
    }

    cout << "NO SOLUTION\n";

    return 0;
}