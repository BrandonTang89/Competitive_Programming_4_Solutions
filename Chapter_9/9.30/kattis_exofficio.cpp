/**Kattis - exofficio
 * Constructive problem with non-trivial solution + tedious output formatting. It think it should be
 * decently clear that forming the BFS tree from the center point is part of the solution, but there
 * can exist many different BFS trees. Fortunately it seems that theres no difference, this is found
 * out by just submitting a bunch of solutions, all will be accepted. However, there is an edge case
 * of where height is even but width is odd. In this case, we should multi-source BFS from the 2
 * available centers...
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

vector<vector<vector<int>>> haswall;  // haswall[r][c] = {wall below, on right}
vector<vector<int>> dist;

int dr[] = {0, 0, 1, -1};
int dc[] = {-1, 1, 0, 0};

void removewall(int r, int c, int nr, int nc) {
    if (r == nr) {  // same row
        haswall[r][min(c, nc)][1] = 0;
    } else if (c == nc) {  // same column
        haswall[min(r, nr)][c][0] = 0;
    }
}
int main() {
    int h, w;
    cin >> h >> w;

    haswall.assign(h + 1, vector<vector<int>>(w + 1, vector<int>(2, 1)));
    dist.assign(h + 1, vector<int>(w + 1, -1));

    int sourceh = h / 2 + 1;
    int sourcew = w / 2 + 1;

    // BFS Floodfill from source
    queue<pair<int, int>> q;
    q.push({sourceh, sourcew});
    dist[sourceh][sourcew] = 0;
    if (h % 2 == 0 && w % 2 == 1) {  // corner case
        q.push({sourceh - 1, sourcew});
        removewall(sourceh - 1, sourcew, sourceh, sourcew);
        dist[sourceh - 1][sourcew] = 0;
    }
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 1 || nr > h || nc < 1 || nc > w) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});

            removewall(r, c, nr, nc);
        }
    }

    for (int r = 0; r < h + 1; r++) {
        if (r == 0) {
            for (int c = 0; c < 2 * w; c++) {
                if (c % 2 == 0)
                    cout << " ";
                else
                    cout << "_";
            }
            cout << endl;
            continue;
        }

        for (int c = 1; c <= 2 * w + 1; c++) {
            if (c == 1 || c == 2 * w + 1) {
                cout << '|';

                if (c == 2 * w + 1) cout << endl;
                continue;
            }
            if (c % 2 == 0) {
                if (r == h) {
                    cout << '_';
                } else if (haswall[r][c / 2][0]) {
                    cout << '_';
                } else {
                    cout << " ";
                }
            } else {
                if (haswall[r][(c - 1) / 2][1]) {
                    cout << "|";
                } else {
                    cout << " ";
                }
            }
        }
    }

    return 0;
}