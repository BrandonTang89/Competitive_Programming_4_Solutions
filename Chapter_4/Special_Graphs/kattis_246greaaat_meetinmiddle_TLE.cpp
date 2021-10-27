/* Kattis - 236greaaat

With all cheers per edge, can assume nodes between 0 to max_node = dest - min_cheer <= 2*dest.
Obviously if node < 0, eventually we have to go above 0 so we should just go above 0 first.
If node - dest > -min_cheer, then we can do the min cheer first, this wont go below 0 cos mincheer
always gonna be at most dest in magnitude.

also if min dist from 0 to u is x, then min dist from (n-u) to u is x. We can use this to meet
in the middle. If we already know dist 0->u and u -> n, we dont need to continue from u to propagate
further.

long long is slower than int, so we use it only when needed. c style IO is faster, thus we use it.

Doing dijkstra (original), I am unable to AC despite optimisations above.

V <= 400000, E <= 200000000 (200 million)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll w, INF = (ll)1e8;
int e, dest, u, v;
vector<tuple<int, ll>> cheers; // d, weight
vector<ll> dist, dist_to_n;
vector<int>parent;
//priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, greater<tuple<ll, ll>>> pq;
set<tuple<ll, int>> pq;
int main() {
    scanf("%d %d", &e, &dest);
    cheers.emplace_back(1, 1);
    int min_cheer = 0;
    for (int i = 0; i < e; i++) {
        scanf("%d %lld", &v, &w);
        cheers.emplace_back(v, w);
        min_cheer = min(min_cheer, v);
    }
    e++;
    int max_node = dest - min_cheer + 1;
    //cout << max_node << endl;
    dist.assign(max_node + 3 , INF);
    dist_to_n.assign(max_node + 3, INF);
    parent.assign(max_node + 3, -1);

    // dijkstra to generate graph + SSSP in increasing distance
    dist[0] = 0;
    parent[0] = -1;
    pq.insert({0, 0});
    int meet_at = 0;
    ll total_dist = INF;
    for (int i=1;i<max_node+3; i++){
        pq.insert({INF, i});
    }
    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());
        if (dist[u] >= total_dist)break;
        
        if (dest > u)
            dist_to_n[dest - u] = dist[u];
        if (dist_to_n[u] != INF){
            if (dist[u] + dist_to_n[u] < total_dist){
                meet_at = u;
                total_dist = dist[u] + dist_to_n[u];
            }
            continue;
        }
         
        //printf("u: %d, dist[u]: %lld\n", u, dist[u]); 
        for (int i=0; i < e; i++) {
            auto [delta, w] = cheers[i];
            v = delta + u;
            if (v <= 0 || v > max_node)continue;
            
            if (dist[u] + w >= dist[v])
                continue;  // relaxing through this node doesn't help

            if (dist[u] + w >= total_dist)continue;

            pq.erase(pq.find(make_tuple(dist[v], v)));
            dist[v] = dist[u] + w;
            parent[v] = i;
            pq.insert(make_tuple(dist[v], v));
        }
    }

    /*
    cout << total_dist << endl;
    cout << meet_at << endl;
    cout << dist[dest] << endl;*/
    
    vector<int> path;
    int cur_node = meet_at;
    while (cur_node != 0) {
        //printf("cur_node: %lld, p[u]: %lld\n", cur_node, parent[cur_node]); 

        path.emplace_back(parent[cur_node]);
        auto [d, w] = cheers[parent[cur_node]];
        cur_node = cur_node - d;
    }
    cur_node = dest-meet_at;
    while (cur_node != 0) {
        path.emplace_back(parent[cur_node]);
        auto [d, w] = cheers[parent[cur_node]];
        cur_node = cur_node - d;
    }
    
    //sort(path.begin(), path.end());
    printf("%d\n", (int) path.size());
    for (auto i : path) {
        printf("%d ",i+1);
    }
    printf("\n"); 
    return 0;
}