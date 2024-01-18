/**Kattis - anewadventure
 * Modified BFS problem. All the arcs can just be treated as normal cells except we can wrap around
 * from the left to the right column. The key insight is that all the motorcycles move at the same
 * speed in the same direction so we can actually not move the motorcycles but just move the person!
 * This reduces to the problem to generic BFS on a fixed grid (with wraparound).
 *
 * The only tricky part now is ensuring that we check whether each move is valid. We cannot just
 * check if the first and end points of each move are valid but should check along the path of the
 * movement to prevent the person from teleporting through motorcycles.
 * 
 * Time: O(hw), Space: O(hw)
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
vector<vector<int>> ms;

inline int mod(int a, int b) { return ((a % b) + b) % b; }
int main()
{
    fast_cin();
    cin >> h >> w;
    ms.assign(h, vector<int>(w, 0));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            char x;
            cin >> x;
            if (x == 'M') ms[i][j] = 1;
        }
    }

    int dr[] = {-1, 0, 0, 1};
    int dc[] = {-1, -2, -1, -1};
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<tuple<int, int>> q;  // <row, col>
    q.push({0, 0});
    dist[0][0] = 0;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = mod(c + dc[i], w);
            if (nr < 0) continue;
            if (nr == h) {
                cout << dist[r][c] + 1 << endl;
                return 0;
            }

            bool valid = true;
            if (i == 0) {
                valid = !ms[nr][c] && !ms[nr][mod(c - 1, w)];
            }
            else if (i == 1) {
                valid = !ms[nr][mod(c - 1, w)] && !ms[nr][mod(c - 2, w)];
            }
            else if (i == 2) {
                valid = !ms[nr][mod(c - 1, w)];
            }
            else if (i == 3) {
                valid = !ms[nr][c] && !ms[nr][mod(c - 1, w)];
            }
            if (!valid) continue;

            if (dist[nr][nc] == -1) {
                dist[nr][nc] = dist[r][c] + 1;
                q.push({nr, nc});
            }
        }
    }

    cout << -1 << endl;
    return 0;
}