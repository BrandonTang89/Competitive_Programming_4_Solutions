/** Kattis - bond
 * Quite a simple bitmask DP problem, very similar to TSP. Let dp(cur, bm) be the probability
 * of completing missions [cur..n-1] assuming that all the bonds that are 1 in bm are available.
 * We just take the max of selecting each possible bond from bm.
 * 
 * Time: O(n^2 * 2^n), Space: O(n*2^n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n;
double memo[21][1 << 20];
vector<vector<double>> ps;

double dp(int cur, int bm)
{  // currentMission, bitmask of all available bonds
    if (cur == n) return 1;
    if (memo[cur][bm] != -1) return memo[cur][bm];

    double ans = 0;
    int m = bm;
    while (m > 0) {
        int selected = __builtin_ctz(m);
        m ^= (1 << selected);
        ans = max(ans, ps[selected][cur] / (100.0) * dp(cur + 1, bm ^ (1 << selected)));
    }
    return memo[cur][bm] = ans;
}
int main()
{
    cin >> n;
    memset(memo, -1, sizeof memo);

    ps.assign(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> ps[i][j];
        }
    }

    cout << fixed << setprecision(12) << dp(0, (1 << n) - 1) * 100 << endl;

    return 0;
}