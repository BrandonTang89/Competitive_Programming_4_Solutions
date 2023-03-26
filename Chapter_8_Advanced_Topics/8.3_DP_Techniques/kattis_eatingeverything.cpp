/**Kattis -eatingeverything
 * Simple DP. Let dp(u) be the max satisfaction achievable from node u (assuming that we eat the
 * whole pizza at u). Then dp(u) = max(eat pizza at u, don't eat pizza at u). If we eat the pizza
 * at u, the max satisfaction is sat[u] + max(dp(v) / 2.0) for all v in adjlist[u]. If we don't eat
 * the pizza at u, the max satisfaction is max(dp(v)) for all v in adjlist[u].
 * 
 * Time: O(V+E), Space: O(V+E)
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

int n, e;
vector<vector<int>> adjlist;
vector<int> sat;
vector<double> memo;

double dp(int u)
{
    if (memo[u] != -1) return memo[u];
    double ans = 0;
    for (int v : adjlist[u]) {
        ans = max(ans, dp(v));
    }
    ans = max(ans, sat[u] + ans / 2.0);

    return memo[u] = ans;
}
int main()
{
    cin >> n >> e;
    adjlist.assign(n, vector<int>());
    sat.assign(n, 0);
    memo.assign(n, -1);

    for (int i = 0; i < n; i++) cin >> sat[i];
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adjlist[a].push_back(b);
    }

    double ans = dp(0);
    cout << fixed << setprecision(10) << ans << endl;

    return 0;
}