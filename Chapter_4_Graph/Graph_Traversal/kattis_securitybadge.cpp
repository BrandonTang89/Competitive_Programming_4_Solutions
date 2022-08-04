/**Kattis - securitybadge
 * Observe that to test if a single badge works, we can simply DFS and check if start is connected
 * to dest. However, there are too many badge numbers to test. But observe that there aren't that
 * many locks, and that if badge X is not a starting badge number for any lock and X-1 is not ending
 * number for any lock, then the connectivity of badge X is the same as the connectivity of X-1. As
 * such, we can keep track of a set of the {starting badge numbers, ending badge numberse + 1} that
 * we need to re-update our current state for, then we iterate through the set, updating the answer
 * for all badge numbers in the range [s[i], s[i+1]-1] after doing a DFS with badge s[i].
 * 
 * Time: O(m * (n + m)), Space: O(m + n)
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

int n, e, b, start, dest;
vector<vector<tuple<int, int, int>>> adjlist;  // v, a, b
set<int> s;

int dfs_counter = 0;
vector<int> visited;
void dfs(int u, int bn) {  // badge number
    visited[u] = dfs_counter;
    if (visited[dest] == dfs_counter) return;
    for (auto &[v, a, b] : adjlist[u]) {
        if (visited[v] == dfs_counter) continue;
        if (a <= bn && bn <= b) {
            dfs(v, bn);
        }
    }
}
int main() {
    fast_cin();
    cin >> n >> e >> b >> start >> dest;
    start--;
    dest--;
    adjlist.assign(n, vector<tuple<int, int, int>>());
    for (int i = 0; i < e; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        u--;
        v--;
        adjlist[u].emplace_back(v, a, b);
        s.insert(a);
        s.insert(b + 1);
    }

    ll ans = 0;
    visited.assign(n, 0);
    for (auto it = s.begin(); next(it) != s.end(); it++) {
        dfs_counter++;
        dfs(start, *it);
        if (visited[dest] == dfs_counter) {
            ans += (*(next(it)) - *(it));  // next minus current
        }
    }
    cout << ans << endl;

    return 0;
}