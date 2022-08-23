/**Kattis - ads
 * Not worth it to solve this problem... Just DFS from the edges first to detect what is webpage, then
 * for each ad char which is not part of the webpage, we DFS from it and flood until its parent image is found,
 * then delete the image.
 * 
 * Time: O(HW), Space: O(HW)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h, w;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
vector<vector<int>> visited;
vector<string> grid;

int cell_visited = 1;
int top, le, ri, bottom;

vector<vector<int>> webpage_visited;
void webpagedfs(int r, int c) {
    webpage_visited[r][c] = 1;
    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (webpage_visited[nr][nc] == 1) continue;
        if (grid[nr][nc] == '+') continue;
        webpagedfs(nr, nc);
    }
}
void dfs(int r, int c) {
    visited[r][c] = cell_visited;
    if (grid[r][c] == '+') {
        top = min(top, r);
        le = min(le, c);
        ri = max(ri, c);
        bottom = max(bottom, r);
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (visited[nr][nc] == cell_visited) continue;
        dfs(nr, nc);
    }
}

int main() {
    string allowed = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?!,. +";
    unordered_set<char> allowed_set(allowed.begin(), allowed.end());
    cin >> h >> w;

    grid.assign(h, "");
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < h; i++) {
        getline(cin, grid[i]);
    }
    visited.assign(h, vector<int>(w, 0));
    webpage_visited.assign(h, vector<int>(w, 0));

    for (int r = 0; r < h; r++) {
        if (grid[r][0] != '+' && webpage_visited[r][0] == 0) {
            webpagedfs(r, 0);
        }
        if (grid[r][w - 1] != '+' && webpage_visited[r][w - 1] == 0) {
            webpagedfs(r, w - 1);
        }
    }
    for (int c = 0; c < w; c++) {
        if (grid[0][c] != '+' && webpage_visited[0][c] == 0) {
            webpagedfs(0, c);
        }
        if (grid[h - 1][c] != '+' && webpage_visited[h - 1][c] == 0) {
            webpagedfs(h - 1, c);
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (!webpage_visited[i][j] && allowed_set.find(grid[i][j]) == allowed_set.end()) {
                le = w;
                ri = -1;
                top = h;
                bottom = -1;

                dfs(i, j);

                for (int r = top; r <= bottom; r++) {
                    for (int c = le; c <= ri; c++) {
                        grid[r][c] = ' ';
                        visited[r][c] = cell_visited;
                    }
                }
            }
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }

    return 0;
}