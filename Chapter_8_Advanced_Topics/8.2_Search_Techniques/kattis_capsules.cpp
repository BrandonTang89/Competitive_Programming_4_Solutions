/**Kattis - capsules
 * Recursive backtracking, sudoku variant. Not too hard.. do something similar to ta sudoku solver,
 * for each empty cell, find the number of options that are possible for it, then we can expand that
 * cell.
 * 
 * Time: O(? pruning is hard to judge), Space: O(hw)
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

int h, w, n;
vector<vector<int>> grid, regiongrid;
vector<vector<pair<int, int>>> regions;

vector<unordered_set<int>> numbersInserted;
int dr[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[] = {0, 1, 1, 1, 0, -1, -1, -1};
bool isDone()
{
    for (int i = 0; i < n; i++) {
        if (numbersInserted[i].size() != regions[i].size()) return false;
    }
    return true;
}

void backtrack()
{
    if (isDone()) {
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                cout << grid[r][c] << " ";
            }
            cout << endl;
        }
        exit(0);
    }

    int minPossibilities = 1e9;
    int rBest = -1, cBest = -1;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == 0) {
                int possibilities = 0;
                for (int i = 1; i <= (int)regions[regiongrid[r][c]].size(); i++) {
                    if (numbersInserted[regiongrid[r][c]].find(i) !=
                        numbersInserted[regiongrid[r][c]].end())
                        continue;

                    bool hasAdjacent = false;
                    for (int j = 0; j < 8; j++) {
                        int nr = r + dr[j];
                        int nc = c + dc[j];
                        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                        if (grid[nr][nc] == i) {
                            hasAdjacent = true;
                            break;
                        }
                    }
                    if (hasAdjacent) continue;
                    possibilities++;
                }
                if (possibilities < minPossibilities) {
                    minPossibilities = possibilities;
                    rBest = r;
                    cBest = c;
                }
            }
        }
    }
    if (minPossibilities == 1e9) return;
    int r = rBest, c = cBest;

    for (int i = 1; i <= (int)regions[regiongrid[r][c]].size(); i++) {
        if (numbersInserted[regiongrid[r][c]].find(i) != numbersInserted[regiongrid[r][c]].end())
            continue;

        bool hasAdjacent = false;
        for (int j = 0; j < 8; j++) {
            int nr = r + dr[j];
            int nc = c + dc[j];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (grid[nr][nc] == i) {
                hasAdjacent = true;
                break;
            }
        }
        if (hasAdjacent) continue;

        grid[r][c] = i;
        numbersInserted[regiongrid[r][c]].insert(i);
        backtrack();
        grid[r][c] = 0;
        numbersInserted[regiongrid[r][c]].erase(i);
    }
}
int main()
{
    fast_cin();
    cin >> h >> w;
    grid.assign(h, vector<int>(w, 0));
    regiongrid.assign(h, vector<int>(w, -1));

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            string x;
            cin >> x;
            if (x == "-") continue;
            grid[r][c] = stoi(x);
        }
    }

    cin >> n;
    regions.assign(n, vector<pair<int, int>>());
    numbersInserted.assign(n, unordered_set<int>());
    for (int i = 0; i < n; i++) {
        int regionSize;
        cin >> regionSize;
        for (int j = 0; j < regionSize; j++) {
            char dummy;
            int r, c;
            cin >> dummy >> r >> dummy >> c >> dummy;
            r--;
            c--;
            regions[i].push_back({r, c});
            regiongrid[r][c] = i;

            if (grid[r][c] != 0) {
                numbersInserted[i].insert(grid[r][c]);
            }
        }
    }

    backtrack();

    return 0;
}