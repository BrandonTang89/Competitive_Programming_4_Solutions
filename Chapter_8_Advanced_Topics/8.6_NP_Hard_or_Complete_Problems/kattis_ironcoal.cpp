/**Kattis - ironcoal
 * Steiner-Tree with 3 vertices problem (modified). We start by adding 2 new vertices, n and n+1
 * which are connected to all the iron and coal nodes respectively (the edges in the direction of
 * resource -> super node). Then we do BFS from 0 and from n and n+1. For the second and third BFS,
 * we do it on the transpose graph since we will be going in the reverse direction of the edges. Then
 * we do an O(V) loop to find the optimal steiner node.
 * 
 * Time: O(V + E), Mem: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n, m, k;
vector<vector<int>> adjlist, adjlistT;
vector<ll> dist, distfrom0, distfromn, distfromnp1;
queue<int> q;
int main()
{
    cin >> n >> m >> k;
    adjlist.assign(n + 2, vector<int>());
    adjlistT.assign(n + 2, vector<int>());
    for (int i = 0; i < m; i++) {  // iron
        int a;
        cin >> a;
        a--;
        adjlist[a].push_back(n);
        adjlistT[n].push_back(a);
    }
    for (int i = 0; i < k; i++) {  // coal
        int a;
        cin >> a;
        a--;
        adjlist[a].push_back(n + 1);
        adjlistT[n + 1].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        int nei;
        cin >> nei;
        for (int j = 0; j < nei; j++) {
            int a;
            cin >> a;
            a--;
            adjlist[i].push_back(a);
            adjlistT[a].push_back(i);
        }
    }

    // BFS from 0
    dist.assign(n + 2, 1e9);
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjlist[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    distfrom0 = dist;

    // BFS from n
    dist.assign(n + 2, 1e9);
    dist[n] = 0;
    q.push(n);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjlistT[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    distfromn = dist;

    // BFS from n+1
    dist.assign(n + 2, 1e9);
    dist[n + 1] = 0;
    q.push(n + 1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adjlistT[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    distfromnp1 = dist;

    ll ans = 1e9;
    for (int i = 0; i < n; i++) {
        if (distfrom0[i] + distfromn[i] + distfromnp1[i] < ans) {  // ensure no overflow
            ans = distfrom0[i] + distfromn[i] + distfromnp1[i];
        }
    }
    if (ans == 1e9) {
        cout << "impossible" << endl;
    }
    else {
        cout << ans - 2 << endl;
    }

    return 0;
}