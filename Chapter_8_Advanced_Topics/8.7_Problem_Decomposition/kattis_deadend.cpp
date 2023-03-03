/**Kattis - deadend
 * Cycle Detection + Tree Operations + Reading Comprehension.
 *
 * For each connected component of the graph, we have 2 cases:
 * 1. The component is a tree. In this case, the answer is the number of leaves in the tree, with
 * one sign at the leaf end of each leaf edge.
 * 2. The component contains a cycle. In this case, we put 1 sign at the cycle end of each edge that
 * joins a node in a cycle (or between 2 cycles) and a node outside the cycle (the root of a
 * subtree) connected to the cycle.
 *
 * We distingush between the 2 cases by doing DFS with a back-edge check (but avoiding the 2 cycles
 * caused by birectional edges). We also push all the leaves into a queue. If the component is a
 * tree, we just process all the leaves in the queue.
 *
 * If the component contains a cycle, we use trees_attached[u] to store the number of sub trees
 * attached to u (have a root adjacent to u). We effectively pluck leaves from the component (from
 * the queue) which may form new leaves which are then pushed into the queue. When we have no more
 * leaves, we sum the number of trees attached to each node in the component that has not been
 * plucked (degree[u] != 0).
 * 
 * Time: O(V log V + E), Mem: O(V + E) (V log V for sorting in the case we have a tree)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, e;
bool iscycle;
vector<vector<int>> adjlist, signs_for_this_node;
vector<tuple<int, int>> signs;
vector<int> visited, trees_attached, cur_component, degree;
queue<int> q;
void dfs(int u, int p)
{
    visited[u] = 1;
    cur_component.push_back(u);
    if (degree[u] == 1) {
        q.emplace(u);  // leaf
    }
    for (auto v : adjlist[u]) {
        if (visited[v] == 0) {
            dfs(v, u);
        }
        else if (visited[v] == 1 && v != p) {
            iscycle = true;
        }
    }
    visited[u] = 2;
}
int main()
{
    fast_cin();
    cin >> n >> e;
    degree.assign(n, 0);
    adjlist.assign(n, vector<int>());
    signs_for_this_node.assign(n, vector<int>());
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
        degree[u]++;
        degree[v]++;
    }
    int ans = 0;
    visited.assign(n, 0);
    trees_attached.assign(n, 0);

    for (int i = 0; i < n; i++) {
        if (visited[i] != 0) continue;
        while (!q.empty()) q.pop();
        cur_component.clear();
        iscycle = false;

        dfs(i, -1);
        if (!iscycle) {
            ans += q.size();
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                assert(degree[u] == 1 && (int)adjlist[u].size() == 1);
                signs.emplace_back(u, adjlist[u][0]);
            }
            continue;
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            degree[u] = 0;  // pluck this leaf
            for (auto v : adjlist[u]) {
                if (degree[v] != 0) {  // still alive
                    degree[v]--;
                    trees_attached[v] += 1;  // u is the root of a subtree attached to v
                    signs_for_this_node[v].push_back(u);
                    if (degree[v] == 1) {  // new leaf
                        q.emplace(v);
                    }
                }
            }
        }

        for (auto u : cur_component) {
            if (degree[u] != 0) {  // not plucked
                ans += trees_attached[u];
                for (auto v : signs_for_this_node[u]) {
                    signs.emplace_back(u, v);
                }
            }
        }
    }
    cout << ans << endl;
    sort(signs.begin(), signs.end());
    for (auto [u, v] : signs) {
        cout << u + 1 << " " << v + 1 << endl;
    }

    return 0;
}