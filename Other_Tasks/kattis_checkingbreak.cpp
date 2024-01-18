/**Kattis - checkingbreak
 * Math / Adhoc / Geom. Most of the properties are easy to check (but also easy to miss out on). The
 * property that there is no cake left over initially seems quite difficult. However, we observe
 * that if the property that the regions have 0 intersection is fufilled, then the size of the union
 * of the regions is equal to the sum of the sizes of the regions. Then we can just compare that to
 * the volume of the cake to check if there is any cake left over. We do need to check that all
 * regions are indeed within the cake.
 *
 * Code for checking if a point is within a region and whether 2 regions intersect is surprisingly
 * easy if done correctly. Since m is small, we can do a pairwise check for intersection.
 * 
 * Time: O(m^2), Space: O(m)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

inline bool doesIntersect(tuple<ll, ll, ll, ll, ll, ll> a, tuple<ll, ll, ll, ll, ll, ll> b)
{
    auto &[x1, y1, z1, u1, v1, w1] = a;
    auto &[x2, y2, z2, u2, v2, w2] = b;

    if (x1 > x2) {
        swap(x1, x2);
        swap(u1, u2);
    }
    if (u1 < x2) return false;

    if (y1 > y2) {
        swap(y1, y2);
        swap(v1, v2);
    }
    if (v1 < y2) return false;

    if (z1 > z2) {
        swap(z1, z2);
        swap(w1, w2);
    }
    if (w1 < z2) return false;

    return true;
}

inline bool doesContain(tuple<ll, ll, ll, ll, ll, ll> a, tuple<ll, ll, ll> b)
{
    auto &[x1, y1, z1, u1, v1, w1] = a;
    auto &[x2, y2, z2] = b;

    if (x1 <= x2 && x2 <= u1 && y1 <= y2 && y2 <= v1 && z1 <= z2 && z2 <= w1)
        return true;
    else
        return false;
}
int main()
{
    while (true) {
        ll a, b, c, m;
        cin >> a;
        if (a == -1) break;
        cin >> b >> c >> m;

        vector<tuple<ll, ll, ll>> arr(m);
        vector<tuple<ll, ll, ll, ll, ll, ll>> sols(m);  // x,y,z,u,v,w
        ll totalVolume = 0;

        for (int i = 0; i < m; i++) {
            int x, y, z;
            cin >> x >> y >> z;
            arr[i] = make_tuple(x, y, z);
        }

        bool valid = true;
        for (int i = 0; i < m; i++) {
            ll x, y, z, u, v, w;
            cin >> x >> y >> z >> u >> v >> w;
            if (x > u || y > v || z > w) valid = false;
            if (u > a || v > b || w > c) valid = false;
            totalVolume += (u - x + 1) * (v - y + 1) * (w - z + 1);
            sols[i] = make_tuple(x, y, z, u, v, w);
            valid &= doesContain(sols[i], arr[i]);
        }

        if (totalVolume != a * b * c) {
            valid = false;
        }

        if (!valid) {
            cout << "NO" << endl;
            continue;
        }

        for (int i = 0; i < m; i++) {
            for (int j = i + 1; j < m; j++) {
                if (doesIntersect(sols[i], sols[j])) {
                    valid = false;
                    break;
                }
            }
            if (!valid) break;
        }

        if (valid)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }

    return 0;
}