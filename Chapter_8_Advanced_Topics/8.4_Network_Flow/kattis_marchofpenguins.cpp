/**Kattis - marchofpenguins
 * Relatively simple max flow with vertex capacities problem. Suppose we have chosen some meeting
 * iceberg mb. We set up a network flow graph with n+1 vertices, each representing each of the
 * icebergs and the last is the source. We set the capacity of the source and mb to infinity, and
 * the capacity of each iceberg to the number of jumps possible from it. We then join the source to
 * all of the icebergs, each with a directed edge with capacity equal to the number of penguins. We
 * then join each iceberg to all other icebergs that are within distance d of it, with a directed
 * edge with capacity infinity. We then run a max flow algorithm from the source to mb. If the max
 * flow is equal to the total number of penguins, then we know that mb is a valid meeting iceberg.
 * We do this for all mb and output the ones that are valid.
 *
 * Time: O(n * sum penguins) = O(n^2 * 10), Space: O(n^2)
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

inline double dist(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main()
{
    int n, totalPenguins = 0;
    double d;
    cin >> n >> d;
    vector<int> ans;
    vector<tuple<int, int, int, int>> icebergs(n);  // (x, y, num penguins, num jumps)
    for (int i = 0; i < n; i++) {
        int x, y, p, q;
        cin >> x >> y >> p >> q;
        icebergs[i] = {x, y, p, q};
        totalPenguins += p;
    }

    for (int mb = 0; mb < n; mb++) {  // meeting iceberg
        max_flow mf(n + 1);
        int src = n;

        mf.set_node(mb, INF);
        mf.set_node(src, INF);
        for (int i = 0; i < n; i++) {
            mf.add_edge(src, i, get<2>(icebergs[i]), false);
            if (i == mb) continue;
            mf.set_node(i, get<3>(icebergs[i]));
        }

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                auto &[x1, y1, p1, q1] = icebergs[i];
                auto &[x2, y2, p2, q2] = icebergs[j];
                if (dist(x1, y1, x2, y2) <= d) {
                    mf.add_edge(i, j, INF, false);
                }
            }
        }

        int flow = mf.dinic(src, mb);
        if (flow == totalPenguins) {
            ans.push_back(mb);
        }
    }

    if (ans.size() == 0) {
        cout << -1 << endl;
    }
    else {
        for (auto &i : ans) {
            cout << i << " ";
        }
        cout << endl;
    }

    return 0;
}