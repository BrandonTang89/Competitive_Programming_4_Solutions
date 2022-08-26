/**Kattis - jetpack
 * Printing the path on a dag to each a certain node. However, the edges are annoying to deal with.
 * This might have been easier to do with DP where we move from left to right instead of backwards
 * ngl. There a bunch of output formatting stuff too... Anyway the general idea is we DFS with a
 * parent array (or specifically an array of the operation that led to that node), then we can
 * backtrack and print the path.
 *
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
int fx = -1, fy = -1;  // final x and ys
vector<vector<int>> parent;
vector<vector<char>> grid;
void dfs(int x, int y) {
    if (grid[y][x] == 'X') return;
    if (x == n - 1) {
        fx = x;
        fy = y;
        return;
    }
    if (y == 0) {
        if (parent[y][x + 1] == 0) {
            parent[y][x + 1] = 1;
            dfs(x + 1, y);
        }
    } else {
        if (parent[y - 1][x + 1] == 0) {
            parent[y - 1][x + 1] = 2;
            dfs(x + 1, y - 1);
        }
    }

    if (y == 9) {
        if (parent[y][x + 1] == 0) {
            parent[y][x + 1] = -1;
            dfs(x + 1, y);
        }
    } else {
        if (parent[y + 1][x + 1] == 0) {
            parent[y + 1][x + 1] = -2;
            dfs(x + 1, y + 1);
        }
    }
}
int main() {
    cin >> n;
    parent.assign(10, vector<int>(n, 0));
    grid.assign(10, vector<char>(n, '.'));
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < n; c++) {
            cin >> grid[r][c];
        }
    }
    dfs(0, 9);
    assert(fx != -1 && fy != -1);

    int x = fx, y = fy;
    vector<int> ans;
    while (x != 0) {
        // cout << x << " " << y << endl;
        ans.push_back(parent[y][x]);
        if (parent[y][x] == -2) {
            assert(y != 0);
            y--;
        } else if (parent[y][x] == 2) {
            assert(y != 9);
            y++;
        }
        x--;
    }

    reverse(ans.begin(), ans.end());
    vector<pair<int, int>> ans2;
    for (int i = 0; i < (int)ans.size(); i++) {
        if (ans[i] > 0) {
            int start = i;
            int duration = 0;
            while (ans[i] > 0) {
                duration++;
                i++;
            }
            ans2.emplace_back(start, duration);
        }
    }
    cout << ans2.size() << endl;
    for (int i = 0; i < (int)ans2.size(); i++) {
        cout << ans2[i].first << " " << ans2[i].second << endl;
    }

    return 0;
}