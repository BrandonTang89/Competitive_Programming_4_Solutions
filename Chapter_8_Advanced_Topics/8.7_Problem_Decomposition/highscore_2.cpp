/**Kattis - highscore2
 * Ternary search + math. We observe that given that we make min(a, b, c) = i, the best move after
 * is to add all the remaining wildcards to the largest of a, b, c. As such, we ternary search on i.
 * We just hope that the function behaves well enough such that ternary search will work, and
 * magically it does.
 *
 * The bounds l = arr[0], r = arr[0] + d; are sketchily chosen. I don't see why doing
 * r = (arr[0] + arr[1] + arr[2] + d) / 3 + 1; doesn't work since that should be the maximum
 * minimum possible but it seems that the last testcase has the optimal as f(arr[0] + d).
 *
 * Time: O(log(d)), Space: O(1)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll d;
ll arr[3];
inline ll f(ll i)
{
    // make all minimally i
    ll amt_left = d - (i - arr[0]);
    if (arr[1] < i) amt_left -= (i - arr[1]);
    if (arr[2] < i) amt_left -= (i - arr[2]);

    if (amt_left < 0) return -1; // not possible
    return ((max(arr[2], i) + amt_left) * (max(arr[2], i) + amt_left) +
            max(arr[1], i) * max(arr[1], i) + i * i + 7 * i);
}
int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> arr[0] >> arr[1] >> arr[2] >> d;

        sort(arr, arr + 3);

        // ternary search
        ll l = arr[0], r = arr[0] + d;
        while (r - l > 2) {
            ll m1 = l + (r - l) / 3;
            ll m2 = r - (r - l) / 3;
            ll f1 = f(m1);
            ll f2 = f(m2);
            if (f1 < f2) {
                l = m1;
            }
            else {
                r = m2;
            }
        }
        ll ans = 0;
        for (ll i = l; i <= r; i++) {
            ans = max(ans, f(i));
        }

        cout << ans << endl;
    }

    return 0;
}