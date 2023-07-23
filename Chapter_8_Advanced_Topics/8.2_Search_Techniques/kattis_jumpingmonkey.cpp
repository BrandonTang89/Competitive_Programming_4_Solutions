/**Kattis - jumpingmonkey
 * Not horrendously hard. The state is a bitmask of the possible monkey positions, initially
 * starting with (1 << n) - 1. Each node has n edges, corresponding to shooting each of n trees.
 * For each node that could have a monkey and is not shot, the "possibility of monkey" propagates
 * to all adjacent nodes. We do a BFS to reach 0, i.e. no possibility of monkey.
 *
 * Also the "print the lexicographically smallest answer" part actually doesn't require extra checks
 * if we do the BFS in the right order, i.e. if we push the nodes from shooting the trees in the
 * order of the trees, the lexicographically smallest answer will be the first one we find.
 * (Invariant: at every BFS level, the node along the lexicographically smallest shortest path will
 * be the first out of all nodes that belong to some shortest path to be popped from the queue and
 * processed.)
 *
 * Time: O(2^n * n), Space: O(2^n)
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

vector<vector<int>> adjlist;
queue<int> q;
vector<int> dist;
vector<pair<int, int>> parent;  // {x, i}
int main()
{
    fast_cin();
    int n, e;
    while (true) {
        cin >> n >> e;
        if (n == 0 && e == 0) break;
        adjlist.assign(n, vector<int>());
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);
        }
        dist.assign(1 << n, 1e9);
        parent.assign(1 << n, {-1, -1});

        q.push((1 << n) - 1);
        dist[(1 << n) - 1] = 0;

        vector<int> y;
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            y.assign(n, 0);
            int bm = x;
            while (bm > 0) {
                int i = __builtin_ctz(bm);
                for (auto v : adjlist[i]) {
                    y[v]++;
                }
                bm -= (1 << i);
            }
            int next = 0;
            for (int i = 0; i < n; i++) {
                if (y[i] > 0) {
                    next |= (1 << i);
                }
            }

            for (int i = 0; i < n; i++) {  // shoot tree i
                int curNext = next;
                if (x & (1 << i)) {
                    for (auto v : adjlist[i]) {
                        if (y[v] == 1) {
                            assert(curNext & (1 << v));
                            curNext ^= (1 << v);
                        }
                    }
                }
                if (dist[curNext] > dist[x] + 1) {
                    dist[curNext] = dist[x] + 1;
                    parent[curNext] = {x, i};
                    q.push(curNext);
                }
            }
        }

        if (dist[0] == 1e9) {
            cout << "Impossible" << endl;
        }
        else {
            cout << dist[0] << ": ";

            vector<int> ans;
            int cur = 0;
            while (cur != (1 << n) - 1) {
                ans.push_back(parent[cur].second);
                cur = parent[cur].first;
            }
            for (int i = ans.size() - 1; i >= 0; i--) {
                cout << ans[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}