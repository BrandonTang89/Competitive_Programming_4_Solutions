/**CF1970 C2
 * We just recursively compute whether the current player will win if we start at a node but can
 * only go to the children.
 * 
 * Time: O(n), Space: O(n)
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
int n, t;

vector<int> visited;
bool dfs(int u)
{  // returns whether player 1 can win from this node
    visited[u] = 1;
    bool win = false;
    for (int v : adjlist[u]) {
        if (visited[v]) continue;
        if (!dfs(v)) win = true;
    }
    return win;
}
int main()
{
    cin >> n >> t;
    adjlist.resize(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    visited.resize(n);
    int start;
    cin >> start;
    start--;

    if (dfs(start))
        cout << "Ron";
    else
        cout << "Hermione";

    return 0;
}