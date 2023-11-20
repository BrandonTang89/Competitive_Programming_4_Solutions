/**Kattis - landscaping
 * Grid Min-Cut problem. The modelling is as follows: we construct a grid with bidirectional edges
 * between adjacent squares, these are weighted A since they represent the cost the the tractors
 * moving between low and high ground. Then we add a source and sink. We add edges of weight B
 * between the source and all high nodes, and edges of weight B between all low nodes and the sink.
 * This means that to stop the flow from some high node, we either need to spend B to stop the flow
 * into the high node (corresponding to lowering the patch), or we need to stop the flows from
 * getting to the low nodes somehow either by accepting a multiple of A cost (corresponding to
 * accepting the cost of the tractor going between the elevations) or a multiple of B cost
 * (corresponding to making all local low nodes into high nodes).
 * 
 * Time: O(V^2 * E = (HW)^3), Space: O(HW)
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

int h, w, a, b;
inline int coord_to_int(int r, int c) { return r * w + c; }
int main()
{
    vector<vector<char>> grid;
    cin >> h >> w >> a >> b;
    grid.assign(h, vector<char>(w));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
        }
    }
    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};
    max_flow mf(h * w + 2);
    int src = h * w;
    int sink = h * w + 1;

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                mf.add_edge(coord_to_int(r, c), coord_to_int(nr, nc), a);
            }
            if (grid[r][c] == '.') {
                mf.add_edge(coord_to_int(r, c), sink, b);
            }
            else if (grid[r][c] == '#') {
                mf.add_edge(src, coord_to_int(r, c), b);
            }
        }
    }

    cout << mf.dinic(src, sink) << endl;

    return 0;
}