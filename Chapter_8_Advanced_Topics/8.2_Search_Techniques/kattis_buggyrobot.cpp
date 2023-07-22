/**Kattis - buggyrobot
 * State Space 0-1 BFS. Modeling the state is not exactly trivial, we let (r, c, i) be the state
 * that the robot is at position (r, c) and we are at position i in the initial sequence provided by
 * the friend. Then for each state, we either follow the next move, insert a new move (and follow it
 * immediately) or delete the next move. The first operation has cost 0 while the next 2 have cost 1
 * each. As the edges are all of weights 0 or 1, we do 0-1 BFS.
 * 
 * Time: O(HW|S|), Mem: O(HW|S|)
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

int h, w, sr, sc, gr, gc;
char grid[51][51];
vector<vector<vector<int>>> dist;
deque<tuple<int, int, int>> q;
string init;

pair<int, int> nextPos(int r, int c, char move)
{
    assert(r >= 0 && r < h && c >= 0 && c < w);
    int nr = -1, nc = -1;
    if (move == 'U') {
        nr = r - 1;
        nc = c;
    }
    else if (move == 'D') {
        nr = r + 1;
        nc = c;
    }
    else if (move == 'L') {
        nr = r;
        nc = c - 1;
    }
    else if (move == 'R') {
        nr = r;
        nc = c + 1;
    }
    else
        assert(false);
    if (nr < 0 || nr >= h || nc < 0 || nc >= w || grid[nr][nc] == '#') {
        return {r, c};
    }
    return {nr, nc};
}
int main()
{
    cin >> h >> w;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == 'S') {
                sr = r;
                sc = c;
            }
            else if (grid[r][c] == 'G') {
                gr = r;
                gc = c;
            }
        }
    }
    cin >> init;
    dist.assign(h, vector<vector<int>>(w, vector<int>(init.size() + 1, 1e9)));

    q.push_back({sr, sc, 0});
    dist[sr][sc][0] = 0;

    while (!q.empty()) {
        auto [r, c, i] = q.front();
        q.pop_front();
        if (r == gr && c == gc) {
            cout << dist[r][c][i] << endl;
            return 0;
        }

        assert(i <= (int)init.size());
        if (i < (int)init.size()) {
            // accept the first move, 0 extra cost
            auto [nr, nc] = nextPos(r, c, init[i]);
            if (dist[nr][nc][i + 1] > dist[r][c][i]) {
                dist[nr][nc][i + 1] = dist[r][c][i];
                q.push_front({nr, nc, i + 1});
            }

            // delete the first move, 1 extra cost
            if (dist[r][c][i + 1] > dist[r][c][i] + 1) {
                dist[r][c][i + 1] = dist[r][c][i] + 1;
                q.push_back({r, c, i + 1});
            }
        }

        // insert 1 move at the front, consume it
        for (char move : {'U', 'D', 'L', 'R'}) {
            auto [nr, nc] = nextPos(r, c, move);
            if (dist[nr][nc][i] > dist[r][c][i] + 1) {
                dist[nr][nc][i] = dist[r][c][i] + 1;
                q.push_back({nr, nc, i});
            }
        }
    }
    assert(false);

    return 0;
}