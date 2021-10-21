#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, w, x, y;
vector<vector<tuple<int,int>>> adjlist;
vector<pair<int,int>> locs;
vector<int> dist, parent, path;
priority_queue<tuple<int,int>, vector<tuple<int,int>>, greater<tuple<int,int>>> pq;

int main(){
    cin >> n;
    n+=2;
    // source at n-2, dest at n-1
    for(int i=0;i<n;i++){
        cin >> x >> y;
        locs.emplace_back(x, y);
    }
    adjlist.assign(n, vector<tuple<int,int>>());
    dist.assign(n, INT_MAX);
    parent.assign(n, -1);

    for (u = 0; u<n; u++){
        for (v=0; v<n; v++){
            if (u == v)continue;
            auto &[x1, y1] = locs[u];
            auto &[x2, y2] = locs[v];
            w = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
            adjlist[u].emplace_back(w, v);
        }
    }
    
    
    dist[n-2] = 0;
    pq.emplace(0, n-2);
    while (!pq.empty()){
        auto [d, u] = pq.top();
        //printf("u: %d, d: %d\n", u, d);
        pq.pop();
        if (d > dist[u])continue; // inferior pair
        for (auto &[w, v]: adjlist[u]){
            if (dist[u]+w >= dist[v])continue; // relaxing through this node doesn't help
            dist[v] = dist[u] + w;
            parent[v] = u;
            pq.emplace(dist[v], v);
        }
    }

    int cur_node = parent[n-1];
    while (cur_node != n-2){
        path.emplace_back(cur_node);
        cur_node = parent[cur_node];
    }
    reverse(path.begin(), path.end());
    for (auto i: path){
        cout << i << endl;
    }
    if (path.size() == 0){
        cout << '-' << endl;
    }






    return 0;
}