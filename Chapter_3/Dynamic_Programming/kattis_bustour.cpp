/**Kattis - bustour
 * TSP variant. We use 2 almost identical DPs, dp_left and dp_right. dp_left has a state of u,
 * cities_left and returns the minimum cost to go from u, visit all the cities in cities_left and
 * then go to the 0th city. dp_right has the same states but returns the minimum cost to go from
 * u, visit all the cities in cities left and then go to the n-1 th city.
 *
 * The key insight to this question is that we will brute force on all h choose h/2 possible
 * selections of our h/2 first half of the cities.
 *
 * Notice that the cost to go from finishing all the cities in the mask to the attraction is
 * dp_right(some vertex u in the mask, complement of the mask) since we should finish up the rest of
 * the cities in the lowest cost. But to know the shortest way to go from 0 to finishing the mask
 * and arriving at u, we use the dp_left function. This is because the length of the shortest path
 * from a to b going through some nodes is the same as the length of the shortest path from b to a
 * going through the same nodes. Thus instead of somehow going going from 0 to the (u, mask), we
 * use dp left to go from (u, mask) to 0. Similar logic can be applied to the trip to put the
 * tourist back. See the actual code for details.
 * 
 * Take note of the edge case of h=1, ie n = 3 since h/2 == 0.
 *
 * Also hey this is how a ICPC World Final question looks like, nice that I could solve it.
 *
 * Time: O(n^2 * 2^n), Space: O(n^2 * n)
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
int n, e, u, v, w;
vector<vector<int>> adjmat;
ll memo_right[21][(1 << 20)];
ll memo_left[21][(1 << 20)];
const int INF = 1e9 + 9;

ll dp_right(int u, int cities_left) {  // dist to finish , intially all 1s (1 << (n-2)) -1)
    ll &ans = memo_right[u][cities_left];
    if (ans != -1) return ans;
    ans = INF;
    if (cities_left == 0) return ans = adjmat[u][n - 1];

    int m = cities_left;
    while (m != 0) {                           // up to O(n)
        int two_pow_v = LSOne(m);              // but this is fast
        int v = __builtin_ctz(two_pow_v) + 1;  // +1 to account for not ever going back to 0
        ans = min(ans, adjmat[u][v] + dp_right(v, cities_left ^ two_pow_v));  // keep the min
        m -= two_pow_v;
    }
    return ans;
}

ll dp_left(int u, int cities_left) {  // dist to finish , intially all 1s (1 << (n-2)) -1)
    ll &ans = memo_left[u][cities_left];
    if (ans != -1) return ans;
    ans = INF;
    if (cities_left == 0) return ans = adjmat[u][0];

    int m = cities_left;
    while (m != 0) {                           // up to O(n)
        int two_pow_v = LSOne(m);              // but this is fast
        int v = __builtin_ctz(two_pow_v) + 1;  // +1 to not go back to 0
        ans = min(ans, adjmat[u][v] + dp_left(v, cities_left ^ two_pow_v));  // keep the min
        m -= two_pow_v;
    }
    return ans;
}

int main() {
    int case_num = 0;
    fast_cin();
    while (cin >> n >> e) {
        adjmat.assign(n, vector<int>(n, INF));
        memset(memo_right, -1, sizeof memo_right);
        memset(memo_left, -1, sizeof memo_left);
        for (int i = 0; i < e; i++) {
            cin >> u >> v >> w;
            adjmat[u][v] = w;
            adjmat[v][u] = w;
        }
        // Floyd Warshall's
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }
        if (n == 3) {
            cout << "Case " << ++case_num << ": " << 2 * (adjmat[0][1] + adjmat[1][2]) << endl;
            continue;
        }
        ll cur_min = INT_MAX;
        for (int bm = 0; bm < (1 << (n - 2)); bm++) {
            if (__builtin_popcount(bm) != (n - 2) / 2) continue;
            // BM identifies the citie to do in the first half
            // cout << bm << endl;
            int bm_complement = (1 << (n - 2)) - 1 - bm;
            for (int i = 1; i < n - 1; i++) {      // finish seeing bm, end at city i
                for (int j = 1; j < n - 1; j++) {  // j is the first city of bm to be seen otw back
                    if (!(bm & (1 << (i - 1)))) continue;
                    if (!(bm & (1 << (j - 1)))) continue;
                    ll cur = dp_right(i, bm_complement) + dp_left(i, bm ^ (1 << (i - 1))) +
                             dp_right(j, bm ^ (1 << (j - 1))) + dp_left(j, bm_complement);
                    // cout << "i: " << i << " j: " << j << " cur: " << cur << endl;
                    cur_min = min(cur_min, cur);
                }
            }
        }
        cout << "Case " << ++case_num << ": " << cur_min << endl;
    }

    return 0;
}