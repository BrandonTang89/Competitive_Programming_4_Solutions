/**Kattis - horror
 * Implicit graph BFS. The nodes are the movies and the edges are similarities (note that the edges
 * are undirected since if A is similart to B, B is similar to A). All horror movies are of horror
 * index 0 and the horror index of adjancent movies is 1 higher than the horror index of lowest
 * adjancent movie. This is just a simple multi-source BFS from the horror movies.
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e, u, v, num_sources;
vi p, dist, sources;
queue<int> q;
vector<vector<int>> adjlist;
int main() {
    fast_cin();
    cin >> n >> num_sources >> e;
    adjlist.assign(n, vector<int>());
    p.assign(n, -1);
    dist.assign(n, INT_MAX);
    for (int i = 0; i < num_sources; i++) {
        cin >> u;
        sources.emplace_back(u);
    }
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }

    // Load Multiple Sources into Queue
    for (auto u : sources) {
        dist[u] = 0;
        q.push(u);
    }
    // BFS
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto v : adjlist[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                p[v] = u;
                q.push(v);
            }
        }
    }

    // Detemine largest distance
    int max_dist = 0, max_node = -1;
    for (int i = 0; i < n; i++) {
        if (dist[i] > max_dist) {
            max_dist = dist[i];
            max_node = i;
        }
    }
    cout << max_node << endl;
    return 0;
}