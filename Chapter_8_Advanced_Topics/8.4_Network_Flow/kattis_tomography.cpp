/**Kattis - tomography
 * Somewhat straightforward network flow problem once you realise how to model. First we check if
 * the sum of row sums is the same as the sum of row columns. If not, then it is impossible.
 * Otherwise, we start constructing the graph.
 *
 * We have h+w nodes representing the sums of the columns and rows. We connect the src to each each
 * row by the rowSum and connect each column to the sink by the row sum. Then we connect each row to
 * each column by edges of weight 1 which represent each possible box being either black or white.
 * If the max flow is the total number of squares, then it is possible.
 *
 * Note that we need to make the optimization that the total max flow we want to get should be no
 * larger than h*w/2 to ensure that Dinic's algorithm runs on time. We do this by complementing
 * the eventual grid produced. I.e. replace each rowsum with w-rowSum and each columnsum with
 * h-columnSum. This ensures that the total max flow is at most h*w/2.
 *
 * Time: O(V^2*E) (V = h+w+2, E = h*w)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;
const ll INF = 1e18;  // large enough

int h, w;

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
    void add_edge(int u, int v, ll w, bool directed = true)
    {
        if (u == v) return;                       // safeguard: no self loop
        EL.emplace_back(v, w, 0);                 // u->v, cap w, flow 0
        AL[u].push_back(EL.size() - 1);           // remember this index
        EL.emplace_back(u, directed ? 0 : w, 0);  // back edge
        AL[v].push_back(EL.size() - 1);           // remember this index
    }

    void reset()  // use if you want to add more edges and reuse the graph
    {
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
int main()
{
    fast_cin();
    cin >> h >> w;
    vector<int> rowSums, colSums;
    rowSums.resize(h);
    colSums.resize(w);
    int totalSum = 0;
    int diff = 0;
    for (int i = 0; i < h; i++) {
        cin >> rowSums[i];
        totalSum += rowSums[i];
    }
    diff = totalSum;
    for (int i = 0; i < w; i++) {
        cin >> colSums[i];
        diff -= colSums[i];
    }
    if (diff != 0) {
        cout << "No" << endl;
        return 0;
    }
    if (totalSum > h * w / 2) {  // important optimization to avoid worst case TLE
        for (int i = 0; i < h; i++) {
            rowSums[i] = w - rowSums[i];
        }
        for (int i = 0; i < w; i++) {
            colSums[i] = h - colSums[i];
        }
        totalSum = h * w - totalSum;
    }

    max_flow mf(h + w + 2);
    int src = h + w;
    int sink = h + w + 1;
    for (int r = 0; r < h; r++) {
        mf.add_edge(src, r, rowSums[r]);
    }
    for (int c = 0; c < w; c++) {
        mf.add_edge(h + c, sink, colSums[c]);
    }
    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++) {
            mf.add_edge(r, h + c, 1);
        }
    }
    ll totalFlow = mf.dinic(src, sink);

    if (totalFlow == totalSum) {
        cout << "Yes" << endl;
    }
    else
        cout << "No" << endl;

    return 0;
}