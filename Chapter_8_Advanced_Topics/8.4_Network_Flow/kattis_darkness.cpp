/**Kattis - darkness
 * Quite an "obvious" min-cut problem (as most fencing problems are). We create a graph and attach
 * each cell with a lower than necessary light level to the sink (with INF weight). Then we attach
 * the source to each border cell (with INF weight). For each edge on the grid, we attach edges with
 * cost depending on whether we are connecting 2 sufficiently bright cells or not. Then just run
 * Dinic's, since max-flow == min-cut, we return max-flow.
 * 
 * Time: O(V^2 * E) = O(H^3 * W^3), Space: O(H * W)
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

int b, cheight, h, w;
inline double lightfn(int s, int r1, int c1, int r2, int c2)
{
    double dist = ((r1 - r2) * (r1 - r2) + (c1 - c2) * (c1 - c2) + cheight * cheight);
    return ((double)s / dist);
}
int main()
{
    cin >> b >> cheight >> h >> w;

    vector<vector<int>> bulbs(h, vector<int>(w));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            char ch;
            cin >> ch;
            bulbs[r][c] = ch - '0';
        }
    }

    vector<vector<double>> light(h, vector<double>(w, 0));
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            // see how bulbs[r][c] affects light[x][y]
            for (int x = 0; x < h; x++) {
                for (int y = 0; y < w; y++) {
                    light[x][y] += lightfn(bulbs[r][c], r, c, x, y);
                }
            }
        }
    }

    max_flow mf(h * w + 2);
    int src = h * w, sink = h * w + 1;

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            if (light[r][c] < b) {
                mf.add_edge(r * w + c, sink, INF);
            }
            for (int i = 0; i < 4; i++) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr < 0 || nr >= h || nc < 0 || nc >= w) continue;

                bool bothOkay = (light[r][c] >= b && light[nr][nc] >= b);
                if (bothOkay) {
                    mf.add_edge(r * w + c, nr * w + nc, 43);
                }
                else {
                    mf.add_edge(r * w + c, nr * w + nc, 11);
                }
            }
        }
    }
    for (int r = 0; r < h; r++) {
        mf.add_edge(src, r * w, INF);
        mf.add_edge(src, r * w + w - 1, INF);
    }
    for (int c = 1; c < w - 1; c++) {
        mf.add_edge(src, c, INF);
        mf.add_edge(src, (h - 1) * w + c, INF);
    }

    cout << mf.dinic(src, sink) << endl;

    return 0;
}