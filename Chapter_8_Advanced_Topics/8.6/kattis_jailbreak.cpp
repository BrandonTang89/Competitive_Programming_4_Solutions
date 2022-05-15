/**Kattis - jailbreak
 * Novel steiner tree grid problem with 3 terminal vertices. I found it pretty hard
 * because I wasn't too confident in my 0-1 BFS code. Also I made a fatally hard to
 * detect bug in the adjlist function. But other than that... It actually should
 * not be too hard. The solution is decently lengthy tho, I spent way too long
 * debugging.
 * 
 * Time: O(HW), Space: O(HW)
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

int h, w, INF = 1e7;
deque<int> dq;       // for our 0-1 BFS
int dist[3][10008];  // the outside is 10000
char grid[109][109];
int cti(int r, int c) { return r * w + c; }

int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
vector<pair<int, int>> adjlist(int idx) {  // weighted Adjacency List
    vector<pair<int, int>> ans;
    if (idx == h * w) {
        // return all border values
        for (int r = 0; r < h; r++) {
            if (grid[r][0] != '*') ans.emplace_back((grid[r][0] == '#'), cti(r, 0));

            if (grid[r][w - 1] != '*') ans.emplace_back((grid[r][w - 1] == '#'), cti(r, w - 1));
        }
        for (int c = 1; c < w - 1; c++) {
            if (grid[0][c] != '*') ans.emplace_back((grid[0][c] == '#'), cti(0, c));

            if (grid[h - 1][c] != '*') ans.emplace_back((grid[h - 1][c] == '#'), cti(h - 1, c));
        }
        return ans;
    }
    int r = idx / w, c = idx % w;
    if (r == 0 || c == 0 || r == h - 1 || c == w - 1)
        ans.emplace_back(0, h * w);  // easy link to outside

    for (int i = 0; i < 4; i++) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
        if (grid[nr][nc] == '*') continue;
        ans.emplace_back((grid[nr][nc] == '#'), cti(nr, nc));
    }

    return ans;
}
int main() {
    fast_cin();
    int num_tc;
    cin >> num_tc;

    while (num_tc--) {
        cin >> h >> w;
        vector<int> sources = {h * w};
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                cin >> grid[r][c];
                if (grid[r][c] == '$') {
                    sources.emplace_back(cti(r, c));
                }
            }
        }

        for (int x = 0; x < 3; x++) {
            for (int i = 0; i <= h * w; i++) dist[x][i] = INF;
            dq.emplace_back(sources[x]);
            dist[x][sources[x]] = 0;

            // 0-1 BFS
            while (!dq.empty()) {
                auto cur = dq.front();
                dq.pop_front();
                for (auto [is_wall, nxt] : adjlist(cur)) {
                    if (dist[x][nxt] > dist[x][cur] + is_wall) {
                        dist[x][nxt] = dist[x][cur] + is_wall;
                        if (is_wall) {
                            dq.push_back(nxt);
                        } else {
                            dq.push_front(nxt);
                        }
                    }
                }
            }
            /*
            for (int i = 0; i <= h * w; i++) {
                cout << dist[x][i] << " ";
            }
            cout << "---" << endl;*/
        }

        int ans = INF;
        for (int sp = 0; sp <= h * w; sp++) {
            int s = dist[0][sp] + dist[1][sp] + dist[2][sp];

            if (sp != h * w) {
                s -= 2 * (grid[sp / w][sp % w] == '#');
            }
            // cout << "sp " << sp << " s " << s << endl;
            ans = min(ans, s);
        }
        cout << ans << endl;
    }

    return 0;
}