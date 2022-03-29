/**Kattis - transportation
 * Max flow with vertex capacities. We let each state and each transportation firm be a node.
 * Each state has infinite capacities, and each transportation firm has a capacity of 1.
 * We connect the source to each state with raw materials with a capacity of 1. We connect the sink
 * to each state with a factory with a capacity of 1. For each transportation firm, we conect
 * the states it serves with a bidirectional edge to itself (capacity 1).
 * 
 * Time: O(V^2 E), Space: O(V + E).
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

    void add_edge_internal(int u, int v, ll w) {
        if (u == v) return;              // safeguard: no self loop
        EL.emplace_back(v, w, 0);        // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);  // remember this index
        EL.emplace_back(u, 0, 0);        // back edge
        AL[v].push_back(EL.size() - 1);  // remember this index
    }

   int in_node(int v) { return v; }
   int out_node(int v) { return v + V / 2; }
   public:
    max_flow(int initialV) {
        V = 2 * initialV;
        EL.clear();
        AL.assign(V, vi());  // double the nodes because vertex capacities
    }

    void set_node(int u, ll w) {  // set vertex capacity, MUST BE CALLED FOR EACH NODE
        add_edge_internal(in_node(u), out_node(u), w);
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        add_edge_internal(out_node(u), in_node(v), w);
        if (directed == false) {
            add_edge_internal(out_node(v), in_node(u), w);
        }
    }

    ll dinic(int s, int t) {
        s = in_node(s);
        t = out_node(t);
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int n, num_raw, num_fac, num_trans;
map<string, int> m;
set<int> raws, facs;
string state_name;
int main() {
    cin >> n >> num_raw >> num_fac >> num_trans;
    int state_counter = 1;
    for (int i = 0; i < num_raw; i++) {
        cin >> state_name;
        if (m.find(state_name) == m.end()) {
            m[state_name] = state_counter++;
        }
        raws.insert(m[state_name]);
    }
    for (int i = 0; i < num_fac; i++) {
        cin >> state_name;
        if (m.find(state_name) == m.end()) {
            m[state_name] = state_counter++;
        }
        facs.insert(m[state_name]);
    }

    max_flow G(n + num_trans + 2);
    for (int i = 1; i <= num_trans; i++) {
        int k, transport_node = i + n;
        cin >> k;
        for (int j = 0; j < k; j++) {
            cin >> state_name;
            if (m.find(state_name) == m.end()) {
                m[state_name] = state_counter++;
            }

            G.add_edge(m[state_name], transport_node, 1, false);
        }
        G.set_node(transport_node, 1);
    }

    for (auto i : raws) {
        G.add_edge(0, i, 1);  // from source
    }
    for (auto i : facs) {
        G.add_edge(i, n + num_trans + 1, 1);  // to sink
    }
    for (int i = 1; i <= n; i++) {
        G.set_node(i, INF);
    }
    G.set_node(0, INF);
    G.set_node(n + num_trans + 1, INF);
    cout << G.dinic(0, n + num_trans + 1);

    return 0;
}