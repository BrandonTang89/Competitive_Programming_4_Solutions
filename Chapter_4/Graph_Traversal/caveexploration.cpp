/* Kattis - Cave Explorer
The question involves counting the number of nodes that are connected to node 0 without passing through a bridge.
So the first step is finding out the bridges using the classic modified DFS. Afterwards, we should DFS from 0,
however we avoid edges that are bridges.

However, a problem i encountered is to get a graph without the bridges. 
    One approach would be to put the bridges into a set in O(B log B) and then create another adjacency list in O(V log B + E log B).

    Another approach would to just be to DFS and loop through the entire bridge list at each node in O(VB+ EB). While it might seem that this will
    take too long since the max number of bridges is for a tree O(V-1) = O(V) --> the algorithm takes O(V^2 + EV), in reality, if this was the case,
    the algoritm would quickly terminate since it would not propagage past node 0. So in reality, it takes less time than O(V^2 + EV)...

    As the second approach is easier to implement, we try it and get AC.

Time: O(B* answer)
Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

typedef vector<int> vi;

int t, n, e, u, v, dfs_num_counter, dfs_root, root_children;
vector<int> adjlist[10000 + 9], articulation_points, dfs_parent, dfs_num, dfs_low;
vector<pair<int, int>> bridges;

void articulation_point_and_bridge(int u) {
    dfs_num[u] = dfs_num_counter++;
    dfs_low[u] = dfs_num[u];

    for (auto v: adjlist[u]) {
        if (dfs_num[v] == -1) {  // tree edge
            dfs_parent[v] = u;
            if (u == dfs_root) {
                root_children++;
            }

            articulation_point_and_bridge(v);

            if (dfs_low[v] >= dfs_num[u]) {
                articulation_points.emplace_back(u);
            }
            if (dfs_low[v] > dfs_num[u]) {
                //cout << "bridge: " << u << " - " << v << endl;
                bridges.emplace_back(u, v);
                //adjlist[u][i] = -1;

            }

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        } else if (v != dfs_parent[u]) {  // back edge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]);
        }
    }
}

int cc_0_size = 0;
vector<bool> visited;
void dfs(int u){
    visited[u] = true;
    //cout << u << endl;
    cc_0_size++;
    for (auto v: adjlist[u]){
        // if (v == -1)continue;
        if (visited[v] == 1)continue;
        bool bridge = false;
        for (auto p: bridges){
            if (p.first == u && p.second == v){
                bridge = true;
                break;
            }
            else if (p.first == v && p.second == u){
                bridge = true;
                break;
            }
        }

        if (bridge)continue;

        dfs(v);
    }
}

int main() {
    fast_cin();
    cin >> n >> e;

    // reset variables
    for (int i = 0; i < n; i++) adjlist[i].clear();
    dfs_parent.assign(n, -1);
    dfs_num.assign(n, -1);
    dfs_low.assign(n, 0);
    articulation_points.clear();
    bridges.clear();
    visited.assign(n, 0);

    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }

    dfs_root = 0;
    root_children = 0;
    articulation_point_and_bridge(0);
    
    dfs(0);
    cout << cc_0_size << endl;

    return 0;
}