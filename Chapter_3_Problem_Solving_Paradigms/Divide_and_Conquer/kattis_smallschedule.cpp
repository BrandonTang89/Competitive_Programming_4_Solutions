/**Kattis - smallschedule
 * Observe that it is easy to check if a given maximum time to run machines for works. We can just
 * schedule as many longer tasks as possible and fill the rest with the shorter tasks greedily.
 * until we max out the time the machine runs for. This allows us to BSTA quite directly. Look out
 * for the need to use long long.
 * 
 * Time: O(log (q*l + s) * m), Space: O(1);
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;

int q, m, s, l;

bool works(ll max_time) {
    ll cs = s, cl = l;
    for (int i = 0; i < m && (cl > 0 || cs > 0); i++) {
        ll num_l = min((max_time) / q, cl);
        cl -= num_l;
        ll time_left = max_time - num_l * q;
        ll num_s = min(time_left, cs);
        cs -= num_s;
    }
    return cl == 0 && cs == 0;
}
int main() {
    cin >> q >> m >> s >> l;

    ll lo = (l > 0 ? q : 0), hi = q * l + s;
    while (lo + 1 < hi) {
        ll mid = (lo + hi) / 2;
        if (works(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    if (works(lo)) hi = lo;

    cout << hi << endl;

    return 0;
}