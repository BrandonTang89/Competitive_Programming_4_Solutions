/* Kattis - shortestpath3
SSSP with negative cycles. After doing bellman-ford, we need to find all nodes that are reachable
from negative cycles. We can just relax with edges again and dfs from nodes that have reduced distance.
However, we opt to do the bellman ford again to get all the nodes in negative cycles, just for 
template code.

Time: O(VE * num_tc), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef vector<int> vi;

const int INF = (int) 1e9;
int n, e, u, v, w, q, s;
bool modified;
vector<vector<tuple<int,int>>> AL;
vector<bool> reachable_from_neg_cycles;
vi dist, dist_now, part_of_neg_cycle;


void dfs(int u){
    reachable_from_neg_cycles[u] = true;
    for (auto &[v, w]: AL[u]){
        if (reachable_from_neg_cycles[v])continue;
        dfs (v);
    }
}

void bellman(){
    for (int i=0;i<n-1; i++){
        modified = false;
        for (u = 0; u < n; u++){
            if (dist[u] != INF){
                for (auto &[v, w]: AL[u]){
                    if (dist[u] + w >= dist[v])continue;
                    dist[v] = dist[u] + w;
                    modified = true;
                }
            }
        }
        if (!modified)break;
    }
}
int main(){
    while (true){
        cin >> n >> e >> q >> s;
        if (n == 0)break;
        dist.assign(n, INF);
        AL.assign(n, vector<tuple<int,int>>());
        part_of_neg_cycle.clear();
        reachable_from_neg_cycles.assign(n, false);
        
        for (int i=0; i<e;i++){
            cin >> u >> v >> w;
            AL[u].emplace_back(v, w);
        }
        dist[s] = 0;
        bellman();

        // find nodes in negative cycles
        dist_now = dist;
        // relax all again
        bellman();

        for (u = 0; u < n; u++){
            if(dist_now[u] != dist[u]){
                part_of_neg_cycle.emplace_back(u);
            } 
        }
        for (auto i: part_of_neg_cycle){
            dfs(i);
            //cout << i << endl;
        }

    
        for (int q_num=0;q_num<q; q_num++){
            cin >> u;
            if (dist[u] == INF){
                cout << "Impossible\n";
            }
            else if (reachable_from_neg_cycles[u]){
                cout << "-Infinity\n";
            }
            else{
                cout << dist[u] << endl;
            }
        }
        cout << endl;



    }
    return 0;   
}