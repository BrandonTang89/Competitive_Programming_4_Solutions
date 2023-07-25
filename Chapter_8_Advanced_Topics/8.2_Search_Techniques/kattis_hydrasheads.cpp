/**Kattis - hydrashead
 * Extremely easy state-space BFS. The state is (h, t) with the edges being the sum of the effects
 * of the knight and the regen ablities of the hydra. The max number of heads and tails in any
 * solution may be hard to find a tight bound for, but surely < 500 will work and indeed it does.
 *
 * Time: O(1), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int h, t;
vector<vector<int>> dist;
queue<pair<int, int>> q;
vector<pair<int, int>> moves = {{0, 1}, {1, -2}, {-2, 0}};
int main()
{
    while (true) {
        cin >> h >> t;
        if (h == 0 && t == 0) break;
        dist.assign(500, vector<int>(500, 1e9));
        dist[h][t] = 0;
        q.push({h, t});

        bool done = false;
        while (!q.empty()) {
            auto [ch, ct] = q.front();
            q.pop();
            if (ch == 0 && ct == 0) {
                cout << dist[ch][ct] << endl;
                done = true;
                break;
            }

            for (auto [dh, dt] : moves) {
                int nh = ch + dh;
                int nt = ct + dt;
                if (nh < 0 || nh >= 500 || nt < 0 || nt >= 500) continue;
                if (dist[nh][nt] <= dist[ch][ct] + 1) continue;
                dist[nh][nt] = dist[ch][ct] + 1;
                q.push({nh, nt});
            }
        }
        while (!q.empty()) q.pop();
        if (!done) cout << -1 << endl;
    }

    return 0;
}