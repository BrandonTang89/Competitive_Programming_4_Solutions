/**Kattis - fairdivision
 * the problem constraints make the problem look tough, but it's actually not that bad. Consider the people that
 * can afford to contribute the least (he can pay <= x). If x < p/n then in order to minimise the amount of
 * excess that other should need to bare as well as the amount of discount that he has, he should just pay x.
 * If x >= p/n, then all other people can also afford to pay the same amount, so everyone left should just pay
 * p/n, this minimises the difference.
 * 
 * Notice that this strategy ensures that people who can afford more, pay more in the event of ties. Since we also
 * need the secondary condition that the person who comes first pays more, we should the people in increasing
 * order of ability to contribute but then in decreasing order of their index in the input. 
 * 
 * Time: O(n log n), Space: O(n)
 */
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
using namespace std;

#define fast_cin()                    \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                    \
    cout.tie(NULL);

int main() {
    fast_cin();
    int num_tc;
    cin >> num_tc;
    while (num_tc--) {
        int p, n;
        vector<pair<int, int>> v;  // amt, -index
        cin >> p >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            v.push_back({a, -i});
        }
        sort(v.begin(), v.end());

        vector<int> ans(n);
        for (int i = 0; i < n; i++) {
            // people left = n - i
            ans[-v[i].second] = min(p / (n-i), v[i].first);
            p -= ans[-v[i].second];
        }
        if (p == 0) {
            for (int i = 0; i < n; i++) cout << ans[i] << " ";
            cout << endl;
        } else {
            cout << "IMPOSSIBLE" << endl;
        }
    }

    return 0;
}