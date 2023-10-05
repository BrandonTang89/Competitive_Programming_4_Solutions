/**Kattis - congest
 * Dijkstra to DAG + Max Flow problem. Since we should only consider the shortest paths, we start by
 * running Dijkstra from the destination (vertex 0) and constructing the DAG of shortest paths that
 * leads to vertex 0 by recording the parents of each vertex. Then we observe that when we run max
 * flow with the source to connected to cities with the same distance from the destination (with
 * weight = number of commuters at that vertex) and the edges in the graph all with capacity 1, we
 * get the number of commuters from these vertices that can reach the destination. We do not have to
 * worry about other commuters since they would pass through each vertex and a different time. We
 * add up the number of commuters from each distance from the source and we are done. We also make
 * the optimisation that if there is only 1 commuter, he will definitely make it so we don't need to
 * run max flow.
 * 
 * Time: O(?) a lot of pruning so it is hard to make a meaningful bound, Space: O(n + m)
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

int n, m, c;
vector<vector<int>> parents;
vector<vector<pair<int, int>>> adjlist;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<int> dist;
int main()
{
    cin >> n >> m >> c;
    adjlist.assign(n, vector<pair<int, int>>());
    parents.assign(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        adjlist[u].push_back({v, w});
        adjlist[v].push_back({u, w});
    }

    dist.assign(n, INT_MAX);
    pq.push({0, 0});
    dist[0] = 0;

    // Dijkstra from 0
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;
        for (auto &[v, w] : adjlist[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
                parents[v].clear();
                parents[v].push_back(u);  // allow for repeated of the same parent if multiple edges
            }
            else if (dist[u] + w == dist[v]) {
                parents[v].push_back(u);
            }
        }
    }

    vector<int> commuters(n, 0);
    for (int i = 0; i < c; i++) {
        int u;
        cin >> u;
        u--;
        commuters[u]++;
    }

    vector<pair<int, int>> dists;
    for (int u = 0; u < n; u++) {
        if (commuters[u] > 0) dists.push_back({dist[u], u});
    }
    sort(dists.begin(), dists.end());

    int ans = 0;
    while ((int)dists.size() > 0) {
        auto [d, u] = dists.back();
        dists.pop_back();
        vector<int> selected = {u};
        while ((int)dists.size() > 0 && dists.back().first == d) {
            selected.push_back(dists.back().second);
            dists.pop_back();
        }

        max_flow mf(n + 1);
        int src = n, sink = 0;
        for (int u = 0; u < n; u++) {
            for (auto &v : parents[u]) {
                mf.add_edge(u, v, 1);
            }
        }
        if ((int)selected.size() == 1 &&
            commuters[selected[0]] == 1) {  // optimisation to skip dinic if only 1 commuter
            ans += 1;
            continue;
        }
        for (auto &u : selected) {
            mf.add_edge(src, u, commuters[u]);
        }
        ans += mf.dinic(src, sink);
    }

    cout << ans << endl;

    return 0;
}