/**Kattis - joggingtrails
 * Basic Chinese Postman Problem. Floyd-warshall + graph manipulation + weighted perfect
 * matching. Fortunately for this question, we don't need to print the solution, else
 * it would be pretty shag.
 * 
 * Time: O(n^2 * 2*n),  Space: O(n^2 * 2*n), limited by weighted matching
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define LSOne(S) (S & (-S))
int n, e;
vector<vector<pair<int, int>>> adjlist;  // node, length
vector<vector<int>> adjmat, oddadjmat;
vector<int> odd_degree;
vector<ll> memo;
ll dp(int mask) {
    ll &ans = memo[mask];
    if (ans != -1) return ans;
    if (mask == 0) return 0;
    ans = 1e9;
    int two_pow_p1 = LSOne(mask);
    int p1 = __builtin_ctz(two_pow_p1);
    int m = mask ^ two_pow_p1;
    while (m) {
        int two_pow_p2 = LSOne(m);
        int p2 = __builtin_ctz(two_pow_p2);
        m ^= two_pow_p2;
        ans = min(ans, dp(mask ^ two_pow_p2 ^ two_pow_p1) + oddadjmat[p1][p2]);
    }
    return ans;
}

int main() {
    while (1) {
        cin >> n;
        if (n == 0)break;
        cin >> e;

        adjlist.assign(n, vector<pair<int, int>>());
        adjmat.assign(n, vector<int>(n, 1e8));
        ll ans = 0;
        for (int i = 0; i < e; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            u--;
            v--;
            adjlist[u].push_back({v, w});
            adjlist[v].push_back({u, w});
            adjmat[u][v] = min(adjmat[u][v], w);
            adjmat[v][u] = min(adjmat[v][u], w);
            ans += w;
        }

        // Floyd Warshall
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }

        odd_degree.clear();
        for (int i = 0; i < n; i++) {
            if (adjlist[i].size() % 2 == 1) odd_degree.emplace_back(i);
        }

        int num_odd = odd_degree.size();
        oddadjmat.assign(num_odd, vector<int>(num_odd, 1e9));
        for (int i = 0; i < num_odd; i++) {
            for (int j = 0; j < num_odd; j++) {
                oddadjmat[i][j] = adjmat[odd_degree[i]][odd_degree[j]];
            }
        }

        // in main
        memo.assign(1 << num_odd, -1);
        ans += dp((1 << num_odd) - 1);

        cout << ans << endl;
    }

    return 0;
}