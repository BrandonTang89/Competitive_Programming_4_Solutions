/**Kattis - ontrack
 * For each junction, assume it is the critical junction, we can do an O(V) dfs to determine the
 * number of components. Then the number of disconnected junctions will be n choose 2 - (k choose 2)
 * where k is the size of each component. The best edge to add joins the 2 largest components, this
 * will lead to the number of disconnected junctions being -((a+b) choose 2) + (a choose 2) + (b
 * choose 2). Note that we can always do this because the critical junction will never be a leaf
 * vertex, so there will always be at least 2 components. Also note that we can optimise our code by
 * skipping checking if leaf vertices are critical junctions.
 *
 * Time: O(V^2), Space: O(V)
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

ll memo_comb[10009][3]; // since we only go up to N choose 2
ll comb(int n, int r) {
    if (r == 0 || n == r) return 1;
    if (n < r) return 0;
    if (memo_comb[n][r] != -1) return memo_comb[n][r];
    return memo_comb[n][r] = comb(n - 1, r - 1) + comb(n - 1, r);
}

int n, e;
int critical_juction;
int best_critical_juction, most_disconnected;
int cc_size;
vector<bool> visited;
vector<int> cc_sizes, best_cc_sizes;
vector<int> adjlist[10001];

void dfs(int u) {
    visited[u] = true;
    if (u == critical_juction) return;  // don't propogate from here

    cc_size++;
    for (int v : adjlist[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
}

ll total_disconnected(vector<int> &cc_sizes) {
    ll ans = comb(n, 2);
    for (auto k : cc_sizes) {
        ans -= comb(k, 2);
    };
    return ans;
}
int main() {
    fast_cin();
    memset(memo_comb, -1, sizeof memo_comb);
    cin >> e;
    n = e + 1;

    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        adjlist[u].emplace_back(v);
        adjlist[v].emplace_back(u);
    }

    for (critical_juction = 0; critical_juction < n; critical_juction++) {
        if (adjlist[critical_juction].size() == 1)
            continue;  // leaf vertex? skip because it can't be critical
        visited.assign(n, false);
        cc_sizes.clear();
        for (int i = 0; i < n; i++) {
            if (critical_juction == i) continue;
            if (!visited[i]) {
                cc_size = 0;
                dfs(i);
                cc_sizes.emplace_back(cc_size);
            }
        }

        int disconnected = total_disconnected(cc_sizes) -
                           (n - 1);  // -(n-1) we don't count the blown up one as a junction
        if (disconnected > most_disconnected) {
            most_disconnected = disconnected;
            best_critical_juction = critical_juction;
            best_cc_sizes = cc_sizes;
        }
    }

    cout << most_disconnected << " ";

    sort(best_cc_sizes.begin(), best_cc_sizes.end(), greater<int>());
    most_disconnected += -comb(best_cc_sizes[0] + best_cc_sizes[1], 2) + comb(best_cc_sizes[0], 2) +
                         comb(best_cc_sizes[1], 2);

    cout << most_disconnected << endl;
    return 0;
}