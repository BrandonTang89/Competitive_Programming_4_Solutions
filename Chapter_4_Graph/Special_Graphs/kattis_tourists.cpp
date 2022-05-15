/* Kattis - tourists
Okay honestly im not very proud but I just blindly copied the LCA subroutine from
https://noiref.codecla.ws/ds/#sparse. Notice that while the code works, the type of code
used is very old, ie using static arrays rather than vectors and using bitset. 
In the future, I'll go learn a proper LCA routine that I understand!

The LCA here utilises a sparse table and runs in O(log n) time.

Time: O(n log n * k) where k is the sum of 1/i for i in [1, n], approx 12.8 for n=2e5
Mem: O(n log n) for sparse table.
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, u, v;
const int MAXN = 2000005;
const int LOGN = 21;
int p[LOGN+1][MAXN], h[MAXN];   //h: number of edges from root
long long d[MAXN];     //dist: sum of edge weight from root
vector<pair<int, int> > adjList[MAXN];   //node, weight
bitset<MAXN> visited;
/* Pre-computation using DFS */
void dfs(int x) {
    if (visited[x]) return;
    visited[x] = 1;
    for (int k = 0; k < LOGN; ++k) {
        if (p[k][x] == -1) break;
        p[k+1][x] = p[k][p[k][x]];
    }
    for (auto it:adjList[x]) {
        if (visited[it.first]) continue;
        p[0][it.first] = x;
        d[it.first] = d[x] + it.second;
        h[it.first] = h[x] + 1;
        dfs(it.first);
    }
}

/* Query */
int lca(int a, int b) { //h[a] < h[b]
    if (h[a] > h[b]) swap(a, b);
    /* advance b by h[b] - h[a] parents */
    for (int k = 0, d = h[b] - h[a]; k < LOGN; ++k) {
        if (d & (1<<k))  b = p[k][b];
    }
    if (a == b) return a;
    assert(h[a] == h[b]); //same height
    /* to be continued */
    for (int k = LOGN-1; k >= 0; --k) {
        if (p[k][a] != p[k][b]) 
            a = p[k][a], b = p[k][b];
    }
    assert(p[0][a] == p[0][b]);        //same immediate parent
    return p[0][a];
}


ll APSP(int u, int v) {
    int lca_v = lca(u, v);
    return d[u] + d[v] - 2 * d[lca_v];
}

int main() {
    fast_cin();
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--;
        v--;
        adjList[u].emplace_back(v, 1);
        adjList[v].emplace_back(u, 1);
    }
    dfs(0);
    
    ll ans = 0;
    for (int u=1;u<=n/2;u++){
        for (int multiplier = 2; multiplier*u <= n; multiplier++){
            int v = multiplier*u;
            // printf("u: %d, v: %d, u->v: %d\n", u, v, APSP(u-1, v-1, SpT));
            ans += APSP(u-1, v-1) + 1;
        }

    }
    cout << ans << endl;

    return 0;
}