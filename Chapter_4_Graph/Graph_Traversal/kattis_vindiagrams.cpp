/**Kattis - vindiagrams
 * Conceptually easy, however it is surprisingly difficult to find an algorithm that can be neatly
 * and efficiently coded. First, I replace the Xs with either I, a or b where I represents an
 * intersection. This is done with a modified floodfill. Then I make 2 copies of the grid, flooding
 * all areas outside of A on 1 and all areas outside of B on the other. Then, each cell that is
 * still a '.' in each of the grids are the cells that are within A and B respectively, we can use
 * this info to find the answer.
 * 
 * Time: O(hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h, w;
vector<vector<char>> grid;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

void dfs(int r, int c, char l) {  // fills in the Xs
    if (grid[r][c] == l) return;
    grid[r][c] = l;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] == 'X')
            dfs(nr, nc, l);

        else if (grid[nr][nc] == 'I') {
            assert(nr + dr[i] < h && nr + dr[i] >= 0);
            assert(nc + dc[i] < w && nc + dc[i] >= 0);
            dfs(nr + dr[i], nc + dc[i], l);
        }
    }
}
void dfs2(vector<vector<char>> &g, int r, int c, char preserved) {  // flood fill from the sides
    if (g[r][c] == preserved) return;
    g[r][c] = '#';
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (g[nr][nc] == preserved || g[nr][nc] == 'I' || g[nr][nc] == '#') continue;
        dfs2(g, nr, nc, preserved);
    }
}
int main() {
    cin >> h >> w;
    grid.assign(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (i > 0 && j > 0 && i < h - 1 && j < w - 1 && grid[i][j] == 'X') {
                bool intersection = true;
                for (int k = 0; k < 4; k++) {
                    if (grid[i + dr[k]][j + dc[k]] != 'X') {
                        intersection = false;
                        break;
                    }
                }

                if (intersection) {
                    grid[i][j] = 'I';
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (grid[i][j] == 'A') {
                dfs(i, j, 'a');
            } else if (grid[i][j] == 'B') {
                dfs(i, j, 'b');
            }
        }
    }

    // deal with A first
    vector<vector<char>> g1 = grid;
    for (int i = 0; i < h; i++) {
        dfs2(g1, i, 0, 'a');
        dfs2(g1, i, w - 1, 'a');
    }
    for (int i = 1; i < w - 1; i++) {
        dfs2(g1, 0, i, 'a');
        dfs2(g1, h - 1, i, 'a');
    }

    // deal with B
    vector<vector<char>> g2 = grid;
    for (int i = 0; i < h; i++) {
        dfs2(g2, i, 0, 'b');
        dfs2(g2, i, w - 1, 'b');
    }
    for (int i = 1; i < w - 1; i++) {
        dfs2(g2, 0, i, 'b');
        dfs2(g2, h - 1, i, 'b');
    }

    int a = 0, b = 0, inter = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int x = 0;
            if (g1[i][j] == '.') {
                x++;
                a++;
            }
            if (g2[i][j] == '.') {
                x++;
                b++;
            }

            if (x == 2) {
                inter++;
                a--;
                b--;
            }
        }
    }
    cout << a << " " << b << " " << inter << endl;
    return 0;
}