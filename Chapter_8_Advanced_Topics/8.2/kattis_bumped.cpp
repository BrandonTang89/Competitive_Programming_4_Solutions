/**Kattis - bumped
 * A decently managable state space search Dijkstra problem. Here we just have state as
 * (city, have_ticket). and we can use the flight edges iff we still have a ticket.
 * 
 * Time: O(E log V), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
#define MAXN 50001

ll n, r, f, u, v, w, source, dest;
map<pair<ll,bool>, ll> dist;
priority_queue<tuple<ll,ll,ll>, vector<tuple<ll,ll,ll>>, greater<tuple<ll,ll,ll>>> pq;
vector<pair<ll, ll>> adjlist[MAXN], fadjlist[MAXN];

int main(){
    cin >> n >> r >> f >> source >> dest;
    for (ll i = 0; i < r; i++){
        cin >> u >> v >> w;
        adjlist[u].emplace_back(v, w);
        adjlist[v].emplace_back(u, w);
    }
    for (ll i=0; i< f; i++){
        cin >> u >> v;
        fadjlist[u].emplace_back(v, 0);
    }

    dist[{source, true}] = 0;
    pq.emplace(0,source, true);

    while (!pq.empty()){
        ll d = get<0>(pq.top());
        ll u = get<1>(pq.top());
        bool have_ticket = get<2>(pq.top());
        pq.pop();

        if (u == dest){
            cout << dist[{u, have_ticket}] << endl;
            return 0;
        }

        if (d > dist[{u, have_ticket}]) continue; // inferior pair

        for (auto &[v, w] : adjlist[u]){
            if (dist.count({v, have_ticket}) && dist[{v, have_ticket}] <= d + w){
                continue;
            }
            dist[{v, have_ticket}] = d + w;
            pq.emplace(d + w, v, have_ticket);
        }

        if (have_ticket){
            for (auto &[v, w] : fadjlist[u]){
                if (dist.count({v, false}) && dist[{v, false}] <= d + w){
                    continue;
                }
                dist[{v, false}] = d + w;
                pq.emplace(d + w, v, false);
            }
        }
    }

    


    return 0;
}