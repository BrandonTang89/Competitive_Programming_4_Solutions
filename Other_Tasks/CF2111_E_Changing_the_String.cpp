#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int n, q;
string s;
set<int> ca, ba, cb, bc;

char a = 'a', b = 'b', c = 'c';
void solve() {
    cin >> n >> q;
    cin >> s;

    ca.clear();
    ba.clear();
    cb.clear();
    bc.clear();
    for (int i = 0; i < q; i++) {
        char x, y;
        cin >> x >> y;

        if (x == 'c' && y == 'a') {
            ca.insert(i);
        } else if (x == 'b' && y == 'a') {
            ba.insert(i);
        } else if (x == 'c' && y == 'b') {
            cb.insert(i);
        } else if (x == 'b' && y == 'c') {
            bc.insert(i);
        }
    }

    for (int i = 0; i < n; i++) {
        if (s[i] == a) continue;

        if (s[i] == b) {
            // try to do b -> a first
            if (!ba.empty()) {
                s[i] = a;
                ba.erase(ba.begin());
            } else if (!bc.empty()) {
                // try to do b -> c -> a
                int idx = *bc.begin();

                // see if we can do c -> a
                auto it = ca.upper_bound(idx);
                if (it != ca.end()) {
                    s[i] = a;
                    bc.erase(bc.begin());
                    ca.erase(it);
                }
            }
        }

        else if (s[i] == c) {
            // try to do c -> a first
            if (!ca.empty()) {
                s[i] = a;
                ca.erase(ca.begin());
            } else if (!cb.empty()) {
                // try to do c -> b
                int idx = *cb.begin();
                cb.erase(cb.begin());
                s[i] = b;

                // try to do b -> a
                auto it = ba.upper_bound(idx);
                if (it != ba.end()) {
                    s[i] = a;
                    ba.erase(it);
                }
            }
        }
    }
    cout << s << endl;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) solve();

    return 0;
}