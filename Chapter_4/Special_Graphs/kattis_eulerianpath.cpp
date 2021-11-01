/* Kattis - Eulerian Path
 I can't begin to describe my annoyance at this question. To solve this, we need to modify the
 Hierholzer's algorithm to do paths rather than just cycles. I didn't notice that sometimes
 the path would take a cycle with the dummy edge within it, causing me 3+ hours of debugging.

 Observation 1:
    We already know how to get a Eulerian cycle. But this question asks for a path. Note that
    if we join the 2 ends of path by a dummy edge, we get a cycle. But which nodes do we connect?

    Well, notice that if we have all except 2 nodes with equal in and out degree, as well as
    the last 2 nodes having the property that one has 1 more in than out and the other has
    1 more out than in, we can connect the one with 1 more in than out to the one with 1 more
    out than in and get an Eulerian graph.

    So we just check for 2 types of paths. Paths that are cycles and paths that aren't cycles.

Debugging:
    The problem with the dummy edge strategy is that on some test cases (which are hard to
construct), the path will traverse through the dummy edge in the middle of the algorithm. Notice
that to deal with this issue, we can remove the last node from the result (which is gauranteed to be
the source) and then cycle using the deque operations until the source is at the start and the dest
is at the end of the deque.

Time: O(V + E)
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

int n, e, u, v;
vector<vi> adjlist;
vi in_deg, out_deg;
deque<int> ans;
vector<bool> visited;

/* Returns a Eulerian Path (s->dest) / Cycle (s -> s) if it exists, else returns empty deque
   Specify path = true if you want a path, false if you want a cycle
   s is the source for both source and cycle, dest is the destination for the path */
deque<int> hierholzer(int s, int dest = -1, bool path = false) {
    vi idx(n, 0), st;
    deque<int> ans;
    if (path) {
        adjlist[dest].emplace_back(s);  // Add dummy edge
    }
    st.push_back(s);
    while (!st.empty()) {
        int u = st.back();
        if (idx[u] < (int)adjlist[u].size()) {  // still has neighbor
            st.push_back(adjlist[u][idx[u]]);
            ++idx[u];
        } else {
            ans.push_back(u);
            st.pop_back();
        }
    }
    reverse(ans.begin(), ans.end());
    if (path) {
        adjlist[dest].pop_back();  // Remove dummy edge
        ans.pop_back();
        while (ans.front() != s || ans.back() != dest) {  // start and end correctly
            ans.push_back(ans.front());
            ans.pop_front();
        }
    }
    if ((int)ans.size() != e + 1) {  // Eulerian path/cycle doesn't exist
        return deque<int>();
    }

    return ans;
}

int main() {
    fast_cin();
    while (true) {
        cin >> n >> e;
        if (n == 0 && e == 0) break;
        adjlist.assign(n, vi());
        in_deg.assign(n, 0);
        out_deg.assign(n, 0);

        for (int i = 0; i < e; i++) {
            cin >> u >> v;
            adjlist[u].emplace_back(v);
            in_deg[v]++;
            out_deg[u]++;
        }

        // check for same in-deg and out-deg
        int one_more_out_than_in = 0, one_more_in_than_out = 0, equal_in_out = 0;
        int one_more_out_than_in_node = -1, one_more_in_than_out_node = -1;
        for (int i = 0; i < n; i++) {
            if (in_deg[i] + 1 == out_deg[i]) {
                one_more_out_than_in++;
                one_more_out_than_in_node = i;
            } else if (in_deg[i] == out_deg[i] + 1) {
                one_more_in_than_out++;
                one_more_in_than_out_node = i;
            } else if (in_deg[i] == out_deg[i])
                equal_in_out++;
        }
        // printf("one_more_out_than_in: %d, one_more_in_than_out: %d\n", one_more_out_than_in,
        // one_more_in_than_out); printf("equalinout: %d\n", equal_in_out);

        ans.clear();
        if (equal_in_out == n) {
            ans = hierholzer(0, -1, false);
        } else if ((one_more_out_than_in == 1) && (one_more_in_than_out == 1) &&
                   (equal_in_out == n - 2)) {
            // printf("start: %d, end: %d\n", one_more_out_than_in_node, one_more_in_than_out_node);
            ans = hierholzer(one_more_out_than_in_node, one_more_in_than_out_node, true);

        }

        if (ans.size() == 0) {
            cout << "Impossible" << endl;
            continue;
        }
        for (int i = 0; i < e; i++) {
            cout << ans[i] << " ";
        }
        cout << ans[e] << endl;
    }

    return 0;
}