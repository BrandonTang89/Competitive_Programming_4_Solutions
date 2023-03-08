/**Kattis - diplomacy
 * DFS and APSP. We start the edges with weight 1. We reduce the weights of the edges between nodes
 * with the same colour to 0 with DFS and then we do APSP. Our answer is the minimum (maximum
 * distance from a node to every other node). I don't quite understand why this works (since we
 * don't need to pick the same person to convert everytime).
 *
 * Time: O(V^3), Mem: O(V^2)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

vector<int> initial_colour, visited;
vector<vector<int>> adjlist, adjmat;
int n, e;

void dfs(int u)
{
    visited[u] = 1;
    for (int v : adjlist[u]) {
        if (visited[v] == -1 && initial_colour[v] == initial_colour[u]) {
            adjmat[v][u] = 0;
            adjmat[u][v] = 0;
            dfs(v);
        }
    }
}
int main()
{
    cin >> n >> e;
    initial_colour.resize(n);
    adjlist.assign(n, vector<int>());
    adjmat.assign(n, vector<int>(n, 1e6));
    for (int i = 0; i < n; i++) {
        cin >> initial_colour[i];
        adjmat[i][i] = 0;
    }
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
        adjmat[u][v] = 1;
        adjmat[v][u] = 1;
    }
    visited.assign(n, -1);
    for (int i = 0; i < n; i++) {
        if (visited[i] == -1) {
            dfs(i);
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
            }
        }
    }
    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        int cur = 0;
        for (int j = 0; j < n; j++) cur = max(cur, adjmat[i][j]);
        ans = min(ans, cur);
    }
    cout << ans << endl;

    return 0;
}