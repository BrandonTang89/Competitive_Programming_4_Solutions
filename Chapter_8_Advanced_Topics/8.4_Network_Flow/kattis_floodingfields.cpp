/**Kattis - floodingfields
 * Max flow with vertex capacities modelling. We make a statespace graph with nodes of the form
 * (time, row, col) each with vertex capacity 1 for time = 0..h, row = 0..n-1, col = 0..n-1. These
 * represent the cows existing when the water level is at water[time] and the cow is at (row, col).
 * Obviously we connect a source to (0, row, col) for all (row, col) with a cow at the start. We
 * also connect all (h, row, col) to a sink since a cow surviving on any node at time h will survive
 * the entire problem. In between, we connect adjacent (t, r, c) with (t+1, r+dr[i], c+dc[i]) if the
 * water level at (r+dr[i], c+dc[i]) is higher than water[t]. We run Dinic's and each unit of flow
 * represents 1 surviving cow.
 *
 * Time: O(maxFlow = k), Space: O(h * n^2)
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

int n, k, h;
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
        // cout << "adding edge (" << u / (n * n) << ", " << (u % (n * n)) / n << ", " << u % n
        //      << ") -> (" << v / (n * n) << ", " << (v % (n * n)) / n << ", " << v % n
        //      << ") with weight " << w << endl;
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
    cin >> n >> k >> h;

    vector<vector<int>> heights(n, vector<int>(n));
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cin >> heights[r][c];
        }
    }

    max_flow mf((h + 1) * n * n + 2);
    int src = (h + 1) * n * n, sink = (h + 1) * n * n + 1;

    int dr[] = {1, -1, 0, 0};
    int dc[] = {0, 0, 1, -1};

    for (int i = 0; i < k; i++) {
        int r, c;
        cin >> r >> c;
        mf.add_edge(src, r * n + c, 1);
    }

    vector<int> water(h);
    for (int i = 0; i < h; i++) {
        cin >> water[i];
    }

    for (int i = 0; i < h; i++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (heights[r][c] > water[i]) {
                    mf.add_edge(i * n * n + r * n + c, (i + 1) * n * n + r * n + c, 1);
                }

                for (int j = 0; j < 4; j++) {
                    int nr = r + dr[j];
                    int nc = c + dc[j];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= n) continue;
                    if (heights[nr][nc] > water[i]) {
                        mf.add_edge(i * n * n + r * n + c, (i + 1) * n * n + nr * n + nc, 1);
                    }
                }
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            mf.add_edge(h * n * n + r * n + c, sink, 1);
        }
    }
    for (int i = 0; i < (h + 1) * n * n; i++) {
        mf.set_node(i, 1);
    }
    mf.set_node(src, INF);
    mf.set_node(sink, INF);

    cout << mf.dinic(src, sink) << endl;

    return 0;
}