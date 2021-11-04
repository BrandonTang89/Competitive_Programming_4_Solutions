/* Kattis - intercept
This is a pretty interesting problem with different subroutines.

Observation 1:
    Once we do Dijkstra to get from source to dest, we will actually get a dijkstra DAG. This is 
    true since there can't be a cycle in any of the shortest paths due to the absence of negative
    cycles as all weights are positive.

    By recording the parents of each node while doing Dijkstra, we can get the adjacency list of
    the DAG.

Observation 2:
    To know which points in the DAG are articulation points, we can use something similar to
    network flow. Essentially we send 1 unit of flow from the dest. And the amount of flow
    entering each node should be the same as the amount flowing out, except for the dest
    and start points. This is done by splitting the total in flow of each node evenly over the out
    going neigbours of each node. 
    
    Iff a node has exactly 1 flow, it is an articulation point.

    Note that we should process the nodes in topological ordering (based on the parents adjacency list)
    to ensure that we put all the possible flow into each node before we start propagating the flow 
    from it.

Debugging:
    Use long long and double.

Time: O(E log V), Space: O(V + E)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define double_equal(a, b) (fabs((a) - (b)) < 1e-9)

ll n, e, u, v, w, source, dest;
const ll INF = (ll)1e18;
vector<vector<tuple<ll, ll>>> adjlist;
vector<vector<ll>> parents;
vector<ll> dist;
priority_queue<tuple<ll, ll>, vector<tuple<ll, ll>>, greater<tuple<ll, ll>>> pq;

vector<int> ts, visited;
void toposort(int u){
    visited[u] = 1;
    for (auto v: parents[u]){
        if (visited[v] == 0){
            toposort(v);
        }
    }
    ts.push_back(u);
}

int main() {
    cin >> n >> e;
    adjlist.assign(n, vector<tuple<ll, ll>>());
    dist.assign(n, INF);
    parents.assign(n, vector<ll>());
    for (ll i = 0; i < e; i++) {
        cin >> u >> v >> w;
        adjlist[u].push_back(make_tuple(w, v));
    }
    cin >> source >> dest;

    dist[source] = 0;
    pq.push(make_tuple(0, source));
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dist[u]) continue;  // inferior pair
        if (u == dest) break;
        for (auto &[w, v] : adjlist[u]) {
            if (dist[u] + w > dist[v]) continue;  // relaxing through this node doesn't help
            if (dist[u] + w == dist[v]) {
                parents[v].push_back(u);
            } else {
                dist[v] = dist[u] + w;
                parents[v].clear();
                parents[v].push_back(u);
                pq.push(make_tuple(dist[v], v));
            }
        }
    }

    for (int i = 0; i < n; i++) {
        set<ll> s(parents[i].begin(), parents[i].end());
        parents[i].assign(s.begin(), s.end());
    }

    // get topological ordering
    visited.assign(n, 0);
    toposort(dest);
    reverse(ts.begin(), ts.end());
    vector<double> flow(n, 0);
    flow[dest] = 1;

    // get flow
    for (auto u: ts){
        //cout << u << endl;
        for (auto v: parents[u]){
            flow[v] += flow[u] / (double) parents[u].size();
        }
    }
    for (int i=0;i<n;i++){
        if (double_equal(flow[i], 1)){
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}