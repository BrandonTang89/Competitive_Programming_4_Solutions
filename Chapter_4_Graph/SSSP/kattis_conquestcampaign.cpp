/**Kattis - conquestcampaign
 * One of the most basic BFS floodfill problems. We just multisource BFS from the places that the
 * troops are parachuted into and record the maximum distance from any one of these sources. The
 * answer is the maximum distance + 1.
 *
 * Time: O(HW), Mem: O(HW)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int h, w, n;
vector<vector<int>> dist;
queue<pair<int, int>> q;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int main()
{
    cin >> h >> w >> n;
    dist.resize(h, vector<int>(w, -1));
    for (int i = 0; i < n; i++) {
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        dist[r][c] = 0;
        q.push({r, c});
    }
    int ans = 0;
    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        ans = max(ans, dist[r][c]);
        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
            if (dist[nr][nc] != -1) continue;
            dist[nr][nc] = dist[r][c] + 1;
            q.push({nr, nc});
        }
    }
    cout << ans + 1 << endl;

    return 0;
}