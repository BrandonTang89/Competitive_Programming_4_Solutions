/**Kattis - bits
 * Simple bit counting
 * Time: O(1), Soace: O(1)
*/
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int tc;
int main()
{
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        int ans = __builtin_popcount(n);

        while (n > 0) {
            n /= 10;
            ans = max(ans, __builtin_popcount(n));
        }
        cout << ans << endl;
    }

    return 0;
}