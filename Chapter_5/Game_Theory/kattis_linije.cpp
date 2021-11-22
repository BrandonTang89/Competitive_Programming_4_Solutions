/**Kattis - linije
 * A good question in my opinion! Relatively difficult to think of the solution, but once that is done,
 * the implementation isn't too difficult.
 * 
 * Observation 1:
 * Dealing with the coordinates and what not makes it difficult to consider. From from the fact that
 * we move from one line to another line we can kind of see that maybe we can represent the problem
 * as being on a graph.. where the lines are nodes of the graph and the N points represent the edges.
 * We note that since there are only 2 types of lines (horizontal and vertical), we can partition
 * the nodes into a bipartite graph since no horizontal line can be followed by another horizontal
 * line (same for vertical lines).
 * 
 * So how is this graph constructed? Given a point (x, y), we can put an edge from x <-> y where x
 * and y are in separate partitions of the bipartite graph. For our implementation, we let all the
 * x values be nodes in the left partition and all the y values be nodes in the right partition.
 * 
 * Now how do we inteprete the game? Mirko will first choose any node, Slavko will then choose any
 * neighbouring node to go. We repeat this process until a person has no unvisited neighbour nodes
 * to go to, that person loses.
 * 
 * Observation 2:
 * Slavko will win if and only if there exist a perfect matching on the graph.
 * 
 * If there exist a perfect matching, then for any first node selcted by Mirko, we just follow the
 * matching to a corresponding node. Mirko will then move to another unvited node, we again follow
 * its matching to a corresponding node, and so on. Eventually, all the nodes will be visited and
 * Mirko will have no more univisted nodes to go to, thus Slavko will win.
 * 
 * The converse is more difficult to prove. If there exists no perfect matching, then there exists
 * at least 1 unmatched vertex (u). Mirko will pick node u. Now Slavko will pick another node v.
 * We note that v cannot also be unmatched, else we can include u <-> v in the matching for a larger
 * MCBM. Thus v will have a corresponding node x based on the MCBM. We then opt to move to x. From
 * x, we note that Slavo cannot pick any node that is unmatched. This is because of Berge's lemma which
 * states that a matching is maximal iff there is no augmenting path. But if we can go from u -> x -> v
 * for some unmatched v, then we have discovered an augmenting path! So in general, if we start from
 * u and go through a series of matched nodes, Slavo will never be able to bring us to an unmatched node.
 * So Mirko's winning strategy is to first start with an unmatched node and then subsequently always
 * follow the matching to a corresponding node for each node that Slavo brings us to. Eventually
 * Slavo will run out of matched nodes to visit and Mirko will win.
 * 
 * Time: O(N) with our augmenting path algorithm.
 * Space: O(N)
 */

#include <bits/stdc++.h>
using namespace std;
int n, e, u, v;
vector<vector<int>> adjlist;
vector<int> match, visited;

// MCBM Augmenting Path Algorithm
int aug(int L) {
    if (visited[L]) return 0;
    visited[L] = 1;
    for (auto &R : adjlist[L]) {
        if (match[R] == -1 || aug(match[R])) {
            match[R] = L;
            match[L] = R;
            return 1;
        }
    }
    return 0;
}

int main() {
    auto rng = std::default_random_engine{};
    cin >> e;
    n = 500;
    adjlist.assign(2*n+1, vector<int>());
    set<int> s;
    for (int i = 0; i < e; i++) {
        cin >> u >> v;
        adjlist[u].emplace_back(v + n);
        adjlist[v + n].emplace_back(u);
        s.insert(u);
        s.insert(v + n);
    }
    
    // Random Greedy Preprocessing
    for (int i = 1; i <= 2 * n; i++) {
        shuffle(adjlist[i].begin(), adjlist[i].end(), rng); // random shuffle edges
    }
    match.assign(2*n + 1, -1);
    int MCBM = 0;
    for (int u = 1; u <= n; u++) {     // all left vectices
        for (auto &v : adjlist[u]) {  // all right vectices neighbouring u
            if (match[v] == -1) {     // if v is unassigned
                match[v] = u;         // match v to u
                match[u] = v;         // match u to v
                MCBM++;
                break;
            }
        }
    }

    // MCBM Calculation
    for (int L = 1; L <= n; L++) {
        if (match[L] == -1) {
            visited.assign(2*n + 1, 0);
            MCBM += aug(L);
        }
    }

    // cout << MCBM << endl;
    if (MCBM*2 == (int) s.size()) {
        cout << "Slavko" << endl;
    } else {
        cout << "Mirko" << endl;
    }
    return 0;
}