// CF2093G
// Line sweep, maintaining 32 sets of last seen hash_maps based on masked versions of the array elements.
// Time: O(n log n), Space: O(n)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
int main() {
    int tc;
    cin >> tc;
    while (tc--) {
        cin >> n >> k;
        a.resize(n);
        for (auto& x : a) {
            cin >> x;
        }

        // check single
        if (k == 0) {
            cout << 1 << endl;
            continue;
        }

        // check adjacent
        bool found_shortcut = false;
        for (int i = 0; i < n - 1; i++) {
            if ((a[i] ^ a[i + 1]) >= k) {
                found_shortcut = true;
                break;
            }
        }
        if (found_shortcut) {
            cout << 2 << endl;
            continue;
        }

        int best = 1e9;
        unordered_map<int, int> last_seen[32];  // last_seen[i][j] is the last seen index of j (masking out the least significant i bits)
        for (int i = 0; i < n; i++) {
            int looking_for = 0;
            for (int j = 31; j >= 0; j--) {
                if ((1 << j) & k) {  // must follow along differently
                    looking_for = looking_for | ((1 << j) ^ ((1 << j) & a[i]));
                } else {  // we can try to find someone who has a different version at this point
                    looking_for = looking_for | ((1 << j) ^ ((1 << j) & a[i]));
                    if (last_seen[j].contains(looking_for)) {
                        int idx = last_seen[j][looking_for];
                        best = min(best, i - idx + 1);
                    }
                    // otherwise assume this bit will be the same
                    looking_for = looking_for ^ (1 << j);
                }
            }

            // also check non-masked
            if (last_seen[0].contains(looking_for)) {
                int idx = last_seen[0][looking_for];
                best = min(best, i - idx + 1);
            }

            int mask = ~0;
            for (int j = 0; j < 32; j++) {
                last_seen[j][a[i] & mask] = i;
                mask = mask ^ (1 << j);
            }
        }

        if (best == 1e9) {
            cout << -1 << endl;
        } else {
            cout << best << endl;
        }
    }
    return 0;
}