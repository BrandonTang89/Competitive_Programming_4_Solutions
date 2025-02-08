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

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        ll l, r, g;
        cin >> l >> r >> g;

        ll ld = (l + g - 1) / g;
        ll rd = r / g;

        bool done = false;
        for (ll diff = (rd - ld); diff >= 0 && !done; diff--) {
            for (ll x = ld; x + diff <= rd; x++) {
                if (gcd(x, x + diff) == 1) {
                    cout << x*g << " " << g*(x + diff) << endl;
                    done = true;
                    break;
                }
            }
        }

        if (!done) {
            cout << -1 << " " << -1 << endl;
        }
    }

    return 0;
}