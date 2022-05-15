/**Kattis - jupiter
 * This is really great practise in max flow modelling, here we construct a massive graph. This
 * graph is a stack of n small graphs that represent each downlink event.
 *
 * In each small graph, we have 4 layers comprising the sensors (length s), in of queue (length q),
 * out of queue (length q), in of downlink (1), out of downlink (1). From the source to the sensors,
 * we have the capacities equal to the data going into the sensors before that downlink event. Then
 * between the sensors and the in-queues, we have infinite capacities that link each sensor to their
 * respective queues. Across the in-queue and out-queue, we have a capacity of the queue size
 * (vertex capacity). From the out of queue to in of downlink, we have inifinite capacity. However
 * between the in and out of downlink we have the capcity of the downlink. This arrangement allows
 * the downlink to process any amount of info from any of the queues as long the the total size is
 * smaller than the capcity of the downlink. Connecting the out of downlink of each small graph is
 * an edge of infinite capacity to the sink (earth).
 *
 * The key idea to "preserve data in queues between downlinks" comes by adding edges across the
 * small graphs. For each queue, we connect the out-queue of the previous small graph with the
 * in-queue of the next small graph. This is representing the fact that the information not
 * downlinked in the previous session must be added to that queue before the next session. These
 * cross-edges have infinite capacity as well.
 *
 * See the picture here https://pasteboard.co/aIvgRiWdHQE1.jpg. The cross edges are in purple. We
 * could actually reduce the number of nodes and edges by n if we compress all the downlink-out
 * nodes into the sink. But hey AC is AC.
 *
 * Doing all these, we have a graph of about 4800 vertices which might be abit scary, but since the
 * graph is very flat (ie the longest path from source to sink is at most abit more than 2*n = 60 by
 * crossing all the cross link edges), dinic's algorithm will not need to BFS that many times! So it
 * is actually not TLE. The main difficulty is labelling the nodes of our massive graph and then
 * coding meticulously such that our graph is constructed correctly.
 *
 * Time: O(V^2 E), Space: O(V + E)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
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

int n, q, s;
ll total_data = 0;
int temp;
int main() {
    fast_cin();
    cin >> n >> q >> s;
    max_flow G(n * s + 2 * n * q + 2 * n + 2);  // massive graph
    for (int i = 1; i <= s; i++) {
        cin >> temp;
        for (int j = 0; j < n; j++) {
            G.add_edge(j * s + i, n * s + j * q + temp, INF);  // set sensors to their queue
        }
    }
    for (int i = 1; i <= q; i++) {
        // queue length
        cin >> temp;
        for (int j = 0; j < n; j++) {
            G.add_edge(n * s + j * q + i, n * s + n * q + j * q + i, temp);
        }
    }
    for (int i = 1; i <= n; i++) {
        cin >> temp;
        G.add_edge(n * s + 2 * n * q + i, n * s + 2 * n * q + n + i, temp);  // downlink total amt
        for (int j = 1; j <= s; j++) {
            cin >> temp;
            total_data += temp;
            G.add_edge(0, (i - 1) * s + j,
                       temp);  // information given to the sensor before downlink
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= q; j++) {
            G.add_edge(n * s + n * q + i * q + j, n * s + 2 * n * q + (i + 1), INF);
        }
        G.add_edge(n * s + 2 * n * q + n + (i + 1), n * s + 2 * n * q + 2 * n + 1, INF);  // Sink
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = 1; j <= q; j++) {
            G.add_edge(n * s + n * q + i * q + j, n * s + (i + 1) * q + j, INF);
        }
    }

    if (G.dinic(0, n * s + 2 * n * q + 2 * n + 1) == total_data) {
        cout << "possible" << endl;
    } else {
        cout << "impossible" << endl;
    }
    return 0;
}