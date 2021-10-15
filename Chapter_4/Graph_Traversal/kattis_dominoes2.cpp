#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

vector<int>adjlist[10009];
int n, total_knocked, e, u, v, s, t, l;
bool visited[10009];

void dfs(int u){
    //cout << u << endl;
    if (visited[u])return; // check if we trying to knock the same thing again
    visited[u] = 1;
    total_knocked++;
    for (auto v: adjlist[u]){
        if (!visited[v])
            dfs(v);
    }
    return;
}
int main(){
    cin >> t;
    for (int tc=0;tc<t;tc++){
        cin >> n >> e >> l; //nodes, edges, knocks

        // reset arrays
        for (int i=0;i<n;i++){
            adjlist[i].clear();
        }
        memset(visited, 0, sizeof(visited));
        total_knocked = 0;

        // Parse Edges
        for (int i=0;i<e;i++){
            cin >> u >> v;
            u--; v--;
            adjlist[u].emplace_back(v);
        }

        for (int i=0;i<l;i++){
            cin >> s;
            s--;
            dfs(s);
        }

        cout << total_knocked << endl;
    }

   return 0;
}