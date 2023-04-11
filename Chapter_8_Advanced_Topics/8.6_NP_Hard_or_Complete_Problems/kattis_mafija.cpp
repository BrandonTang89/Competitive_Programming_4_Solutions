/**Kattis - mafija
 * Maximum independent set variation. Here we have a functional graph (directed with all nodes
 * having out-degree 1) and we want to find the MIS (n - MVC). This implies each connected component
 * is a pseudo-tree with 1 main loop and the rest of the nodes pointing inward to the loop. Clearly
 * the MIS of the whole graph is the sum of the MIS of each connected component. For each connected
 * component, we can find the loop using DFS and seeing if we find a back-edge. We then label the
 * entire loop as inloop and then do a DP on the loop to find the minimum vertex cover for the
 * connected component.
 *
 * We let dp1(i, selected) be the MVC of the subgraph assuming that we are currently at node i (i
 * is in the loop) and we have/haven't selected it. The base-case is the node before the loop root.
 * If we have haven't selected the root, we must select the node before the root. For each node, we
 * will compute the cost to cover the subtree rooted at the node with dp2(i, selected). Then we can
 * compute dp1(i, selected) using dp2(i, selected) and recursive calls to dp(i, selected/!selected).
 * I.e. cover the subtree at that node and whether or not to select the next node.
 *
 * dp2 is the standard MVC on a tree, just that for this question I chose to use the state (i,
 * selected) rather than the usual (i, prev_selected) since I felt that this made it easier to call
 * the function correctly. Note that we need to "reverse" the direction of the edges on the trees
 * attached to the loop so we use adjlist which contains a transposed version of the original graph.
 *
 * dp1 should be reset for every (loop_root, root_selected) pair. dp2 doesn't ever need to be reset.
 * 
 * Time: O(V), Mem: O(V)
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

int n;
vector<int> nex, inloop, visited;
vector<vector<int>> adjlist;

int overall_answer, loop_root, root_selected;
vector<vector<int>> memo, memo2;
int dp2(int i, int selected)
{  // minimum to cover the subtree
    int &ans = memo2[i][selected];
    if (ans != -1) return ans;

    ans = selected;
    for (auto c : adjlist[i]) {
        if (inloop[c]) continue;  // don't go back to the loop
        int can = dp2(c, 1);
        if (selected) can = min(can, dp2(c, 0));
        ans += can;
    }

    return ans;
}
int dp1(int i, int selected)
{  // dp around the loop
    int &ans = memo[i][selected];
    if (ans != -1) return ans;

    int cover_node = dp2(i, selected);
    if (nex[i] == loop_root) {
        if (selected) return ans = cover_node;
        if (root_selected)
            return ans = cover_node;  // and not selected
        else
            return ans = 1e8;  // impossible
    }

    ans = cover_node + dp1(nex[i], 1);                          // select the next one
    if (selected) ans = min(ans, cover_node + dp1(nex[i], 0));  // don't select the next one

    return ans;
}

void fill_loop(int i)
{
    inloop[i] = 1;
    int j = nex[i];
    while (j != i) {
        inloop[j] = 1;
        j = nex[j];
    }
}
void dfs(int i)
{
    if (visited[nex[i]] == 0) {
        visited[nex[i]] = 1;
        dfs(nex[i]);
    }
    else if (visited[nex[i]] == 1) {
        fill_loop(i);
        int can = 1e8;
        memo.assign(n, vector<int>(2, -1));
        loop_root = i;
        root_selected = 0;

        can = min(can, dp1(i, 0));

        memo.assign(n, vector<int>(2, -1));
        root_selected = 1;
        can = min(can, dp1(i, 1));

        overall_answer += can;
    }
    visited[i] = 2;
}
int main()
{
    fast_cin();
    cin >> n;
    nex.assign(n, 0);
    adjlist.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        cin >> nex[i];
        nex[i]--;
        adjlist[nex[i]].push_back(i);
    }

    inloop.assign(n, 0);
    visited.assign(n, 0);
    memo2.assign(n, vector<int>(2, -1));

    overall_answer = 0;
    for (int i = 0; i < n; i++) {
        if (visited[i] == 0) {
            visited[i] = 1;
            dfs(i);
        }
    }
    cout << n - overall_answer << endl;

    return 0;
}