/**Kattis - catandmince
 * Quite a hard question with many things happening. The first thing to realise is its
 * a BSTA + DP question. And in this case, the DP is a TSP variant. However, it is difficult
 * to write because of the fact that we need to keep track of the time taken to arrive at
 * each vertex...
 * I ended up choosing the set dp(u, mask) = minimum time taken to eat
 * all the 1s in mask and end up at u (an invriant is mask & (1 << u) = true).
 * Instead of regular TSP where look for what vertices are remaining and go there, we instead
 * see where we came from and go backwards. This allows us to test all possible previous
 * vertices and see if we can find the best one. We use this set of transitions since our
 * dp output is the minimum time to get to a state, rather than the minimum time to get
 * from our state to the end... This is useful because the time taken to get from a state
 * to the dest state actually is not entirely determined by the state because we could have
 * spent too long to get to our state and thus can't catch some of the mice before they
 * hide away. The selected dp output allows us to check if we are able to arrive at
 * each state on time.
 *
 * After coding the dp, we had to optimise to avoid TLE. The big ones were avoiding re-initialising
 * the memo array and doing pre-computations for the distances between the vertices. There are other
 * minor ones commented down below. We also played around with the number of iterations of binary
 * search and the upperbound on the initial velocity. A bit of squeezing between TLE and WA...
 *
 * Time: O(50 * n^2 * 2^n), Space: O(n*2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long double ld;

int n, x, y, s, use = 0;
ld multiplier, powers[16];
ld INF = 1e12, initial_v, EPS = 1e-9;
vector<tuple<int, int, int>> mice;

ld dist[15][15], time_from_house[15];
ld dist_internal(int m1, int m2) {
    return hypot(get<0>(mice[m1]) - get<0>(mice[m2]), get<1>(mice[m1]) - get<1>(mice[m2]));
}
ld time_from_house_internal(int m) { return hypot(get<0>(mice[m]), get<1>(mice[m])) / initial_v; }
ld velocity(int mice_eaten) { return initial_v * powers[mice_eaten]; }
ld memo[15][1 << 15];
int last_used[15][1 << 15];
ld dp(int u, int mask) {  // mask is the eaten mice
    ld &ans = memo[u][mask];
    if (last_used[u][mask] == use) return ans;
    last_used[u][mask] = use;  // avoid re-initialisation optimisation

    if (__builtin_popcount(mask) == 1) {
        ld t = time_from_house[u];
        return ans = (t <= get<2>(mice[u])) ? t : INF;
    }
    ans = INF;
    int bm = mask ^ (1 << u);
    int mice_eaten = __builtin_popcount(bm);
    ld prev_v = (initial_v * powers[mice_eaten]);  // compute these once rather than every time
    while (bm) {
        int k = __builtin_ctz(bm);
        bm -= (1 << k);
        // what if we came from k first
        ld t = dp(k, mask ^ (1 << u));
        if (t == INF) continue;
        t += dist[k][u] / prev_v;
        ans = min(ans, t);
    }
    if (ans > (ld)get<2>(mice[u])) ans = INF;
    return ans;
}

bool can_eat_all() {
    use++;
    for (int i = 0; i < n; i++) {
        if (INF - dp(i, (1 << n) - 1) > EPS) return true;  // INF > ans, early exit optimisation
    }
    return false;
}
int main() {
    cin >> n;
    mice.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> x >> y >> s;
        mice[i] = {x, y, s};
    }
    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            dist[u][v] = dist_internal(u, v);
        }
    }
    cin >> multiplier;
    powers[0] = 1;
    for (int j = 1; j <= n; j++) {
        powers[j] = powers[j - 1] * multiplier;  // precompute optimisation
    }
    ld lo = 0, hi = 100000;
    for (int i = 0; i < 50; i++) {
        ld mid = (lo + hi) / 2;
        initial_v = mid;

        for (int j = 0; j < n; j++) {
            time_from_house[j] = time_from_house_internal(j);  // precompute optimisation
        }

        if (can_eat_all())
            hi = mid;
        else
            lo = mid;
    }
    cout << fixed << setprecision(15) << hi << endl;

    return 0;
}