/**CF1971F
 * Finding the number of lattice points (x, y) suc that r^2 <= x^2 + y^2 < (r + 1)^2
 * We can restrict ourselves to finding (x, y) with x >= 1 and y >= 0 then multiplying by 4 due to
 * rotational symmetry.
 *
 * For each 1 <= x <= r, we are interested in finding the number of y such thar r^2 - x^2 <= y^2 <
 * (r + 1)^2 - x^2 To do this, we can binary search our precomputed array of square numbers twice.
 * Might be non-trivial to reason about how exactly to do this but just do it.
 * 
 * Time: O(r log r), Space: O(r)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll r, rs, rp1s;
vector<ll> squares;
int main()
{
    ll rmax = 1e5 + 1;
    squares.resize(rmax + 2);
    for (ll i = 1; i <= (rmax + 1); i++) {
        squares[i] = i * i;
    }

    int tc;
    cin >> tc;
    while (tc--) {
        cin >> r;
        rs = squares[r];
        rp1s = squares[r + 1];

        ll ans = 0;
        for (int x = 1; x <= r; x++) {
            // find the largest i such that squares[i] < rp1s - squares[x]
            ll bound = rp1s - squares[x];
            ll high = lower_bound(squares.begin(), squares.end(), bound) - squares.begin() - 1;

            // find the largest i such that squares[i] < rs - squares[x]
            bound = rs - squares[x];
            ll low = lower_bound(squares.begin(), squares.end(), bound) - squares.begin() - 1;

            ans += high - low;
        }
        cout << ans * 4LL << endl;
    }
    return 0;
}