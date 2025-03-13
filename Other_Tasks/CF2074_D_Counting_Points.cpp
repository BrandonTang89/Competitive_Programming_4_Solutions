#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll isqrt(ll n) {
    ll hi = n < 1e8 ? n : 1e8;
    ll lo = 0;
    while (lo < hi) {
        ll mid = (hi + lo + 1) / 2;
        if (mid * mid <= n) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;

    while (tc--) {
        unordered_map<ll, ll> cnt;
        ll n, m;
        cin >> n >> m;
        vector<ll> a(n);
        for (ll& x : a) {
            cin >> x;
        }
        vector<ll> r(n);
        for (ll& x : r) {
            cin >> x;
        }

        for (int i = 0; i < n; i++) {
            ll center = a[i];
            ll rad = r[i];

            for (ll x = center - rad; x <= center + rad; x++) {
                ll s = isqrt(rad * rad - (x - center) * (x - center));
                cnt[x] = max(cnt[x], s * 2 + 1);
            }
        }

        ll ans = 0;
        for (auto& [k, v] : cnt) {
            ans += v;
        }

        cout << ans << endl;
    }

    return 0;
}