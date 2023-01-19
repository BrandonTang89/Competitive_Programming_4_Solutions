/**Kattis - carvet
 * We have to make the observation that it is not possible for the "hole" to be in the same place
 * and have the rest of the grid in 2 or more different states. As such, we only visit at most HW
 * states and can check if we have revisited a state by checking where the hole is. From there, it
 * is more or less regular recursive backtracking using the location of the hole as the state and
 * propogating to other states. We need to take note to get all the solutions of the minimum length
 * and then sort them lexicograhically.
 *
 * Time: O(HW), Space: O(HW) (assuming the time for sorting is negligible)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int h, w;
int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};
int tr, tc;
int grid[250][250];
set<pair<int, int>> visited;
vector<int> cur_path;
vector<vector<int>> sols;
int min_moves = INT_MAX;

void bf(int r, int c)
{
    // cout << r << " " << c << endl;
    visited.insert({r, c});
    if (r == tr && c == tc) {
        if ((int)cur_path.size() < min_moves) {
            min_moves = cur_path.size();
            sols.clear();
            sols.push_back(cur_path);
        }
        else if ((int)cur_path.size() == min_moves) {
            sols.push_back(cur_path);
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        if (r + 2 * dr[i] < 0 || r + 2 * dr[i] >= h || c + 2 * dc[i] < 0 || c + 2 * dc[i] >= w)
            continue;  // out of grid
        if (grid[r + dr[i]][c + dc[i]] != grid[r + 2 * dr[i]][c + 2 * dc[i]])
            continue;                                                 // not 1 car
        if (grid[r + dr[i]][c + dc[i]] == -1) continue;               // blocked
        if (visited.count({r + 2 * dr[i], c + 2 * dc[i]})) continue;  // visited

        swap(grid[r][c], grid[r + 2 * dr[i]][c + 2 * dc[i]]);
        cur_path.push_back(grid[r][c]);
        bf(r + 2 * dr[i], c + 2 * dc[i]);
        cur_path.pop_back();
        swap(grid[r][c], grid[r + 2 * dr[i]][c + 2 * dc[i]]);
    }
}
int main()
{
    cin >> h >> w;
    int er = 0, ec = 0;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == -1) {
                er = r;
                ec = c;
            }
        }
    }
    cin >> tr >> tc;
    tr--;
    tc--;
    bf(er, ec);
    sort(sols.begin(), sols.end());
    if ((int)sols.size() == 0) {
        cout << "impossible" << endl;
        return 0;
    }

    for (auto i : sols[0]) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}