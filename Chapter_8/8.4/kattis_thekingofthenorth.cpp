/**Kattis - thekingofthenorth
 * Min-Cut problem with vertex capacities. We convert the 2d grid into integer indices. We set
 * vertex capacities equal to the amount of bannerman needed to defend each square. The sink
 * is the castle and the source connects to all edge squares.
 *
 * Time: O(V^2 E), Space: O(E + V)
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

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

    void add_edge_internal(int u, int v, ll w) {
        if (u == v) return;              // safeguard: no self loop
        EL.emplace_back(v, w, 0);        // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);  // remember this index
        EL.emplace_back(u, 0, 0);        // back edge
        AL[v].push_back(EL.size() - 1);  // remember this index
    }

    int in_node(int v) { return v; }
    int out_node(int v) { return v + V / 2; }

   public:
    max_flow(int initialV) {
        V = 2 * initialV;
        EL.clear();
        AL.assign(V, vi());  // double the nodes because vertex capacities
    }

    void set_node(int u, ll w) {  // set vertex capacity, MUST BE CALLED FOR EACH NODE
        add_edge_internal(in_node(u), out_node(u), w);
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        add_edge_internal(out_node(u), in_node(v), w);
        if (directed == false) {
            add_edge_internal(out_node(v), in_node(u), w);
        }
    }

    ll dinic(int s, int t) {
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
int cti(int r, int c) { return r * w + c; }           // coordinates to index
pair<int, int> itc(int i) { return {i / w, i % w}; }  // index to coordinates
bool onedge(int i) {
    auto [r, c] = itc(i);
    return r == 0 || r == h - 1 || c == 0 || c == w - 1;
}

int castle_r, castle_c;
int grid[301][301];
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};
int main() {
    cin >> h >> w;
    max_flow G(h * w + 1);
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            cin >> grid[r][c];
            G.set_node(cti(r, c), grid[r][c]);

            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;
                G.add_edge(cti(r, c), cti(nr, nc), INF);
                // will eventually be bidirectional once (nr, nc) and (r, c) swap
            }

            if (onedge(cti(r, c))) {
                G.add_edge(h * w, cti(r, c), INF);  // from source
            }
        }
    }
    G.set_node(h * w, INF);  // source
    cin >> castle_r >> castle_c;
    int sink = cti(castle_r, castle_c);

    cout << G.dinic(h * w, sink) << endl;

    return 0;
}