/**kattis  - maximizingyourpay
 * Maximum hamiltonian tour variant, unweighted by not perfect graph, we can choose to end the tour early
 * assuming that there is and edge from u back to 0.
 * 
 * Time: O(2^n * n^2), Space: O(n * 2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define LSOne(S) ((S) & -(S))
#define MAX_n 10
int adjmat[MAX_n][MAX_n], memo[MAX_n][1 << (MAX_n - 1)];

int n, e;
int dp(int u, int mask) {  // mask = free coordinates
    if (mask == 0) {
        return memo[u][mask] = (adjmat[u][0] ? 0 : -1e9);  // close the loop
    }
    int &ans = memo[u][mask];
    if (ans != -1) return ans;        // computed before
    ans = (adjmat[u][0] ? 0 : -1e6);  // either go back straight away or cannot go back
    int m = mask;
    while (m) {                                // up to O(n)
        int two_pow_v = LSOne(m);              // but this is fast
        int v = __builtin_ctz(two_pow_v) + 1;  // offset v by +1
        m -= two_pow_v;
        if (!adjmat[u][v]) continue;                  // Cannot traverse this edge
        ans = max(ans, 1 + dp(v, mask ^ two_pow_v));  // keep the min
    }
    return ans;
}

int main() {
    while (true) {
        cin >> n;
        if (n == 0) break;
        cin >> e;
        memset(memo, -1, sizeof(memo));
        memset(adjmat, 0, sizeof(adjmat));
        for (int i = 0; i < e; i++) {
            int u, v;
            cin >> u >> v;
            adjmat[u][v] = adjmat[v][u] = 1;
        }
        adjmat[0][0] = 1;  // important to ensure that minimally we visit 1 place :)
        int longest_tour = dp(0, (1 << (n - 1)) - 1);
        cout << longest_tour + 1 << endl;
    }

    return 0;
}