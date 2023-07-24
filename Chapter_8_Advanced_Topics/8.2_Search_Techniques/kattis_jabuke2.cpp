/**Kattis - jabuke2
 * State Space Dijkstra Variant. The idea is to do something like a multisource Dijkstra from
 * each of the trees, updating the distances in increasing distance from each source. If you imagine
 * the field as a water puddle and the trees as starting points of ripples, the ripples carry on
 * until they destructively interfere with each other at intersection points. It should be known
 * that adjacent cells are done with diagonals (for reasons that still elude me but seem intuitively
 * true).
 * 
 * Time: O(HW * Q) though it really is much less than that. Space: O(HW)
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
priority_queue<tuple<int, int, int, int, int>, vector<tuple<int, int, int, int, int>>,
               greater<tuple<int, int, int, int, int>>>
    pq;
vector<vector<int>> dist;
int dr[] = {0, 0, 1, -1, 1, 1, -1, -1};
int dc[] = {1, -1, 0, 0, 1, -1, 1, -1};
int main()
{
    fast_cin();
    cin >> h >> w;
    dist.assign(h, vector<int>(w, 1e9));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            char x;
            cin >> x;
            if (x == 'x') {
                pq.push({0, r, c, r, c});
                dist[r][c] = 0;
            }
        }
    }

    int qu;
    cin >> qu;
    while (qu--) {
        // Dijkstra from pq
        while (!pq.empty()) {
            auto [d, sr, sc, r, c] = pq.top();
            pq.pop();
            if (dist[r][c] < d) continue;
            for (int i = 0; i < 8; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                int newDist = (nr - sr) * (nr - sr) + (nc - sc) * (nc - sc);
                if (dist[nr][nc] > newDist) {
                    dist[nr][nc] = newDist;
                    pq.push({dist[nr][nc], sr, sc, nr, nc});
                }
            }
        }

        // Query
        int r, c;
        cin >> r >> c;
        r--;
        c--;
        cout << dist[r][c] << endl;

        if (dist[r][c] != 0) {
            pq.push({0, r, c, r, c});
            dist[r][c] = 0;
        }
    }

    return 0;
}