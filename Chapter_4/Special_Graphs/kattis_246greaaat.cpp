/* Kattis - 236greaaat
This is the most difficult question I have done at the time of writing.

Observation 0:
    If we treat each cheer as an edge and each total enthuism value as a node we get a directed
    cyclic weighted graph. We thus can't use DP or DAG toposort. We have to use dijkstra.

Observation 1:
    If we know dist 0->u and dist u->dest, we don't need to continue processing u and propagating
    dist[u] to its neighbours. Instead, we can have a candidate shortest path 0 -> u -> n. We pick the
    shortest out of all these candidate shortest paths for all times we are able to "meet in the middle"
    at u. This should cut our time down by about half... Not much in terms of order of magnitude but
    is actually very significant to ACing.

    In terms of printing the optimal combination of cheers, we note that we can join all the
    cheers that are required to go from 0->u and 0->n-u, both of which are accessible
    via the parent array since we have process u and n-u before.

Observation 2:
    We only need to consider nodes in the range [0, dest - min(min(delta), 0)] where delta
    is the change caused by a cheer. We denote min_cheer = min(min(delta), 0) which is the minimum
    delta of cheers (or 0 if all cheers have positive delta)

    Each permutation of cheers corresponds to a unique path on the graph.

    It is obvious that for the optimal combination of cheers, there exist at least one that only
    passes through non-negative nodes. This is because we can put all the positive cheers before
    all then negative cheers. Since dest > 0, the nodes will always be positive.

    Now, consider the optimal combination of cheers. will We prove that there exist a permutation
    that only uses nodes within [0, dest - min_cheer]. Consider some permutation
    that only uses non-negative nodes (we already proved that such a permutation exists). 
    if all nodes on this path are within the range, we are done. If not, there must exist a node
    N which is the first node on the path such that N > dest - min_cheer. Let the node immediately
    before that be n and the change from n to N be d-pos, ie N = n + d-pos.
    
    Since N > dest, we must eventually get to dest via a -ve delta cheer. We call the first negative
    delta cheer d-neg. If we move d-neg to be the next cheer after n, we will be able to "delay"
    the path getting over dest - min_cheer. This is because obviously N < n < dest - min_cheer (by
    definition of N being the first over the max). Now, instead of increasing n to N, we instead
    decrease n to n + d-neg. However, we note that n + d-neg will be non-negative. This is because
    N = n + d-pos > dest - min-cheer. ==> n + min-cheer > dest - d-pos. Since each delta must be <= dest.
    Then n + min-cheer > dest - d-pos > 0. Furthermore, min_cheer <= d-neg. 
    Thus n + d-neg > n + min_cheer > 0.

    By repeatedly "delaying" the node which has N > dest - min_cheer, we will eventually get to dest while
    remaining within the required range of [0, dest - min(min(delta), 0)].

Observation 3:
    dist (0 -> x) <= dest for all x that we have to consider. This is because Dijkstra considers
    the nodes in increasing distance. But we know that dist(0->dest) <= dest, so dist (0 -> x) <= dest
    for all nodes x that we process in our Dijkstra.

Idea 1:
    Instead of a priority queue, since we have limited dist to between 0 and dest, we can use a 
    dest+1 sized vector of queues (Q) where Q[d] contains all the nodes x with dist(0->x) = d.
    (ofc this is still with the modified dijkstra lazy delete).

    This allows for O(1) rather than O(log V) insert of new nodes and access of the closest node!

Further Optimisations:
- use pair rather than tuple, it is significantly faster
- use int rather than long long, it is significantly faster
- use Ofast compilation flag, not essential but helps

Debugging:
- prevent v = 0 to avoid self loops
- initialise all variables to proper values (refer to code)

Time; O(kV) where k is the number of cheers, V is the number of nodes (at most dest*2)
Memory: O(V + k)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int e, dest, u, v, temp_d, w, delta, INF = (int) 1e8;
vector<pair<int, int>> cheers; // d, weight, note that pairs are faster than tuples
vector<int> dist, dist_to_n,parent; 
vector<queue<int>> q; 
int main() {
    scanf("%d %d", &e, &dest);
    cheers.emplace_back(1, 1);
    int min_cheer = 0;
    for (int i = 0; i < e; i++) {
        scanf("%d %d", &v, &w);
        if (v == 0){ // prevent self loops
            w = INF;
        }
        cheers.emplace_back(v, w);
        min_cheer = min(min_cheer, v);
    }
    e++; // account for first cheer
    int max_node = dest - min_cheer;
    dist.assign(max_node+ 9, INF);
    dist_to_n.assign(max_node + 9, INF);
    parent.assign(max_node + 9, -1);
    q.assign(dest+9, queue<int>());

    // Dijkstra using modified "priority queue"
    dist[0] = 0;
    parent[0] = -1;
    q[0].emplace(0);
    int meet_at = 0, total_dist = dest + 1 ;
    // dest +1 ensures that parent array is properly updated for edge cases
    for (int d=0;d<=dest; d += (q[d].empty())){
        if (q[d].empty())
            continue;

        u = q[d].front();
        q[d].pop();

        if (dist[u] >= total_dist || u == dest)break;
        if (d > dist[u])continue; // inferior pair
        
        // Meet in the middle stuff
        if (dest > u)
            dist_to_n[dest - u] = dist[u];
        if (dist_to_n[u] != INF){
            if (dist[u] + dist_to_n[u] < total_dist){
                meet_at = u;
                total_dist = dist[u] + dist_to_n[u];
            }
            continue;
        }
        for (int i=0; i < e; i++) {
            delta = cheers[i].first;
            w = cheers[i].second;
            v = delta + u;
            if (v <= 0 || v > max_node)continue;
            temp_d = dist[u] + w;
            if (temp_d >= dist[v])
                continue;  // relaxing through this node doesn't help

            if (temp_d > total_dist)continue; // out of bounds (ie will never go there)

            dist[v] = temp_d;

            parent[v] = i;
            q[temp_d].emplace(v);
        }
    }

    vector<int> path;
    int cur_node = meet_at;
    while (cur_node != 0) {
        path.emplace_back(parent[cur_node]);
        auto [d, w] = cheers[parent[cur_node]];
        cur_node = cur_node - d;
    }
    cur_node = dest-meet_at;
    while (cur_node != 0) {
        path.emplace_back(parent[cur_node]);
        auto [d, w] = cheers[parent[cur_node]];
        cur_node = cur_node - d;
    }
    
    printf("%d\n", (int) path.size());
    for (auto i : path) {
        printf("%d ",i+1);
    }
    printf("\n"); 
    return 0;
}
