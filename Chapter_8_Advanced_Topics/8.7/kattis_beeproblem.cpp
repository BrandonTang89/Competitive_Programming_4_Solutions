/**Kattis - beeproblem
 * A many parts but easy problem. First we figure out how to move on the bee grid. Then we
 * flood fill each possible component to find the component sizes. Then we sort the components
 * and greedily pick the largest components.
 * 
 * Time: O(h*w log hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int honey, h, w;
vector<vector<char>> grid;
vector<vector<int>> visited;
// every odd row is + NE and SE
vector<int> dc_odd = {-1, 1, 0, 0, 1, 1};
vector<int> dr_odd = {0, 0, -1, 1, 1, -1};
// every even row is + NW and SW
vector<int> dc_even = {-1, 1, 0, 0, -1, -1};
vector<int> dr_even = {0, 0, -1, 1, -1, 1};


int cur_cc = 0;
void dfs(int r, int c) {
    visited[r][c] = 1;
    cur_cc++;

    vector<int> &dc = (r % 2 == 0) ? dc_even : dc_odd;
    vector<int> &dr = (r % 2 == 0) ? dr_even : dr_odd;

    for (int i = 0; i < 6; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] == '.' && visited[nr][nc] == 0) {
            dfs(nr, nc);
        }
    }
}
int main() {
    cin >> honey >> h >> w;
    grid.assign(h, vector<char>(w, '.'));
    visited.assign(h, vector<int>(w, 0));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
        }
    }
    vector<int> cc_sizes;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (grid[r][c] == '.' && visited[r][c] == 0) {
                cur_cc = 0;
                dfs(r, c);
                cc_sizes.push_back(cur_cc);
            }
        }
    }

    sort(cc_sizes.begin(), cc_sizes.end(), greater<int>());

    int ans = 0;
    for (int i=0; i< (int) cc_sizes.size(); i++) {
        if (honey <= 0) break;
        ans += 1;
        honey -= cc_sizes[i];
    }

    cout << ans << endl;
    return 0;
}