/**Kattis - conveyorbelts
 * Mostly reading comprehension and max flow modelling. The actual (non-library) code is very short.
 * The modelling is as follows: we expand each junction into k nodes where the ith node represents
 * that junction at times x*k + i for x >= 0. Then for each conveyor belt, we connect the relevant
 * nodes together with directed edges of capacity 1. We connect the source to each relevant producer
 * node (only 1 of the k nodes that represent the producer, specifically the (i+1)%k node for the
 * ith producer). We connect each warehouse to the sink with an edge with infinite capacity since we
 * can accept multiple items at the same time at the warehouse. Then we run max flow and the answer
 * is the max flow. Draw it out and observe that yes this works.
 *
 * Time: O(V^2 * E) (V = n*k + 2, E = O(m*k)), Space: O(V + E)
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

    bool BFS(int s, int t)
    {  // find augmenting path
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

    ll DFS(int u, int t, ll f = INF)
    {  // traverse from s->t
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
    max_flow(int initialV) : V(initialV)
    {
        EL.clear();
        AL.assign(V, vi());
    }

    // if you are adding a bidirectional edge u<->v with weight w into your
    // flow graph, set directed = false (default value is directed = true)
    int add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v) return -1;                    // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index

        return EL.size() - 2;  // return index of u->v edge
    }

    ll getFlow(int edgeLabel) { return get<2>(EL[edgeLabel]); }

    ll dinic(int s, int t)
    {
        ll mf = 0;                    // mf stands for max_flow
        while (BFS(s, t)) {           // an O(V^2*E) algorithm
            last.assign(V, 0);        // important speedup
            while (ll f = DFS(s, t))  // exhaust blocking flow
                mf += f;
        }
        return mf;
    }
};

int main()
{
    int n, m, k;
    cin >> n >> k >> m;
    max_flow mf(n * k + 2);
    int src = n * k, sink = n * k + 1;

    for (int e = 0; e < m; e++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;

        for (int i = 0; i < k; i++) {
            mf.add_edge(u * k + i, v * k + (i + 1) % k, 1);
        }
    }

    for (int i = 0; i < k; i++) {
        mf.add_edge(src, i * k + (i + 1) % k, 1);
        mf.add_edge((n - 1) * k + i, sink, INF);
    }

    int totalFlow = mf.dinic(src, sink);
    cout << totalFlow << endl;

    return 0;
}