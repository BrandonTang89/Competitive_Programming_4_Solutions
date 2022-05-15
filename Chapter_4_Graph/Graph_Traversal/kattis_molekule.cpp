/* Kattis - molekule
Observation 1:
    Since the molecule is a completely connected and has n-1 edges, it is a tree. It is a known
    fact that trees are bipartite. As such, we can just select the directions to go from
    one partition to the other for a max of a path of only length 1 (minimum obviously).

    We do this by bicolouring the graph and setting the direction to be from one colour to the other
    colour.

Time: O(V + E), Mem: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef long double ld;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, u, v;
vector<int> adjlist[100009];
queue<int> q;
vector<pair<int,int>> el;
int state[100009]; //-1 unvisited, 0 colour 0, 1 colour 1 
//(note this selection allows the use of !state[u] for the other colour)

int main(){
    fast_cin();
    memset(state, -1, sizeof(state));
    cin >> n;
    for (int i=0;i<n-1;i++){
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
        el.emplace_back(u, v);
    }   

    q.push(0);
    state[0] = 0;
    while(!q.empty()){
        u = q.front();
        q.pop();

        for (auto v: adjlist[u]){
            if (state[v] == -1){
                state[v] = !state[u];
                q.push(v);
            }
        }
    }

    for (auto i: el){
        cout << state[i.first] << endl;
    }

    return 0;
}