/**CF2051G Snakes
 * Construct a graph G(V, E) such that V = {1, 2, ..., n} and E = {(u, v, w) | the minimum distance snake v must be put to the immediate right of snake u (i.e. s_u - s_v) must be at least w}.
 * Now we are just looking for a variation of the shortest hamiltonian path (where we also need to count the number of positions the last snake moves, i.e. the final head position of the last snake).
 * This is done with bitmask DP in O(n^2 2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

constexpr ll inf = 1e18;
int n, q;
vector<int> heads;
vector<int> tails;
vector<vector<int>> adjmat;
vector<vector<ll>> memo;
ll dp(int u, int avail) {
    if (avail == 0) return heads[u];
    if (memo[u][avail] != -1) return memo[u][avail];

    memo[u][avail] = inf;
    int bm = avail;
    while (bm) {
        int v = __builtin_ctz(bm);
        bm ^= (1 << v);
        memo[u][avail] = min(memo[u][avail], dp(v, avail ^ (1 << v)) + adjmat[u][v]);
    }

    return memo[u][avail];
}

int main() {
    cin >> n >> q;
    heads.assign(n, 0);
    tails.assign(n, 0);
    adjmat.assign(n, vector<int>(n, 1));

    for (int i = 0; i < q; i++) {
        int u;
        char op;
        cin >> u >> op;
        u--;
        if (op == '+') {
            heads[u]++;
            for (int v = 0; v < n; v++) {
                if (u != v) {
                    adjmat[u][v] = max(adjmat[u][v], heads[u] - tails[v] + 1);
                }
            }
        } else {
            tails[u]++;
        }
    }

    memo.assign(n, vector<ll>(1 << n, -1));
    ll ans = inf;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp(i, ((1 << n) - 1) ^ (1 << i)));
    }
    cout << ans + 1 << endl;

    return 0;
}