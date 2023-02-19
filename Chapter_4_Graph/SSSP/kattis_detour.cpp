/**Kattis - detour
 * Notice that the signs essentially point from u->v iff during the dijkstra from the destination
 * (1) to the source (0), v is the parent of u i.e. parent[u] = v. So we do a dijkstra from the
 * destination to the source and then we do a dfs from the source to the destination, avoiding
 * going from u to v if parent[u] = v.
 * 
 * Time: O(E log V), Space: O(V + E)
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

int n, e;
vector<vector<tuple<int, int>>> adjlist;
vector<int> dist, parent;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<int> visited;

bool found;
vector<int> valid_path;
void dfs(int u)
{
    visited[u] = 1;  // mark as visited

    if (u == 1) {
        found = true;
        valid_path.push_back(u);
        return;
    }

    for (auto &[v, w] : adjlist[u]) {
        if (visited[v] == 0 && parent[u] != v) {  // not the optimal path
            dfs(v);
            if (found) {
                valid_path.push_back(u);
                return;
            }
        }
    }
}
int main()
{
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<int, int>>());
    for (int i = 0; i < e; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        adjlist[a].push_back(make_tuple(b, w));
        adjlist[b].push_back(make_tuple(a, w));
    }
    dist.assign(n, INT_MAX);
    parent.assign(n, -1);
    dist[1] = 0;
    pq.push(make_pair(0, 1));

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, w] : adjlist[u]) {
            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    visited.assign(n, 0);
    dfs(0);

    if (!found) {
        cout << "impossible" << endl;
        return 0;
    }
    else {
        cout << valid_path.size() << " ";
        for (int i = valid_path.size() - 1; i >= 0; i--) cout << valid_path[i] << " ";
        cout << endl;
    }
    return 0;
}