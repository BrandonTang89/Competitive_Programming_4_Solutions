#include <queue>
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

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> arr(n);

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end(), greater<int>());

    while (q--) {
        int x;
        cin >> x;

        priority_queue<int> pq;
        while (!pq.empty()) pq.pop();
        for (int i = 0; i < min(n, 32); i++) {  // at most 32 needed
            pq.push(arr[i]);
        }

        int cur = x;
        int count = 0;
        while (cur > 0) {
            int ref = (pq.empty()) ? 0 : pq.top();
            if (!pq.empty()) {
                pq.pop();
            }

            if (cur <= ref) {
                break;
            } else if (ref == 0) {
                count += cur;
                break;
            } else if (__builtin_clz(ref) > __builtin_clz(cur)) {
                int target = (1 << (32 - __builtin_clz(cur) - 1));
                count += (target - ref);
                cur -= target;
            } else {
                assert(__builtin_clz(cur) == __builtin_clz(ref));
                int part = (1 << (31 - __builtin_clz(ref)));
                cur ^= part;
                pq.emplace(ref ^ part);
            }
        }

        cout << count << endl;
    }
}

int main() {
    int tc;
    cin >> tc;
    while (tc--) solve();

    return 0;
}