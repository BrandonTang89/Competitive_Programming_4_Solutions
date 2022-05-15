/* kattis - naturereserve
Observation 1:
    The optimal graph is acyclic.

    Assume the graph contains a cycle component. In this cycle, the information goes from
    a to b to c and back to a. This can be reduced to a to b and b to c, As such, the cycle must
    be unoptimal, thus all components are trees.

Observation 2:
    The minmum energy to propage the program is equal to the (number of nodes not in S) * l.

    Each node not in S needs to get the programme. However, propagating it along a channel only
    allows at most 1 additional node to get the programme, thus we need to propagate at most
    (number of nodes not in S) times.

Observation 3
    Assume there are 2 nodes s1 and s2 (in S) in the same tree component. We can remove an
    edge from s1. Since all edges in trees are bridges, this results in 2 disconnected trees being
    formed. The cost of forming the trees is lower. However, the cost of propagating the programme
    remains unchanged. This is because for each tree, we can propagate the programme from s1 or s2 and
    make it pass through all edges. This obviously propagates to all nodes. Furthermore, it is the minimum
    since the number of edges is equal to the number of vertices in the 2 components - 2 (for s1 and s2).
    (extension of observation 2).

    Thus, the optimal graph is a spanning forest where each tree has at exactly one node in S.

To solve this, we can process all nodes in S with prim first and then continue as per ususal, stopping
once all the nodes are part of the forest.
Time: O(E log V), Mem: O(V + E)
*/

#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n, e, u, v, w, t, l, s;
vector<vector<tuple<int, int>>> adjlist;
vi taken;
priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>,
               greater<tuple<int, int, int>>>
    pq;

void process(int u) {
    taken[u] = 1;
    for (auto &[w, v] : adjlist[u]) {
        if (!taken[v]) pq.emplace(w, v, u);
    }
}

vi initial_stations;
int main() {
    cin >> t;
    for (int tc = 0; tc < t; tc++) {
        cin >> n >> e >> l >> s;


        // reset variables
        taken.assign(n, 0);
        adjlist.assign(n, vector<tuple<int, int>>());
        initial_stations.clear();
        while (!pq.empty()) {
            pq.pop();
        }

        for (int i=0;i<s;i++){
            cin >> u;
            u--;
            initial_stations.emplace_back(u);
        }


        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            u--; v--;
            adjlist[u].emplace_back(w, v);
            adjlist[v].emplace_back(w, u);
        }

        ll mst_cost = 0, num_nodes_taken = 0, num_edges_taken = 0;
        for (auto i: initial_stations){
            process(i);
            num_nodes_taken++;
        }

        while (!pq.empty()) {
            auto [w, u, p] = pq.top();  // p -> u is an MST edge
            pq.pop();
            if (taken[u]) continue;

            // We take the current edge in the MST
            mst_cost += w;
            num_nodes_taken++;
            num_edges_taken++;

            // Propagate from u
            process(u);

            if (num_nodes_taken == n) break;
        }

        cout << mst_cost + num_edges_taken*l << endl;
    }
}