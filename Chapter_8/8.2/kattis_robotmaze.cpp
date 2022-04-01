/**Kattis - robotmaze
 * BFS State Space Search. State: (row, col, prev_dir, num_of_prev_dir_jumps - 1). So for
 * each of the 4 directions, we ensure we don't jump in the reverse direction and don't jump
 * in the same direction if the 4th variable of the state is 1. We start the search with
 * 4 sources which are all at the source but in each of the 4 directions.
 * 
 * Time: O(h*w*8), Space: O(h*w*8)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int h, w;
int s_r, s_c, d_r, d_c;
char board[1001][1001];
int dist[1001][1001][4][2];  // State Space Dist, (r, c, prev-direction, num_times_prev-1)
queue<tuple<int, int, int, int>> q;

int dc[] = {0, 1, 0, -1};
int dr[] = {1, 0, -1, 0};
int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        bool done = false;
        cin >> h >> w;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> board[i][j];
                if (board[i][j] == 'R') {
                    s_r = i;
                    s_c = j;
                }
                if (board[i][j] == 'D') {
                    d_r = i;
                    d_c = j;
                }
            }
        }

        while (!q.empty()) q.pop();
        memset(dist, -1, sizeof(dist));
        dist[s_r][s_c][0][0] = dist[s_r][s_c][1][0] = dist[s_r][s_c][2][0] = dist[s_r][s_c][3][0] =
            0;
        q.push(make_tuple(s_r, s_c, 0, 0));
        q.push(make_tuple(s_r, s_c, 1, 0));
        q.push(make_tuple(s_r, s_c, 2, 0));
        q.push(make_tuple(s_r, s_c, 3, 0));

        while (!q.empty()) {
            int r = get<0>(q.front());
            int c = get<1>(q.front());
            int prev_dir = get<2>(q.front());
            int prev_jump = get<3>(q.front());
            q.pop();

            if (r == d_r && c == d_c) {
                cout << dist[r][c][prev_dir][prev_jump] << endl;
                done = true;
                break;
            }

            for (int i = 0; i < 4; i++) {
                if (i == (prev_dir + 2) % 4) continue; // prevent going backwards
                if (i == prev_dir && prev_jump == 1) continue;
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                    continue;
                }
                if (board[nr][nc] == 'B') {
                    continue;
                }

                int next_jump = (i == prev_dir) ? 1 : 0;
                if (dist[nr][nc][i][next_jump] == -1) {
                    dist[nr][nc][i][next_jump] = dist[r][c][prev_dir][prev_jump] + 1;
                    q.push(make_tuple(nr, nc, i, next_jump));
                }
            }
        }

        if (!done) cout << -1 << endl;
    }

    return 0;
}