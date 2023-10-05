/**Kattis - copsandrobbers
 * Relatively obvious to spot min-cut with vertex capacities problem. We express the grid as a graph
 * and set the vertex capacities to be the cost of building a barricade on that location. We do
 * max-flow min-cut and see if the min-cut is infinite, if so then it is not possible to stop the
 * robbers, else the max-flow is the answer.
 * 
 * Time: O(V^2 * E), Space: O(V + E) where E = O(V) = O(HW)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

// max_flow with vertex capacities
typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e16;  // large enough
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

    void add_edge_internal(int u, int v, ll w)
    {
        if (u == v) return;              // safeguard: no self loop
        EL.emplace_back(v, w, 0);        // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);  // remember this index
        EL.emplace_back(u, 0, 0);        // back edge
        AL[v].push_back(EL.size() - 1);  // remember this index
    }

    int in_node(int v) { return v; }
    int out_node(int v) { return v + V / 2; }

   public:
    max_flow(int initialV)
    {
        V = 2 * initialV;
        EL.clear();
        AL.assign(V, vi());  // double the nodes because vertex capacities
    }

    void set_node(int u, ll w)
    {  // set vertex capacity, MUST BE CALLED FOR EACH NODE
        add_edge_internal(in_node(u), out_node(u), w);
    }

    void add_edge(int u, int v, ll w, bool directed = true)
    {
        add_edge_internal(out_node(u), in_node(v), w);
        if (!directed) {
            add_edge_internal(out_node(v), in_node(u), w);
        }
    }

    ll dinic(int s, int t)
    {
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
int main()
{
    int h, w, t;
    cin >> w >> h >> t;
    vector<vector<char>> grid(h, vector<char>(w));
    int src = -1;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            if (grid[r][c] == 'B') {
                src = r * w + c;
            }
        }
    }
    assert(src != -1);

    vector<int> costs(t);
    for (int i = 0; i < t; i++) cin >> costs[i];

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    max_flow mf(h * w + 1);
    int sink = h * w;
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
                    mf.add_edge(r * w + c, sink, INF);
                    continue;
                }
                mf.add_edge(r * w + c, nr * w + nc, INF);
            }
            if (grid[r][c] != 'B' && grid[r][c] != '.') {
                assert(grid[r][c] - 'a' < t);
                mf.set_node(r * w + c, costs[grid[r][c] - 'a']);
            }
            else
                mf.set_node(r * w + c, INF);
        }
    }

    mf.set_node(sink, INF);
    ll ans = mf.dinic(src, sink);
    if (ans >= INF)
        cout << -1 << endl;
    else
        cout << ans << endl;

    return 0;
}