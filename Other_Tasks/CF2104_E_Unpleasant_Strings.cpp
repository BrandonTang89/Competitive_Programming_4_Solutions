#include <algorithm>
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

int n, k;
int main() {
    cin >> n >> k;
    vector<int> a(n);
    for (auto &x : a) {
        char c;
        cin >> c;
        x = c - 'a';
    }

    vector<int> dp(n + 1, -1);
    vector<int> nexts(k, n);
    dp[n] = 0;
    for (int i = n - 1; i >= 0; i--) {
        int idx =
            distance(nexts.begin(), max_element(nexts.begin(), nexts.end()));
        dp[i] = dp[nexts[idx]] + 1;
        nexts[a[i]] = i;
    }

    vector<vector<int>> positions(k);
    for (int i = 0; i < n; i++) {
        positions[a[i]].push_back(i);
    }

    int q;
    cin >> q;
    while (q--) {
        string s;
        cin >> s;

        // We iterate through the string by jumping via positions
        int cur = -1;
        for (auto &c : s) {
            int char_idx = c - 'a';
            auto it = upper_bound(positions[char_idx].begin(),
                                  positions[char_idx].end(), cur);
            if (it == positions[char_idx].end()) {
                cur = n;
            } else {
                cur = *it;
            }
        }

        cout << (dp[cur]) << endl;
    }

    return 0;
}