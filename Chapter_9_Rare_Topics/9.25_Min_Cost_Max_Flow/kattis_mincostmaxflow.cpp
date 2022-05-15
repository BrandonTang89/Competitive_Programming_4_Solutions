/**Kattis - mincostmaxflow
 * Basic and direct mincostmaxflow. 
 * 
 * Time: O(V^2 E^2), Space: O(E + V)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll, ll> edge;
typedef vector<int> vi;
typedef vector<ll> vll;

const ll INF = 1e18;  // INF = 1e18, not 2^63-1 to avoid overflow

class min_cost_max_flow {
   private:
    int V;
    ll total_cost;
    vector<edge> EL;
    vector<vi> AL;
    vll d;
    vi last, vis;

    bool SPFA(int s, int t) {  // SPFA to find augmenting path in residual graph
        d.assign(V, INF);
        d[s] = 0;
        vis[s] = 1;
        queue<int> q({s});
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = 0;
            for (auto &idx : AL[u]) {                            // explore neighbors of u
                auto &[v, cap, flow, cost] = EL[idx];            // stored in EL[idx]
                if ((cap - flow > 0) && (d[v] > d[u] + cost)) {  // positive residual edge
                    d[v] = d[u] + cost;
                    if (!vis[v]) q.push(v), vis[v] = 1;
                }
            }
        }
        return d[t] != INF;  // has an augmenting path
    }

    ll DFS(int u, int t, ll f = INF) {  // traverse from s->t
        if ((u == t) || (f == 0)) return f;
        vis[u] = 1;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {  // from last edge
            auto &[v, cap, flow, cost] = EL[AL[u][i]];
            if (!vis[v] && d[v] == d[u] + cost) {  // in current layer graph
                if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                    total_cost += pushed * cost;
                    flow += pushed;
                    auto &[rv, rcap, rflow, rcost] = EL[AL[u][i] ^ 1];  // back edge
                    rflow -= pushed;
                    vis[u] = 0;
                    return pushed;
                }
            }
        }
        vis[u] = 0;
        return 0;
    }

   public:
    min_cost_max_flow(int initialV) : V(initialV), total_cost(0) {
        EL.clear();
        AL.assign(V, vi());
        vis.assign(V, 0);
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, ll w, ll c, bool directed = true) {
        if (u == v) return;                   // safeguard: no self loop
        EL.emplace_back(v, w, 0, c);          // u->v, cap w, flow 0, cost c
        AL[u].push_back(EL.size() - 1);       // remember this index
        EL.emplace_back(u, 0, 0, -c);         // back edge
        AL[v].push_back(EL.size() - 1);       // remember this index
        if (!directed) add_edge(v, u, w, c);  // add again in reverse
    }

    pair<ll, ll> mcmf(int s, int t, ll tf = INF) {  // cap the flow at tf
        ll mf = 0;                                  // mf stands for max_flow
        while (SPFA(s, t)) {                        // an O(V^2*E) algorithm
            last.assign(V, 0);                      // important speedup
            while (ll f = DFS(s, t, tf - mf))       // exhaust blocking flow,
                mf += f;                            // send at most tf-mf more flow
        }
        return {mf, total_cost};  // note to check if mf == tf if needed
    }
};

int n, e, s, t;
int main() {
    cin >> n >> e >> s >> t;
    min_cost_max_flow mcmf(n);
    for (int i = 0; i < e; ++i) {
        int u, v, cap, cost;
        cin >> u >> v >> cap >> cost;
        mcmf.add_edge(u, v, cap, cost);
    }
    auto [flow, cost] = mcmf.mcmf(s, t);
    cout << flow << " " << cost << endl;
    return 0;
}