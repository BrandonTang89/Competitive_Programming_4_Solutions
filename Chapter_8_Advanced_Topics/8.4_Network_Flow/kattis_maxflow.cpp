/**Kattis - maxflow
 * Standard max-flow problem. Avoid self-loops and compress edges.
 * 
 * Time: O(V^2*E), Space: O(V^2)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>  
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;  // <dest, cap, flow>
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

    void reset()
    {  // use if you want to add more edges and reuse the graph
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
int main(){
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
    vector<vector<int>> adjmat(n, vector<int>(n, 0));
    max_flow mf(n);
    for (int i=0; i<m; i++){
        int u, v, w;
        cin >> u >> v >> w;
        adjmat[u][v] += w;
    }
    for (int u=0; u<n; u++){
        for (int v=0; v<n; v++){
            if (u == v) continue; // important to avoid self loops
            if (adjmat[u][v] > 0){
                adj[u].push_back({v, mf.add_edge(u, v, adjmat[u][v])});
            }
        }
    }

    ll flow = mf.dinic(s, t);
    vector<tuple<int, int, int>> used;
    for (int i=0; i<n; i++){
        for (auto e : adj[i]){
            if (mf.getFlow(e.second) > 0){
                used.push_back({i, e.first, mf.getFlow(e.second)});
            }
        }
    }
    cout << n << " " << flow << " " << used.size() << endl;
    for (auto e : used){
        cout << get<0>(e) << " " << get<1>(e) << " " << get<2>(e) << endl;
    }

    return 0;
}