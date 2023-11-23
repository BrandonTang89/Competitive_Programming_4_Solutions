/**Kattis - neutralground
 * Very standard min-cut with vertex capacities on a grid problem. We just connect the source to all
 * cells with A, connect all cells with B to the sink and connect all cells to their adjacent cells.
 * We set vertex capacities of cells with numbers (with capacity equal to cost of the cell). We then
 * run a max flow algorithm and output max-flow = min-cut.
 * 
 * Time: O((HW)^3), Space: O(HW)
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

// max_flow with vertex capacities
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

int h, w;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, 1, 0, -1};  // up, right, down, left
inline int idx(int r, int c) { return r * w + c; }
int main()
{
    cin >> w >> h;
    vector<vector<char>> grid(h, vector<char>(w));
    max_flow mf(h * w + 2);
    int src = h * w, sink = h * w + 1;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> grid[i][j];
            if (grid[i][j] == 'A') {
                mf.set_node(idx(i, j), 1e9);
                mf.add_edge(src, idx(i, j), 1e9);
            }
            else if (grid[i][j] == 'B') {
                mf.set_node(idx(i, j), 1e9);
                mf.add_edge(idx(i, j), sink, 1e9);
            }
            else
                mf.set_node(idx(i, j), grid[i][j] - '0');

            for (int k = 0; k < 4; k++) {
                int r = i + dr[k], c = j + dc[k];
                if (r < 0 || c < 0 || r >= h || c >= w) continue;
                mf.add_edge(idx(i, j), idx(r, c), 1e9);
            }
        }
    }
    mf.set_node(src, 1e9);
    mf.set_node(sink, 1e9);
    cout << mf.dinic(src, sink) << endl;

    return 0;
}