/**Kattis - godzilla
 * Should be easy (though I spent 1.5 hours debugging because I used grid.resize rather than
 * grid.assign). Just get the path of the Godzilla then do a multi source BFS from each mech
 * to find the minimum turn that a mech can be at each cell. Then for each cell in the path of
 * Godzilla, we check if it can be killed at that point of time.
 * 
 * Time: O(HW * O(H+W)) but hard to make a worst case, Space: O(HW)
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
int gr, gc;
queue<pair<int, int>> q;
vector<vector<char>> grid;
vector<vector<int>> dist;
vector<vector<int>> time_stepped;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};

vector<pair<int, int>> path;
void simulategodzilla()
{
    int curtime = 0;
    int i = gr, j = gc;
    while (true) {
        time_stepped[i][j] = curtime++;
        bool moved = false;
        for (int k = 0; k < 4; k++) {
            int nr = i + dr[k];
            int nc = j + dc[k];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (time_stepped[nr][nc] != -1) continue;
            if (grid[nr][nc] == 'R') {
                i = nr;
                j = nc;
                path.push_back({i, j});
                moved = true;
                break;
            }
        }
        if (moved) continue;
        for (int k = 0; k < 4; k++) {
            int nr = i + dr[k];
            int nc = j + dc[k];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (time_stepped[nr][nc] != -1) continue;
            i = nr;
            j = nc;
            path.push_back({i, j});
            moved = true;
            break;
        }
        if (moved) continue;
        break;
    }
}
int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> w >> h;
        grid.assign(h, vector<char>(w, ' '));
        dist.assign(h, vector<int>(w, -1));
        time_stepped.assign(h, vector<int>(w, -1));
        path.clear();
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> grid[i][j];
                if (grid[i][j] == 'M') {
                    q.push({i, j});
                    dist[i][j] = 0;
                }
                if (grid[i][j] == 'G') {
                    gr = i;
                    gc = j;
                }
            }
        }

        simulategodzilla();
        while (!q.empty()) {
            auto [r, c] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                if (dist[nr][nc] != -1) continue;

                if (grid[nr][nc] == 'R' &&
                    (dist[r][c] + 1 < time_stepped[nr][nc] || time_stepped[nr][nc] == -1))
                    continue;  // too early
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }

        int ans = 0;
        int ctime = 0;
        bool done = false;
        for (auto [r, c] : path) {
            ctime++;
            if (grid[r][c] == 'R') {
                ans += 1;
                grid[r][c] = '.';
            }
            for (int pr = r; pr >= 0; pr--) {
                if (grid[pr][c] == 'R') break;
                if (dist[pr][c] != -1 && dist[pr][c] <= ctime) {
                    done = true;
                }
            }
            for (int pr = r; pr < h; pr++) {
                if (grid[pr][c] == 'R') break;
                if (dist[pr][c] != -1 && dist[pr][c] <= ctime) {
                    done = true;
                }
            }
            for (int pc = c; pc >= 0; pc--) {
                if (grid[r][pc] == 'R') break;
                if (dist[r][pc] != -1 && dist[r][pc] <= ctime) {
                    done = true;
                }
            }
            for (int pc = c; pc < w; pc++) {
                if (grid[r][pc] == 'R') break;
                if (dist[r][pc] != -1 && dist[r][pc] <= ctime) {
                    done = true;
                }
            }
            if (done) break;
        }

        cout << ans << endl;
    }

    return 0;
}