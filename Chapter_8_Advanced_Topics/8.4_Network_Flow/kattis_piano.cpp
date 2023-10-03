/**Kattis - piano
 * Decent max flow modelling question. We make 100+m+2 nodes, 0 is the sink, 1-100 are the days and
 * 101 to 100+m are the pianos to move. We connect the src to each of the weekdays with p/2 cap. We
 * connect each piano to the sink with 1 cap. Then we connect each day to the pianos that can be
 * moved on that day by edges of cap 1. Just do a bit of observing to see that this is indeed the
 * correct model.
 *
 * Time: O(V^2*E) (V = 100+m+2, E = 100*m) Honestly should probably be too slow but it seems that
 * generally these flow questions don't really hit the worst case scenario.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int m, p;
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
    void add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v) return;                       // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index
    }

    void reset()  // use if you want to add more edges and reuse the graph
    {
        for (auto &[v, cap, flow] : EL) flow = 0;
    }

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
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> m >> p;
        p /= 2;

        max_flow mf(100 + m + 2);
        int src = 0, sink = 100 + m + 1;

        for (int i = 1; i <= 100; i++) {
            if (!(i % 7 == 0 || i % 7 == 6)) {  // exclude weekends first
                mf.add_edge(src, i, p);
            }
        }

        for (int i = 1; i <= m; i++) {
            int a, b;
            cin >> a >> b;
            mf.add_edge(100 + i, sink, 1);

            for (int j = a; j <= b; j++) {
                mf.add_edge(j, 100 + i, 1);
            }
        }

        ll totalFlow = mf.dinic(src, sink);
        if (totalFlow == m) {
            cout << "fine\n";
            continue;
        }

        mf.reset();
        for (int i = 1; i <= 100; i++) {
            if (i % 7 == 0 || i % 7 == 6) {  // include weekends
                mf.add_edge(src, i, p);
            }
        }
        totalFlow = mf.dinic(src, sink);
        if (totalFlow == m) {
            cout << "weekend work\n";
            continue;
        }

        cout << "serious trouble\n";
    }

    return 0;
}