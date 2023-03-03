/**Kattis - bicikli
 * Cycle Finding + Topological Sort + Output Procesing. To determine if we even have a path, we
 * should DFS from src to dest. To determine if there are inf paths, we should DFS from src to dest
 * and record at least 1 node in each cycle as being in a cycle. Then we can DFS from dest to src
 * along the transpose graph and see if we encounter one of these nodes in a cycle. If we do, then
 * there are inf paths. It is important that we only care about cycles that are along some path
 * between the src and dest.
 *
 * If the subgraph between src and dest is a DAG, then we can do a topological sort and count the
 * number of paths on the DAG. Note that we can record the toposort order when we do our first DFS.
 *
 * We need to be careful in ensuring that we prepend our output with enough 0s to make it 9 digits
 * if and only if the total number of ways is >= 1e9.
 * 
 * Time: O(V + E), Mem: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, e;
const int MOD = 1e9;
vector<vector<int>> adjlist, adjlistT;
vector<int> explored, incycle, topo, num_ways;
bool inf = false;
void dfs(int u)
{
    explored[u] = 1;
    for (auto v : adjlist[u]) {
        if (explored[v] == 0) {
            dfs(v);
        }
        else if (explored[v] == 1) {  // back edge
            incycle[v] = 1;
        }
    }
    topo.push_back(u);
    explored[u] = 2;
}
void dfs2(int u)
{
    explored[u] = 1;
    if (incycle[u] == 1) {
        inf = true;
        return;
    }
    for (auto v : adjlistT[u]) {
        if (explored[v] == 0) {
            dfs2(v);
        }
    }
}
int main()
{
    cin >> n >> e;
    adjlist.assign(n, vector<int>());
    adjlistT.assign(n, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        assert(u != v);
        adjlist[u].push_back(v);
        adjlistT[v].push_back(u);
    }
    explored.assign(n, 0);
    incycle.assign(n, 0);
    dfs(0);
    if (explored[1] == 0) {
        cout << 0 << endl;
        return 0;
    }
    explored.assign(n, 0);
    dfs2(1);
    if (inf) {
        cout << "inf" << endl;
        return 0;
    }

    num_ways.assign(n, 0);
    num_ways[0] = 1;
    reverse(topo.begin(), topo.end());
    bool morethan9 = false;
    for (auto u : topo) {
        for (auto v : adjlist[u]) {
            num_ways[v] += num_ways[u];
            if (num_ways[v] >= MOD) {
                morethan9 = true;
                num_ways[v] %= MOD;
            }
        }
    }
    if (morethan9) {
        cout << setfill('0') << setw(9) << num_ways[1] << endl;
    }
    else
        cout << num_ways[1] << endl;
    return 0;
}