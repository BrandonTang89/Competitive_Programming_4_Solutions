/**Kattis - constraintedfreedomofchoice
 * Simple counting paths on DAGs. The DAG is actually not the physical graph but rather a statespace
 * graph where each node corresponds to (row, col, prev_row, prev_col) the 3 transitions are moving
 * in the 3 possible directions such that we don't revisit prev_row, pre_col and also we don't
 * collide with the '#'s. We could probably use a 4d array as the memo table, but I'm lazy so I just
 * used a hash map.
 *
 * Time: O(h^2 w^2 log (hw)), Space: O(h^2 w^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int h, w;
vector<vector<char>> grid;
map<tuple<int, int, int, int>, int> memo;

int dr[] = {1, 0, -1};
int dc[] = {0, 1, 0};
int dp(int r, int c, int pr, int pc)
{
    if (r == 0 && c == w - 1) return 1;
    if (memo.count({r, c, pr, pc})) return memo[{r, c, pr, pc}];
    int ans = 0;
    for (int i = 0; i < 3; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] == '#') continue;
        if (nr == pr && nc == pc) continue;
        ans += dp(nr, nc, r, c);
    }
    return memo[{r, c, pr, pc}] = ans;
}
int main()
{
    while (true) {
        cin >> h >> w;
        if (h == 0 && w == 0) break;

        memo.clear();
        grid.assign(h, vector<char>(w, ' '));
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> grid[i][j];
            }
        }

        cout << dp(h - 1, 0, -1, -1) << endl;
    }

    return 0;
}