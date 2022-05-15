/* Kattis - knightjump
This is the basic version of knight movement since the constraints are such that
we can do a bfs for every query. However, some cells are excluded (simply not go there if
blocked).

Time: O(n^2), Mem: O(n^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h, w;
string line;
int dr[] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[] = {1, 2, 2, 1, -1, -2, -2, -1};
vector<vector<int>> dist;
vector<vector<char>> grid;
queue<tuple<int, int>> q;

int main() {
    cin >> h;
    w = h;

    dist.assign(h, vector<int>(w, -1));
    grid.assign(h, vector<char>(w, '.'));

    for (int r=0;r<h;r++){
        cin >> line;
        for (int c=0;c<w;c++){
            grid[r][c] = line[c];
            if (grid[r][c] == 'K'){
                dist[r][c] = 0;
                q.emplace(r, c);
            }
        }
    }

    while (!q.empty()) {
        auto &[r, c] = q.front();
        q.pop();

        if (r == 0 && c == 0) break;

        for (int i = 0; i < 8; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nc < 0 || nr < 0 || nc >= w || nr >= h) continue;
            if (dist[nr][nc] != -1) continue;
            if (grid[nr][nc] == '#')continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.emplace(nr, nc);
        }
    }
    cout << dist[0][0] << endl;
}