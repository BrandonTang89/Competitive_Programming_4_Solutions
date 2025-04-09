// CF2093G
// Line sweep, maintaining 32 sets of last seen hash_maps based on masked versions of the array elements.
// Time: O(n log n), Space: O(n)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> a;
unordered_map<int, int> last_seen[31];  // last_seen[i][j] is the last seen index of j (masking out the least significant i bits)
int main() {
    for (int i = 0; i < 31; i++) {
        last_seen[i].reserve(1e4); // deal with the hacking issue...
    }
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

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
        for (int i = 0; i < 31; i++) {
            last_seen[i].clear();
        }

        for (int i = 0; i < n; i++) {
            int looking_for = 0;
            for (int j = 30; j >= 0; j--) {
                if ((1 << j) & k) {  // must follow along differently
                    looking_for = looking_for | ((1 << j) ^ ((1 << j) & a[i]));
                } else {  // we can try to find someone who has a different version at this point
                    looking_for = looking_for | ((1 << j) ^ ((1 << j) & a[i]));
                    auto it = last_seen[j].find(looking_for);
                    if (it != last_seen[j].end()) {
                        int idx = it->second;
                        best = min(best, i - idx + 1);
                    }
                    // otherwise assume this bit will be the same
                    looking_for = looking_for ^ (1 << j);
                }
            }

            // also check non-masked
            auto it = last_seen[0].find(looking_for);
            if (it != last_seen[0].end()) {
                int idx = it->second;
                best = min(best, i - idx + 1);
            }

            int mask = ~0;
            for (int j = 0; j < 31; j++) {
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
