/* Kattis - pick up sticks
Conduct a cycle check on the directed graph while constructing a topological ordering at the same time. If there is no cycle, the algorithm
generates a valid topological sort, then we just output that.

Time: O(V + E), Mem: (V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v;
int state[1000009]; // 0 is unvisited, 1 is explored, 2 is completed
vector<int> topo; //topological ordering
vector<int> adjlist[1000009];

bool acyclic = true;
void dfs(int u){
    //cout << "u " << u << endl;
    state[u] = 1; //explored

    for (auto v: adjlist[u]){
        if (state[v] == 0){
            dfs(v);
        }
        else if (state[v] == 1){
            acyclic = false;
        }
    }

    
    state[u] = 2;
    topo.emplace_back(u);
}
int main(){
    fast_cin();
    cin >> n >> e;
    for (int i=0;i<e;i++){
        cin >> u >> v;
        u--; v--;
        adjlist[u].emplace_back(v);
    }

    memset(state, 0, sizeof(state));
    for (int i=0;i<n;i++){
        if (state[i]== 0)dfs(i);
    }

    reverse(topo.begin(), topo.end());
    if (acyclic){
        for (auto i:topo){
            cout << i+1 << endl;
        }
    }
    else{
        cout << "IMPOSSIBLE" << endl;
    }
    return 0;
}