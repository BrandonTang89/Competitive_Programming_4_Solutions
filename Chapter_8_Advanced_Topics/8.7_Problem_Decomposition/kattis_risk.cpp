/**Kattis - risk
 * BSTA + Max Flow. We BSTA for the maximum minimum number of armies at a border region. To check
 * this, we model the problem as a max flow problem with vertex capacities (with the vertex
 * splitting technique).
 *
 * For each region, have an edge from the source to the region with capacity equal to the number of
 * armies in the region. We set the region vertex capacity to be the number of armies in the region.
 * This ensures that we cannot move armies across 2 edges in 1 turn. We then add edges of infinite
 * capacity between connected regions.
 *
 * Internal regions are connected to the sink with a capacity of 1 since we need at least 1 army in
 * each internal region. Border regions are connected to the sink with a capacity of x since we are
 * trying to get at least x armies in each border region. Note however that we connect the in-node
 * of each of these regions to the sink. This is to prevent contributions to the sink as movements
 * of troops within the turn. We check if we can attain at least x armies in each border region by
 * seeing if we can get a max flow that maxes out the edges to the sink, i.e. x in each border
 * region and 1 in each internal region.
 *
 * Time: O(EV^2 log num_armies), Space: O(V + E)
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
    void add_edge_in_to_in(int u, int v, ll w) { add_edge_internal(in_node(u), in_node(v), w); }
};

int num_tc;
int n, total_armies, num_internal, num_border_regions;
vector<int> num_armies;
vector<int> region_type;  // 0: enemy, 1: border, 2: internal
vector<vector<int>> adjmat;

bool check(int x)
{
    // can we have at least x armies in each border region?
    max_flow mf(n + 2);  // + 2 for source and sink
    for (int i = 0; i < n; i++) {
        mf.set_node(i, num_armies[i]);
        mf.add_edge(n, i, num_armies[i]);

        if (region_type[i] == 1) {              // border
            mf.add_edge_in_to_in(i, n + 1, x);  // to sink with capacity x
        }
        else if (region_type[i] == 2) {         // internal
            mf.add_edge_in_to_in(i, n + 1, 1);  // to sink with capacity 1
        }

        for (int j = 0; j < n; j++) {
            if (adjmat[i][j] == 1) {
                mf.add_edge(i, j, INF);
            }
        }
    }
    mf.set_node(n, INF);
    mf.set_node(n + 1, INF);  // source and sink

    int curmaxflow = mf.dinic(n, n + 1);
    return curmaxflow == (num_border_regions * x + num_internal);
}
int main()
{
    cin >> num_tc;
    while (num_tc--) {
        cin >> n;
        total_armies = 0;
        num_internal = 0;
        num_border_regions = 0;
        num_armies.resize(n);
        region_type.assign(n, 2);
        for (int i = 0; i < n; i++) {
            cin >> num_armies[i];
            total_armies += num_armies[i];
            if (num_armies[i] == 0) {
                region_type[i] = 0;
            }
        }
        adjmat.assign(n, vector<int>(n, 0));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                char c;
                cin >> c;
                adjmat[i][j] = (c == 'Y' ? 1 : 0);
            }
        }
        for (int i = 0; i < n; i++) {
            if (region_type[i] == 0) {  // for each enemy node
                for (int v = 0; v < n; v++) {
                    if (adjmat[i][v] == 1 &&
                        region_type[v] == 2) {  // if it has an internal neighbor, it is a border
                        region_type[v] = 1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            if (region_type[i] == 1) {
                num_border_regions++;
            }
            else if (region_type[i] == 2) {
                num_internal++;
            }
        }

        int le = 1, ri = total_armies;
        while (le < ri) {
            int mid = (le + ri) / 2 + 1;
            if (check(mid)) {
                le = mid;
            }
            else {
                ri = mid - 1;
            }
        }
        cout << le << endl;
    }

    return 0;
}