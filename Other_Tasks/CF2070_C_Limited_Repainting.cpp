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

ll n, k;
string s;
vector<int> a;

bool canDo(int maxPenalty) {
    int numOperations = k;

    bool painting = false;
    for (int i = 0; i < n; i++) {
        if (a[i] <= maxPenalty) {
            continue;
        }

        if (!painting) {
            if (s[i] == 'B') {
                painting = true;
                if (numOperations == 0) return false;
                numOperations--;
            }
        } else {
            if (s[i] == 'R') {
                painting = false;
            }
        }
    }

    return true;
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        cin >> s;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        int l = 0;
        int h = 1e9;

        while (l < h) {
            int m = (h + l) / 2;
            if (canDo(m)) {
                h = m;
            } else {
                l = m + 1;
            }
        }

        cout << l << endl;
    }

    return 0;
}