/**CF1974C
 * Straightforward but annoying implementation problem. It is important to remember that the triples are
 * ordered.
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;
vector<int> a;
map<pair<int, int>, int> mp[3];
map<tuple<int, int, int>, int> trips;

int main()
{
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        mp[0].clear();
        mp[1].clear();
        mp[2].clear();
        trips.clear();

        ll ans = 0;
        for (int i = 0; i < n - 2; i++) {
            // consider the triple a[i], a[i+1], a[i+2]
            int x = a[i];
            int y = a[i + 1];
            int z = a[i + 2];
            ll cur = -3LL * trips[{x, y, z}];
            trips[{x, y, z}]++;

            cur += (ll)mp[0][{x, y}];
            mp[0][{x, y}]++;
            cur += (ll)mp[1][{y, z}];
            mp[1][{y, z}]++;
            cur += (ll)mp[2][{z, x}];
            mp[2][{z, x}]++;

            ans += cur;
        }

        cout << ans << endl;
    }

    return 0;
}