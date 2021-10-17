/* Kattis - Hoppers

Observation 1:
    if there exist at least 1 non-bipartite CC, we can connect all other CCs to that and we will be able to distribute the hopper programme.
    This results in the answer being the number of CCs - 1.
    
    However, if all CCs are bipartitie, we can make one into a non-bipartite cc and do the same. This results in the answer being the number of CC.
    Of course, there exist thzedge case where all CCs are of size 2 or less. But you can reason out that by having at least 3 nodes and 2 edges,
    we can still constuct a non bipartite graph overall.

Note of the errata on the hint for CP4 regarding this problem.

Time: O(V+E), Mem: O(V+E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, cc = 0;
const int MAX_N = (int) 5e5 + 6;
vector<int> adjlist[MAX_N];
int state[MAX_N]; //-1 unvisited, 0 is coloured 0, 1 is coloured 1
bool all_bipartite = true;
queue<int> q;

int main(){
    fast_cin();
    cin >> n >> e;
    for (int i=0;i<e;i++){
        cin >> u >> v;
        u--; v--;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }
    memset(state, -1, sizeof(state));
    for (int i=0;i<n;i++){
        if (state[i] == -1){
            //cout << "new componenet at "<< i << endl;
            cc++;
            q.push(i);
            state[i] = 0;
            while (!q.empty()){
                u = q.front();
                q.pop();
                for (auto v: adjlist[u]){
                    if (state[v] == -1){
                        state[v] = not(state[u]);
                        q.push(v);
                    }
                    else if (state[v] == state[u]){
                        all_bipartite = false;
                    }
                }
            }
        }
    }

    if (all_bipartite){
        cout << cc << endl;
    }
    else cout << cc-1 << endl;


    return 0;
}