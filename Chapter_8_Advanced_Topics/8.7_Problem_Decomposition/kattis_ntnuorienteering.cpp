/**Kattis - ntnorienteering
 * Relatively chill. Let dp(i) be the number of lectures we can attend after we attend lecture i
 * (not including i). We can go from lecture i to lecture v if and only if end_time(i) +
 * dist[location(i)][location(v)] <= start_time(v). Then, the answer is max(dp(i) + 1) for all i
 * since we can start from any lecture. We preprocess dist using Floyd-Warshall.
 * 
 * Time: O(L^2 + N^3), Space: O(N^2 + L)
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

int n, l;
vector<vector<ll>> adjmat;
vector<ll> memo;
vector<tuple<int, ll, ll>> lectures;

ll dp(int cur_l)
{
    if (memo[cur_l] != -1) return memo[cur_l];

    ll ans = 0;
    for (int i = 0; i < l; i++) {
        // try going to this new lecture
        auto [uloc, us, ue] = lectures[cur_l];
        auto [vloc, vs, ve] = lectures[i];

        if (vs >= ue + adjmat[uloc][vloc]) {
            ans = max(ans, 1 + dp(i));
        }
    }
    return memo[cur_l] = ans;
}
int main()
{
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> l;
        int e = n * (n - 1) / 2;
        adjmat.assign(n, vector<ll>(n, 1e18));
        for (int i = 0; i < e; i++) {
            int a, b, c;
            cin >> a >> b >> c;
            adjmat[a][b] = c;
            adjmat[b][a] = c;
        }

        // Floyd-Warshall
        for (int k = 0; k < n; k++) {
            adjmat[k][k] = 0;
        }
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    adjmat[i][j] = min(adjmat[i][j], adjmat[i][k] + adjmat[k][j]);
                }
            }
        }

        lectures.assign(l, {0, 0, 0});
        for (int i = 0; i < l; i++) {
            int loc, s, e;
            cin >> loc >> s >> e;
            lectures[i] = {loc, s, e};
        }

        memo.assign(l, -1);
        ll ans = 0;
        for (int i = 0; i < l; i++) {
            ans = max(ans, dp(i) + 1);
        }

        cout << ans << endl;
    }

    return 0;
}