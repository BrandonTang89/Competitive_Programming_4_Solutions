/**Kattis - protectingthecollection
 * One of those super tedious laser simulation problems... We need to write auxiliary functions to
 * move the laser from one position to another based on the current direction and to change the
 * direction of the laser based on specific mirrors.
 *
 * The DP part uses the state (row, col, direction, alr added a mirror?) and transition by
 * proceeding as per direction or adding a mirror (if there is no mirror there).
 *
 * Note that one might ask: what if we needed to a / mirror then the laser
 * bounces from above, travelling downwards, turns left, does stuff, comes back up and bounces to
 * the right? it wont know that we already added a mirror??? But we notice that actually this is
 * okay because we could have just added a \ mirror and avoided the whole fiasco, preventing false
 * negatives.
 *
 * Also, we dont have to worry about the light bounching upwards and ignoring the mirror
 * we added (since our implementation doesnt keep track of where we added the mirror) and bounching
 * to the target, leading to a false positive. This is because the light will trace (in reverse) the
 * previous trajectory before our added mirror, bounching back to the source and stopping there...
 * 
 * Time: O(n^2 * 4 * 2), Space: O(n^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, laser_c, sensor_r;
char grid[2001][2001];

pair<int, int> next_pos(int r, int c, int dir) {
    if (dir == 0) {
        return {r - 1, c};
    }
    if (dir == 1) {
        return {r, c + 1};
    }
    if (dir == 2) {
        return {r + 1, c};
    }
    if (dir == 3) {
        return {r, c - 1};
    } else {
        return {-1, -1};
    }
}
int process_mirror(int dir, char mirror) {
    if (mirror == '/') {
        if (dir == 0) {
            return 1;
        }
        if (dir == 1) {
            return 0;
        }
        if (dir == 2) {
            return 3;
        }
        if (dir == 3) {
            return 2;
        } else
            return -1;
    } else if (mirror == '\\') {
        if (dir == 0) {
            return 3;
        }
        if (dir == 1) {
            return 2;
        }
        if (dir == 2) {
            return 1;
        }
        if (dir == 3) {
            return 0;
        } else
            return -1;
    } else {
        return -1;
    }
}
// dir -> 0: up, 1: right, 2: down, 3: left
int memo[2001][2001][4][2];
bool dp(int row, int col, int dir, bool installed_mirror) {
    // cout << row << " " << col << " " << dir << " " << installed_mirror << endl;
    if (row == sensor_r && col == n) return 1;                 // reached the end
    if (row < 0 || col < 0 || row >= n || col >= n) return 0;  // out of bounds
    if (memo[row][col][dir][installed_mirror] != -1) {
        return memo[row][col][dir][installed_mirror];
    }

    if (grid[row][col] == '/' || grid[row][col] == '\\') {  // if theres already a mirror there
        int new_dir = process_mirror(dir, grid[row][col]);
        auto [new_row, new_col] = next_pos(row, col, new_dir);
        return (memo[row][col][dir][installed_mirror] =
                    dp(new_row, new_col, new_dir, installed_mirror));
    }

    auto [new_row, new_col] = next_pos(row, col, dir);
    bool ans = dp(new_row, new_col, dir, installed_mirror);
    if (!installed_mirror) {
        // try a /
        int new_dir = process_mirror(dir, '/');
        new_row = next_pos(row, col, new_dir).first;
        new_col = next_pos(row, col, new_dir).second;
        ans = ans || dp(new_row, new_col, new_dir, true);

        // try a back slash
        new_dir = process_mirror(dir, '\\');
        new_row = next_pos(row, col, new_dir).first;
        new_col = next_pos(row, col, new_dir).second;
        ans = ans || dp(new_row, new_col, new_dir, true);
    }
    return (memo[row][col][dir][installed_mirror] = ans);
}
int main() {
    cin >> n >> laser_c >> sensor_r;
    laser_c--;
    sensor_r--;
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> grid[r][c];
        }
    }
    memset(memo, -1, sizeof(memo));
    cout << (dp(0, laser_c, 2, false) ? "YES" : "NO") << endl;

    return 0;
}