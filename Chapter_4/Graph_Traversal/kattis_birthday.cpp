/* Kattis - Birthday
Introductory problem to bridges and articulation points. Simply determine if the graph has
a bridge. Note that it is assumed that the graph is connected at the beginning.

Although this question only requires finding of bridges, we include the code for articulation
points as a part of template code.

Time: O(V + E), Mem: O(V + E)
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int t, n, e, u, v, dfs_num_counter, dfs_root, root_children;
vector<int> adjlist[109], articulation_points, dfs_parent, dfs_num, dfs_low; 
vector<pair<int, int>> bridges;

void articulation_point_and_bridge(int u){
    dfs_num[u] = dfs_num_counter++;
    dfs_low[u] = dfs_num[u];

    for (int v: adjlist[u]){
        if (dfs_num[v] == -1){ // tree edge
            dfs_parent[v] = u;
            if (u == dfs_root){
                root_children++;
            }

            articulation_point_and_bridge(v);

            if(dfs_low[v] >= dfs_num[u]){
                articulation_points.emplace_back(u);
            }
            if (dfs_low[v] > dfs_num[u]){
                bridges.emplace_back(u, v);
            }

            dfs_low[u] = min(dfs_low[u], dfs_low[v]);
        }
        else if (v != dfs_parent[u]){ // back edge
            dfs_low[u] = min(dfs_low[u], dfs_num[v]); 
        }
    }

}

int main(){
    while(1){
        cin >> n >> e;
        if (n == 0 && e == 0){
            break;
        }

        // reset variables
        for (int i=0; i<n;i++)
            adjlist[i].clear();
        dfs_parent.assign(n, -1);
        dfs_num.assign(n, -1);
        dfs_low.assign(n, 0);
        articulation_points.clear();
        bridges.clear();

        for (int i=0;i<e;i++){
            cin >> u >> v;
            adjlist[u].emplace_back(v);
            adjlist[v].emplace_back(u);
        }

        for (int i=0;i<n;i++){
            if (dfs_num[i] == -1){
                dfs_root = i;
                root_children = 0;
                articulation_point_and_bridge(i);
                if (root_children > 1)
                    articulation_points.emplace_back(i);
            }
        }
        
        cout << ((bridges.size() == 0) ? "No" : "Yes") << endl;
    }


    return 0;
}