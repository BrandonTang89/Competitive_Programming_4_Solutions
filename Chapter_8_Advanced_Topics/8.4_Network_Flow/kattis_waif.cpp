/**Kattis - waif
 * Quite a straightforward max flow problem. The modelling is as follows: src to each category with
 * capacity equal to the max number of toys from that category. src to a special category called
 * noCat with infinite capacity. Each category (including noCat) to each toy within that category
 * with capacity 1. Each toy to each children that can play with that toy with capacity 1. Each
 * child to sink with capacity 1. Draw this out and observe that this is correct. We just run
 * Dinic's algorithm and report the answer.
 * 
 * Time: O(V^2 * E), Mem: O(V + E) (V = O(n+m+p), E = O(n*m + p))
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

int n, m, p;  // children, toys, toy categories
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
    cin >> n >> m >> p;
    max_flow mf(n + m + p + 3);
    int src = n + m + p + 1, sink = n + m + p + 2, noCat = n + m + p;
    unordered_set<int> toys;
    for (int i = 0; i < m; i++) {
        toys.insert(i);
    }

    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int toy;
            cin >> toy;
            mf.add_edge(n + toy - 1, i, 1);
        }
        mf.add_edge(i, sink, 1);
    }
    for (int i = 0; i < p; i++) {
        int l, r;
        cin >> l;
        for (int j = 0; j < l; j++) {
            int toy;
            cin >> toy;
            mf.add_edge(n + m + i, n + toy - 1, 1);
            toys.erase(toy - 1);
        }
        cin >> r;
        mf.add_edge(src, n + m + i, r);
    }

    for (auto toy : toys) {
        mf.add_edge(noCat, n + toy, 1);
    }
    mf.add_edge(src, noCat, INF);
    cout << mf.dinic(src, sink) << endl;

    return 0;
}