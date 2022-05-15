/**Kattis - catering
 * Reading online solutions, I see that this problem can be solved by reduction to a weighted MCBM
 * https://www.csc.kth.se/~austrin/icpc/finals2015solutions.pdf
 *
 * Here, I proposed an alternative solution that directly uses min_cost_max_flow. The central
 * idea is that if we just run the MCMF algorithm directly on the graph of locations, we will not
 * get the flows (which represent the teams) to pass through all the locations. But what if we
 * assigned a super super large negative cost to the locations (vertex cost)? Then the flows
 * will try to pass through all the locations! This is exactly what we want. We can do this by
 * using the vertex spliting technique.
 *
 * We create a graph with 2*n + 2 nodes, node 0 is the source, 2*n+1 is the sink. Nodes 1 to n are
 * the "in" points of the events, and nodes n+1 to 2n are the "out" points of the events. We connect
 * all out points of the events to the in nodes of events that begin later. We then find the MCMF
 * of sending k flows through the graph.
 *
 * Note that this technique only works because the locations/events form a DAG, ie we are not able
 * to go from event A to event B then back to event A somehow. If we had a cycle, due to the large
 * negative cost, we would get a negative cycle which would break our MCMF algorithm, even with
 * assigning a max capacity of 1 between the in or out nodes of each event.
 *
 * Note this extremely difficult to catch "bug": while it is not explicitly stated, a team cannot
 * pass through a location without catering for it! Previously i connceted the in node of each event
 * with the in node of other events that start later. This would allow a team to use an indirect
 * route between events, but this is not allowed in the problem.
 *
 * Time: O(V^2*E^2), Space: O(V + E)
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
            // cout << "u " << u << " dist " << d[u] << endl;
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
        // cout << "adding edge " << u << " " << v << " " << w << " " << c << endl;
        if (u == v) return;                   // safeguard: no self loop
        EL.emplace_back(v, w, 0, c);          // u->v, cap w, flow 0, cost c
        AL[u].push_back(EL.size() - 1);       // remember this index
        EL.emplace_back(u, 0, 0, -c);         // back edge
        AL[v].push_back(EL.size() - 1);       // remember this index
        if (!directed) add_edge(v, u, w, c);  // add again in reverse
    }

    pair<ll, ll> mcmf(int s, int t, ll tf = INF) {  // cap the flow at tf
        ll mf = 0;                                  // mf stands for max_flow
        while (SPFA(s, t) && mf != tf) {            // at most run min(tf, V) times
            last.assign(V, 0);                      // important speedup
            while (ll f = DFS(s, t, tf - mf))       // exhaust blocking flows in O(E)
                mf += f;                            // send at most tf-mf more flow
        }
        return {mf, total_cost};  // note to check if mf == tf if needed
    }
};

int main() {
    ll n, k;
    cin >> n >> k;
    ll big_num = (1e11);
    min_cost_max_flow mcmf(2 * n + 2);
    // 0 is source
    // 1 to n is the normal nodes
    // n+1 to 2n is the extra nodes
    // 2n + 1 is the sink
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j <= n; j++) {
            ll cost;
            ll cap = k;
            cin >> cost;
            if (i == 0) mcmf.add_edge(i, j, cap, cost);
            if (i != 0) mcmf.add_edge(i + n, j, cap, cost);
        }
    }
    for (int i = 1; i <= n; i++) {
        mcmf.add_edge(i, i + n, 1, -big_num);
        mcmf.add_edge(i + n, 2 * n + 1, k, 0);
        mcmf.add_edge(i, 2 * n + 1, k, 0);
    }
    mcmf.add_edge(0, 2 * n + 1, k, 0);
    auto [flow, cost] = mcmf.mcmf(0, 2 * n + 1, k);
    assert(flow == k);
    assert(cost + (long long)n * big_num < big_num);
    cout << cost + (long long)n * big_num << endl;
}