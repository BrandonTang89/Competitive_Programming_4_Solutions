/**Kattis - justpassingthrough
 * SSSP Flood Fill on State-Space DAG. Let the state be (row, col, num_passes_left). We do
 * a h*w preprocessing to determine the passes. Then we let the sources be all the drivable
 * left border cells. We dijkstra according to the 3 transitions (NE, E, SE) and get the min
 * of all the distances to the right border with 0 passes left. Note that we should prevent 
 * the algorithm from going into negative passes_left.
 * 
 * Time: O(hw log hw), Space: O(hw)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int h, w, n, INF = 1e9;
int grid[501][501];
bool ispass[501][501];
int dist[501][501][11];  // r, c, num_pass_left

int dr_n[] = {1, 0, -1, 0};
int dc_n[] = {0, 1, 0, -1};

int dr[] = {0, -1, 1};

priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>,
               greater<tuple<int, int, int, int>>>
    pq;
int main() {
    cin >> h >> w >> n;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
        }
    }
    for (int r = 1; r < h - 1; r++) {
        for (int c = 1; c < w - 1; c++) {
            int adjc_min = grid[r][c];
            for (int i = 0; i < 4; i++) {
                adjc_min = min(adjc_min, grid[r + dr_n[i]][c + dc_n[i]]);
            }
            if (adjc_min == -1) continue;  // border or is undrivable

            ispass[r][c] = (grid[r][c] < min(grid[r - 1][c], grid[r + 1][c])) &&
                           (grid[r][c] > max(grid[r][c - 1], grid[r][c + 1]));
        }
    }
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            for (int k = 0; k <= n; k++) {
                dist[r][c][k] = INF;
            }
        }
    }
    for (int r = 0; r < h; r++) {
        if (grid[r][0] == -1) continue;
        pq.push(make_tuple(0, r, 0, n));
        dist[r][0][n] = grid[r][0];
    }

    while (!pq.empty()) {
        auto [d, r, c, k] = pq.top();
        pq.pop();
        if (d > dist[r][c][k]) continue;  // inferior pair
        for (int i = 0; i < 3; i++) {
            int nc = c + 1;
            int nr = r + dr[i];
            if (nc < 0 || nr < 0 || nc >= w || nr >= h) continue;
            if (grid[nr][nc] == -1) continue;

            int nk = (ispass[nr][nc] ? k - 1 : k);
            if (nk < 0) continue;  // important check
            if (dist[r][c][k] + grid[nr][nc] >= dist[nr][nc][nk]) continue;
            dist[nr][nc][nk] = dist[r][c][k] + grid[nr][nc];
            pq.emplace(dist[nr][nc][nk], nr, nc, nk);
        }
    }

    int ans = INF;
    for (int r = 0; r < h; r++) {
        ans = min(ans, dist[r][w - 1][0]);
    }
    if (ans == INF) {
        cout << "impossible" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}