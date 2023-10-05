/**Kattis - chesscompetition
 * Straightforward once you see it kind of flow modelling. We try making each person from 1..n win.
 * To do so, we construct a flow graph where we connect edges of all points won by each other person
 * from the source to that person. Then for each unplayed game, we create a virtual node with input
 * edge of weight 2 and is connected to the 2 people playing that game, with edges of weight 2. This
 * allows the points for the unplayed game to be distributed to either of the 2 players. We need
 * compute the maximum possible score for the player (let this be X) we want to win and connect all
 * other players to the sink by edges of that weight. Then we run dinic's and see if the max flow is
 * equal to the total input flow. If this is the case, it would be that we were able to distribute
 * the points such that each other player has <= X points.
 * 
 * Time: O(V^2 * E) (V = n^2 + n + 2, E = O(n^2)), Space: O(V + E)
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

int n;
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        vector<vector<char>> grid(n, vector<char>(n));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cin >> grid[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            // we see if person i can win
            int inFlow = 0;
            max_flow mf(n * n + n + 2);
            int src = n * n + n, sink = n * n + n + 1;

            for (int u = 0; u < n; u++) {
                if (u == i) continue;
                for (int v = 0; v < n; v++) {  // add in-edges for u
                    if (u == v) continue;
                    if (grid[u][v] == '1') {
                        mf.add_edge(src, n * n + u, 2);
                        inFlow += 2;
                    }
                    else if (grid[u][v] == 'd') {
                        mf.add_edge(src, n * n + u, 1);
                        inFlow += 1;
                    }
                    else if (grid[u][v] == '.' &&
                             v != i) {  // don't spread the points if i can take all instead
                        if (u < v) {
                            mf.add_edge(n * u + v, n * n + u, 2);
                            mf.add_edge(n * u + v, n * n + v, 2);
                            mf.add_edge(src, n * u + v, 2);
                            inFlow += 2;
                        }
                    }
                    else
                        assert(grid[u][v] == '0' || (grid[u][v] == '.' && v == i));
                }
            }

            int maxI = 0;
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '1' || grid[i][j] == '.') {
                    maxI += 2;
                }
                else if (grid[i][j] == 'd') {
                    maxI += 1;
                }
            }

            for (int j = 0; j < n; j++) {
                if (j == i) continue;
                mf.add_edge(n * n + j, sink, maxI);
            }

            int flow = mf.dinic(src, sink);
            if (flow == inFlow) {
                cout << i + 1 << " ";
            }
        }
        cout << endl;
    }

    return 0;
}