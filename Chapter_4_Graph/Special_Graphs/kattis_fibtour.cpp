/* Kattis - fibtour
A pretty long question.
preprocess a map of m[fib(i)] = i (for all fib(i) < 1e18)
for each road, there exist an edge u -> v iff m[h[u]] + 1 = m[h[v]]
we now have a dag, we then do a topo sort
then we process the nodes in the topological order, propgating the dist to achieve the longest path...

Note that we need to take care of the special edges case of height = 1. If are exist a road connecting
2 buildings of height 1, both of those buildings start with dist = 2. This is because all routes that
start from either of them can just be extended by starting at the other. Note that we cannot just make 
a birectional edge because this would mess up the toposort subroutine.

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

int n, e, u, v, w; 
vector<vector<int>> adjlist;
vector<ll> h; // heights
map<ll,ll> m; // m[fib(i)] = i
vector<int> ts, dist;
vector<bool> dual_1;

void toposort(int u){
    dist[u] = 1;
    for (auto v: adjlist[u]){
        if (dist[v] == 0){
            toposort(v);
        }
    }
    ts.push_back(u);
}

int main(){

    // On the fly fib calculation
    m.clear();
    ll fib[2] = {1, 1};
    m[0] = m[1] = 1;
    for (int i = 2; i < 89; i++){
        fib[i&1] = fib[0] + fib[1]; 
        m[fib[i&1]] = i;
        //printf("m[%lld] = %d\n",fib[i&1], i);
        // all the way until abit more than 1e18
    }

    cin >> n >> e;
    adjlist.assign(n, vector<int>());
    h.assign(n, -1);
    dual_1.assign(n, false);
    for (int i=0;i<n;i++){
        cin >> h[i];
    }

    for (int i=0;i<e;i++){
        cin >> u >> v;
        u--; v--;
        if (m[h[u]] + 1 == m[h[v]]){
            adjlist[u].emplace_back(v);
        }
        else if (m[h[v]] + 1 == m[h[u]]){
            adjlist[v].emplace_back(u);
        }
        else if (h[v] == 1 && h[u] == 1){ // edge case
            dual_1[u] = dual_1[v] = true;
        }
    }

    /*
    for (int i=0;i<n;i++){
        for (auto v:adjlist[i]){
            cout << v << " ";
        }
        cout << endl;
    }*/
    
    // generate toposort
    dist.assign(n, 0);
    for (int i=0;i<n;i++){
        if (dist[i] == 0){
            toposort(i);
        }
    }
    reverse(ts.begin(), ts.end());
    
    dist.assign(n, 0);
    for (int i=0;i<n;i++){
        if (h[i] == 1 && dual_1[i]){
            dist[i] = 2;
        }
        else if (m[h[i]] > 0){ // is a fibo number
            dist[i] = 1;
        }
    }
    int total_max = 0;
    for (auto u: ts){ // process in topological order
        total_max = max(total_max, dist[u]);
        //printf("dist[%d] = %d\n", u, dist[u]);
        for (auto v: adjlist[u]){
            // longest path
            dist[v] = max(dist[v], dist[u] + 1);
        }
    }

    cout << total_max << endl;
    return 0;
}