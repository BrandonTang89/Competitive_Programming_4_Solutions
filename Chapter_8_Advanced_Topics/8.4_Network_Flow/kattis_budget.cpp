/**Kattis - budget
 * A more difficult version of kattis - tomography. We use a similar idea (so go read the write up
 * for that first) but with more pre and post processing. We start by parsing all the constraints at
 * once and accumulating the constraints for each cell. Then for each cell, we connect the cell's
 * row and column nodes by an edge that varies depending on the constraints. If there is an equality
 * constraint, we just assume the flow already exists and subtract that from the row and column
 * sums. Else, we assume greaterThan[i][j] + 1 flow already exist and remove that. Then we add an
 * edge of weight lessThan[i][j] - greaterThan[i][j] - 2 that represents all the additional flow
 * that can occur. Once we are done with all the cells, we check if the total rowSum is the same as
 * that of the columnSum. If so, we do Dinic's algorithm to check if the matrix can be constructed.
 *
 * Along the way, we need to check for impossible conditions, there are numerous ways it can be
 * impossible, examine the code for the specific instances.
 * 
 * Time: O(V^2*E) (V = h+w+2, E = h*w)
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

int h, w;
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        bool possible = true;
        cin >> h >> w;
        vector<vector<ll>> greaterThan, lessThan, equalTo;
        greaterThan.assign(h, vector<ll>(w, -1));
        lessThan.assign(h, vector<ll>(w, INF));
        equalTo.assign(h, vector<ll>(w, -1));
        vector<int> rowSum, colSum;
        rowSum.assign(h, 0);
        colSum.assign(w, 0);
        for (int r = 0; r < h; r++) cin >> rowSum[r];
        for (int c = 0; c < w; c++) cin >> colSum[c];

        int k;
        cin >> k;
        while (k--) {
            ll r, c, val;
            char op;
            cin >> r >> c >> op >> val;
            r--;
            c--;

            for (int i = (r == -1 ? 0 : r); i < (r == -1 ? h : r + 1); i++) {
                for (int j = (c == -1 ? 0 : c); j < (c == -1 ? w : c + 1); j++) {
                    if (op == '=') {
                        if (equalTo[i][j] != -1 && equalTo[i][j] != val) possible = false;
                        equalTo[i][j] = val;
                    }
                    else if (op == '>') {
                        greaterThan[i][j] = max(greaterThan[i][j], val);
                    }
                    else if (op == '<') {
                        lessThan[i][j] = min(lessThan[i][j], val);
                        if (lessThan[i][j] <= 0) possible = false;
                    }
                    else
                        assert(false);
                }
            }
        }

        vector<vector<int>> edges;
        edges.assign(h, vector<int>(w, 0));
        max_flow mf(h + w + 2);
        int src = h + w, sink = h + w + 1;
        for (int r = 0; r < h; r++) {
            for (int c = 0; c < w; c++) {
                if (greaterThan[r][c] + 1 >= lessThan[r][c]) {
                    possible = false;
                    break;
                }
                if (equalTo[r][c] != -1) {
                    if (equalTo[r][c] <= greaterThan[r][c] || equalTo[r][c] >= lessThan[r][c]) {
                        possible = false;
                        break;
                    }
                    colSum[c] -= equalTo[r][c];
                    rowSum[r] -= equalTo[r][c];
                }
                else {
                    colSum[c] -= (greaterThan[r][c] + 1);
                    rowSum[r] -= (greaterThan[r][c] + 1);
                    edges[r][c] = mf.add_edge(r, h + c, lessThan[r][c] - greaterThan[r][c] - 2);
                }
            }
        }

        int totalSum = 0;
        for (int r = 0; r < h; r++) {
            if (rowSum[r] < 0) possible = false;
            mf.add_edge(src, r, rowSum[r]);
            totalSum += rowSum[r];
        }
        int diff = totalSum;
        for (int c = 0; c < w; c++) {
            if (colSum[c] < 0) possible = false;
            mf.add_edge(h + c, sink, colSum[c]);
            diff -= colSum[c];
        }
        if (diff != 0) possible = false;

        if (!possible)
            cout << "IMPOSSIBLE" << endl;
        else {
            int flow = mf.dinic(src, sink);
            if (flow != totalSum)
                cout << "IMPOSSIBLE" << endl;
            else {
                for (int r = 0; r < h; r++) {
                    for (int c = 0; c < w; c++) {
                        if (equalTo[r][c] != -1)
                            cout << equalTo[r][c] << " ";
                        else
                            cout << mf.getFlow(edges[r][c]) + greaterThan[r][c] + 1 << " ";
                    }
                    cout << endl;
                }
            }
        }

        cout << endl;
    }

    return 0;
}