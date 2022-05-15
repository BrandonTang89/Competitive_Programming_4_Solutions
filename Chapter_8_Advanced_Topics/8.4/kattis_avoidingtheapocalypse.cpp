/**Kattis - avoidingtheapocalypse
 * A state-space max-flow problem. We have each vertex as (location, time).
 * Each road is a set of directed edges from (u, time) to (v, time + t) for all possible times,
 * with weight p. This represents p people traversing the road in time t. Within each location,
 * we have that (location, t) -> (location, t + 1) with infinite capacity for all locations and
 * times. This represents people waiting at a location for before crossing to other locations.
 * We have a super source going into (starting location, 0) with capacity g to inject our people
 * into the graph. We have a super sink connected to (hospital, max_steps) for all hospitals
 * to represent people who get to the hospital surviving.
 * 
 * Again, there seems to be alot of vertices and edges.. but each path is not more than 100
 * steps because each edge moves to at least the next time step.. So its not as bad as it seems.
 * 
 * Time: O(V^2 E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e18;  // large enough

class max_flow {
   private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {  // find augmenting path
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q({s});
        p.assign(V, {-1, -1});  // record BFS sp tree
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;                                    // stop as sink t reached
            for (auto &idx : AL[u]) {                             // explore neighbors of u
                auto &[v, cap, flow] = EL[idx];                   // stored in EL[idx]
                if ((cap - flow > 0) && (d[v] == -1))             // positive residual edge
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};  // 3 lines in one!
            }
        }
        return d[t] != -1;  // has an augmenting path
    }

    ll DFS(int u, int t, ll f = INF) {  // traverse from s->t
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {  // from last edge
            auto &[v, cap, flow] = EL[AL[u][i]];
            if (d[v] != d[u] + 1) continue;  // not part of layer graph
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[AL[u][i] ^ 1]);  // back edge
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

   public:
    max_flow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    void add_edge(int u, int v, ll w, bool directed = true) {
        if (u == v) return;                       // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index
    }

    ll dinic(int s, int t) {
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int num_tc;
int n, source, g, steps;
int m;
int cti(int pos, int t) { return n * t + pos; }
int main() {
    cin >> num_tc;
    for (int tc = 0; tc < num_tc; tc++) {
        cin >> n;
        cin >> source >> g >> steps;  // source, group size, num_steps
        cin >> m;                     // num_hospital
        max_flow G(n * (steps + 1) + 2);
        int sink = n * (steps + 1) + 1;

        for (int i = 1; i <= n; i++) {
            for (int t = 0; t < steps; t++) {
                G.add_edge(cti(i, t), cti(i, t + 1), INF);
            }
        }

        int hos;
        for (int i = 0; i < m; i++) {
            cin >> hos;
            G.add_edge(cti(hos, steps), sink, INF);
        }

        int e, u, v, p, t;
        cin >> e;
        for (int i = 0; i < e; i++) {
            cin >> u >> v >> p >> t;
            for (int time = 0; time + t <= steps; time++) {
                G.add_edge(cti(u, time), cti(v, time + t), p);
            }
        }

        G.add_edge(0, source, g);

        cout << G.dinic(0, sink) << endl;
    }

    return 0;
}