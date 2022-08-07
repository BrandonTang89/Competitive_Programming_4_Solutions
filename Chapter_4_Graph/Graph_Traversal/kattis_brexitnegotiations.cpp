/**Kattis - brexitnegotiations
 * Topological sort with specific requirement. Observe that given several in-deg 0 nodes to select
 * as the next node in the topological sort, we should pick the one which "unlocks" the event that
 * takes the longest time. We can do this by sorting the events by their time taken and DFSing from
 * the longest, second-longest event, etc along the tranpose graph, noting down the value of the
 * longest event unlocked as we visit each node. Then we use this information in our priority queue
 * to select the best event to do first.
 *
 * Time: O(v log v + E), Space: O(E + V)
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

int n;
vector<int> times, indegs, maxi, visited;
vector<vector<int>> adjlist, adjlistT;
vector<pair<int, int>> nodes;
priority_queue<pair<int, int>> pq;

void dfs(int u, int t) {
    visited[u] = 1;
    maxi[u] = t;

    for (int v : adjlistT[u]) {
        if (visited[v]) continue;
        dfs(v, t);
    }
    return;
}

int main() {
    fast_cin();
    cin >> n;
    times.assign(n, 0);
    indegs.assign(n, 0);
    adjlist.assign(n, vi());
    adjlistT.assign(n, vi());
    visited.assign(n, 0);
    maxi.assign(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> times[i];
        int e;
        cin >> e;
        for (int j = 0; j < e; j++) {
            int u;
            cin >> u;
            u--;
            adjlist[u].emplace_back(i);
            adjlistT[i].emplace_back(u);
            indegs[i]++;
        }
        nodes.push_back({times[i], i});
    }
    sort(nodes.begin(), nodes.end(), greater<pair<int, int>>());
    for (auto &[t, u] : nodes) {
        if (visited[u] == 0) {
            dfs(u, t);
        }
    }

    for (int i = 0; i < n; i++) {
        if (indegs[i] == 0) {
            pq.push({maxi[i], i});
        }
    }

    int num_done = 0;
    int ans = 0;
    while (!pq.empty()) {
        int curr = pq.top().second;
        pq.pop();
        ans = max(ans, num_done + times[curr]);
        num_done++;
        for (int i = 0; i < (int)adjlist[curr].size(); i++) {
            int next = adjlist[curr][i];
            indegs[next]--;
            if (indegs[next] == 0) pq.push({maxi[next], next});
        }
    }
    cout << ans << endl;

    return 0;
}