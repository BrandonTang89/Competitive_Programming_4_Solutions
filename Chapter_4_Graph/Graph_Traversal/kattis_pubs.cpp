/**Kattis - pubs
 * Observe that a connected component with size 2 or more can always be bicolored such that each
 * node has at least 1 node of the other color adjacent to it. This can be done by DFSing from any node
 * in the CC and coloring each layer of the DFS spanning tree with alternate colors. We check detect the
 * impossible case by finding CC's of size 1.
 * 
 * Time: O(V + E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, e;
vector<vector<int>> adjlist;

vector<int> color;  // color it 0 and 1;
int ccsize = 0;
void dfs(int u, int c) {
    color[u] = c;
    ccsize++;
    for (int v : adjlist[u]) {
        if (color[v] == -1) {
            dfs(v, 1 ^ c);
        }
    }
}
int main() {
    cin >> n >> e;
    adjlist.assign(n, vi());

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }

    color.assign(n, -1);

    for (int i = 0; i < n; i++) {
        if (color[i] == -1) {
            ccsize = 0;
            dfs(i, 0);
            if (ccsize == 1) {
                cout << " Impossible" << endl;
                return 0;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << (color[i] == 0 ? "pub" : "house") << " ";
    }

    return 0;
}