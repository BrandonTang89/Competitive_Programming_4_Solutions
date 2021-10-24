/* Kattis - xyzzy
This is an interesting Bellman-Ford algo modification question. There are 2 main modifications we need
to make. 
1.
    Since we are trying to maximise rather than minimise a variable (in this case energy at room),
    we should negate all weights and the starting "distance" (energy), then we run bellman-ford
2. 
    If at any point on a path, we run out of energy, we can't just walk to another room that has 
    more energy and then continue! this sounds tricky to do, but it just means that if we are at 
    node u with dist >= 0 (no more energy), then we don't use u and its edges to relax distances
    to its neighbours!

Also we need to do the extended "reachable from negative cycles" subroutine rather than just the simple
negative cycle detection.

Time: O(VE), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int INF = (int) 1e9;
int n, k, u, v, w;
string s, line;
bool modified;
vector<vector<int>> adjlist;
vi dist, dist_init, part_of_neg_cycle, room_e;
vector<bool> reachable_from_neg_cycles; 

void bellman(bool cycle_check) {
    for (int i = 0; i < n - 1; i++) {
        modified = false;
        for (u = 0; u < n; u++) {
            if (dist[u] < 0) { // very IMPORTANT modification
                for (auto v : adjlist[u]) {
                    w = -room_e[v];
                    if (dist[u] + w >= dist[v]) continue;
                    dist[v] = dist[u] + w;
                    modified = true;
                }
            }
        }
        if ((!modified) || cycle_check) break;
    }
}

void dfs_to_reachable(int u) {
    reachable_from_neg_cycles[u] = true;
    for (auto v: adjlist[u]) {
        if (reachable_from_neg_cycles[v]) continue;
        dfs_to_reachable(v);
    }
}


int main(){
    fast_cin();
    while (true){
        cin >> n;
        if (n == -1)break;
        adjlist.assign(n, vector<int>());
        room_e.assign(n, 0);
        dist.assign(n, INF);
        part_of_neg_cycle.clear();
        reachable_from_neg_cycles.assign(n, false);

        for (u = 0; u < n; u++){
            cin >> room_e[u];
            cin >> k;
            for (int i=0;i<k;i++){
                cin >> v;
                v--;
                adjlist[u].emplace_back(v);
            }
        }
        
        //for (auto i: room_e){cout << i << " ";}cout << endl;
        dist[0] = -100;
        bellman(false);
        // find nodes in negative cycles
        dist_init = dist;
        bellman(true);
        
        for (u = 0; u < n; u++) {
            if (dist_init[u] != dist[u]) { 
                // u is a part of a negative cycle
                part_of_neg_cycle.emplace_back(u);

                // find nodes reachable from negative cycles (-infinity distance)
                if (!reachable_from_neg_cycles[u]){
                    dfs_to_reachable(u);
                }
            }
        }

        if (reachable_from_neg_cycles[n-1])cout << "winnable" << endl;
        else{
            cout << ((dist[n-1] < 0) ? "winnable" : "hopeless") << endl;
        }
        /*
        */

    }

    return 0;
}