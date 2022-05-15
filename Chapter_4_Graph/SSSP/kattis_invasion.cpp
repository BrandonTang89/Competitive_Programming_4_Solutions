/* Kattis - invasion
Multi source dijkstra, but iteratively. So we dijstra from the first base. Then we 
repeat with the second base and so on so forth without resetting the dist array.

Note that the dijkstra cost should become lighter since we should be updating less and less
dist values as we go on.

Time: O(VE log V), Mem: O(E + V)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

int n, e, u, v, w, a, k;
vector<vector<tuple<int,int>>> adjlist;
vector<int> dist, sources;
priority_queue<tuple<int,int>, vector<tuple<int,int>>, greater<tuple<int,int>>> pq;

int main(){
    fast_cin();
    while (true){
        cin >> n >> e >> a >> k;
        if (n == 0)break;
        adjlist.assign(n, vector<tuple<int,int>>());
        dist.assign(n, (int)1e8);
        sources.assign(a, -1);
        while (!pq.empty())pq.pop();

        for (int i=0;i<e;i++){
            cin >> u >> v >> w;
            u--; v--;
            adjlist[u].emplace_back(w, v);
            adjlist[v].emplace_back(w, u);
        }

        for (int i=0;i<a;i++){
            cin >> sources[i];
            sources[i]--;
        }

        for (int t=0;t<a;t++){
            // build sources[t];
            dist[sources[t]] = 0;
            pq.emplace(0, sources[t]);

            while (!pq.empty()){
                auto [d, u] = pq.top();
                pq.pop();
                if (d > dist[u])continue; // inferior pair
                for (auto &[w, v]: adjlist[u]){
                    if (dist[u]+w >= dist[v])continue; // relaxing through this node doesn't help
                    dist[v] = dist[u] + w;
                    pq.emplace(dist[v], v);
                }
            }

            int ans = 0;
            for (int i=0;i<n;i++){
                //cout << dist[i] << " "; 
                if (dist[i] >= k)ans++;
            }
            //cout << endl;

            cout << ans << endl;
        }

        cout << endl;
    }



    return 0;
}