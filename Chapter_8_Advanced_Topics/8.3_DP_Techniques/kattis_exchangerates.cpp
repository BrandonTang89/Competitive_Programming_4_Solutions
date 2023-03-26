/**Kattis - exchangerates
 * A simple DP but kinda weird in the sense that the basecase is the start rather than the end. We
 * let maxcad(i) be the max amt of canadian cents we can get at the start of day i, maxusd(i) is the
 * same for usd.
 *
 * Our required recurrences are thus
 * maxcad[i + 1] = max(maxcad[i], (ll)((double)maxusd[i] * ex[i] * 0.97));
 * maxusd[i + 1] = max(maxusd[i], (ll)((double)maxcad[i] / ex[i] * 0.97));
 *
 * With the base case maxcad[0] = 100000;
 *
 * And our answer is maxcad[n] / 100.0
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int n;
vector<double> ex;
vector<ll> maxcad;
vector<ll> maxusd;
int main()
{
    while (1) {
        cin >> n;
        if (n == 0) break;
        ex.assign(n, 0);
        maxcad.assign(n + 1, 0);
        maxusd.assign(n + 1, 0);
        for (int i = 0; i < n; i++) cin >> ex[i];
        maxcad[0] = 100000;

        for (int i = 0; i < n; i++) {
            maxcad[i + 1] = max(maxcad[i], (ll)((double)maxusd[i] * ex[i] * 0.97));
            maxusd[i + 1] = max(maxusd[i], (ll)((double)maxcad[i] / ex[i] * 0.97));
        }
        double ans = (double)maxcad[n] / 100.0;
        cout << fixed << setprecision(2) << ans << endl;
    }

    return 0;
}