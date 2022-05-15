/* Kattis - faultyrobot

Observation 1:
    We note that at each node, the robot can either have made the buggy move already, or not.
    This is 2 states that we can then separate the node into, creating a graph of 2n nodes.
    Thus, for every non-forced edge, we move from a -> b+n since we have made the bug in using this edge.
    As for forced edges, we move from a -> b or a+n -> b+n.

    By using DFS on node 0, we visit all possible nodes and states at the node. If we can visit a node that has
    no outward forced edge, whether it be after using the bug or not, we add it to our solution set.

    Note that we use the set to prevent double counting if we can reach the same node with the bug and without the bug.

Time: O(V + E), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v;
vi adjlist[2009]; // 0 to n-1 is for 0 bug, n to 2n-1 is for 1 bug
bool visited[2009], has_forced_edge[2009];

void dfs(int u){
    visited[u] = true;
    for (auto v: adjlist[u]){
        if (!visited[v]){
            dfs(v);
        }
    }
}
int main(){
    fast_cin();
    cin >> n >> e;
    for(int i=0;i<e;i++){
        cin >> u >> v;
        if (u > 0){
            u--; v--; //non forced edge
            adjlist[u].emplace_back(v+n); // use a bug to move 
        }
        if (u < 0){
            u = -u;
            u--; v--;
            has_forced_edge[u] = true;
            adjlist[u].emplace_back(v); // doesn't use a bug to move 
            adjlist[u+n].emplace_back(v+n); 
        }
    }

    dfs(0);
    unordered_set<int> s;
    for (int i=0;i<n;i++){
        if (has_forced_edge[i])continue;
        if (visited[i])
            s.insert(i); 
    }
    for (int i=n; i<2*n; i++){
        if (has_forced_edge[i-n])continue;
        if (visited[i])
            s.insert(i-n);
    }

    cout << s.size() << endl;
    return 0;
}