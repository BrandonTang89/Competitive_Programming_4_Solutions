/**Kattis - vuk
 * Relatively simple BSTA + BFS + DFS. We preprocess using a multisource BFS from each of the trees
 * such that we record the minimum distance from each cell to any tree. Then we BSTA, each time
 * doing a DFS and avoiding cells with distance less than the current BSTA value. If we can reach
 * the destination, then we can increase the BSTA value, otherwise we decrease it.
 * 
 * Time: O(HW log (H+W)), Space: O(HW)
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

int h, w, srcr, srcc, dstr, dstc;
int inline dist(int x1, int y1, int x2, int y2) { return abs(x1 - x2) + abs(y1 - y2); }
vector<vector<char>> grid;
vector<vector<int>> dists, visited;
queue<tuple<int, int>> q;
int dr[4] = {1, 0, -1, 0};
int dc[4] = {0, 1, 0, -1};

int cur_min_dist;
void dfs(int r, int c)
{
    if (visited[r][c] || dists[r][c] < cur_min_dist) return;
    visited[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        dfs(nr, nc);
    }
}
bool workable(int c)
{
    visited.assign(h, vector<int>(w, 0));
    cur_min_dist = c;
    dfs(srcr, srcc);
    return visited[dstr][dstc];
}

int main()
{
    fast_cin();
    cin >> h >> w;
    grid.resize(h, vector<char>(w));
    dists.resize(h, vector<int>(w, -1));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == '+') {
                q.push({i, j});
                dists[i][j] = 0;
            }
            else if (grid[i][j] == 'V') {
                srcr = i;
                srcc = j;
            }
            else if (grid[i][j] == 'J') {
                dstr = i;
                dstc = j;
            }
        }
    }
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dr[i];
            int ny = y + dc[i];
            if (nx < 0 || nx >= h || ny < 0 || ny >= w) continue;
            if (dists[nx][ny] != -1) continue;
            dists[nx][ny] = dists[x][y] + 1;
            q.push({nx, ny});
        }
    }

    int l = 0, r = h + w;
    while (l < r) {
        int m = (l + r + 1) / 2;
        if (workable(m))
            l = m;  // we can go further
        else
            r = m - 1;
    }
    cout << l << endl;

    return 0;
}