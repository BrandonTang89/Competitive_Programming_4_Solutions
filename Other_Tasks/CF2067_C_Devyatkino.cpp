#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

ll best;
void can(ll n, ll j) {
    for (ll i = 0; i <= 6; i++) {
        ll x = n + i * j;
        while (x) {
            if (x % 10 == 7) {
                best = min(best, i);
                return;
            };
            x /= 10;
        }
    }
}

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        ll n;
        cin >> n;
        best = 7;

        can(n, 9LL);
        can(n, 99LL);
        can(n, 999LL);
        can(n, 9999LL);
        can(n, 99999LL);
        can(n, 999999LL);
        can(n, 9999999LL);
        can(n, 99999999LL);
        can(n, 999999999LL);
        cout << best << endl;
    }

    return 0;
}