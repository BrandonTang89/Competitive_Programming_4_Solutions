/**Kattis - droppingdirections
 * Graph modelling question. We decompose each node i into ix and iy where ix represents the node
 * joining the horizontal roads and iy represents the node joining the vertical roads. Observe that
 * each node has degree 2 and such the graph consists of several simple cycles.
 *
 * Observe that we can connected 1 cycle to another by a directed edge, requiring only 1 sign. We
 * are interested in gettting to either dx or dy. If they are within the same cycle then we report
 * (number of CC - 1) else we report (number of CC - 2). This works assuming that it is even
 * possible for the people to get to the destination (which isn't explicitly stated in the question
 * but is implied?)
 * 
 * Time: O(n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, d;
int d1, d2, ans;
vector<vector<int>> nodes;
int getvxy(int u, int v) {  // 0 if x, else 1 if y
    assert(u < n);
    for (int i = 0; i < 4; i++) {
        if (nodes[v][i] == u) return (i % 2);
    }
    assert(false);
}

vector<int> visited;  // 0 to n-1 is ix, n to 2n-1 is iy
void dfs(int u) {
    visited[u] = 1;
    if (u == d) {
        d1 = ans;
    } else if (u == d + n) {
        d2 = ans;
    }
    int isx = (u < n);
    if (u >= n) u -= n;
    for (int i = 0; i < 4; i++) {
        if (i % 2 != isx) {  // if isx == 1, will match with i%2 == 0
            int nxy = getvxy(u, nodes[u][i]);
            int v;
            if (nxy) {
                v = nodes[u][i] + n;
            } else {
                v = nodes[u][i];
            }

            if (!visited[v]) {
                dfs(v);
            }
        }
    }
}

int main() {
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        cin >> n >> d;
        d--;
        nodes.assign(n, vector<int>(4, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> nodes[i][j];
                nodes[i][j]--;
            }
        }

        visited.assign(2 * n, 0);
        ans = 0;

        for (int i = 0; i < 2 * n; i++) {
            if (!visited[i]) {
                dfs(i);
                ans++;
            }
        }

        cout << ans - 1 - (d1 != d2) << endl;
    }

    return 0;
}