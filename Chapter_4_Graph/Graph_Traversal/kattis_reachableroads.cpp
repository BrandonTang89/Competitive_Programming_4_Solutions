/**Kattis - reachableroads
 * Simply output number of connected components -1
 * Time: O(V + E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef vector<int> vi;

int num_tc, n, e, u, v;
vector<vector<int>> adjlist;
vector<bool> visited;

void dfs(int u){
    for (int v : adjlist[u]){
        if (!visited[v]){
            visited[v] = true;
            dfs(v);
        }
    }
}
int main(){
    cin >> num_tc;
    for (int tc=0; tc<num_tc; tc++){
        cin >> n >> e;
        adjlist.assign(n, vi());
        visited.assign(n, false);

        for (int i=0; i<e; i++){
            cin >> u >> v;
            adjlist[u].push_back(v);
            adjlist[v].push_back(u);  
        }
        // count number of CC
        int cc = 0;
        for (int i=0; i<n; i++){
            if (!visited[i]){
                cc++;
                dfs(i);
            }
        }
        cout << cc-1 << endl;
    }
    return 0;
}