/**Kattis - openpitmining
 * Quite an atypical max flow problem. Firstly we let the value of each node be v-c so nodes are
 * either positive or negative.
 *
 * The idea for the solution is that if we run max flow with the source connected to all positive
 * nodes and all negative node are connected to the sink (also with node i connected to node j iff i
 * is obstructed by j), then if the flow through some negative node to the sink is not full, we
 * didn't get enough value from removing that negative node since the value produced later on as a
 * result of mining that node did not fully make up for the value lost from removing that node.
 * (Think about this statement for a while to convince yourself that it is true, note that the
 * converse "if a negative node's flow is full then it is worth mining" is not necessarily true).
 *
 * As such, we can remove that node and all nodes that are obstructed by it (recursively with
 * a DFS).
 *
 * We do that process repeatedly until we end up in a state where all the negative nodes have full
 * flows to the sink. In this case, removing any negative node is not beneficial since we could have
 * extra flows through the negative node to the surface.
 *
 * [Looking at someone else's solution, it seems a better strategy is with the same construction:
 * the max flow is the amount of value that is spilt into mining negative value nodes, any value
 * that doesn't flow out is extracted at the surface so we take "sum of positive nodes - max flow"
 * as our answer]
 *
 * Time: O(V^2*E * num_iterations) which is difficult to
 * quantify Space: O(V^2)
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
    bool notFull(int edgeLabel) { return get<1>(EL[edgeLabel]) > get<2>(EL[edgeLabel]); }

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
vector<vector<int>> obstructs;
vector<int> value;

unordered_set<int> notgetting;
void dfs(int u)
{
    if (notgetting.count(u)) return;
    notgetting.insert(u);
    for (auto v : obstructs[u]) {
        dfs(v);
    }
}
int main()
{
    cin >> n;
    value.assign(n, 0);
    obstructs.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        int v, c, k;
        cin >> v >> c >> k;
        value[i] = v - c;

        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            x--;
            obstructs[i].push_back(x);
        }
    }

    while (true) {
        max_flow mf(n + 2);
        int src = n, sink = n + 1;
        unordered_map<int, int> edgeidx;
        for (int i = 0; i < n; i++) {
            if (notgetting.count(i)) continue;
            if (value[i] > 0) {
                mf.add_edge(src, i, value[i]);
            }
            else if (value[i] < 0) {
                edgeidx[i] = mf.add_edge(i, sink, -value[i]);
            }

            for (auto v : obstructs[i]) {
                if (notgetting.count(v)) continue;
                mf.add_edge(v, i, 1e9);
            }
        }
        
        // // This would be the alternative solution:
        // int sum = 0;
        // for (int i=0; i<n; i++){
        //     if (value[i] > 0) sum += value[i];
        // }
        // cout << sum - mf.dinic(src, sink) << endl;
        // return 0;

        mf.dinic(src, sink);

        bool changed = false;
        for (auto &[u, idx] : edgeidx) {
            if (mf.notFull(idx)) {
                dfs(u);
                changed = true;
            }
        }
        if (!changed) break;
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (notgetting.count(i)) continue;
        ans += value[i];
    }
    cout << ans << endl;

    return 0;
}