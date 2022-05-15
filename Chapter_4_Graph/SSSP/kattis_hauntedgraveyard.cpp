/* Kattis - hauntedgraveyeard
This a "long" problem. The best way to go about it is to transform the 2D grid into to
a linear list of nodes. We then populate an adjacency list based on gravestones, holes
and the location of each cell. Then we do bellman-ford with negative cycle check.

Debugging:
    Note that if a cell has a hole, he has to use it.

    Note that even if a negative cycle doesn't eventually lead to the exit after leaving
    the negative cycle, we should still output never, ie we don't need to DFS from negative cycle
    nodes

Our programme is rather inefficient at detecting the negative cycle, opting to do the full bellman-ford
again rather than just once. This is just due to reusing of template code.

Time: O(V), Mem: O(V) // since O(E) = V for grid graphs
*/ 
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

const int INF =  (int) 3e9;
int dc[] = {0, 0, 1, -1};
int dr[] = {1, -1, 0, 0};

int wid, hei, n, n_graves, n_holes, u, v, w, r, c;
bool graveyard[31][31], modified;
vector<vector<tuple<int,int>>> adjlist;
vector<bool> reachable_from_neg_cycles;
vector<ll> dist, dist_init, part_of_neg_cycle;

int convert_index(int r, int c){
    return r*wid + c;
}

void bellman(){
    for (int i=0;i<n-1; i++){
        modified = false;
        for (u = 0; u < n; u++){
            if (dist[u] != INF){
                for (auto &[v, w]: adjlist[u]){
                    if (dist[u] + w >= dist[v])continue;
                    dist[v] = dist[u] + w;
                    modified = true;
                }
            }
        }
        if (!modified)break;
    }
}

void dfs(int u){
    reachable_from_neg_cycles[u] = true;
    for (auto &[v, w]: adjlist[u]){
        if (reachable_from_neg_cycles[v])continue;
        dfs (v);
    }
}

int main(){
    fast_cin();
    while (true){
        cin >> wid >> hei;
        if (wid == 0)break;
        n = wid*hei;

        // reset variables
        memset(graveyard, 0, sizeof(graveyard));
        adjlist.assign(hei*wid, vector<tuple<int,int>>());
        dist.assign(wid*hei,INF); // set all to INF
        reachable_from_neg_cycles.assign(n, 0);
        part_of_neg_cycle.clear();

        cin >> n_graves;
            
        
        for (int i=0;i<n_graves;i++){
            cin >> c >> r;
            graveyard[r][c] = true;
        }
        
        for (int r=0;r<hei;r++){
            for (int c=0;c<wid;c++){
                if(r == hei-1 && c == wid-1)continue; // no edges from ending node
                if (graveyard[r][c])continue; // no edges from grave stones;

                for (int i=0;i<4;i++){
                    int nr = r + dr[i];
                    int nc = c + dc[i];

                    if (nc < 0 || nr < 0 || nc >= wid || nr >= hei)continue;
                    if (graveyard[nr][nc])continue; // no edges to grave stones
                    //printf("adjlist[%d] <-- (%d, %d)\n", convert_index(r, c), convert_index(nr, nc), 5);
                    adjlist[convert_index(r, c)].emplace_back(convert_index(nr, nc), 1);
                }
            }
        }
        
        cin >> n_holes;
        int r1, c1, r2, c2;
        for (int i=0;i<n_holes;i++){
            cin >> c1 >> r1 >> c2 >> r2 >> w;
            adjlist[convert_index(r1, c1)].clear(); // must use the haunted hole
            adjlist[convert_index(r1, c1)].emplace_back(convert_index(r2, c2), w);
        }

        dist[0] = 0; // starting from (0, 0)
        bellman();
        // find nodes in negative cycles
        dist_init = dist;
        // relax all again
        bellman();
        /*
        for (auto i: dist_init){cout << i << " ";} cout << endl;
        for (auto i: dist){cout << i << " ";} cout << endl;*/

        for (u = 0; u < n; u++){
            if(dist_init[u] != dist[u]){
                part_of_neg_cycle.emplace_back(u);
                break;
            } 
        }

        if (part_of_neg_cycle.size() > 0){
            cout << "Never" << endl;
        }
        else if (dist[convert_index(hei-1, wid-1)] == INF){
            cout << "Impossible" << endl;
        }
        else{
            cout << dist[convert_index(hei-1, wid-1)] << endl;
        }
        
        

    }

    return 0;
}
