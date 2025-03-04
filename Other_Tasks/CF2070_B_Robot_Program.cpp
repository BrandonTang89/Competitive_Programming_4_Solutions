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
        ll n, x, k;
        cin >> n >> x >> k;
        string s;
        cin >> s;

        // consider x to 0
        ll c = x;
        ll t = 0;
        for (; t < n && c != 0; t++) {
            if (s[t] == 'R') {
                c++;
            } else {
                c--;
            }
        }

        if (c != 0) {
            cout << 0 << endl;
            continue;
        }

        ll l = 0;
        do {
            if (s[l] == 'R') {
                c++;
            } else {
                c--;
            }
            l++;
        } while (l < n && c != 0);

        if (c != 0) {
            cout << 1 << endl;
            continue;
        }
        cout << (k - t) / l + 1 << endl;
    }

    return 0;
}