#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

typedef vector<int> vi;
#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    fast_cin();
    int tc;
    cin >> tc;
    while (tc--) {
        int n;
        cin >> n;
        vi arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        unordered_map<int, int> c;
        for (int i = 0; i < n; i++) {
            c[arr[i]]++;
        }
        vi d(n);
        for (int i = 0; i < n; i++) {
            if (c[arr[i]] > 1) {
                d[i] = 1;
            }
        }
        int curStart = -1;
        int bestStart = -1;
        int bestLength = 0;
        for (int i = 0; i < n; i++) {
            if (d[i] == 0 && ((i == 0) || (d[i - 1] == 1))) {
                curStart = i;
            }
            if (d[i] == 0 && (i == n - 1 || d[i + 1] == 1)) {
                if (i - curStart + 1 > bestLength) {
                    bestLength = i - curStart + 1;
                    bestStart = curStart;
                }
            }
        }
        if (bestStart == -1) {
            cout << 0 << endl;
        } else {
            cout << bestStart + 1 << " " << bestStart + bestLength << endl;
        }
    }

    return 0;
}