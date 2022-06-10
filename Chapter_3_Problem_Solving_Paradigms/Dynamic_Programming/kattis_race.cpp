/**Kattis - race
 * Interesting problem that is kinda variant of TSP but needs to be solved with a different
 * approach. We let dp(current location, bitmask of locations visited (including current)) be the
 * minimum time taken to do arrive at that state. If dp(n+1, bm) < T, it is possible to go to
 * all the nodes in bm within the time available and we can take ans = max(ans, points(bm))
 * where points(bm) is the points that we gather from visiting all locations in bm. By considering
 * all the bms, we can get our optimal answer.
 *
 * Now how to calculate dp(cur, bm)? In the base case, we have that theres only 1 location in bm,
 * cur. In this case, we get the time to go from the start to cur + the time to spend at cur.
 * However, if this time taken is > deadline(cur) then we should just return INF since we can't do
 * it. The transition is to check for all locations in bm, prev, go from the previous state (prev,
 * bm^(1<<cur)) to the current state, plus the adjmat[prev][cur] + time[cur]. Similarly if this time
 * is greater than the deadline of cur, we just return INF.
 * 
 * We need to work the edge cases for cur = n+1 as well, then we'll be good to go. Also note to
 * get the lexicographically smallest optimal solution, we just code a custom comparison function
 * for that.
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
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);
#define LSOne(S) ((S) & -(S))
int n, T;
vector<int> t, D, p;
vector<vector<int>> adjmat;
const int INF = 1e8;
int memo[22][(1 << 20)];
int dp(int cur, int bm) {
    // Minimum time taken to arrive at cur, given that we have visited all in bm
    // cout << "cur: " << (cur) <<" bm: " << bitset<3>(bm) << endl;

    int &ans = memo[cur][bm];
    if (ans != -1) return ans;
    if (cur == n + 1 && bm == 0) {
        return ans = adjmat[n][n + 1];
    }
    assert(__builtin_popcount(bm) != 0);

    if (cur == n + 1) {  // at the end
        ans = INF;
        int m = bm;
        while (m) {
            int two_pow_v = LSOne(m);  // but this is fast
            int v = __builtin_ctz(two_pow_v);
            int tx = dp(v, bm) + adjmat[v][cur];

            ans = min(tx, ans);
            m -= two_pow_v;
        }

        return ans;
    }

    if (__builtin_popcount(bm) == 1) {  // Next to the start, not at end
        assert((1 << cur) & bm);
        int tx = adjmat[n][cur] + t[cur];
        if (D[cur] == -1 || tx <= D[cur]) {
            return ans = tx;
        } else {
            return ans = INF;
        }
    }

    ans = INF;
    int m = bm;
    while (m) {
        int two_pow_v = LSOne(m);  // but this is fast
        m -= two_pow_v;
        int v = __builtin_ctz(two_pow_v);
        if (v == cur) continue;
        int tx = dp(v, bm ^ (1 << cur)) + t[cur] + adjmat[v][cur];

        if (D[cur] == -1 || tx <= D[cur]) {
            ans = min(tx, ans);
        }
    }

    return ans;
}

int pts(int bm) {
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if ((1 << i) & bm) ans += p[i];
    }
    return ans;
}

bool left_smaller(int l, int r) {
    while (true) {
        if (l == 0) return true;
        if (r == 0) return false;

        int li = LSOne(l);
        l -= li;
        int ri = LSOne(r);
        r -= ri;

        if (li < ri) return true;
        if (ri < li) return false;
    }
}
int main() {
    fast_cin();
    memset(memo, -1, sizeof memo);
    cin >> n >> T;
    t.resize(n);
    D.resize(n);
    p.resize(n);
    adjmat.assign(n + 2, vector<int>(n + 2, 0));
    for (int i = 0; i < n; i++) {
        cin >> p[i] >> t[i] >> D[i];
    }

    for (int i = 0; i < n + 2; i++) {
        for (int j = 0; j < n + 2; j++) {
            cin >> adjmat[i][j];
        }
    }

    int best_pts = 0, best_mask = 0;
    bool way = false;
    for (int i = 0; i < (1 << n); i++) {
        // cout << bitset<5>(i).to_string() << " " << pts(i) << " " << dp(n + 1, i) << endl;
        if (dp(n + 1, i) <= T) {
            way = true;
            if (best_pts < pts(i)) {
                best_pts = pts(i);
                best_mask = i;
            } else if (best_pts == pts(i)) {
                best_mask = left_smaller(best_mask, i) ? best_mask : i;
            }
        }
    }
    if (!way) {
        cout << 0 << endl;
        return 0;
    }
    cout << best_pts << endl;
    while (best_mask) {
        int two_pow_v = LSOne(best_mask);
        cout << __builtin_ctz(two_pow_v) + 1 << ' ';
        best_mask -= two_pow_v;
    }
    cout << endl;
    return 0;
}