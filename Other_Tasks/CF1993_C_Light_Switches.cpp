#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<int> v;
int main() {
    int tc;
    cin >> tc;

    while (tc--) {
        cin >> n >> k;
        v.assign(2 * k, 0);

        int over = 0;
        int maxq = 0;
        int maxa = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            maxq = max(maxq, x / (2 * k));  // number of periods before last room activated
            maxa = max(maxa, x);            // number of rooms activated in last period
            x %= (2 * k);
            v[x]++;
            v[(x + k) % (2 * k)]--;
            if (x >= k) over++;
        }

        int cur = over;
        vector<int> possible(2 * k, 0);
        for (int i = 0; i < 2 * k; i++) {
            cur += v[i];
            if (cur == n) possible[i] = 1;
        }

        int minTime = -1;
        for (int i = maxa; i < maxa + k; i++) {
            if (possible[i % (2 * k)]) {
                minTime = i;
                break;
            }
        }

        cout << minTime << endl;
    }

    return 0;
}