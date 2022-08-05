/**Kattis - island
 * A mix of input procesing and flood fill. Observe how the input is handled somwhat neatly here.
 * Also note the edge case where you cannot flood from a B to # or vice versa.
 *
 * Time: O(hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

int h, w;
int dc[] = {0, 1, 0, -1};
int dr[] = {1, 0, -1, 0};
vector<vector<int>> visited;
void dfs(int r, int c, int mode) {
    // mode 0 detects islands, mode 1 detects bridges, mode 2 detects bus
    visited[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w || visited[nr][nc] || grid[nr][nc] == '.')
            continue;

        if (mode == 0 && grid[nr][nc] == 'B') continue;
        if (mode == 1 && (grid[nr][nc] == 'X' || grid[nr][nc] == '#')) continue;
        if (mode == 2 && grid[r][c] == 'B' && grid[nr][nc] == '#') continue;
        if (mode == 2 && grid[r][c] == '#' && grid[nr][nc] == 'B') continue;

        dfs(nr, nc, mode);
    }
}

int main() {
    string line;
    int map_index = 0;
    while (1) {
        grid.clear();
        cout << "Map " << ++map_index << endl;

        while (getline(cin, line)) {
            grid.emplace_back(line);
            if (grid.back() == "") {
                break;
            }
        }
        bool quit_flag = false;
        if (grid.back() == "")
            grid.pop_back();
        else
            quit_flag = true;

        w = grid[0].size();
        h = grid.size();

        // cout << w << " " << h << endl;
        int ans[3];
        for (int i = 0; i < 3; i++) {
            visited.assign(h, vector<int>(w, 0));
            ans[i] = 0;
            for (int r = 0; r < h; r++) {
                for (int c = 0; c < w; c++) {
                    if (grid[r][c] == '.' || visited[r][c]) continue;
                    if (i == 0 && grid[r][c] == 'B') continue;
                    if (i == 1 && (grid[r][c] == 'X' || grid[r][c] == '#')) continue;

                    dfs(r, c, i);
                    ans[i]++;
                }
            }
        }
        cout << "islands: " << ans[0] << endl;
        cout << "bridges: " << ans[1] << endl;
        cout << "buses needed: " << ans[2] << endl;
        cout << endl;

        if (quit_flag) break;
    }

    return 0;
}